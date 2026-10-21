> **Serious Sam Classics Patch** implements new special packets that can be executed by the server (either via console or via a dedicated server plugin) in order to implement custom gamemodes or extend gameplay mechanics in some way.

# Event setup
- `pck_SetupEvent(INDEX)` - Start setting up an event under a specific identifier (see below).
- `pck_EventFieldIndex(INDEX, INDEX)` - Set event property under an index to some integer.
- `pck_EventFieldFloat(INDEX, FLOAT)` - Set event property under an index to some real number.
- `pck_EventFieldVector(INDEX, FLOAT, FLOAT, FLOAT)` - Set three event properties starting from an index to three vector numbers.

### Avaialble event identifiers
These event identifiers match the ones from Serious Engine SDK. You can look up event fields by searching for `event <event name without EVENTCODE_>` within `.es` files of the `Entities` project.

<details>
<summary>Event identifier list</summary>

```cpp
// Common events
EVENTCODE_EStop
EVENTCODE_EStart
EVENTCODE_EActivate
EVENTCODE_EDeactivate
EVENTCODE_EEnvironmentStart
EVENTCODE_EEnvironmentStop
EVENTCODE_EEnd
EVENTCODE_ETrigger
EVENTCODE_ETeleportMovingBrush
EVENTCODE_EReminder
EVENTCODE_EStartAttack
EVENTCODE_EStopAttack
EVENTCODE_EStopBlindness
EVENTCODE_EStopDeafness
EVENTCODE_EReceiveScore
EVENTCODE_EKilledEnemy
EVENTCODE_ESecretFound

// Specific events for the player
EVENTCODE_ESound
EVENTCODE_EScroll
EVENTCODE_ETextFX
EVENTCODE_EHudPicFX
EVENTCODE_ECredits
EVENTCODE_ECenterMessage
EVENTCODE_EComputerMessage
EVENTCODE_EVoiceMessage
EVENTCODE_EHitBySpaceShipBeam

// Events for item receival
EVENTCODE_EAmmoItem
EVENTCODE_EAmmoPackItem
EVENTCODE_EArmor
EVENTCODE_EHealth
EVENTCODE_EKey
EVENTCODE_EMessageItem
EVENTCODE_EPowerUp
EVENTCODE_EWeaponItem

// Specific entity events
EVENTCODE_ERestartAttack
EVENTCODE_EReconsiderBehavior
EVENTCODE_EForceWound
EVENTCODE_ESelectWeapon
EVENTCODE_EBoringWeapon
EVENTCODE_EFireWeapon
EVENTCODE_EReleaseWeapon
EVENTCODE_EReloadWeapon
EVENTCODE_EWeaponChanged

// Initialization events
EVENTCODE_EAirShockwave
EVENTCODE_EAirWave
EVENTCODE_ESpawnEffect
EVENTCODE_ESpawnSpray
EVENTCODE_EBulletInit
EVENTCODE_ELaunchCannonBall
EVENTCODE_ECyborgBike
EVENTCODE_ESpawnDebris
EVENTCODE_EDevilProjectile
EVENTCODE_ESpawnEffector
EVENTCODE_EFlame
EVENTCODE_ELaunchLarvaOffspring
EVENTCODE_EAnimatorInit
EVENTCODE_EViewInit
EVENTCODE_EWeaponsInit
EVENTCODE_EWeaponEffectInit
EVENTCODE_ELaunchProjectile
EVENTCODE_EReminderInit
EVENTCODE_ESeriousBomb
EVENTCODE_ESpawnerProjectile
EVENTCODE_ESpinnerInit
EVENTCODE_ETwister
EVENTCODE_EWatcherInit
EVENTCODE_EWater
```

</details>

# Entity packets
Packets for modifying in-game entities. All commands beginning with `pck_Entity` that take `INDEX` as the first argument always contain an entity ID in there.

