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

#ifndef XGIZMO_INCL_BASECLASSES_H
#define XGIZMO_INCL_BASECLASSES_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include "LibClassHolder.h"

// Class IDs of base entity classes
#define CEntity_ClassID         32000
#define CLiveEntity_ClassID     32001
#define CRationalEntity_ClassID 32002
#define CMovableEntity_ClassID      1
#define CMovableModelEntity_ClassID 2
#define CMovableBrushEntity_ClassID 3
#define CPlayerEntity_ClassID       4

// Containers of base entities
typedef CDynamicContainer<CEntity>             CEntities;
typedef CDynamicContainer<CLiveEntity>         CLiveEntities;
typedef CDynamicContainer<CRationalEntity>     CRationalEntities;
typedef CDynamicContainer<CMovableEntity>      CMovableEntities;
typedef CDynamicContainer<CMovableModelEntity> CMovableModelEntities;
typedef CDynamicContainer<CMovableBrushEntity> CMovableBrushEntities;
typedef CDynamicContainer<CPlayerEntity>       CPlayerEntities;

// Check if the entity is of a specific class by its ID (e.g. CHeadman_ClassID)
inline BOOL IsOfClassID(LibClassHolder lch, INDEX iClassID)
{
  if (lch.pdec == NULL) return FALSE;
  return (lch.pdec->dec_iID == iClassID);
};

// Check if the entity is derived from a specific class by its ID (e.g. CEnemyBase_ClassID)
inline BOOL IsDerivedFromID(LibClassHolder lch, INDEX iClassID)
{
  // Go through the class hierarchy
  CDLLEntityClass *pdec = lch.pdec;

  for (; pdec != NULL; pdec = pdec->dec_pdecBase)
  {
    if (pdec->dec_iID == iClassID) return TRUE;
  }

  return FALSE;
};

// Check if the entity is derived from CLiveEntity
inline BOOL IsLiveEntity(LibClassHolder lch)
{
  // Go through the class hierarchy
  CDLLEntityClass *pdec = lch.pdec;

  for (; pdec != NULL; pdec = pdec->dec_pdecBase) {
    // [Cecil] NOTE: CLiveEntity or CRationalEntity because the hierarchy ends on only one of them
    if (pdec->dec_iID == CLiveEntity_ClassID
     || pdec->dec_iID == CRationalEntity_ClassID) {
      return TRUE;
    }
  }

  return FALSE;
};

// Check if the entity is derived from CRationalEntity
inline BOOL IsRationalEntity(LibClassHolder lch) {
  return IsDerivedFromID(lch, CRationalEntity_ClassID);
};

#endif
