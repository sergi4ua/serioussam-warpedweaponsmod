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

#ifndef XGIZMO_INCL_ENTITYREFLIST_H
#define XGIZMO_INCL_ENTITYREFLIST_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

class CEntityReferences;

// Universal node of some entity that can be added to different reference lists
// When removed, it removes itself from all lists that reference this node
// Similar to CListNode but with the exception of being able to be added to different lists at the same time
class CEntityNode {
  private:
    // Entity that owns this node
    CEntity *_owner;

    // All the lists that this node is in
    CDynamicContainer<CEntityReferences> _lists;

    // Cannot be copied
    CEntityNode(const CEntityNode &) {};
    void operator=(const CEntityNode &) {};

  public:
    // Constructor with no owner
    CEntityNode() : _owner(NULL) {};

    // Remove from all lists on destruction
    ~CEntityNode() {
      Remove();
    };

    // Set owner entity
    __forceinline void SetOwner(CEntity *pen) {
      _owner = pen;
    };

    // Get owner entity
    __forceinline CEntity *GetOwner(void) const {
      return _owner;
    };

    // Check if this node is referenced by any list
    BOOL IsLinked(void);

    // Remove this node from all lists that reference it
    void Remove(void);

  private:
    friend class CEntityReferences;

    // Reference some list that this node is supposedly in
    void Add(CEntityReferences *pList);
};

// Class that keeps track of currently referenced entity nodes
// When cleared, all referenced nodes lose connection to this list
// Similar to CListHead but with the exception of referencing nodes from other lists instead of taking ownership of them
class CEntityReferences {
  private:
    // References to specific entities via nodes
    CDynamicContainer<CEntityNode> _nodes;

    // Cannot be copied
    CEntityReferences(const CEntityReferences &other) {};
    void operator=(const CEntityReferences &other) {};

  public:
    // Default constructor
    CEntityReferences() {};

    // Remove all references on destruction
    ~CEntityReferences() {
      Clear();
    };

    // Get a list of referenced nodes (purely for iteration!)
    inline CDynamicContainer<CEntityNode> &GetNodes(void) {
      return _nodes;
    };

    // Remove all references to current nodes
    void Clear(void) {
      FOREACHINDYNAMICCONTAINER(_nodes, CEntityNode, it) {
        ASSERT(it->_lists.IsMember(this));
        it->_lists.Remove(this);
      }

      _nodes.Clear();
    };

    // Reference a new node in the list
    inline void Add(CEntityNode &node) {
      if (!_nodes.IsMember(&node)) {
        node.Add(this);
        _nodes.Add(&node);
      }
    };

    // Return amount of referenced nodes
    inline INDEX Count(void) const {
      return _nodes.Count();
    };

    // Check if the list of nodes is empty
    inline BOOL IsEmpty(void) const {
      return Count() != 0;
    };

    // Check if some entity is referenced by one of the nodes
    BOOL IsReferenced(CEntity *penCheck) {
      FOREACHINDYNAMICCONTAINER(_nodes, CEntityNode, it) {
        if (it->GetOwner() == penCheck) return TRUE;
      }

      return FALSE;
    };

  private:
    friend class CEntityNode;

    // Stop referencing a specific node in this list
    inline void Remove(CEntityNode *pNode) {
      ASSERT(_nodes.IsMember(pNode));
      _nodes.Remove(pNode);
    };
};

// Check if this node is referenced by any list
inline BOOL CEntityNode::IsLinked(void) {
  return _lists.Count() != 0;
};

// Reference some list that this node is supposedly in
inline void CEntityNode::Add(CEntityReferences *pList) {
  _lists.Add(pList);
};

// Remove this node from all lists that reference it
inline void CEntityNode::Remove(void) {
  FOREACHINDYNAMICCONTAINER(_lists, CEntityReferences, it) {
    it->Remove(this);
  }

  _lists.Clear();
};

// Iteration macro for convenience
#define FOREACHNODEINREFS(_RefList, _It) FOREACHINDYNAMICCONTAINER((_RefList).GetNodes(), CEntityNode, _It)

#endif
