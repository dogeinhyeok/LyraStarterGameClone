**Trace Start: Fire
Custom Event** (CustomEvent)

```blueprint
* Event Fire
    * Sequence
        |-- then_0:
        |   * Call Function: [Sort Impact Arrays](#b-weaponimpacts-sort-impact-arrays)()
        |       * For Loop ((Number of Surface Types - 1) to 0) [Index:int]
        |           L-- LoopBody:
        |               * Set Index 0:int = Loop Index
        |                   * Set Current Impact Surface:PhysicsCore:EPhysicalSurface = (Impact Surface Types)[(Start Offset)[Loop Index]]
        |                       * Set Current Impact Surface Index:int = Conv_ByteToInt(InByte=(Impact Surface Types)[(Start Offset)[Loop Index]])
        |                           * Set Current System Template:Niagara:NiagaraSystem = Select(Index=Current Impact Surface, Options={SurfaceType_Default=Default, SurfaceType1=Character, SurfaceType2=Concrete(NS_ImpactConcrete), SurfaceType3=Glass(NS_ImpactGlass)})
        |                               * Is Valid (Current System Template)
        |                                   L-- Is Valid:
        |                                       * Set Current Impact Position:Vector = (Impact Positions(Vector))[0]
        |                                           * If (ResultOf((Impact Systems).Array_IsValidIndex(IndexToTest=Current Impact Surface Index)))
        |                                               |-- true:
        |                                               |   * If (ResultOf((System Positions(Vector)).Array_IsValidIndex(IndexToTest=Current Impact Surface Index)))
        |                                               |       |-- true:
        |                                               |       |   * Set Impact Outside Threshold Distrace:bool = (Vector_DistanceSquared(V1=Current Impact Position(Vector), V2=(System Positions(Vector))[Current Impact Surface Index]) > (Distance Threshold * Distance Threshold))
        |                                               |       |       * Array Op Array_Set(bSizeToFit=true, Index=Current Impact Surface Index, Item=Current Impact Position(Vector)) on (System Positions(Vector))
        |                                               |       |           * Is Valid ((Impact Systems)[Current Impact Surface Index])
        |                                               |       |               |-- Is Valid:
        |                                               |       |               |   * If (Impact Outside Threshold Distrace)
        |                                               |       |               |   |   |-- true:
        |                                               |       |               |   |   |   * Niagara:NiagaraFunctionLibrary.SpawnSystemAtLocation((bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=Current Impact Position(Vector), PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=Rotator(P=0, Y=0, R=0), Scale=Vector(X=1, Y=1, Z=1), SystemTemplate=Current System Template))
        |                                               |       |               |   |   |       * Set Impact System:Niagara:NiagaraComponent = Niagara:NiagaraFunctionLibrary.SpawnSystemAtLocation(bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=Current Impact Position(Vector), PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=Rotator(P=0, Y=0, R=0), Scale=Vector(X=1, Y=1, Z=1), SystemTemplate=Current System Template)
        |                                               |       |               |   |   |           * Array Op Array_Set(bSizeToFit=true, Index=Current Impact Surface Index, Item=Impact System) on (Impact Systems)
        |                                               |       |               |   |   |               * Impact System.K2_SetWorldLocation((bSweep=false, bTeleport=false, NewLocation=Current Impact Position(Vector)))
        |                                               |       |               |   |   |                   * Niagara:NiagaraDataInterfaceArrayFunctionLibrary.SetNiagaraArrayPosition((ArrayData=Impact Positions(Vector), NiagaraSystem=Impact System, Parameter Name=User.ImpactPositions))
        |                                               |       |               |   |   |                       * Niagara:NiagaraDataInterfaceArrayFunctionLibrary.SetNiagaraArrayPosition((ArrayData=Impact Positions(Vector), NiagaraSystem=Impact System, Parameter Name=User.ImpactNormals))
        |                                               |       |               |   |   |                           * Impact System.SetVariableInt((InValue=(Number of Impacts)[Index 0], InVariableName=User.NumberOfHits))
        |                                               |       |               |   |   |                               * Impact System.SetVariablePosition((InValue=Muzzle Position(Vector), InVariableName=User.MuzzlePosition))
        |                                               |       |               |   |   |                                   * Impact System.SetVariableInt((InValue=(Number of Impacts)[Index 0], InVariableName=User.StartOffset))
        |                                               |       |               |   |   |                                       * Impact System.SetTickBehavior((NewTickBehavior=Niagara:ENiagaraTickBehavior::Use Component Tick Group))
        |                                               |       |               |   |   |                                           * Impact System.Activate((bReset=false))
        |                                               |       |               |   |   |                                               * [Path ends]
        |                                               |       |               |   |   L-- false:
        |                                               |       |               |   |       * Set Impact System:Niagara:NiagaraComponent = (Impact Systems)[Current Impact Surface Index]
        |                                               |       |               |   |           * [Continue execution at: Impact System.K2_SetWorldLocation((bSweep=false, bTeleport=false, NewLocation=Current Impact Position(Vector))) → Previously detailed]
        |                                               |       |               L-- Is Not Valid:
        |                                               |       |                   * [Continue execution at: Niagara:NiagaraFunctionLibrary.SpawnSystemAtLocation((bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=Current Impact Position(Vector), PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=Rotator(P=0, Y=0, R=0), Scale=Vector(X=1, Y=1, Z=1), SystemTemplate=Current System Template)) → Previously detailed]
        |                                               |       L-- false:
        |                                               |           * Set Impact Outside Threshold Distrace:bool = false
        |                                               |               * [Continue execution at: Array Op Array_Set(bSizeToFit=true, Index=Current Impact Surface Index, Item=Current Impact Position(Vector)) on (System Positions(Vector)) → Previously detailed]
        |                                               L-- false:
        |                                                   * [Continue execution at: Niagara:NiagaraFunctionLibrary.SpawnSystemAtLocation((bAutoActivate=true, bAutoDestroy=true, bPreCullCheck=true, Location=Current Impact Position(Vector), PoolingMethod=Niagara:ENCPoolMethod::[Default Value], Rotation=Rotator(P=0, Y=0, R=0), Scale=Vector(X=1, Y=1, Z=1), SystemTemplate=Current System Template)) → Previously detailed]
        L-- then_1:
            * RetriggerableDelay((Duration=3)) [(Latent)]
                * Set Has Valid Systems:bool = false
                    * For Each in (Impact Systems) [Element:Niagara:NiagaraComponent, Index:int]
                        |-- LoopBody:
                        |   * If (IsValid(Object=Loop Element))
                        |   |   * true:
                        |   |       * Set Has Valid Systems:bool = IsValid(Object=Loop Element)
                        |   |           * [Path ends]
                        L-- Completed:
                            * If (Has Valid Systems)
                                |-- true:
                                |   * [Continue execution at: RetriggerableDelay((Duration=3)) [(Latent)] → Previously detailed]
                                L-- false:
                                    * K2_DestroyActor(())
                                        * [Path ends]
```

