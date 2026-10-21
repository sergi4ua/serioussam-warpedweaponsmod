WARPED WEAPONS for Serious Sam Classic: The Second Encounter 1.07
=================================================================

Adds two weapons from the "Seriously Warped Deathmatch" mod to the normal game:

  PLASMA THROWER (key 9)
    Fire            - plasma bolt (1 cell)
    Alternate Fire  - spread of 8 bolts (5 cells)
    Ammo            - Plasma Packs (+50), max 300

  MINE LAYER (key -)
    Fire            - throw an energy mine (up to 3 at a time); a mine arms itself
                      after landing and explodes when a player touches it or it is shot
    Alternate Fire  - detonate all of your mines
    Ammo            - Mine Packs (+3), max 15

Both weapons work in single player, cooperative and deathmatch, and come with the
Serious Pack, back packs and the cheat cht_bGiveAll. Level designers can place them with
the Serious Editor: WeaponItem types "Plasma Thrower" / "Mine Layer" and AmmoItem types
"Plasma Packs" / "Mine Packs".


INSTALL
-------
1. Close the game.
2. Extract this archive anywhere (for example into the game folder).
3. Run Install.bat. It finds the game in your Steam libraries (or asks for the folder),
   backs up the original Bin\EntitiesMP.dll to WarpedWeaponsBackup\ and copies the new
   files in (see SERIOUS SAM CLASSICS PATCH below if you use it).

The installer also adds three buttons to all your controls (Options > Players and
Controls > Change controls > Customize buttons):

    Alternate Fire   G or Right Ctrl
    Plasma Thrower   9
    Mine Layer       -

Alternate Fire also sits on the sniper scope key (Use / NETRICSA / Sniper Zoom, right
mouse button by default): with the Plasma Thrower or Mine Layer in hand that key fires
the alternate fire, and with the Sniper pressing Alternate Fire works the scope. With these
two weapons the scope key still uses switches but doesn't open NETRICSA.

If one of these keys is already used for something else in your controls, that button is
added without a key - just assign one in the menu.

To install into a specific folder: Install.bat -GameDir "D:\Games\Serious Sam Classic The Second Encounter"


UNINSTALL
---------
Close the game and run Uninstall.bat. It restores the original Bin\EntitiesMP.dll (and
the Classics Patch files, if they were replaced), deletes the mod's files and removes the
three buttons from your controls (your other bindings stay as they are). Steam's "Verify
integrity of game files" also restores the original game DLL.


MULTIPLAYER
-----------
The server and every player must have the same version of Warped Weapons installed, and
all of them must use the same client: either everyone plays the normal game
(SeriousSam.exe) or everyone plays the Classics Patch (SeriousSam_Custom.exe).
While it is installed you cannot play on normal (unmodded) servers - uninstall it first.
A dedicated server (Bin\DedicatedServer.exe, or DedicatedServer_Custom.exe for the
Classics Patch) uses the new weapons automatically once the mod is installed into its
game folder.


SERIOUS SAM CLASSICS PATCH
--------------------------
The weapons also work in the Classics Patch (Bin\SeriousSam_Custom.exe,
DedicatedServer_Custom.exe), including its Advanced HUD. This needs Classics Patch
version 1.9.4 exactly: the installer recognizes it and then also replaces (and backs up)
Bin\Entities_Custom.dll and Bin\Plugins\AdvancedHUD.dll. With any other version of the
Classics Patch, only the normal game (Bin\SeriousSam.exe) gets the weapons.

If you update the Classics Patch later, its new files replace these two and the weapons
disappear from it until there is a Warped Weapons build for that version; the normal game
keeps them. Uninstall.bat leaves the newer Classics Patch files alone.


REQUIREMENTS
------------
Serious Sam Classic: The Second Encounter, patch 1.07 (Steam/GOG version).


CREDITS
-------
Weapons, models, textures and sounds: the Seriously Warped Deathmatch team.
Port to The Second Encounter: built on Croteam's Serious Engine 1 source code (GPL v2)
and Dreamy Cecil's SE1 Mod SDK. Source code: WarpedWeapons-<version>-src.zip.
