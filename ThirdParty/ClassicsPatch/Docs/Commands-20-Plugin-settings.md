> Descriptions for commands that are modifiable through the **OPTIONS** -> **CLASSICS PATCH** -> **Plugin settings** menu.  
> These commands are only available in external plugins that are bundled with **Serious Sam Classics Patch**.

# Accessibility
- `axs_bRedScreenOnDamage` - Toggle screen reddening upon taking damage (ON by default).
- `axs_bFixPlayerInfoSound` - Prevent notification sound from playing after killing every single enemy while playing multiplayer with prediction (ON by default).

# Advanced HUD
Commands for interface customization can be found on the [**HUD settings**](Commands-02-HUD-settings) page.

# Extended Input
- `inp_fAxisPressThreshold` - Set movement threshold (`0.0` - `1.0`) for game controller axes after which they are considered "pressed" (`0.2` by default).

# Extra commands
Relevant functionality that isn't usable or configurable via these options.

## Local Cheats
Keep in mind that these commands are **not** multiplayer synchronized and have been banned from use on remote servers as a result to prevent unnecessary desynchronizations with others.

> [!WARNING]
> If you use them as the server host, it will desynchronize and kick all of the clients from the server!

- `cht_WallWalking()` - Toggle wall walking for all local players.
- `cht_Noclip()` - Toggle noclip mode for all local players.
- `cht_Trigger()` - Trigger entities at the crosshair position for all local players.
- `cht_SetHealth(INDEX)` - Set some health for all local players.
  - Example: `cht_SetHealth(1000)` - Sets 1000 health for all players.
- `cht_CreateWeapon(INDEX)` - Create `WeaponItem` of a specific type at all local players.
  - Example: `cht_CreateWeapon(4)` - Creates Tommygun weapon.
- `cht_CreateAmmo(INDEX)` - Create `AmmoItem` of a specific type at all local players.
  - Example: `cht_CreateAmmo(2)` - Creates Bullets ammo.
- `cht_CreateHealth(INDEX)` - Create `HealthItem` of a specific type at all local players.
  - Example: `cht_CreateHealth(0)` - Creates Pill health.
- `cht_CreateArmor(INDEX)` - Create `ArmorItem` of a specific type at all local players.
  - Example: `cht_CreateArmor(3)` - Creates Strong armor.
- `cht_CreatePowerUp(INDEX)` - Create `PowerUpItem` of a specific type at all local players.
  - Example: `cht_CreatePowerUp(4)` - Creates Serious Bomb power-up.
- `cht_iAutoKill` - Kill alive enemies every game tick.
  - `0` - Disabled
  - `1` - Only enemies that can see you
  - `2` - All enemies (may be unstable)
- `cht_fAutoKillRange` - How close the enemies should be for the autokill cheat to affect them (`256.0` by default).

## Scripting Engine

The following commands return a string containing the optional return value from the script and also discard any previous script execution, if it has been suspended at any point:
- `scr_ExecuteString(CTString)` - Execute a new Squirrel script from a string value.
- `scr_ExecuteFile(CTString)` - Execute a new Squirrel script from a file within the game directory.

Other commands:
- `scr_IsSuspended()` - Check if the global Squirrel VM is currently suspended.
- `scr_ResumeVM()` - Resume a previously suspended Squirrel VM. If the script has previously finished its full execution, it does nothing.
- `scr_ResetVM()` - Reset the global Squirrel VM. Useful for when some execution is stuck in an infinite loop like `while (true) { suspend(); }`.

## Server Utilities
These commands are mostly usable while setting up a dedicated server via a config file, rather than the in-game console, so some of these commands won't appear in the console upon autocompletion (such as item type replacements).

If a command specifies a numerical range at the end, it means that the actual command should have a specific integer at the end of it, e.g. `sutl_iGiveWeapon1` is one of the commands in `sutl_iGiveWeapon<0 - 30>`, while `sutl_iGiveWeapon` and `sutl_iGiveWeapon31` are not.

