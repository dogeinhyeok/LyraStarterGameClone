**Trace Start: Event OnEquipped**

```blueprint
* Event K2_OnEquipped
    * Call Function: [DetermineCosmeticTags](#b-weaponinstance-base-determinecosmetictags)()
        * Macro: [Activate Anim Layer and Play Paired Anim](#b-weaponinstance-base-activate-anim-layer-and-play-paired-anim)(bEquipped=true, WeaponMontangeToPlay=WeaponMontagePlay)
            * [Path ends after call to macro "Activate Anim Layer and Play Paired Anim"]
```

---

**Trace Start: Event OnUnequipped**

```blueprint
* Event K2_OnUnequipped
    * [Path ends]
```

---

## Referenced Graphs

### Functions

#### `B_WeaponInstance_Base.DetermineCosmeticTags` <a id="b-weaponinstance-base-determinecosmetictags"></a>

**Inputs:**
_(No distinct data inputs)_

**Execution Flow:**

```blueprint
* Event DetermineCosmeticTags
    * Set CosmeticComponent:LyraStarterGameClone:LyraPawnComponent_CharacterParts = GetPawn().GetComponentByClass(ComponentClass=LyraStarterGameClone:LyraPawnComponent_CharacterParts)
        * Is Valid (GetPawn().GetComponentByClass(ComponentClass=LyraStarterGameClone:LyraPawnComponent_CharacterParts))
            L-- Is Valid:
                * CosmeticComponent.GetCombinedTags((RequiredPrefix=GameplayTag(...)))
                    * Set CosmeticAnimStyle:GameplayTagContainer = CosmeticComponent.GetCombinedTags(RequiredPrefix=GameplayTag(...))
                        * [Path ends]
```

**Outputs:**
_(No distinct data outputs)_

---

### Executable Macros

#### `B_WeaponInstance_Base.Activate Anim Layer and Play Paired Anim` <a id="b-weaponinstance-base-activate-anim-layer-and-play-paired-anim"></a>

**Inputs:**

- `bEquipped` (bool)
- `WeaponMontangeToPlay` (AnimMontage)

**Execution Flow:**

```blueprint
* Tunnel (Inputs)
    * PickBestAnimLayer((bEquipped=ValueFrom(Tunnel.bEquipped), CosmeticTags=CosmeticAnimStyle(GameplayTagContainer)))
        * If (IsValidClass(Class=PickBestAnimLayer(bEquipped=ValueFrom(Tunnel.bEquipped), CosmeticTags=CosmeticAnimStyle(GameplayTagContainer))))
            * true:
                * Mesh.LinkAnimClassLayers((InClass=PickBestAnimLayer(bEquipped=ValueFrom(Tunnel.bEquipped), CosmeticTags=CosmeticAnimStyle(GameplayTagContainer))))
                    * Play Montage ValueFrom(Tunnel.WeaponMontangeToPlay)(bShouldStopAllMontages=true, PlayRate=1, StartingPosition=0, StartingSection=None) [(Latent)]
                        * Tunnel (Outputs)
```

**Outputs:**
_(No distinct data outputs)_

---
