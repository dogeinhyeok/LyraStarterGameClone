// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraHeroComponent.h"
#include "LyraPawnData.h"
#include "LyraPawnExtensionComponent.h"
#include "PlayerMappableInputConfig.h"
#include "InputMappingContext.h"
#include "../Input/LyraMappableConfigPair.h"
#include "../Input/LyraInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/GameFrameworkComponentManager.h"
#include "../LyraGameplayTags.h"
#include "../LogChannels.h"
#include "../Camera/LyraCameraComponent.h"
#include "../Player/LyraPlayerController.h"
#include "../Player/LyraPlayerState.h"
#include "Engine/LocalPlayer.h"

const FName ULyraHeroComponent::NAME_ActorFeatureName("Hero");

ULyraHeroComponent::ULyraHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void ULyraHeroComponent::OnRegister()
{
	Super::OnRegister();

	{
		if (!GetPawn<APawn>())
		{
			UE_LOG(LogLyra, Error,
				TEXT(
					"This component has been added to a Blueprint whose base class is not a Pawn!"));
			return;
		}
	}

	RegisterInitStateFeature();
}

void ULyraHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	BindOnActorInitStateChanged(
		ULyraPawnExtensionComponent::NAME_ActorFeatureName, FGameplayTag(), false);

	ensure(TryToChangeInitState(FLyraGameplayTags::Get().InitState_Spawned));

	CheckDefaultInitialization();
}

void ULyraHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void ULyraHeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();

	if (Params.FeatureName == ULyraPawnExtensionComponent::NAME_ActorFeatureName)
	{
		if (Params.FeatureState == InitTags.InitState_DataInitialized)
		{
			CheckDefaultInitialization();
		}
	}
}

bool ULyraHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager,
	FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();
	APawn* Pawn = GetPawn<APawn>();
	ALyraPlayerState* LyraPlayerState = GetPlayerState<ALyraPlayerState>();

	if (!CurrentState.IsValid() && DesiredState == InitTags.InitState_Spawned)
	{
		if (Pawn)
		{
			return true;
		}
	}

	if (CurrentState == InitTags.InitState_Spawned
		&& DesiredState == InitTags.InitState_DataAvailable)
	{
		if (!LyraPlayerState)
		{
			return false;
		}

		return true;
	}

	if (CurrentState == InitTags.InitState_DataAvailable
		&& DesiredState == InitTags.InitState_DataInitialized)
	{
		return LyraPlayerState
			&& Manager->HasFeatureReachedInitState(Pawn,
				ULyraPawnExtensionComponent::NAME_ActorFeatureName,
				InitTags.InitState_DataInitialized);
	}

	if (CurrentState == InitTags.InitState_DataInitialized
		&& DesiredState == InitTags.InitState_GameplayReady)
	{
		return true;
	}

	return false;
}

void ULyraHeroComponent::HandleChangeInitState(
	UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();

	if (CurrentState == InitTags.InitState_DataAvailable
		&& DesiredState == InitTags.InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		ALyraPlayerState* LyraPlayerState = GetPlayerState<ALyraPlayerState>();
		if (!ensure(Pawn && LyraPlayerState))
		{
			return;
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const ULyraPawnData* PawnData = nullptr;
		if (ULyraPawnExtensionComponent* PawnExtensionComponent =
				ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnData = PawnExtensionComponent->GetPawnData<ULyraPawnData>();
		}

		if (bIsLocallyControlled && PawnData)
		{
			if (ULyraCameraComponent* CameraComponent =
					ULyraCameraComponent::FindCameraComponent(Pawn))
			{
				CameraComponent->DetermineCameraModeDelegate.BindUObject(
					this, &ThisClass::DetermineCameraMode);
			}
		}

		if (ALyraPlayerController* LyraPlayerController = GetController<ALyraPlayerController>())
		{
			if (Pawn->InputComponent != nullptr)
			{
				InitializePlayerInput(Pawn->InputComponent);
			}
		}
	}
}

void ULyraHeroComponent::CheckDefaultInitialization()
{
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();
	static const TArray<FGameplayTag> StateChain = { InitTags.InitState_Spawned,
		InitTags.InitState_DataAvailable, InitTags.InitState_DataInitialized,
		InitTags.InitState_GameplayReady };
	ContinueInitStateChain(StateChain);
}

UE_DISABLE_OPTIMIZATION
TSubclassOf<ULyraCameraMode> ULyraHeroComponent::DetermineCameraMode() const
{
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return nullptr;
	}

	if (ULyraPawnExtensionComponent* PawnExtensionComponent =
			ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const ULyraPawnData* PawnData = PawnExtensionComponent->GetPawnData<ULyraPawnData>())
		{
			return PawnData->DefaultCameraMode;
		}
	}

	return nullptr;
}
UE_ENABLE_OPTIMIZATION

void ULyraHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	static bool bInputInitialized = false;
	if (bInputInitialized)
	{
		UE_LOG(LogLyra, Warning, TEXT("InitializePlayerInput already called, skipping..."));
		return;
	}
	bInputInitialized = true;
	UE_LOG(LogLyra, Warning, TEXT("InitializePlayerInput called for the first time"));

	const APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}

	const APlayerController* PlayerController = Pawn->GetController<APlayerController>();
	check(PlayerController);

	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();
	UE_LOG(LogLyra, Warning, TEXT("DefaultInputConfigs array size: %d"), DefaultInputConfigs.Num());

	if (const ULyraPawnExtensionComponent* PawnExtComp =
			ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const ULyraPawnData* PawnData = PawnExtComp->GetPawnData<ULyraPawnData>())
		{
			if (const ULyraInputConfig* InputConfig = PawnData->InputConfig)
			{
				UE_LOG(LogLyra, Warning, TEXT("InputConfig found: %s"), *InputConfig->GetName());
				const FLyraGameplayTags& GameplayTags = FLyraGameplayTags::Get();

				for (const FLyraMappableConfigPair& Pair : DefaultInputConfigs)
				{
					if (Pair.bShouldActivateAutomatically)
					{
						FModifyContextOptions Options = {};
						Options.bIgnoreAllPressedKeysUntilRelease = false;

						if (const auto ConfigObject = Pair.Config.LoadSynchronous())
						{
							UE_LOG(LogLyra, Warning, TEXT("Loading PlayerMappableInputConfig: %s"),
								*ConfigObject->GetName());
							for (const auto& MappingContextPair :
								ConfigObject->GetMappingContexts())
							{
								const UInputMappingContext* MappingContext = MappingContextPair.Key;
								const int32 Priority = MappingContextPair.Value;
								if (MappingContext)
								{
									UE_LOG(LogLyra, Warning,
										TEXT("Adding MappingContext: %s with Priority: %d"),
										*MappingContext->GetName(), Priority);
									Subsystem->AddMappingContext(MappingContext, Priority, Options);
								}
								else
								{
									UE_LOG(LogTemp, Error, TEXT("MappingContext is null!"));
								}
							}
						}
						else
						{
							UE_LOG(
								LogTemp, Error, TEXT("Failed to load PlayerMappableInputConfig"));
						}
					}
				}

				ULyraInputComponent* LyraInputComponent =
					CastChecked<ULyraInputComponent>(PlayerInputComponent);
				{
					UE_LOG(LogLyra, Warning, TEXT("Binding native actions..."));
					UE_LOG(LogLyra, Warning, TEXT("InputTag_Move: %s"),
						*GameplayTags.InputTag_Move.ToString());
					UE_LOG(LogLyra, Warning, TEXT("InputTag_Look_Mouse: %s"),
						*GameplayTags.InputTag_Look_Mouse.ToString());

					LyraInputComponent->BindNativeAction(InputConfig, GameplayTags.InputTag_Move,
						ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
					LyraInputComponent->BindNativeAction(InputConfig,
						GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this,
						&ThisClass::Input_LookMouse, false);
					UE_LOG(LogLyra, Warning, TEXT("Native actions bound successfully"));
				}
			}
		}
	}
}

void ULyraHeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		UE_LOG(
			LogLyra, Warning, TEXT("Input_Move called with value: X=%f, Y=%f"), Value.X, Value.Y);
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void ULyraHeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();
	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		double AimInversionValue = -Value.Y;
		Pawn->AddControllerPitchInput(AimInversionValue);
	}
}