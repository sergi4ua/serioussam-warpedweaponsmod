> **Serious Sam Classics Patch** can be built for forks of [open-source version of Serious Engine 1](https://github.com/Croteam-official/Serious-Engine). This page with guide you through the process of preparing your engine fork for the patch.

Even though it's possible to build the patch for 1.10, it's not officially supported due to the ambiguity of engine forks. It is still mainly recommended that you go through the code of Classics Patch and extract chunks of code that you need in your code (with respect to the license, of course).

This guide is primarily targeted towards users who aren't extremely familiar with **Serious Engine 1** code but already had some experience with building it. If you're an experienced programmer and know quite a bit about the engine code, this guide will simply help point you in the right direction. It's not necessary to implement the exact code changes as described here. You are free to modify both **Serious Engine 1** and **Classics Patch** code however you like.

# Prelude
Some features of **Classics Patch** have been automatically disabled when building under the **TSE 1.10** configuration in order to minimize the external engine modifications and to avoid random errors with patching certain functions.

You can see which features are being automatically disabled in `Core/Config.h` file. If you wish to restore them, it's recommended to port all of the related code directly into the engine instead of trying to reenable them and fixing all the issues in Classics Patch itself.

> [!IMPORTANT]
> Be aware that if you have too many modifications in your fork, particularly in `Ecc`, `Engine`, `EntitiesMP` and `GameMP` projects, it might not be compatible with the patch and would require extra work in both the engine fork and Classics Patch to make them compatible with each other.

# Engine fork modifications
Here's a list of changes you have to make for your fork first.

## Symbol exporting
You need to export certain classes and functions from the engine in order to let the patch hook and utilize them.

The steps described here aren't the most clean or convenient ways of doing things, but they are the easiest.

**Global symbols to export:**
- Classes: `CActionBuffer`, `CPlayerTarget`, `CSessionSocketParams`, `CSessionSocket`
- Filesystem functionality: `InitStreams()`, `_azeFiles`, `_azhHandles`, `_afnmArchives`, `zip_csLock`

**Class methods to export:**
- `CNetworkMessage &CPlayerCharacter::operator<<(CNetworkMessage &, CPlayerCharacter &)`
- `CNetworkMessage &CPlayerCharacter::operator>>(CNetworkMessage &, CPlayerCharacter &)`
- `CNetworkMessage &CPlayerAction::operator<<(CNetworkMessage &, const CPlayerAction &)`
- `CNetworkMessage &CPlayerAction::operator>>(CNetworkMessage &, CPlayerAction &)`
- `CTStream &CPlayerAction::operator<<(CTStream &, const CPlayerAction &)`
- `CTStream &CPlayerAction::operator>>(CTStream &, CPlayerAction &)`
- `CNetworkMessage &CSessionSocketParams::operator<<(CNetworkMessage &, CSessionSocketParams &)`
- `CNetworkMessage &CSessionSocketParams::operator>>(CNetworkMessage &, CSessionSocketParams &)`

---
Insert `ENGINE_API` in the beginning of this line.
> [`Engine/Base/Stream.cpp` @ line 117](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Base/Stream.cpp#L117)
```cpp
void InitStreams(void)
```

---
Replace `static` keyword with `ENGINE_API` in the beginning of these lines.
> [`Engine/Base/Unzip.cpp` @ line 201-206](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Base/Unzip.cpp#L201-L206)
```cpp
// all files in all active zip archives
static CStaticStackArray<CZipEntry>  _azeFiles;
// handles for currently open files
static CStaticStackArray<CZipHandle> _azhHandles;
// filenames of all archives
static CStaticStackArray<CTFileName> _afnmArchives;
```

---
Insert `ENGINE_API` in the beginning of this line.
> [`Engine/Engine.cpp` @ line 61](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Engine.cpp#L61)
```cpp
CTCriticalSection zip_csLock;
```

---
Insert `ENGINE_API` in the beginning of these lines inside the `CPlayerCharacter` class definition.
> [`Engine/Entities/PlayerCharacter.h` @ line 73-74](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Entities/PlayerCharacter.h#L73-L74)
```cpp
friend CNetworkMessage &operator<<(CNetworkMessage &nm, CPlayerCharacter &pc);
friend CNetworkMessage &operator>>(CNetworkMessage &nm, CPlayerCharacter &pc);
```

---
Insert `ENGINE_API` in the beginning of these lines inside the `CPlayerAction` class definition.

> [`Engine/Network/NetworkMessage.h` @ line 299-306](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Network/NetworkMessage.h#L299-L306)
```cpp
friend CNetworkMessage &operator<<(CNetworkMessage &nm, const CPlayerAction &pa);
friend CNetworkMessage &operator>>(CNetworkMessage &nm, CPlayerAction &pa);
friend CTStream &operator<<(CTStream &strm, const CPlayerAction &pa);
friend CTStream &operator>>(CTStream &strm, CPlayerAction &pa);
```

---
Export `CActionBuffer` class by adding `ENGINE_API` to its declaration.
> [`Engine/Network/ActionBuffer.h` @ line 25](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Network/ActionBuffer.h#L25)
```cpp
// buffer of player actions, sorted by time of arrival
class ENGINE_API CActionBuffer {
```

---
Export `CPlayerTarget` class by adding `ENGINE_API` to its declaration.
> [`Engine/Network/PlayerTarget.h` @ line 29](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Network/PlayerTarget.h#L29)
```cpp
/*
 * Player target, located in each session state; receiving actions
 */
class ENGINE_API CPlayerTarget {
```

---
Export `CSessionSocketParams` and `CSessionSocket` classes by adding `ENGINE_API` to their declarations.
> [`Engine/Network/SessionSocket.h` @ line 24](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Network/SessionSocket.h#L24)
```cpp
// parameters for a client
class ENGINE_API CSessionSocketParams {
```
> [`Engine/Network/SessionSocket.h` @ line 45](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Network/SessionSocket.h#L45)
```cpp
// connection data for each session connected to a server
class ENGINE_API CSessionSocket {
```

---
Insert `ENGINE_API` in the beginning of these lines inside the `CSessionSocketParams` class declaration.
> [`Engine/Network/SessionSocket.h` @ line 40-41](https://github.com/Croteam-official/Serious-Engine/blob/b408e88a16fd01aa1cfd0e0a999c86c2c1437c9e/Sources/Engine/Network/SessionSocket.h#L40-L41)
```cpp
friend CNetworkMessage &operator<<(CNetworkMessage &nm, CSessionSocketParams &ssp);
friend CNetworkMessage &operator>>(CNetworkMessage &nm, CSessionSocketParams &ssp);
```

# Classics Patch modifications
Now this is a list of changes you have to make for Classics Patch.

> [!TIP]
> Find a way to replace text in multiple source files at once, for example by using [Notepad++](https://notepad-plus-plus.org/downloads/) and its **Ctrl+Shift+F** shortcut.

## Engine headers and libraries
After you're done building your engine fork, you need to copy its engine headers and libraries to replace the default ones for the 1.10 version.

### Headers
1. Go to your engine fork and copy all `.h` and `.inl` files from the `Engine` folder (or copy the folder in its entirety and delete the other files later).
2. Navigate to `Includes/Engine110/Engine` within the Classics Patch source code and place all the copied files there, replacing existing ones.

### Libraries
1. Find where your `Engine` binaries have been built (e.g. `Sources/Engine/Release` in the original source code) and copy `Engine.lib` file from it.
2. Navigate to `Includes/Engine110` and replace `Engine.lib` in there with your library.

## Entities sources (optional)
If you've made significant changes to the `EntitiesMP` project in your engine fork, you need to copy its sources as well and do some slight adjustments to the code.

### Copying the files
1. Go to your engine fork and navigate to the `EntitiesMP` folder.
2. Copy all `.es` files from the folder itself and `.h` files from `Common` and `StdH` subfolders.
3. Navigate to `Includes/Engine110/EntitiesV` within the Classics Patch source code and place all the copied files there, replacing existing ones.

### Modifying the code
1. Navigate to `Includes/Engine110/EntitiesV` folder and replace all paths to sources from `EntitiesMP` folder to `EntitiesV` in all `.es` and `.h` files, either by using regex or by performing simple replacements:
  - `#include "EntitiesMP` -> `#include "EntitiesV`
  - `uses "EntitiesMP` -> `uses "EntitiesV`
2. Go back to `Includes/Engine110` folder and run the `CompileAllEntities.bat` script to generate new `.h` files from the entity sources.
3. Open `Includes/Engine110/EntitiesV/StdH/StdH.h` and modify it:
  - Remove inclusion of `Engine/Engine.h` header.
  - Replace `DECL_DLL` definition with `_declspec(dllimport)`.
  - (If applicable) Replace all include paths from `GameMP` files to `GameV` files.

## Game headers (optional)
If you've made significant changes to the `GameMP` project in your engine fork, you need to copy its headers as well.

1. Go to your engine fork and copy all `.h` files from the `GameMP` folder (or copy the folder in its entirety and delete the other files later).
2. Navigate to `Includes/Engine110/GameV` within the Classics Patch source code and place all the copied files there, replacing existing ones.
3. (If applicable) Replace all include paths from `GameMP` files to `GameV` files in all headers.