### Entity instantiation
- `pck_EntityCreate(CTString)` - Create a new entity using a class link filename from the `Classes` folder (e.g. `"Boneman"` to create a Kleer skeleton).
- `pck_EntityDelete(INDEX, INDEX)` - Delete an entity from the world. Second argument determines whether or not to delete **all** entities of the same class type.
- `pck_EntityCopy(INDEX, INDEX)` - Copy an entity at the same place a number of times (from `0` to `31`).

### Entity logic
- `pck_EntityEvent(INDEX)` - Send [previously set up event](#Event-setup) to an entity.
- `pck_EntityItem(INDEX)` - Receive item by an entity via a [previously set up event](#Event-setup).
- `pck_EntityInit(INDEX)` - Initialize a freshly created entity (or reinitialize it).
- `pck_EntityInitEvent(INDEX)` - Initialize a freshly created entity (or reinitialize it) with a [previously set up event](#Event-setup).

### Entity placement
- `pck_EntitySetPos(INDEX, FLOAT, FLOAT, FLOAT, INDEX)` - Set new position to an entity (X, Y, Z). Last argument determines whether or not to set a relative position (add to the current one).
- `pck_EntitySetRot(INDEX, FLOAT, FLOAT, FLOAT, INDEX)` - Set new rotation to an entity (H, P, B). Last argument determines whether or not to set a relative rotation (add to the current one).
- `pck_EntityTeleport(INDEX, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, INDEX)` - Teleport an entity (X, Y, Z, H, P, B). Last argument determines whether or to teleport relative to the current position and orientation.

> [!NOTE]
> `pck_EntitySetPos()` sets relative position on the absolute grid, disregarding its orientation, while `pck_EntityTeleport()` takes orientation into consideration. For example, if the last created entity is rotated on its side, then `pck_EntityTeleport(0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1)` will move it horizontally by 1 meter, while `pck_EntitySetPos(0, 0.0, 1.0, 0.0, 1)` will move it slightly upwards.

### Entity properties
- `pck_EntityParent(INDEX, INDEX)` - Parent an entity to another entity (or clear the parent if it doesn't exist under some ID).
- `pck_EntityNumberProp(INDEX, CTString, INDEX, FLOAT)` - Set entity property under some name or ID to a number (integer, float, bool, color etc.). Relies on an index if the name is empty.
- `pck_EntityStringProp(INDEX, CTString, INDEX, CTString)` - Set entity property under some name or ID to a string. Relies on an index if the name is empty.
- `pck_EntityHealth(INDEX, FLOAT)` - Set entity health to a specific amount.

### Entity flags
- `pck_EntityFlags(INDEX, INDEX, INDEX)` - Set common flags as a mask to an entity. Last argument determines whether or not to remove the flags.
- `pck_EntityPhysicalFlags(INDEX, INDEX, INDEX)` - Set physical flags as a mask to an entity. Last argument determines whether or not to remove the flags.
- `pck_EntityCollisionFlags(INDEX, INDEX, INDEX)` - Set collision flags as a mask to an entity. Last argument determines whether or not to remove the flags.

### Available entity flags

<details>
<summary>Entity flag list</summary>

```cpp
// Entity flags
ENF_SELECTED              // 1 << 0
ENF_ZONING                // 1 << 1
ENF_DELETED               // 1 << 2
ENF_ALIVE                 // 1 << 3
ENF_INRENDERING           // 1 << 4
ENF_VALIDSHADINGINFO      // 1 << 5
ENF_SEETHROUGH            // 1 << 6
ENF_FOUNDINGRIDSEARCH     // 1 << 7
ENF_CLUSTERSHADOWS        // 1 << 8
ENF_BACKGROUND            // 1 << 9
ENF_ANCHORED              // 1 << 10
ENF_HASPARTICLES          // 1 << 11
ENF_INVISIBLE             // 1 << 12
ENF_DYNAMICSHADOWS        // 1 << 13
ENF_NOTIFYLEVELCHANGE     // 1 << 14
ENF_CROSSESLEVELS         // 1 << 15
ENF_PREDICTABLE           // 1 << 16
ENF_PREDICTOR             // 1 << 17
ENF_PREDICTED             // 1 << 18
ENF_WILLBEPREDICTED       // 1 << 19
ENF_TEMPPREDICTOR         // 1 << 20
ENF_HIDDEN                // 1 << 21
ENF_NOSHADINGINFO         // 1 << 22

// Entity physics flags
EPF_ORIENTEDBYGRAVITY     // 1 << 0
EPF_TRANSLATEDBYGRAVITY   // 1 << 1
EPF_PUSHABLE              // 1 << 2
EPF_STICKYFEET            // 1 << 3
EPF_RT_SYNCHRONIZED       // 1 << 4
EPF_ABSOLUTETRANSLATE     // 1 << 5
EPF_NOACCELERATION        // 1 << 6
EPF_HASLUNGS              // 1 << 7
EPF_HASGILLS              // 1 << 8
EPF_MOVABLE               // 1 << 9
EPF_NOIMPACT              // 1 << 10
EPF_NOIMPACTTHISTICK      // 1 << 11
EPF_CANFADESPINNING       // 1 << 12
EPF_ONSTEEPSLOPE          // 1 << 13
EPF_ORIENTINGTOGRAVITY    // 1 << 14
EPF_FLOATING              // 1 << 15
EPF_FORCEADDED            // 1 << 16

EPF_ONBLOCK_MASK          // 7 << 29
EPF_ONBLOCK_STOP          // 0 << 29
EPF_ONBLOCK_SLIDE         // 1 << 29
EPF_ONBLOCK_CLIMBORSLIDE  // 2 << 29
EPF_ONBLOCK_BOUNCE        // 3 << 29
EPF_ONBLOCK_PUSH          // 4 << 29
EPF_ONBLOCK_STOPEXACT     // 5 << 29
```

</details>

### Entity movement
- `pck_EntityMove(INDEX, FLOAT, FLOAT, FLOAT)` - Set new movement speed to a movable entity.
- `pck_EntityRotate(INDEX, FLOAT, FLOAT, FLOAT)` - Set new rotation speed to a movable entity.
- `pck_EntityImpulse(INDEX, FLOAT, FLOAT, FLOAT)` - Give impulse to a movable entity to launch it in some absolute direction.

### Entity damage
- `pck_SetupDamage(INDEX, INDEX, FLOAT)` - Begin setting up damage. First argument is an inflictor entity ID. Second argument is a damage type (from `DamageType` enum in SE1) and the last argument is damage amount.
- `pck_SetDirectDamage(INDEX, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT)` - Setup direct damage. First argument is a target entity ID and the rest are two vectors: hit point and damage direction (hitX, hitY, hitZ, dirX, dirY, dirZ).
- `pck_SetRangeDamage(FLOAT, FLOAT, FLOAT, FLOAT, FLOAT)` - Setup damage in a radius. First three arguments define center position, while the last two arguments are fall-off and hot spot ranges.
- `pck_SetBoxDamage(FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT)` - Setup damage in a box area. Arguments are separated into min and max position vectors (X1, Y1, Z1, X2, Y2, Z2).
- `pck_EntityDamage()` - Send previously set up damage.

# World change
- `pck_ChangeLevel(CTString)` - Immediately change to a different world file by creating and triggering a default `WorldLink` entity, if supported.
- `pck_ChangeWorld(CTString)` - Immediately change to a different world file using a more universal method but with possible undesired side-effects, e.g. making all players teleport to the center of the world instead of some starting `PlayerMarker`.

# Session properties
These commands are used for setting up and sending a modified chunk of session properties.

It starts with specifying offset in the destination session properties from where the changes will be made. For example, `pck_StartSesProps(12)` (12 bytes is three 32-bit integers in) in vanilla TSE ends up on `sp_bCooperative` session property.

Then, each new changed property advances the size of this session properties chunk. For example, if you start at `12` offset in vanilla TSE and enter `pck_SesPropIndex(0)`, it will register a change of `sp_bCooperative` to `FALSE` and stop at `sp_bSinglePlayer` property. Another call of `pck_SesPropIndex(0)` will also register its change to `FALSE` and advance onto `sp_bUseFrags`. If no more changes occur, `pck_SendSesProps()` will send a packet with 8 bytes of session properties that will be changed, i.e. the values of `sp_bCooperative` and `sp_bSinglePlayer`.

If no change occurs, an empty packet is sent, which won't change any bytes in real session properties.

`pck_SesPropString()` is a special kind of command that copies all bytes from the string directly into session properties. If some mod contains a session property that is an array of characters, for example `char sp_strName[32]`, the string with 32 characters will change every byte in the array **without the null-terminator** and stop at the byte afterwards, which is presumably the next property.

- `pck_StartSesProps(INDEX)` - Begin configuration of session properties at a specific byte offset that will be sent later.
- `pck_SesPropIndex(INDEX)` - Set index value at the current offset and advance session properties offset and size by 4 bytes.
- `pck_SesPropFloat(FLOAT)` - Set float value at the current offset and advance session properties offset and size by 4 bytes.
- `pck_SesPropString(CTString)` - Set string characters at the current offset and advance session properties offset and size by the amount of characters in the string.
- `pck_SeekSesProp(INDEX)` - Change current session properties offset and size relatively.
- `pck_SendSesProps()` - Send packet with previously preconfigured session properties.

# Gameplay extensions
These packets can be used to modify built-in gameplay extensions by their variable names that are defined by the `EGameplayExt` enum (and registered in the constructor of `GameplayExt`).

All variable names correspond to their command counterparts. For example, `gex_bEnable` becomes `"Enable"` and `gex_fMoveSpeed` becomes `"MoveSpeed"`.

- `pck_GameplayExtNumber(CTString, FLOAT)` - Change number value of some gameplay extension. For integers and state switches full numbers must be specified (e.g. `0.0` and `1.0`).
- `pck_GameplayExtString(CTString, CTString)` - Change string value of some gameplay extension.

# Sound playback
These packets can be used to play sounds for all clients on a server. These sounds don't exist in the world, so they cannot be setup to play at a specific location. Instead, they are played globally in the entire game, even in the menu.

> [!TIP]
> Paths to sound files have two special properties to them:
> - When set to `"/stop/"`, it stops playing any sound on the specified channel.
> - When left blank, it simply changes sound parameters without stopping or replaying the sound (e.g. for changing volume or pitch while the sound is already playing).

- `pck_PlayQuickSound(CTString, INDEX, FLOAT)` - Play a quick sound with minimal setup. Arguments are as follows:
  - Path to a sound file
  - Channel (`0` to `31`)
  - Volume (`0.0` to `4.0`)
- `pck_PlayGlobalSound(CTString, INDEX, INDEX, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT)` - Play a sound with full setup. Arguments are as follows:
  - Path to a sound file
  - Channel (from `0` to `31`)
  - Sound flags (see below)
  - Delay before playing the sound (in seconds)
  - Playback offset for skipping (in seconds)
  - Volume (from `0.0` to `4.0`)
  - Bass filter (from `1.0` to `500.0`); use the value of `20.0` for simulating 3D sounds underwater
  - Pitch (from `0.0` to `10.0`)

### Available sound flags

<details>
<summary>Sound flag list</summary>

```cpp
SOF_NONE          // 0
SOF_LOOP          // 1 << 0
SOF_3D            // 1 << 1
SOF_VOLUMETRIC    // 1 << 2
SOF_SURROUND      // 1 << 3
SOF_LOCAL         // 1 << 4
SOF_SMOOTHCHANGE  // 1 << 5
SOF_MUSIC         // 1 << 6
SOF_NONGAME       // 1 << 7
SOF_NOFILTER      // 1 << 8
```

</details>
