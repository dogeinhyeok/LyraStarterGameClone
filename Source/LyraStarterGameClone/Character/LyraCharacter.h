// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LyraCharacter.generated.h"

class ULyraPawnExtensionComponent;

/**
 * Lyra 캐릭터: 기본 ACharacter를 상속받는 메인 플레이어 캐릭터 클래스
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ALyraCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALyraCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<ULyraPawnExtensionComponent> PawnExtensionComponent;
};
