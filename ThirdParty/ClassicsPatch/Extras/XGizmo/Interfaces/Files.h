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

#ifndef XGIZMO_INCL_FILESINTERFACE_H
#define XGIZMO_INCL_FILESINTERFACE_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include "Data.h"

#include <io.h>

// Listed files/paths
typedef CDynamicStackArray<CTFileName> CFileList;

// Interface of useful methods for file manipulation
namespace IFiles {

// Find any slash in a string and return its position
inline INDEX GetSlashPos(const char *strString) {
  const char *pStart = strString;

  for (; *strString != '\0'; strString++) {
    if (*strString == '\\' || *strString == '/') {
      return (strString - pStart);
    }
  }

  return -1;
};

// CTFileName method from 1.10
inline void SetAbsolutePath(CTString &strPath) {
  // Collect path parts
  CTString strRemaining(strPath);
  CStringStack astrParts;

  INDEX iSlashPos = GetSlashPos(strRemaining);

  // Invalid path
  if (iSlashPos <= 0) return;

  for (;;) {
    CTString &strBeforeSlash = astrParts.Push();
    CTString strAfterSlash;

    strRemaining.Split(iSlashPos, strBeforeSlash, strAfterSlash);
    strAfterSlash.TrimLeft(strAfterSlash.Length() - 1);
    strRemaining = strAfterSlash;

    iSlashPos = GetSlashPos(strRemaining);

    if (iSlashPos <= 0) {
      astrParts.Push() = strRemaining;
      break;
    }
  }

  INDEX iPart;

  // Remove certain path parts
  for (iPart = 0; iPart < astrParts.Count(); ++iPart) {
    if (astrParts[iPart] != "..") {
      continue;
    }

    // Invalid path
    if (iPart == 0) return;

    // Remove ordered
    CStringStack astrShrunk;
    astrShrunk.Push(astrParts.Count() - 2);
    astrShrunk.PopAll();

    for (INDEX iCopiedPart = 0; iCopiedPart < astrParts.Count(); iCopiedPart++)
    {
      if ((iCopiedPart != iPart - 1) && (iCopiedPart != iPart)) {
        astrShrunk.Push() = astrParts[iCopiedPart];
      }
    }

    astrParts.MoveArray(astrShrunk);
    iPart -= 2;
  }

  // Set new content
  strRemaining.Clear();

  for (iPart = 0; iPart < astrParts.Count(); ++iPart) {
    strRemaining += astrParts[iPart];

    if (iPart < astrParts.Count() - 1) {
      strRemaining += "\\";
    }
  }

  strPath = strRemaining;
};

// Fix formatting of paths from Revolution
inline void FixRevPath(CTString &strPath) {
  CTString strParse = strPath;

  char *pchSrc = strParse.str_String;
  char *pchDst = strPath.str_String;

  // Clear path characters
  memset(pchDst, '\0', strlen(pchDst));

  while (*pchSrc != '\0') {
    // Correct forward slashes to backslashes
    if (*pchSrc == '/') {
      *pchSrc = '\\';
    }

    // Check for succeeding slashes
    char *pchNext = pchSrc + 1;

    if (*pchSrc == '\\' && (*pchNext == '/' || *pchNext == '\\')) {
      // Skip them
      pchSrc++;
      continue;
    }

    // Copy the character and proceed
    *pchDst = *pchSrc;
    pchSrc++;
    pchDst++;
  }

  // Remove slash from the beginning
  strPath.RemovePrefix("\\");
};

// Check if the file is readable
inline BOOL IsReadable(const char *strFullPath) {
  FILE *pFile = fopen(strFullPath, "rb");

  if (pFile != NULL) {
    fclose(pFile);
    return TRUE;
  }

  return FALSE;
};

// Load a list of meaningful strings
inline BOOL LoadStringList(CFileList &afnm, const CTFileName &fnmList) {
  try {
    CTFileStream strm;
    strm.Open_t(fnmList);

    // Add every non-empty line with trimmed spaces
    while (!strm.AtEOF()) {
      char strBuffer[1024];
      IData::GetLineFromStream_t(strm, strBuffer, sizeof(strBuffer));

      CTString strLine = strBuffer;
      strLine.TrimSpacesLeft();
      strLine.TrimSpacesRight();

      if (strLine != "") {
        afnm.Push() = strLine;
      }
    }

  } catch (char *strError) {
    CPrintF("%s\n", strError);
    return FALSE;
  }

  return TRUE;
};

// CTFileName comparison method for qsort()
inline int CompareFileNames(const void *pElement1, const void *pElement2)
{
  const CTFileName &fnm1 = **(CTFileName **)pElement1;
  const CTFileName &fnm2 = **(CTFileName **)pElement2;

  return strcmp(fnm1.str_String, fnm2.str_String);
};

// Check if some name pattern matches any file in the list
inline INDEX MatchesList(const CFileList &afnm, const CTString &strPattern)
{
  for (INDEX i = 0; i < afnm.Count(); i++) {
    const CTFileName &fnmCheck = afnm[i];

    // Skip empty lines
    if (fnmCheck == "") continue;

    // Starts with the pattern or matches the wildcards
    if (strPattern.HasPrefix(fnmCheck) || strPattern.Matches(fnmCheck)) {
      return i;
    }
  }

  return -1;
};

}; // namespace

#endif
