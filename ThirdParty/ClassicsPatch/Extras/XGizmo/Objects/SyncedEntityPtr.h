/* Copyright (c) 2024 Dreamy Cecil
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

#ifndef XGIZMO_INCL_SYNCEDENTITYPTR_H
#define XGIZMO_INCL_SYNCEDENTITYPTR_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Entities/Entity.h>

// Class that can establish a synchronized connection between two specific entities and only those entities
class CSyncedEntityPtr {
  private:
    CEntity *_owner; // Entity that owns this sync class
    CSyncedEntityPtr *_sync; // Another class to sync with

    // Cannot be copied
    CSyncedEntityPtr(const CSyncedEntityPtr &) {};
    void operator=(const CSyncedEntityPtr &) {};

  public:
    CSyncedEntityPtr() : _owner(NULL), _sync(NULL) {};
    ~CSyncedEntityPtr() { Unsync(); };

    // Set owner entity
    __forceinline void SetOwner(CEntity *pen) {
      _owner = pen;
    };

    // Get owner entity
    __forceinline CEntity *GetOwner(void) const {
      return _owner;
    };

    // Compare synced class
    __forceinline BOOL IsSyncedWith(CSyncedEntityPtr *pSyncOther) const {
      return _sync == pSyncOther;
    };

    // Check if this class is synced
    __forceinline BOOL IsSynced(void) const {
      return !IsSyncedWith(NULL);
    };

    // Get owner entity of the synced class
    __forceinline CEntity *GetSyncedEntity(void) const {
      if (_sync == NULL) return NULL;
      return _sync->GetOwner();
    };

  public:
    // Unsync this class from the other one
    inline void Unsync(void) {
      if (_sync != NULL) {
        // Must be synced to this one
        ASSERT(_sync->_sync == this);
        _sync->_sync = NULL;
      }

      _sync = NULL;
    };

    // Sync with another class
    inline void Sync(CSyncedEntityPtr *pSyncOther) {
      // Unsync current class
      Unsync();

      // Sync another class
      if (pSyncOther != NULL) {
        pSyncOther->Unsync();

        pSyncOther->_sync = this;
        _sync = pSyncOther;
      }
    };
};

#endif