---

## Referenced Graphs

### Functions

#### `B_WeaponImpacts.Sort Impact Arrays` <a id="b-weaponimpacts-sort-impact-arrays"></a>

**Inputs:**
_(No distinct data inputs)_

**Execution Flow:**

```blueprint
* Event Sort Impact Arrays
    * Sequence
        |-- then_0:
        |   * Array Op Array_Clear() on (Sorted Impact Positions(Vector))
        |       * Array Op Array_Clear() on (Sorted Impact Normals(Vector))
        |           * Array Op Array_Clear() on (Sorted Impact Surface Types)
        |               * Array Op Array_Clear() on (Start Offset)
        |                   * Array Op Array_Clear() on (Number of Impacts)
        |                       * Set Previous Value:int = -1
        |                           * Set Number of Surface Types:int = 0
        |                               * Set Unsorted Impact Surface Types:Array<PhysicsCore:EPhysicalSurface> = Impact Surface Types
        |                                   * [Path ends]
        L-- then_1:
            * For Loop (0 to (ResultOf((Unsorted Impact Surface Types).Array_Length()) - 1)) [Index:int]
                |-- LoopBody:
                |   * Set Index:int = Loop Index
                |   |   * Set Index of Min Value:int = (MinOfByteArray(ByteArray=Unsorted Impact Surface Types)).IndexOfMinValue
                |   |       * If (((MinOfByteArray(ByteArray=Unsorted Impact Surface Types)).MinValue != Previous Value))
                |   |           |-- true:
                |   |           |   * Set Number of Surface Types:int = (Number of Surface Types + 1)
                |   |           |       * Array Op Array_Add(NewItem=Index) on (Start Offset)
                |   |           |           * Array Op Array_Resize(Size=Number of Surface Types) on (Number of Impacts)
                |   |           |               * Set Previous Value:int = Conv_ByteToInt(InByte=(MinOfByteArray(ByteArray=Unsorted Impact Surface Types)).MinValue)
                |   |           |                   * Array Op Array_Add(NewItem=Cast<PhysicsCore:EPhysicalSurface>((MinOfByteArray(ByteArray=Unsorted Impact Surface Types)).MinValue)) on (Sorted Impact Surface Types)
                |   |           |                       * Array Op Array_Set(bSizeToFit=true, Index=Index, Item=(Impact Positions(Vector))[Index of Min Value]) on (Sorted Impact Positions(Vector))
                |   |           |                           * Array Op Array_Set(bSizeToFit=true, Index=Index, Item=(Impact Normals(Vector))[Index of Min Value]) on (Sorted Impact Normals(Vector))
                |   |           |                               * Array Op Array_Set(bSizeToFit=true, Index=Index, Item=Cast<PhysicsCore:EPhysicalSurface>(Surface Magic Number)) on (Unsorted Impact Surface Types)
                |   |           |                                   * Array Op Array_Set(bSizeToFit=true, Index=(Number of Surface Types - 1), Item=((Number of Impacts)[(Number of Surface Types - 1)] + 1)) on (Number of Impacts)
                |   |           |                                       * [Path ends]
                |   |           L-- false:
                |   |               * [Continue execution at: Set Previous Value:int = Conv_ByteToInt(InByte=(MinOfByteArray(ByteArray=Unsorted Impact Surface Types)).MinValue) → Previously detailed]
                L-- Completed:
                    * Set Impact Surface Types:Array<PhysicsCore:EPhysicalSurface> = Sorted Impact Surface Types
                        * Set Impact Positions:Array<Vector> = Sorted Impact Positions(Vector)
                            * Set Impact Normals:Array<Vector> = Sorted Impact Normals(Vector)
                                * [Path ends]
```

**Outputs:**
_(No distinct data outputs)_

---
