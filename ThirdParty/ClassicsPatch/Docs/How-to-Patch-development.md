If you wish to fork the patch repository and make your own changes to the code, you might find tips on this page useful.

If you wish to create plugins for existing versions of the patch, take a look at [this page](How-to-Plugin-modules) first.

# Project structure
**Classics Patch** consists out of many projects that depend on each other to work. But all of them are always based on `Core`.

`Core` is responsible for:
- Making the patch function at all.
- Handling standalone plugins, which may optionally rely on `Core` back.
- Implementing calls to specific plugin events.
- Dynamically hooking onto engine functions (and in some cases vanilla `Entities` functions) and replacing them with own ones for injecting new code.

# Developer comments
Across the entire codebase there are comments that are prefixed with `[Cecil]`. These comments are added before any piece of code that's inserted in either original code written by Croteam (including borrowed chunks from 1.10) or to add a note of sorts that wasn't previously there to clearly distinguish different pieces of code.

There are multiple kinds of these developer comments:
- `// [Cecil]` - Normal developer comment that marks a new feature in-between vanilla code.
- `// [Cecil] FIXME` - Something that needs to be looked at in case it behaves in some unintended way. Similar to `[Cecil] TODO` but is usually added before a clear issue that hasn't been resolved yet.
- `// [Cecil] TEMP` - Marks a feature that wasn't intended to be added from the beginning and that can either be removed in a future release or be permanently left in its place as is.
- `// [Cecil] TODO` - A note to self about something that still needs to be worked on.
- `// [Cecil] NOTE` - An important note with an explanation about why some piece of code exists or how it works in case it looks weird and confusing at first.

All of the comments follow a consistent formatting in order to find them easily. It is recommended to specifically look up `[Cecil] NOTE` across the project you're working on in order to find important notes for better understanding of what's written there and how it works.

### Feature comments
Some comments can be suffixed with a keyword to signify that some piece of code belongs to a large group of other pieces under a specific global feature.

For example, comments that start with `[Cecil] Rev` mean that the features they describe belong to content support from **Serious Sam: Revolution** or its engine as a whole (if built under its configuration).

# Feature toggles
**Classics Patch** can be built with some of its features disabled either for compatibility, for testing or for any other reason.

For that, take a look at `Core/Config.h` header file. It contains macro switches for specific features that can be toggled by switching `1` under each of them to `0` and vice versa.

Some features can also be disabled automatically depending on the selected build configuration by modifying the macro value to rely on another macro switch, like it's already done with **Revolution** and its `_APCT_NREV` switch that's added to some of the features that aren't compatible with **Revolution** engine.

# Compatibility features
**Classics Patch** code includes useful structures that can be utilized for optimized compatibility with different engine versions and user-made modifications that interact with the patch in any way.

## Value per game & engine
> Include: `Core/GameSpecific.h`

In order to easily return specific values without wrapping pieces of code under game and engine checks, two macros are available to you:
- `CHOOSE_FOR_ENGINE(_107, _150, _110)` - Returns one of the values depending on the engine version that the patch is being built for.
  - Values from `_107` are returned for engine versions 1.07 and below.
  - Revolution configuration uses values from `_110`, since it's technically based on Serious Engine 1.10.
- `CHOOSE_FOR_GAME(_TFE105, _TSE105, _TSE107)` - Returns one of the values depending on the relevant game that the patch is being built for.
  - Values from `_TSE107` are returned for any game on engine versions starting from 1.07, e.g. Revolution, 1.10 forks, beta 1.50 patch etc.

## Shell symbol pointers
> Include: `Extras/XGizmo/Objects/SymbolPtr.h`

> Purpose: *Structure for storing shell symbols by name that look them up only once and store a pointer to them.*

If you need to work with shell symbols and frequently look them up via `_pShell` pointer, you might want to utilize this structure for optimization purposes.

Normally, when you need to look up a shell symbol, you'd call one of the following functions:
- `CShell::GetSymbol()`
- `CShell::GetFLOAT()`
- `CShell::GetINDEX()`
- `CShell::GetString()`
- `CShell::GetValue()`

