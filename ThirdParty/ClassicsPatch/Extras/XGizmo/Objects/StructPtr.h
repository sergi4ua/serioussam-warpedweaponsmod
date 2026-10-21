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

#ifndef XGIZMO_INCL_STRUCTPTR_H
#define XGIZMO_INCL_STRUCTPTR_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

// Caster between raw addresses and pointers to structures
struct StructPtr {
  size_t iAddress; // Raw address

  // Constructor from a raw address
  StructPtr(size_t iSetAddress = NULL) : iAddress(iSetAddress)
  {
  };

  // Copy constructor
  StructPtr(const StructPtr &other) : iAddress(other.iAddress)
  {
  };

  // Constructor from a pointer to a structure
  template<class Type>
  StructPtr(Type pSetStruct) {
    // Brute-force converter
    union {
      size_t iAddress;
      Type pStruct;
    } conv;

    // Cast structure pointer into an address
    conv.pStruct = pSetStruct;
    iAddress = conv.iAddress;
  };

  // Get pointer to the structure
  // 'pDummy' is for specifying a typed pointer because VC6.0 does not allow 'TempMethod<...>(...)' calls
  template<class Type>
  Type operator()(Type pDummy) {
    // Brute-force converter
    union {
      size_t iAddress;
      Type pStruct;
    } conv;

    // Cast address into a structure pointer
    conv.iAddress = iAddress;
    return conv.pStruct;
  };
};

#endif
