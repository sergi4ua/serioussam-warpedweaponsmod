/* Copyright (c) 2023-2025 Dreamy Cecil
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

#ifndef XGIZMO_INCL_LIBRARIESINTERFACE_H
#define XGIZMO_INCL_LIBRARIESINTERFACE_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

// Module symbol that contains its name and a pointer to it
struct SModuleSymbol {
  const char *strName;
  void *pSymbol;
};

// Array of module symbols
typedef CStaticStackArray<SModuleSymbol> CModuleSymbols;

namespace ILib {

// Load dynamic link library and throw exception upon any error
inline HMODULE LoadLib(const char *strFileName)
{
  HMODULE hiDLL = ::LoadLibraryA(strFileName);

  // Loaded properly
  if (hiDLL != NULL) return hiDLL;

  // Get the error code
  DWORD dwMessageId = GetLastError();

  // Format the Windows error message
  LPVOID lpMsgBuf;
  DWORD dwSuccess = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
    NULL, dwMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPSTR)&lpMsgBuf, 0, NULL);

  CTString strWinError;

  // If formatting succeeds
  if (dwSuccess != 0) {
    // Copy the result
    strWinError = (char *)lpMsgBuf;

    // Free the Windows message buffer
    LocalFree(lpMsgBuf);

  // Otherwise report failure
  } else {
    strWinError.PrintF(TRANS(
      "Cannot format error message!\nOriginal error code: %d\nFormatting error code: %d\n"),
      dwMessageId, GetLastError());
  }

  // Report error
  ThrowF_t(TRANS("Cannot load module '%s':\n%s"), strFileName, strWinError);
  return NULL;
};

// Gather symbols in a list that match a string with wildcards
inline void GetSymbolAddresses(CModuleSymbols &aSymbols, const HMODULE hModule, const char *strMatchName)
{
  typedef ULONG DWORD_PTR;

  // Address of the module
  DWORD_PTR dwModuleAddr = (DWORD_PTR)hModule;

  const PIMAGE_DOS_HEADER pDOSHeader = (const PIMAGE_DOS_HEADER)hModule;
  const PIMAGE_NT_HEADERS pNTHeader = (const PIMAGE_NT_HEADERS)((DWORD_PTR)pDOSHeader + pDOSHeader->e_lfanew);

  DWORD_PTR dwDataAddress = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

  // No data
  if (dwDataAddress == 0) return;

  // Get export directory
  const PIMAGE_EXPORT_DIRECTORY pDir = (PIMAGE_EXPORT_DIRECTORY)(dwModuleAddr + dwDataAddress);

  // Go through all names
  INDEX ctNames = pDir->NumberOfNames;

  for (INDEX i = 0; i < ctNames; i++) {
    // Check if the name of the current symbol matches
    LPCSTR strSymbolName = (LPCSTR)(((ULONG *)(pDir->AddressOfNames + dwModuleAddr))[i] + dwModuleAddr);

    if (CTString(strSymbolName).Matches(strMatchName)) {
      // Find symbol by its relative virtual address
      UWORD uwOrdinal = ((UWORD *)(pDir->AddressOfNameOrdinals + dwModuleAddr))[i];
      ULONG ulSymbolRVA = ((ULONG *)(dwModuleAddr + pDir->AddressOfFunctions))[uwOrdinal];

      // Add a new symbol
      SModuleSymbol &symbol = aSymbols.Push();
      symbol.strName = strSymbolName;
      symbol.pSymbol = (void *)(dwModuleAddr + ulSymbolRVA);
    }
  }
};

}; // namespace

#endif