However, they are *extremely* slow because they take a string for a symbol name as the first argument and then iterate through all existing symbols in the shell, comparing the name of each one using `strcmp()` function internally.

To avoid this, you can declare this structure as `static` to make it look up any symbol once upon construction and then reuse it as many times as you need:
```cpp
void MethodThatIsCalledEveryFrame(void)
{
  // Set random scaling of the heads-up interface for the funsies
  static CSymbolPtr symptr("hud_fScaling");

  if (symptr.Exists()) {
    symptr.GetFloat() = 0.5f + FLOAT(rand() % 11) / 20.0f; // 0.5 - 1.0
  }
};
```

You can also define symbol pointers in global scope to be initialized upon module initialization (e.g. in plugins) but it's suggested to avoid this as much as possible because if Serious Engine hasn't been initialized yet, the game will crash.

To work around this, you can define an empty symbol pointer and make it look up the symbol at a later point:
```cpp
static CSymbolPtr symptr;

void MethodThatIsCalledEveryFrame(void)
{
  // Use another static switch to look up the symbol only once instead of each call, in case it's not found
  static bool bFindSymbol = true;

  if (bFindSymbol) {
    bFindSymbol = false;
    symptr.Find("hud_fScaling");
  }

  // Set random scaling of the heads-up interface for the funsies
  if (symptr.Exists()) {
    symptr.GetFloat() = 0.5f + FLOAT(rand() % 11) / 20.0f; // 0.5 - 1.0
  }
};
```

## Vanilla events
> Include: `Extras/XGizmo/Vanilla/EntityEvents.h`

> Purpose: *Local reimplementations of common entity events from vanilla `Entities` library for direct interactions with their logic.*

All vanilla event classes are prefixed with `VNL_` to avoid confusion with real event classes.

For example, this is how event sending looks like in vanilla `Entities` library:
```cpp
ETrigger ee;
ee.penCaused = penPlayer;

penTrigger->SendEvent(ee);
CPrintF("Event code: %d\n", EVENTCODE_ETrigger);
```

And outside the `Entities` library (e.g. in a plugin) with this header included it looks like this:
```cpp
VNL_ETrigger ee;
ee.penCaused = penPlayer;

penTrigger->SendEvent(ee);
CPrintF("Event code: %d\n", EVENTCODE_VNL_ETrigger);
```

### Entity IDs instead of pointers
Before including vanilla events, you may optionally want to define a `VANILLA_EVENTS_ENTITY_ID` macro. This macro will replace every `CEntityPointer` field in event classes with `ULONG` for storing entity IDs instead of direct pointers to them.

This is useful for when you need to save event data between game sessions. But it's also a requirement if you intend to send entity events as synchronized extension packets.

For example, if you have a server plugin that needs to start a specific `Trigger` entity for all clients, you can write it as such:
```cpp
#define VANILLA_EVENTS_ENTITY_ID
#include <Core/Compatibility/VanillaEvents.h>

void TriggerATrigger(CEntity *penTrigger, CEntity *penOptionalPlayer)
{
  // Get player entity ID
  ULONG ulPlayerID = (penOptionalPlayer != NULL ? penOptionalPlayer->en_ulID : 0);

  // Create an event with the player that triggered it
  VNL_ETrigger ee;
  ee.penCaused = ulPlayerID;

  // Send event to this Trigger for all clients
  CExtEntityEvent pckEvent;
  pckEvent.ulEntity = penTrigger->en_ulID;
  pckEvent.SetEvent(ee, sizeof(ee));
  pckEvent.SendPacket();
};
```

But if for some reason you **need** to keep direct pointers to entities in events and **also** send packets with entity IDs in the same source file, you can write it as such (not recommended):
```cpp
//#define VANILLA_EVENTS_ENTITY_ID
#include <Core/Compatibility/VanillaEvents.h>

void TriggerATrigger(CEntity *penTrigger, CEntity *penOptionalPlayer)
{
  // Get player entity ID
  ULONG ulPlayerID = (penOptionalPlayer != NULL ? penOptionalPlayer->en_ulID : 0);

  // Create an event with the player that triggered it
  VNL_ETrigger ee;
  (ULONG &)ee.penCaused = ulPlayerID; // Insert an ID instead of a pointer

  // Send event to this Trigger for all clients
  CExtEntityEvent pckEvent;
  pckEvent.ulEntity = penTrigger->en_ulID;
  pckEvent.SetEvent(ee, sizeof(ee));
  pckEvent.SendPacket();

  // Clear entity pointer to avoid crashes
  (ULONG &)ee.penCaused = NULL;
};
```

