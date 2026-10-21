/* Copyright (c) 2024-2025 Dreamy Cecil
This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License as published by
the Free Software Foundation


This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#ifndef XGIZMO_INCL_DIRECTORIESINTERFACE_H
#define XGIZMO_INCL_DIRECTORIESINTERFACE_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include "Files.h"

#include "../Base/STLIncludesBegin.h"
#include <string>
#include <direct.h>
#include "../Base/STLIncludesEnd.h"

// Interface of useful methods for interactions with the game directory
namespace IDir {

// Get filename of some library (e.g. "Game" + _strModExt for standard Game library)
inline CTString GetLibFile(const CTString &strLibName, const CTString &strLibExt = ".dll") {
  // Construct library filename
  #ifdef NDEBUG
    return strLibName + strLibExt; // Release library
  #else
    return "Debug\\" + strLibName + "D" + strLibExt; // Debug library
  #endif
};

// Get cut-off position before the Bin directory
inline size_t BinDirPos(std::string strExePath) {
  // Cut off module filename to end up with Bin (e.g. "C:\SeriousSam\Bin" and "\SeriousSam_Custom.exe")
  strExePath.erase(strExePath.rfind("\\"));

  // Skip Debug directory
  #ifndef NDEBUG
    // If found Debug directory at the very end, cut it off
    const size_t iDebug = strExePath.rfind("\\Debug");

    if (iDebug == strExePath.length() - 6) {
      strExePath.erase(iDebug);
    }
  #endif

  // Go up to the root directory (e.g. "C:\SeriousSam\" and "Bin\SeriousSam_Custom.exe")
  return strExePath.rfind("\\") + 1;
};

// Get relative path to the game executable
inline const CTFileName &AppExe(void) {
  // Use existing path
  if (_fnmApplicationExe != "") return _fnmApplicationExe;

  static CTFileName fnmLocalPath;

  // Get executable path locally
  if (fnmLocalPath == "") {
    char strPathBuffer[1024];
    GetModuleFileNameA(NULL, strPathBuffer, sizeof(strPathBuffer));

    std::string strExePath = strPathBuffer;
    size_t iBinDir = BinDirPos(strExePath);

    // Copy relative path to the executable with the Bin directory
    fnmLocalPath = CTString(strExePath.substr(iBinDir).c_str());
  }

  return fnmLocalPath;
};

// Get relative path to the Bin directory (folder name)
__forceinline CTFileName AppBin(void) {
  return AppExe().FileDir();
};

// Get relative path to the mod's Bin directory (folder name)
__forceinline CTFileName AppModBin(void) {
  // Use game's or mod's Bin directory
  return (_fnmMod == "") ? AppBin() : CTString("Bin\\");
};

// Get absolute path to the game directory
inline const CTFileName &AppPath(void) {
  // Use existing path
  if (_fnmApplicationPath != "") return _fnmApplicationPath;

  static CTFileName fnmLocalPath;

  // Get application path locally
  if (fnmLocalPath == "") {
    char strPathBuffer[1024];
    GetModuleFileNameA(NULL, strPathBuffer, sizeof(strPathBuffer));

    std::string strExePath = strPathBuffer;
    size_t iBinDir = BinDirPos(strExePath);

    // Copy absolute path to the game directory
    fnmLocalPath = CTString(strExePath.erase(iBinDir).c_str());
  }

  return fnmLocalPath;
};

// Get full path relative to the game to some library (mod Bin -> custom Bin -> vanilla Bin)
inline CTString FullLibPath(const CTString &strLibName, const CTString &strLibExt = ".dll") {
  // Check for existence of libraries in order:
  // 1. Mods/<mod>/Bin/<lib> (e.g. Mods/MyMod/Bin/Debug/Game_CustomD.dll)
  // 2. <custom bin>/<lib>   (e.g. Bin_Custom/Debug/Game_CustomD.dll)
  // 3. Bin/<lib>            (e.g. Bin/Debug/Game_CustomD.dll)
  const CTFileName &fnmRootDir = AppPath();
  const CTString strLibFile = GetLibFile(strLibName, strLibExt);

  // Check if library file exists on disk and return it
  CTString strCheckFile;
  #define CHECK_AND_RETURN_PATH { if (IFiles::IsReadable((fnmRootDir + strCheckFile).str_String)) return strCheckFile; }

  // Check in the mod's Bin folder
  if (_fnmMod != "") {
    strCheckFile = _fnmMod + "Bin\\" + strLibFile;
    CHECK_AND_RETURN_PATH;
  }

  // Check in the custom Bin folder (from where it's currently running)
  strCheckFile = AppBin() + strLibFile;
  CHECK_AND_RETURN_PATH;

  // Check in the vanilla Bin folder as the last resort
  strCheckFile = "Bin\\" + strLibFile;
  CHECK_AND_RETURN_PATH;

  // No library found
  ASSERT(FALSE);
  return "";
};

// Create a series of directories within the game folder
inline void CreateDir(const CTString &strPath) {
  std::string strDirs = strPath;
  const char *strAppPath = AppPath().str_String;

  size_t iDir = 0;

  // Get next directory from the last position
  while ((iDir = strDirs.find_first_of('\\', iDir)) != std::string::npos) {
    // Include the slash
    iDir++;

    // Create current subdirectory
    _mkdir((strAppPath + strDirs.substr(0, iDir)).c_str());
  }
};

// Convert relative paths into absolute paths and add missing backslashes
inline void SetFullDirectory(CTString &strDir) {
  INDEX iLength = strDir.Length();

  // Add missing backslash at the end
  if (iLength > 0 && strDir[iLength - 1] != '\\') {
    strDir += CTString("\\");
  }

  // If shorter than 2 characters or doesn't start with a drive directory
  if (iLength < 2 || strDir[1] != ':') {
    // Convert relative path into absolute path
    strDir = AppPath() + strDir;
  }

  // Convert the rest of the path into absolute path
  IFiles::SetAbsolutePath(strDir);
};

}; // namespace

#endif
