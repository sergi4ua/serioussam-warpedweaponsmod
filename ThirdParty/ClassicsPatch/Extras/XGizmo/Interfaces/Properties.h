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

#ifndef XGIZMO_INCL_PROPERTIESINTERFACE_H
#define XGIZMO_INCL_PROPERTIESINTERFACE_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Entities/Entity.h>
#include <Engine/Entities/EntityProperties.h>

// Interface of useful methods for entity property manipulation
namespace IProperties {

// Narrow down the easily editable property type
inline INDEX ConvertType(CEntityProperty::PropertyType eProperty)
{
  ASSERT(eProperty > 0 && eProperty < 27);

  static const INDEX aiPropertyTypes[27] = {
    -1, // Invalid type
    CEntityProperty::EPT_INDEX,
    CEntityProperty::EPT_INDEX,
    CEntityProperty::EPT_FLOAT,
    CEntityProperty::EPT_INDEX,
    CEntityProperty::EPT_STRING,
    CEntityProperty::EPT_FLOAT,
    CEntityProperty::EPT_ENTITYPTR,
    CEntityProperty::EPT_STRING,
    CEntityProperty::EPT_INDEX,
    CEntityProperty::EPT_INDEX,
    CEntityProperty::EPT_INDEX,
    -1, // EPT_FLOATAABBOX3D
    CEntityProperty::EPT_FLOAT,
    CEntityProperty::EPT_FLOAT3D,
    CEntityProperty::EPT_FLOAT3D,
    -1, // EPT_FLOATplane3D
    -1, // EPT_MODELOBJECT
    -1, // EPT_PLACEMENT3D
    -1, // EPT_ANIMOBJECT
    CEntityProperty::EPT_STRING,
    -1, // EPT_SOUNDOBJECT
    CEntityProperty::EPT_STRING,
    -1, // EPT_FLOATQUAT3D
    -1, // EPT_FLOATMATRIX3D
    CEntityProperty::EPT_INDEX,
    -1, // EPT_MODELINSTANCE
  };

  return aiPropertyTypes[eProperty];
};

// Set property value from a pointer to the variable
inline BOOL SetPropValue(CEntity *penEntity, CEntityProperty *pep, void *pValue) {
  INDEX iPropType = ConvertType(pep->ep_eptType);
  SLONG slOffset = pep->ep_slOffset;

  switch (iPropType)
  {
    case CEntityProperty::EPT_INDEX: {
      INDEX &iValue = ENTITYPROPERTY(penEntity, slOffset, INDEX);
      iValue = *(INDEX *)pValue;
    } break;

    case CEntityProperty::EPT_FLOAT: {
      FLOAT &fValue = ENTITYPROPERTY(penEntity, slOffset, FLOAT);
      fValue = *(FLOAT *)pValue;
    } break;

    case CEntityProperty::EPT_STRING: {
      CTString &strValue = ENTITYPROPERTY(penEntity, slOffset, CTString);
      strValue = *(CTString *)pValue;
    } break;

    case CEntityProperty::EPT_ENTITYPTR: {
      CEntityPointer &penPointer = ENTITYPROPERTY(penEntity, slOffset, CEntityPointer);
      penPointer = *(CEntity **)pValue; // Pointer to entity pointer for consistency
    } break;

    case CEntityProperty::EPT_FLOAT3D: {
      FLOAT3D &vValue = ENTITYPROPERTY(penEntity, slOffset, FLOAT3D);
      vValue = *(FLOAT3D *)pValue;
    } break;

    // Invalid type
    default: return FALSE;
  }

  // Value has been set
  return TRUE;
};

// Get value from an entity property and write it into a variable by its pointer
inline BOOL GetPropValue(CEntity *penEntity, CEntityProperty *pep, void **pValue) {
  INDEX iPropType = ConvertType(pep->ep_eptType);
  SLONG slOffset = pep->ep_slOffset;

  switch (iPropType)
  {
    case CEntityProperty::EPT_INDEX: {
      INDEX &iValue = ENTITYPROPERTY(penEntity, slOffset, INDEX);
      *pValue = &iValue;
    } break;

    case CEntityProperty::EPT_FLOAT: {
      FLOAT &fValue = ENTITYPROPERTY(penEntity, slOffset, FLOAT);
      *pValue = &fValue;
    } break;

    case CEntityProperty::EPT_STRING: {
      CTString &strValue = ENTITYPROPERTY(penEntity, slOffset, CTString);
      *pValue = &strValue;
    } break;

    case CEntityProperty::EPT_ENTITYPTR: {
      CEntityPointer &penPointer = ENTITYPROPERTY(penEntity, slOffset, CEntityPointer);
      *pValue = (CEntity *)penPointer;
    } break;

    case CEntityProperty::EPT_FLOAT3D: {
      FLOAT3D &vValue = ENTITYPROPERTY(penEntity, slOffset, FLOAT3D);
      *pValue = &vValue;
    } break;

    // Invalid type
    default: {
      *pValue = NULL;
    } return FALSE;
  }

  // Value has been retrieved
  return TRUE;
};

// Get value of from an entity property of an index type
inline BOOL GetIndexValue(CEntity *penEntity, CEntityProperty *pep, INDEX &iValue) {
  void *pGetValue;
  if (!GetPropValue(penEntity, pep, &pGetValue)) return FALSE;

  iValue = *(INDEX *)pGetValue;
  return TRUE;
};

// Get value of from an entity property of a float type
inline BOOL GetFloatValue(CEntity *penEntity, CEntityProperty *pep, FLOAT &fValue) {
  void *pGetValue;
  if (!GetPropValue(penEntity, pep, &pGetValue)) return FALSE;

  fValue = *(FLOAT *)pGetValue;
  return TRUE;
};

// Get value of from an entity property of a string type
inline BOOL GetStringValue(CEntity *penEntity, CEntityProperty *pep, CTString &strValue) {
  void *pGetValue;
  if (!GetPropValue(penEntity, pep, &pGetValue)) return FALSE;

  strValue = *(CTString *)pGetValue;
  return TRUE;
};

// Get value of from an entity property of an entity pointer type
inline BOOL GetPointerValue(CEntity *penEntity, CEntityProperty *pep, CEntity *&penValue) {
  void *pGetValue;
  if (!GetPropValue(penEntity, pep, &pGetValue)) return FALSE;

  penValue = (CEntity *)pGetValue;
  return TRUE;
};

// Get value of from an entity property of a vector type
inline BOOL GetVectorValue(CEntity *penEntity, CEntityProperty *pep, FLOAT3D &vValue) {
  void *pGetValue;
  if (!GetPropValue(penEntity, pep, &pGetValue)) return FALSE;

  vValue = *(FLOAT3D *)pGetValue;
  return TRUE;
};

}; // namespace

#endif