## Entity property pointers
> Include: `Core/Objects/PropertyPtr.h`

> Purpose: *Structure for storing pointers to entity properties that can be looked up using a variety of methods only once, including names of C++ class fields.*

This structure's concept is very similar to **shell symbol pointers**. It's useful for when you need to figure out where a specific entity property lies within a specific entity class but you don't want to iterate through all properties every single time, since the field offset remains the same in all instances of the class.

The usage of this structure is very specific. You start by defining a static variable that will hook onto a specific entity class. Constructor method can take a pointer to either one:
- `CEntity`
- `CEntityClass`
- `CDLLEntityClass`

Every type results in `CPropertyPtr` to store a pointer to the appropriate `CDLLEntityClass` in itself for instant access to the property table of a specific class.

Then, after the structure gains access to the class, you can begin looking up its properties using various methods:
- `CPropertyPtr::ByIdOrOffset(ULONG ulType, ULONG ulID, SLONG slOffset)` - Look up property of a specific type and try to match it by ID or field offset, if ID is wrong (e.g. has been renumbered in a mod).
- `CPropertyPtr::ByName(ULONG ulType, const char *strProperty)` - Look up property of a specific type and try to match it by its display name (the one that is visible in the property list in Serious Editor).
- `CPropertyPtr::ByNameOrId(ULONG ulType, const char *strProperty, ULONG ulID)` - Same as by name but with a property ID as the fallback in case the name string mismatches or is empty.
- `CPropertyPtr::ByVariable(const char *strClass, const char *strVariable)` - Look up property by its C++ name in a C++ class. This is a custom method that relies on a pregenerated table of properties for each vanilla class. Extremely useful when writing logic that's compatible with vanilla entities first and foremost.

All of these methods have a `BOOL` return type that determines whether or not a needed variable has been found and can be referred to. All lookup methods search for the property only once and only in the class type specified in the constructor, so it's advised to use this structure **after** manually checking for appropriate entity class types.

After the property is found, it's only a matter of accessing it using an `ENTITYPROPERTY()` macro from the engine itself using property offset from the `CPropertyPtr::Offset()` method.

### Code examples

<details>
<summary>Example using ID or offset</summary>

This example tries to retrieve and print out a mask of weapons that a player entity under `pen` entity pointer currently has.

```cpp
// Check for vanilla player entity (401 - CPlayer class ID)
if (IsDerivedFromID(pen, 401)) // If "EntitiesV/Player.h" is included, CPlayer_ClassID can be used instead
{
  static CPropertyPtr pptrWeapons(pen);
  static const INDEX iWeaponsID = (401 << 8) + 16; // 16 - property ID of m_penWeapons within Player.es

  // Try to retrieve CPlayer::m_penWeapons by vanilla ID (disregard offset)
  if (pptrWeapons.ByIdOrOffset(CEntityProperty::EPT_ENTITYPTR, iWeaponsID, 0)) {
    // Retrieve a pointer to CPlayerWeapons
    CEntity *penWeapons = ENTITYPROPERTY(pen, pptrWeapons.Offset(), CEntityPointer);

    static CPropertyPtr pptrMask(penWeapons);
    static const INDEX iMaskID = (402 << 8) + 11;

    // Now try to retrieve CPlayerWeapons::m_iAvailableWeapons
    if (pptrMask.ByIdOrOffset(CEntityProperty::EPT_INDEX, iMaskID, 0)) {
      // Print its value out
      ULONG ulWeaponMask = ENTITYPROPERTY(penWeapons, pptrMask.Offset(), ULONG);

      CPrintF("%s's weapons: 0x%X\n", pen->GetName(), ulWeaponMask);
    }
  }
}
```