### Server settings
- `sutl_iActionButtons` - Mask of action buttons that are allowed to be used by clients. Can be dynamically toggled during the game (`0xFFFFFFFF` - all buttons enabled by default).
> [!NOTE]
> Each bit in the mask corresponds to a button in `CPlayerAction::pa_ulButtons` mask and uses the same flags as constants from `Player.es` starting with `PLACT_` (e.g. `PLACT_WEAPON_NEXT`).
- `sutl_iThirdPersonViewButton` - Specifies which button is used to toggle third person view. When set to anything but `-1`, it also prevents player characters from toggling "Prefer 3rd person view" option (`-1` by default).
> [!NOTE]
> In vanilla game it's defined as the 8th bit in the button mask based on the fact of `PLACT_3RD_PERSON_VIEW` defined as `(1 << 7)`. So in order to disable third person view, the value of `7` should be used.

### World settings
- `sutl_fStartHealth` - Set new starting health on all `PlayerStart` markers (`100.0` by default).
- `sutl_fStartArmor` - Set new starting armor on all `PlayerStart` markers (`0.0` by default).
- `sutl_fEnemyMultiplier` - Multiply amount of enemies from enemy spawners (`1.0` by default).
- `sutl_bMaxAmmo` - Give maximum amount of ammo on start (OFF by default).
- `sutl_iGiveWeapon<0 - 30>` - Give out (`1`) or take away (`0`) a specific weapon on start (`-1` - ignored by default).

### Item settings
- `sutl_iWeaponType<0 - 30>` - Replace specific weapon item type with another type or remove it using `-1` (`-100` - ignored by default).
- `sutl_iAmmoType<0 - 30>` - Replace specific ammo item type with another type or remove it using `-1` (`-100` - ignored by default).
- `sutl_iHealthType<0 - 14>` - Replace specific health item type with another type or remove it using `-1` (`-100` - ignored by default).
- `sutl_iArmorType<0 - 14>` - Replace specific armor item type with another type or remove it using `-1` (`-100` - ignored by default).
- `sutl_iPowerUpType<0 - 14>` - Replace specific power up item type with another type or remove it using `-1` (`-100` - ignored by default).
- `sutl_iReplaceWeapons` - Replace all weapon items (that haven't been specifically replaced) with a certain type (`-1` - ignored by default).
- `sutl_iReplaceAmmo` - Replace all ammo items (that haven't been specifically replaced) with a certain type (`-1` - ignored by default).
- `sutl_iReplaceHealth` - Replace all health items (that haven't been specifically replaced) with a certain type (`-1` - ignored by default).
- `sutl_iReplaceArmor` - Replace all armor items (that haven't been specifically replaced) with a certain type (`-1` - ignored by default).

### Sandbox commands (not multiplayer synchronized!)
These commands can be scheduled before the game starts (before loading in the world for dedicated servers) or executed during the game by the server client.

- `sutl_DeleteEntity(EntityID)` - Delete an entity under a specific ID.
- `sutl_InitEntity(EntityID)` - Inititalize/reinitialize an entity under a specific ID.
- `sutl_SetEntityPosition(EntityID, X, Y, Z)` - Move entity under a specific ID to a new position.
- `sutl_SetEntityRotation(EntityID, H, P, B)` - Rotate entity under a specific ID on its position (Heading, Pitch, Banking).
- `sutl_SetEntityProperty(EntityID, PropertyName, ValueAsString)` - Change property of an entity under a specific ID by its name.
  - Integer, boolean or type. For example: `"0"`.
  - Float number or range. For example: `"1.0"`.
  - String or path to a file. For example: `"Sounds\\Default.wav"`.
  - Entity ID for an entity pointer. For example: `"100"`.
  - 3D vector or angle. For example: `"180.0, 45.0, 0.0"`.
- `sutl_ParentEntity(EntityID, ParentID)` - Parent an entity under a specific ID to another entity by ID.

### Command scheduling
- `sutl_ListScheduledCommands()` - Show all sandbox commands that have been scheduled for the next server start.
- `sutl_ClearScheduledCommands()` - Clear all sandbox commands that have been scheduled for the next server start.
