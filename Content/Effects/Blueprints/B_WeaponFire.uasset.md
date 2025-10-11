**Trace Start: Fire
Custom Event** (CustomEvent)

```blueprint
* Event Fire
    * Sequence
        |-- then_0:
        |   * If (Enable Shell Eject)
        |       * true:
        |           * Is Valid (NS_ShellEject)
        |               |-- Is Valid:
        |               |   * If (NS_ShellEject.IsActive())
        |               |   |   |-- true:
        |               |   |   |   * Set Shell Eject Trigger:bool = ! (Shell Eject Trigger)
        |               |   |   |       * NS_ShellEject.SetVariableBool((InValue=Shell Eject Trigger, InVariableName=User.Trigger))
        |               |   |   |           * [Path ends]
        |               |   |   L-- false:
        |               |   |       * Niagara:NiagaraFunctionLibrary.SpawnSystemAttached((AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=ShellEject, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Shell Eject System(NS_WeaponFire_ShellEject)))
        |               |   |           * Set NS_ShellEject:Niagara:NiagaraComponent = Niagara:NiagaraFunctionLibrary.SpawnSystemAttached(AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=ShellEject, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Shell Eject System(NS_WeaponFire_ShellEject))
        |               |   |               * (Niagara:NiagaraFunctionLibrary.SpawnSystemAttached(AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=ShellEject, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Shell Eject System(NS_WeaponFire_ShellEject))).SetVariableStaticMesh((InValue=Shell Eject Mesh(SM_rifleshell), InVariableName=User.ShellEjectStaticMesh))
        |               |   |                   * Set Shell Eject Trigger:bool = false
        |               |   |                       * [Continue execution at: Set Shell Eject Trigger:bool = ! (Shell Eject Trigger) → Previously detailed]
        |               L-- Is Not Valid:
        |                   * [Continue execution at: Niagara:NiagaraFunctionLibrary.SpawnSystemAttached((AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=ShellEject, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Shell Eject System(NS_WeaponFire_ShellEject))) → Previously detailed]
        |-- then_1:
        |   * If (Enable Muzzle Flash)
        |       * true:
        |           * Is Valid (NS_MuzzleFlash)
        |               |-- Is Valid:
        |               |   * If (NS_MuzzleFlash.IsActive())
        |               |   |   |-- true:
        |               |   |   |   * Set Muzzle Flash Trigger:bool = ! (Muzzle Flash Trigger)
        |               |   |   |       * NS_MuzzleFlash.SetVariableBool((InValue=Muzzle Flash Trigger, InVariableName=User.Trigger))
        |               |   |   |           * NS_MuzzleFlash.SetVariableVec3((InValue=Normal(A=((Impact Positions(Vector))[0] - (BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=Muzzle, TransformSpace=ERelativeTransformSpace::RTS World))).Location), Tolerance=0), InVariableName=User.Direction))
        |               |   |   |               * [Path ends]
        |               |   |   L-- false:
        |               |   |       * Niagara:NiagaraFunctionLibrary.SpawnSystemAttached((AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=Muzzle, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Muzzle Flash System(NS_WeaponFire)))
        |               |   |           * Set NS_MuzzleFlash:Niagara:NiagaraComponent = Niagara:NiagaraFunctionLibrary.SpawnSystemAttached(AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=Muzzle, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Muzzle Flash System(NS_WeaponFire))
        |               |   |               * Set Muzzle Flash Trigger:bool = false
        |               |   |                   * [Continue execution at: Set Muzzle Flash Trigger:bool = ! (Muzzle Flash Trigger) → Previously detailed]
        |               L-- Is Not Valid:
        |                   * [Continue execution at: Niagara:NiagaraFunctionLibrary.SpawnSystemAttached((AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=Muzzle, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Muzzle Flash System(NS_WeaponFire))) → Previously detailed]
        |-- then_2:
        |   * If (Enable Tracer)
        |       * true:
        |           * Is Valid (NS_Tracer)
        |               |-- Is Valid:
        |               |   * If (NS_Tracer.IsActive())
        |               |   |   * false:
        |               |   |       * Niagara:NiagaraFunctionLibrary.SpawnSystemAttached((AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=Muzzle, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Tracer System(NS_WeaponFire_Tracer)))
        |               |   |           * Set NS_Tracer:Niagara:NiagaraComponent = Niagara:NiagaraFunctionLibrary.SpawnSystemAttached(AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=Muzzle, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Tracer System(NS_WeaponFire_Tracer))
        |               |   |               * [Path ends]
        |               L-- Is Not Valid:
        |                   * [Continue execution at: Niagara:NiagaraFunctionLibrary.SpawnSystemAttached((AttachPointName=None, AttachToComponent=DefaultSceneRoot, bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=(BreakTransform(InTransform=Skeletal Mesh Component.GetSocketTransform(InSocketName=Muzzle, TransformSpace=ERelativeTransformSpace::RTS Actor))).Location, LocationType=EAttachLocation::Keep Relative Offset, PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=MakeRotator(Y (Pitch)=0, X (Roll)=0, Z (Yaw)=90), SystemTemplate=Tracer System(NS_WeaponFire_Tracer))) → Previously detailed]
        L-- then_3:
            * RetriggerableDelay((Duration=3)) [(Latent)]
                * If (BooleanOR(IsValid(Object=NS_ShellEject), IsValid(Object=NS_MuzzleFlash), IsValid(Object=NS_Tracer)))
                    |-- true:
                    |   * [Continue execution at: RetriggerableDelay((Duration=3)) [(Latent)] → Previously detailed]
                    L-- false:
                        * K2_DestroyActor(())
                            * [Path ends]
```

---