</details>

<details>
<summary>Example using display name</summary>

This example searches for all beheaded enemies in the current world and replaces them with kamikazes.

```cpp
// Gather all beheads and iterate through them
CEntities cenHeadmen;
IWorld::FindClassesByID(IWorld::GetWorld()->wo_cenEntities, cenHeadmen, 303); // CHeadman_ClassID

FOREACHINDYNAMICCONTAINER(cenHeadmen, CEntity, iten) {
  CEntity *pen = iten;

  // Find property offset within CHeadman class by display name
  static CPropertyPtr pptrType(pen);

  if (pptrType.ByName(CEntityProperty::EPT_ENUM, "Type"))
  {
    // Set kamikaze type and reinitialize the enemy
    ENTITYPROPERTY(pen, pptrType.Offset(), INDEX) = 3; // HDT_KAMIKAZE
    iten->Reinitialize();
  }
}
```

</details>

<details>
<summary>Example using display name or ID</summary>

This example checks whether or not an enemy entity under `pen` entity pointer is a template or not.

```cpp
// Assume that 'pen' is always an entity derived from CEnemyBase
BOOL IsEnemyTemplate(CEntity *pen)
{
  // If property can't be found, assume that it's a living enemy by default
  BOOL bTemplate = FALSE;

  // Look up CEnemyBase::m_bTemplate property
  static CPropertyPtr pptr(pen);

  if (pptr.ByNameOrId(CEntityProperty::EPT_BOOL, "Template", (0x136 << 8) + 86))
  {
    bTemplate = ENTITYPROPERTY(pen, pptr.Offset(), BOOL);
  }

  return bTemplate;
};
```

</details>

<details>
<summary>Example using C++ field name</summary>

This example checks whether a world file exists that's been specified in a `CWorldLink` under `pen` entity pointer.

```cpp
// Assume that 'pen' is always an entity of CWorldLink class
BOOL WorldLinkWorldExists(CEntity *pen)
{
  // Retrieve CWorldLink::m_strWorld
  static CPropertyPtr pptrWorld(pen);

  if (pptrWorld.ByVariable("CWorldLink", "m_strWorld"))
  {
    // Check if the file in the string field exists
    CTFileNameNoDep &strWorld = ENTITYPROPERTY(pen, pptrWorld.Offset(), CTFileNameNoDep);

    return FileExists(strWorld);
  }

  // No world field found
  return FALSE;
};
```

</details>

## Structure pointer converter
> Include: `Extras/XGizmo/Objects/StructPtr.h`

> Purpose: *Structure for converting between raw addresses to objects in memory and pointers of a specific type.*

This structure has very niche use cases when the compiler is being very fussy.

Its constructor accepts any pointer type and raw address integers (as `size_t`) and stores them as a raw address inside.

Then, the pointer is casted into any typed pointer by using the parentheses operator:
```cpp
static int _iMyNumber = 0;

// Create a pointer to the integer
StructPtr pIntPtr(&_iMyNumber);

// Retrieve a pointer to the integer using a dummy pointer value
int *pDummy;
int *pInt = pIntPtr(pDummy);

// Another way by specifying a direct value
int *pInt2 = pIntPtr((int *)NULL);
```

In Classics Patch it is mostly used for casting void pointers and raw addresses into typed function pointers for the function patcher:
```cpp
// Try to find a 'CEnemyBase::HandleEvent()' symbol within the loaded Entities library
StructPtr pHandleEventPtr(ClassicsCore_GetEntitiesSymbol("?HandleEvent@CEnemyBase@@UAEHABVCEntityEvent@@@Z"));

// If it has been found
if (pHandleEventPtr.iAddress != NULL)
{
  // Retrieve a typed pointer to the function
  typedef BOOL (CEntity::*CHandleEventFunc)(const CEntityEvent &);
  CHandleEventFunc pHandleEvent = pHandleEventPtr(CHandleEventFunc());

  // And patch it with our own event handling method
  CreatePatch(pHandleEvent, &CEnemyPatch::P_HandleEvent, "CEnemyBase::HandleEvent(...)");
}
```
