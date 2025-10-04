**Trace Start: Received Notify** (FunctionEntry)

```blueprint
* Event Received Notify
    * Sequence
        |-- then_0:
        |   * Cast (Animation) To AnimMontage
        |       * Set MontageLeader:AnimMontage = Cast<AnimMontage>(Animation)
        |           * [Path ends]
        L-- then_1:
            * If ((ResultOf((ValueFrom(Received Notify.MeshComp).GetOwner().GetComponentByClass(ComponentClass=LyraStarterGameClone:LyraEquipmentManagerComponent).GetEquipmentInstancesOfType(InstanceType=LyraStarterGameClone:LyraWeaponInstance)).Array_Length()) > 0))
                * true:
                    * If ((ResultOf(((ValueFrom(Received Notify.MeshComp).GetOwner().GetComponentByClass(ComponentClass=LyraStarterGameClone:LyraEquipmentManagerComponent).GetEquipmentInstancesOfType(InstanceType=LyraStarterGameClone:LyraWeaponInstance))[0].GetSpawnedActors()).Array_Length()) > 0))
                        * true:
                            * Is Valid (((ValueFrom(Received Notify.MeshComp).GetOwner().GetComponentByClass(ComponentClass=LyraStarterGameClone:LyraEquipmentManagerComponent).GetEquipmentInstancesOfType(InstanceType=LyraStarterGameClone:LyraWeaponInstance))[0].GetSpawnedActors())[0])
                                L-- Is Valid:
                                    * Is Valid (((ValueFrom(Received Notify.MeshComp).GetOwner().GetComponentByClass(ComponentClass=LyraStarterGameClone:LyraEquipmentManagerComponent).GetEquipmentInstancesOfType(InstanceType=LyraStarterGameClone:LyraWeaponInstance))[0].GetSpawnedActors())[0].GetComponentByClass(ComponentClass=SkeletalMeshComponent))
                                        L-- Is Valid:
                                            * Set FollowerAnimInstance:AnimInstance = ((ValueFrom(Received Notify.MeshComp).GetOwner().GetComponentByClass(ComponentClass=LyraStarterGameClone:LyraEquipmentManagerComponent).GetEquipmentInstancesOfType(InstanceType=LyraStarterGameClone:LyraWeaponInstance))[0].GetSpawnedActors())[0].GetComponentByClass(ComponentClass=SkeletalMeshComponent).GetAnimInstance()
                                                * (((ValueFrom(Received Notify.MeshComp).GetOwner().GetComponentByClass(ComponentClass=LyraStarterGameClone:LyraEquipmentManagerComponent).GetEquipmentInstancesOfType(InstanceType=LyraStarterGameClone:LyraWeaponInstance))[0].GetSpawnedActors())[0].GetComponentByClass(ComponentClass=SkeletalMeshComponent).GetAnimInstance()).Montage_Play((bStopAllMontages=true, InPlayRate=RateScale, InTimeToStartMontageAt=0, MontageToPlay=MontageToPlay(AM_MM_Pistol_Fire), ReturnValueType=EMontagePlayReturnType::Montage Length))
                                                    * FollowerAnimInstance.MontageSync_Follow((MontageFollower=None, MontageLeader=MontageLeader, OtherAnimInstance=MeshComp.GetAnimInstance()))
                                                        * Return()
```

---
