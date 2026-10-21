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

#ifndef XGIZMO_INCL_PROPERTYPTR_H
#define XGIZMO_INCL_PROPERTYPTR_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Entities/EntityClass.h>

#include "../Interfaces/World.h"

class CPropertyPtr {
  public:
    CEntityProperty *_pep; // Found property in an entity
    LibClassHolder _lch; // Class of entities with this property

  public:
    // Default constructor
    CPropertyPtr() : _pep(NULL), _lch()
    {
    };

    // Constructor from a holder
    CPropertyPtr(LibClassHolder lchSet) : _pep(NULL), _lch(lchSet)
    {
    };

    // Get property offset
    inline SLONG Offset(void) const {
      return _pep->ep_slOffset;
    };

  public:
    // Get property by ID or offset
    BOOL ByIdOrOffset(ULONG ulType, ULONG ulID, SLONG slOffset) {
      if (_pep == NULL) {
        _pep = IWorld::PropertyForIdOrOffset(_lch, ulType, ulID, slOffset);
        ASSERTMSG(_pep != NULL, "Cannot find property by ID for CPropertyPtr!");
      }

      return (_pep != NULL);
    };

    // Get property by name
    BOOL ByName(ULONG ulType, const char *strProperty) {
      if (_pep == NULL) {
        _pep = IWorld::PropertyForName(_lch, ulType, strProperty);
        ASSERTMSG(_pep != NULL, "Cannot find property by name for CPropertyPtr!");
      }

      return (_pep != NULL);
    };

    // Get property by name or ID
    BOOL ByNameOrId(ULONG ulType, const char *strProperty, ULONG ulID) {
      if (_pep == NULL) {
        _pep = IWorld::PropertyForNameOrId(_lch, ulType, strProperty, ulID);
        ASSERTMSG(_pep != NULL, "Cannot find property by name or ID for CPropertyPtr!");
      }

      return (_pep != NULL);
    };
};

#endif
