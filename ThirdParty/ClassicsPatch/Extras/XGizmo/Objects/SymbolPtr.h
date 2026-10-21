/* Copyright (c) 2022-2025 Dreamy Cecil
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

#ifndef XGIZMO_INCL_SYMBOLPTR_H
#define XGIZMO_INCL_SYMBOLPTR_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Base/Shell.h>

// Class to be utilized statically that searches for shell symbols
class CSymbolPtr {
  public:
    CShellSymbol *_pss;

  public:
    // Default constructor
    CSymbolPtr() : _pss(NULL)
    {
    };

    // Constructor with a symbol name
    CSymbolPtr(const char *strSymbolName) {
      Find(strSymbolName);
    };

    // Find symbol under a specific name
    void Find(const char *strSymbolName) {
      _pss = _pShell->GetSymbol(strSymbolName, TRUE);
    };

    // Check if symbol has been found
    BOOL Exists(void) const {
      return (_pss != NULL);
    };

  // Constant getters
  public:

    // Get index value
    INDEX GetIndex(void) const {
      ASSERT(_pss != NULL);
      return *(INDEX *)_pss->ss_pvValue;
    };

    // Get float value
    FLOAT GetFloat(void) const {
      ASSERT(_pss != NULL);
      return *(FLOAT *)_pss->ss_pvValue;
    };

    // Get string value
    const CTString &GetString(void) const {
      ASSERT(_pss != NULL);
      return *(CTString *)_pss->ss_pvValue;
    };

    // Get pointer to the value
    void *GetValue(void) const {
      ASSERT(_pss != NULL);
      return _pss->ss_pvValue;
    };

  // Reference getters
  public:

    // Get index value
    INDEX &GetIndex(void) {
      ASSERT(_pss != NULL);
      return *(INDEX *)_pss->ss_pvValue;
    };

    // Get float value
    FLOAT &GetFloat(void) {
      ASSERT(_pss != NULL);
      return *(FLOAT *)_pss->ss_pvValue;
    };

    // Get string value
    CTString &GetString(void) {
      ASSERT(_pss != NULL);
      return *(CTString *)_pss->ss_pvValue;
    };
};

#endif
