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

#ifndef XGIZMO_INCL_LIBCLASSHOLDER_H
#define XGIZMO_INCL_LIBCLASSHOLDER_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Entities/EntityProperties.h>

// Structure for retrieving a library entity class from any of its owners
struct LibClassHolder
{
  CDLLEntityClass *pdec; // Stored library entity class

  // Default constructor
  LibClassHolder(CDLLEntityClass *pdecSet = NULL) : pdec(pdecSet)
  {
  };

  // Constructor from an entity class
  LibClassHolder(CEntityClass *pecSet) : pdec(NULL)
  {
    if (pecSet != NULL) {
      pdec = pecSet->ec_pdecDLLClass;
    }
  };

  // Constructor from an entity
  LibClassHolder(CEntity *penSet) : pdec(NULL)
  {
    if (penSet != NULL && penSet->GetClass() != NULL) {
      pdec = penSet->GetClass()->ec_pdecDLLClass;
    }
  };

  // Constructor from an entity pointer
  LibClassHolder(CEntityPointer penSet) : pdec(NULL)
  {
    if (penSet != NULL && penSet->GetClass() != NULL) {
      pdec = penSet->GetClass()->ec_pdecDLLClass;
    }
  };

  // Implicit converters into the library entity class
  inline CDLLEntityClass *operator->(void) const { return pdec; };
  inline operator CDLLEntityClass *(void) const { return pdec; };
  inline CDLLEntityClass &operator*(void) const { return *pdec; };
};

#endif
