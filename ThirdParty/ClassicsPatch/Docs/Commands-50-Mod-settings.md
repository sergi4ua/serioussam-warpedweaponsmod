> Descriptions for commands that are modifiable through the **OPTIONS** -> **CLASSICS PATCH** -> **Custom mod settings** menu.

# Mod commands
These commands are usable in a special mod that comes with the patch. They can be used in the main game and are not exclusive to the mod itself (if custom mod isn't disabled).

# Visual options
- `gam_strClassicsPatchTheme` - Path to the game theme config that needs to be loaded.
  - `Scripts\\ClassicsPatch\\Themes\\01_TFE.ini` be default in **The First Encounter**
  - `Scripts\\ClassicsPatch\\Themes\\03_TSE.ini` be default in **The Second Encounter**
- `gam_bShowPointerInBorderless` - Toggle display of game's mouse pointer in borderless window mode (ON by default).
- `con_tmConsoleFade` - Animation speed for opening and closing the console (`0.5` by default).
- `con_iBigFont` - Toggle bigger font in console that also scales with resolution (`0` by default).
  - `0` - Never big font.
  - `1` - Only for last lines (for better readability of chat messages).
  - `2` - Always on, including opened console.
- `con_fBigFontScale` - Additional scaling of the bigger font in console (`1.0` by default).
- `cmp_bBigFont` - Toggle bigger font in NETRICSA that also scales with resolution higher than 720p (ON by default).
- `cmp_fBigFontScale` - Additional scaling of the bigger font in NETRICSA (`1.0` by default).

# Gameplay options
- `gam_bDisableLocalPrediction` - Toggle local player prediction to eliminate player jittering while playing on servers (using non-LAN connection setting) with latency below 50ms (`-1` by default).
  - `-1` - Automatic (disables local prediction when latency goes below 50ms)
  - `0` - Enable local prediction (vanilla logic)
  - `1` - Disable local prediction
- `plr_iSpawnInvulIndicator` - Toggle indication of spawn invulnerability for local players, as if Invulnerability powerup is being activated upon respawning (`2` by default).
  - `0` - Disabled
  - `1` - Only shows Invulnerability icon
  - `2` - Shows the icon and plays the powerup pickup sound
- `gfx_bAdjustModelHolderMipFactor` - Toggle mip factor adjustments of `ModelHolder2` entities to allow them to fade into the distance for optimization purposes (ON by default).

- `gam_iCustomBloodColor` - Custom client-side color for blood particles, stains and flesh (`0xFF0000FF` - red by default).
- `gam_iCustomBloodTheme` - Custom client-side theming for blood and gibs (`0` by default).
  - `0` - Automatically changes based on seasonal events; defaults to `1` otherwise
  - `1` - Simple coloring using `gam_iCustomBloodColor`
  - `2` - Forced color override using `gam_iCustomBloodColor`; uses brighter texture for the gibs
  - `3` - Hippie mode with flowers and fruit from the vanilla game
  - `4` - Party mode
  - `5` - Christmas mode

# Weapon viewmodel
- `wpn_bTSECannon` - Toggles alignment of the Cannon weapon viewmodel between **The First Encounter** and **The Second Encounter** (default state depends on the game).
- `wpn_bViewMirrored` - Weapon viewmodel mirroring, a.k.a. left-handed mode (OFF by default).
- `wpn_bPowerUpParticles` - Displays particles of active power-ups on the weapon viewmodel (OFF by default).

### Global adjustments
Viewmodel customization for all weapons at once.

- `wpn_fViewPosX` - Viewmodel position addition by the X axis (`0.0` by default).
- `wpn_fViewPosY` - Viewmodel position addition by the Y axis (`0.0` by default).
- `wpn_fViewPosZ` - Viewmodel position addition by the Z axis (`0.0` by default).
- `wpn_fViewPosH` - Viewmodel rotation addition by the H angle (`0.0` by default).
- `wpn_fViewPosP` - Viewmodel rotation addition by the P angle (`0.0` by default).
- `wpn_fViewPosB` - Viewmodel rotation addition by the B angle (`0.0` by default).
- `wpn_fViewFOV` - Viewmodel FOV multiplication (`1.0` by default).

### Adjustments per weapon
Viewmodel customization per specific weapon type. Each index corresponds to a value from the `WeaponType` enum in the `PlayerWeapons` class.

- `wpn_afAddPosX[20]` - Viewmodel position addition per specific weapon by the X axis (`0.0` by default).
- `wpn_afAddPosY[20]` - Viewmodel position addition per specific weapon by the Y axis (`0.0` by default).
- `wpn_afAddPosZ[20]` - Viewmodel position addition per specific weapon by the Z axis (`0.0` by default).
- `wpn_afAddPosH[20]` - Viewmodel rotation addition per specific weapon by the H angle (`0.0` by default).
- `wpn_afAddPosP[20]` - Viewmodel rotation addition per specific weapon by the P angle (`0.0` by default).
- `wpn_afAddPosB[20]` - Viewmodel rotation addition per specific weapon by the B angle (`0.0` by default).
- `wpn_afAddFOV[20]` - Viewmodel FOV addition per specific weapon (`0.0` by default).

# Multiple player views
- `gam_bObserverViewOverlay` - Display observer view windows over the main view instead of to the side during the game (ON by default).
- `gam_bObserverViewBackground` - Cover empty space under the observer view windows with a simple background, if `gam_bObserverViewOverlay` is disabled (ON by default).
- `gam_fObserverViewSize` - Set the percentage of how much of the main screen will be used for observer view windows (`0.25` by default).
- `gam_bVerticalSplitScreen` - Place split-screen views side by side for two players on a single screen, e.g. 2 players on a normal resolution or 3-4 players in dualhead mode (OFF by default).

# Extra commands
Relevant functionality that isn't usable or configurable via these options.

- `ResetWeaponPosition()` - Resets viewmodel commands for all weapons to default values.
- `ResetPerWeaponPositions()` - Resets viewmodel commands per specific weapon to default values.

Arrays for adding values to each controls axis for mimicking joysticks using keyboard keys:
- `ctl_afAddTranslation[3]` - Values to add to each translation axes per local player.
- `ctl_afAddRotation[3]` - Values to add to each rotation axes per local player.
- `ctl_afAddViewRotation[3]` - Values to add to each view rotation axes per local player.
