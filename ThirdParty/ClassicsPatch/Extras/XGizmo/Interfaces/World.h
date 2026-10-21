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

#ifndef XGIZMO_INCL_WORLDINTERFACE_H
#define XGIZMO_INCL_WORLDINTERFACE_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Entities/Entity.h>
#include <Engine/World/World.h>

#include "../Entities/BaseClasses.h"

// Interface of useful methods for world and entity manipulation
namespace IWorld { 

// Get current game world
inline CWorld *GetWorld(void) {
  return &_pNetwork->ga_World;
};

// Gather entities of the same class
inline void GetEntitiesOfClass(CEntities &cInput, CEntities &cOutput, LibClassHolder lchClass) {
  FOREACHINDYNAMICCONTAINER(cInput, CEntity, iten) {
    CEntity *pen = &*iten;

    if (pen->GetFlags() & ENF_DELETED) {
      continue;
    }

    // Same class
    if (pen->GetClass()->ec_pdecDLLClass == lchClass.pdec) {
      cOutput.Add(pen);
    }
  }
};

// Find entity in a world by its ID
inline CEntity *FindEntityByID(CWorld *pwo, const ULONG ulEntityID) {
  FOREACHINDYNAMICCONTAINER(GetWorld()->wo_cenEntities, CEntity, iten) {
    CEntity *pen = &*iten;

    if (pen->GetFlags() & ENF_DELETED) {
      continue;
    }

    // Same ID
    if (pen->en_ulID == ulEntityID) {
      return pen;
    }
  }

  return NULL;
};

// Find existing entity property by its ID
inline CEntityProperty *PropertyForId(LibClassHolder lch, ULONG ulID) {
  CDLLEntityClass *pdec = lch;

  while (pdec != NULL) {
    // For each property
    for (INDEX iProp = 0; iProp < pdec->dec_ctProperties; iProp++) {
      CEntityProperty &ep = pdec->dec_aepProperties[iProp];

      // Matching ID
      if (ep.ep_ulID == ulID) {
        return &ep;
      }
    }

    // Next class in the hierarchy
    pdec = pdec->dec_pdecBase;
  }

  return NULL;
};

// Find existing entity property by its name hash
inline CEntityProperty *PropertyForHash(LibClassHolder lch, ULONG ulNameHash) {
  CDLLEntityClass *pdec = lch;

  while (pdec != NULL) {
    // For each property
    for (INDEX iProp = 0; iProp < pdec->dec_ctProperties; iProp++) {
      CEntityProperty &ep = pdec->dec_aepProperties[iProp];

      // Matching name hash
      ULONG ulCheckHash = CTString(ep.ep_strName).GetHash();

      if (ulCheckHash == ulNameHash) {
        return &ep;
      }
    }

    // Next class in the hierarchy
    pdec = pdec->dec_pdecBase;
  }

  return NULL;
};

// Find entity property by its ID or offset of a specific type
inline CEntityProperty *PropertyForIdOrOffset(LibClassHolder lch, ULONG ulType, ULONG ulID, SLONG slOffset) {
  CDLLEntityClass *pdec = lch;

  while (pdec != NULL) {
    // For each property
    for (INDEX iProp = 0; iProp < pdec->dec_ctProperties; iProp++) {
      CEntityProperty &ep = pdec->dec_aepProperties[iProp];

      // Only check the matching type
      if (ep.ep_eptType != ulType) continue;

      // Matching ID or offset (ID is more likely to remain the same)
      if (ep.ep_ulID == ulID || ep.ep_slOffset == slOffset) {
        return &ep;
      }
    }

    // Next class in the hierarchy
    pdec = pdec->dec_pdecBase;
  }

  return NULL;
};

// Find entity property by its name of a specific type
inline CEntityProperty *PropertyForName(LibClassHolder lch, ULONG ulType, const CTString &strName) {
  CDLLEntityClass *pdec = lch;

  while (pdec != NULL) {
    // For each property
    for (INDEX iProp = 0; iProp < pdec->dec_ctProperties; iProp++) {
      CEntityProperty &ep = pdec->dec_aepProperties[iProp];

      // Only check the matching type
      if (ep.ep_eptType != ulType) continue;

      // Matching name
      if (strName == ep.ep_strName) {
        return &ep;
      }
    }

    // Next class in the hierarchy
    pdec = pdec->dec_pdecBase;
  }

  return NULL;
};

// Find entity property by its name or ID of a specific type
inline CEntityProperty *PropertyForNameOrId(LibClassHolder lch, ULONG ulType, const CTString &strName, ULONG ulID) {
  // Find property by name first, if there's any
  CEntityProperty *pep = (strName == "" ? NULL : PropertyForName(lch, ulType, strName));

  // Try searching by ID
  if (pep == NULL) {
    pep = PropertyForIdOrOffset(lch, ulType, ulID, -1);
  }

  return pep;
};

// Find WorldSettingsController in a world
inline CEntity *GetWSC(CWorld *pwo) {
  CEntity *penBack = pwo->GetBackgroundViewer();

  if (penBack != NULL) {
    // Get property offset only once
    static SLONG slPointerOffset = -1;

    if (slPointerOffset == -1) {
      // Obtain entity pointer property
      CEntityProperty *pep = penBack->PropertyForName("World settings controller");

      // No entity pointer
      if (pep == NULL) return NULL;

      slPointerOffset = pep->ep_slOffset;
    }

    // Obtain WorldSettingsController
    return (CEntity *)ENTITYPROPERTY(penBack, slPointerOffset, CEntityPointer);
  }

  return NULL;
};

// Find entities of a specific class
inline void FindClasses(CEntities &cInput, CEntities &cOutput, const char *strClass) {
  ASSERT(cOutput.Count() == 0);

  FOREACHINDYNAMICCONTAINER(cInput, CEntity, iten) {
    CEntity *penCheck = iten;

    if (!IsDerivedFromClass(penCheck, strClass)) {
      continue;
    }

    cOutput.Add(penCheck);
  }
};

// Find entities of a specific class ID
inline void FindClassesByID(CEntities &cInput, CEntities &cOutput, INDEX iClassID) {
  ASSERT(cOutput.Count() == 0);

  FOREACHINDYNAMICCONTAINER(cInput, CEntity, iten) {
    CEntity *penCheck = iten;

    if (!IsDerivedFromID(penCheck, iClassID)) {
      continue;
    }

    cOutput.Add(penCheck);
  }
};

// Check if there are any local players
inline BOOL AnyLocalPlayers(void)
{
  FOREACHINSTATICARRAY(_pNetwork->ga_aplsPlayers, CPlayerSource, itpls) {
    // At least one player has been added
    if (itpls->pls_Index >= 0) return TRUE;
  }

  // No local players (observers may be present)
  return FALSE;
};

// Get pointers to local player entities
inline void GetLocalPlayers(CPlayerEntities &cOutput) {
  ASSERT(cOutput.Count() == 0);

  // Go through all local players
  FOREACHINSTATICARRAY(_pNetwork->ga_aplsPlayers, CPlayerSource, itpls) {
    INDEX iPlayer = itpls->pls_Index;

    // Player hasn't been added
    if (iPlayer < 0) continue;

    // Add player entity
    CPlayerTarget &plt = _pNetwork->ga_sesSessionState.ses_apltPlayers[iPlayer];
    cOutput.Add(plt.plt_penPlayerEntity);
  }
};

// Get viewpoint of a player entity
inline CPlacement3D GetViewpoint(CPlayerEntity *pen, BOOL bLerped) {
  CPlacement3D plView;

  if (bLerped) {
    plView.Lerp(pen->en_plLastViewpoint, pen->en_plViewpoint, _pTimer->GetLerpFactor());
    plView.RelativeToAbsoluteSmooth(pen->GetLerpedPlacement());

  } else {
    plView = pen->en_plViewpoint;
    plView.RelativeToAbsoluteSmooth(pen->GetPlacement());
  }

  return plView;
};

}; // namespace

#endif
