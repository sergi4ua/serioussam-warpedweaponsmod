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

#ifndef XGIZMO_INCL_ANYVALUE_H
#define XGIZMO_INCL_ANYVALUE_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Entities/EntityProperties.h>

#include <algorithm>

// Type-safe container for single values of any type
class CAnyValue {
  public:
    // Rely on entity property types for supported types
    enum EType {
      // Invalid type
      E_VAL_NULL = 0,

      // Basic types
      E_VAL_BOOL     = CEntityProperty::EPT_BOOL,
      E_VAL_FLOAT    = CEntityProperty::EPT_FLOAT,
      E_VAL_STRING   = CEntityProperty::EPT_STRING,
      E_VAL_PTR      = CEntityProperty::EPT_ENTITYPTR,
      E_VAL_INDEX    = CEntityProperty::EPT_INDEX,

      // Spatial types
      E_VAL_VECTOR   = CEntityProperty::EPT_FLOAT3D,
      E_VAL_PLANE    = CEntityProperty::EPT_FLOATplane3D,
      E_VAL_PLACE    = CEntityProperty::EPT_PLACEMENT3D,
      E_VAL_BOX      = CEntityProperty::EPT_FLOATAABBOX3D,
      E_VAL_QUAT     = CEntityProperty::EPT_FLOATQUAT3D,
      E_VAL_MATRIX   = CEntityProperty::EPT_FLOATMATRIX3D,

      // Extra types
      E_VAL_DOUBLE = 50,
    };

    // Value placeholder
    struct Placeholder {
      virtual ~Placeholder() {};
      virtual EType GetType() const = 0;
      virtual Placeholder *Clone() const = 0;
    };

    // Value holder of a specific type
    template<class Type, EType eType>
    struct Holder : public Placeholder {
      Type _value;

      Holder(const Type &valSet) : _value(valSet) {};
      virtual EType GetType() const { return eType; };
      virtual Placeholder *Clone() const { return new Holder(_value); };
    };

    typedef Holder<INDEX,    E_VAL_BOOL>   Bool_t;
    typedef Holder<INDEX,    E_VAL_INDEX>  Int_t;
    typedef Holder<FLOAT,    E_VAL_FLOAT>  Float_t;
    typedef Holder<DOUBLE,   E_VAL_DOUBLE> Double_t;
    typedef Holder<CTString, E_VAL_STRING> String_t;
    typedef Holder<void *,   E_VAL_PTR>    Ptr_t;

    typedef Holder<FLOAT3D,       E_VAL_VECTOR> Vector_t;
    typedef Holder<FLOATplane3D,  E_VAL_PLANE>  Plane_t;
    typedef Holder<CPlacement3D,  E_VAL_PLACE>  Place_t;
    typedef Holder<FLOATaabbox3D, E_VAL_BOX>    Box_t;
    typedef Holder<FLOATquat3D,   E_VAL_QUAT>   Quat_t;
    typedef Holder<FLOATmatrix3D, E_VAL_MATRIX> Matrix_t;

  private:
    Placeholder *_content; // Currently held value

  public:
    // Default constructor
    CAnyValue() : _content(NULL) {};

    // Constructors from supported types
    CAnyValue(bool   bSet) : _content(new Bool_t  (bSet)) {};
    CAnyValue(int    iSet) : _content(new Int_t   (iSet)) {};
    CAnyValue(float  fSet) : _content(new Float_t (fSet)) {};
    CAnyValue(double fSet) : _content(new Double_t(fSet)) {};
    CAnyValue(const CTString &strSet) : _content(new String_t(strSet)) {};
    CAnyValue(const char     *strSet) : _content(new String_t(strSet)) {};
    CAnyValue(void             *pSet) : _content(new Ptr_t(pSet)) {};

    CAnyValue(const FLOAT3D       &vSet)   : _content(new Vector_t(vSet)) {};
    CAnyValue(const FLOATplane3D  &plSet)  : _content(new Plane_t (plSet)) {};
    CAnyValue(const CPlacement3D  &plSet)  : _content(new Place_t (plSet)) {};
    CAnyValue(const FLOATaabbox3D &boxSet) : _content(new Box_t   (boxSet)) {};
    CAnyValue(const FLOATquat3D   &qSet)   : _content(new Quat_t  (qSet)) {};
    CAnyValue(const FLOATmatrix3D &mSet)   : _content(new Matrix_t(mSet)) {};

    // Copy constructor
    CAnyValue(const CAnyValue &other) : _content(!other.IsEmpty() ? other._content->Clone() : NULL) {};

    // Destructor
    ~CAnyValue() {
      delete _content;
    };

  public:
    // Get value type
    inline EType GetType() const {
      return !IsEmpty() ? _content->GetType() : E_VAL_NULL;
    };

    // Swap values
    inline void Swap(CAnyValue &other) {
      std::swap(_content, other._content);
    };

    // Assign a new value by swapping values with a temporary copy
    inline CAnyValue &operator=(const CAnyValue &other) {
      CAnyValue(other).Swap(*this);
      return *this;
    };

    // Check if value is empty
    inline bool IsEmpty() const {
      return _content == NULL;
    };

  // Value accessors
  public:

    inline INDEX &GetIndex(void) {
      ASSERT(GetType() == E_VAL_BOOL || GetType() == E_VAL_INDEX);
      return ((Int_t *)_content)->_value;
    };

    inline FLOAT &GetFloat(void) {
      ASSERT(GetType() == E_VAL_FLOAT);
      return ((Float_t *)_content)->_value;
    };

    inline DOUBLE &GetDouble(void) {
      ASSERT(GetType() == E_VAL_DOUBLE);
      return ((Double_t *)_content)->_value;
    };

    inline CTString &GetString(void) {
      ASSERT(GetType() == E_VAL_STRING);
      return ((String_t *)_content)->_value;
    };

    inline void *&GetPtr(void) {
      ASSERT(GetType() == E_VAL_PTR);
      return ((Ptr_t *)_content)->_value;
    };

    inline FLOAT3D &GetVector(void) {
      ASSERT(GetType() == E_VAL_VECTOR);
      return ((Vector_t *)_content)->_value;
    };

    inline FLOATplane3D &GetPlane(void) {
      ASSERT(GetType() == E_VAL_PLANE);
      return ((Plane_t *)_content)->_value;
    };

    inline CPlacement3D &GetPlacement(void) {
      ASSERT(GetType() == E_VAL_PLACE);
      return ((Place_t *)_content)->_value;
    };

    inline FLOATaabbox3D &GetBox(void) {
      ASSERT(GetType() == E_VAL_BOX);
      return ((Box_t *)_content)->_value;
    };

    inline FLOATquat3D &GetQuat(void) {
      ASSERT(GetType() == E_VAL_QUAT);
      return ((Quat_t *)_content)->_value;
    };

    inline FLOATmatrix3D &GetMatrix(void) {
      ASSERT(GetType() == E_VAL_MATRIX);
      return ((Matrix_t *)_content)->_value;
    };
    
  // Value converters
  public:

    inline bool IsTrue(void) const {
      switch (GetType()) {
        case E_VAL_BOOL:
        case E_VAL_INDEX:  return ((Int_t    *)_content)->_value != 0;
        case E_VAL_FLOAT:  return ((Float_t  *)_content)->_value != 0.0f;
        case E_VAL_DOUBLE: return ((Double_t *)_content)->_value != 0.0;
        case E_VAL_STRING: return ((String_t *)_content)->_value.Length() != 0;
        case E_VAL_PTR:    return ((Ptr_t    *)_content)->_value != NULL;
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::IsTrue()");
      return false;
    };

    // Implicit conversion
    __forceinline operator bool() const {
      return IsTrue();
    };

    inline INDEX ToIndex(void) const {
      switch (GetType()) {
        case E_VAL_BOOL:
        case E_VAL_INDEX:  return ((Int_t    *)_content)->_value;
        case E_VAL_FLOAT:  return ((Float_t  *)_content)->_value;
        case E_VAL_DOUBLE: return ((Double_t *)_content)->_value;
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::ToIndex()");
      return 0;
    };

    inline DOUBLE ToFloat(void) const {
      switch (GetType()) {
        case E_VAL_BOOL:
        case E_VAL_INDEX:  return ((Int_t    *)_content)->_value;
        case E_VAL_FLOAT:  return ((Float_t  *)_content)->_value;
        case E_VAL_DOUBLE: return ((Double_t *)_content)->_value;
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::ToFloat()");
      return 0.0;
    };

    inline CTString ToString(void) const {
      switch (GetType()) {
        case E_VAL_BOOL:   return ((Int_t *)_content)->_value ? "1" : "0";
        case E_VAL_INDEX:  return CTString(0, "%d", ((Int_t    *)_content)->_value);
        case E_VAL_FLOAT:  return CTString(0, "%g", ((Float_t  *)_content)->_value);
        case E_VAL_DOUBLE: return CTString(0, "%g", ((Double_t *)_content)->_value);
        case E_VAL_STRING: return ((String_t *)_content)->_value;
        case E_VAL_PTR:    return CTString(0, "0x%p", ((Ptr_t  *)_content)->_value);

        case E_VAL_VECTOR: {
          const FLOAT3D &v = ((Vector_t *)_content)->_value;
          return CTString(0, "v[%g, %g, %g]", v(1), v(2), v(3));
        }

        case E_VAL_PLANE: {
          const FLOATplane3D &pl = ((Plane_t *)_content)->_value;
          return CTString(0, "pl[%g, %g, %g; ->%g]", pl(1), pl(2), pl(3), pl.pl_distance);
        }

        case E_VAL_PLACE: {
          const CPlacement3D &pl = ((Place_t *)_content)->_value;
          return CTString(0, "pl[%g, %g, %g;  %g, %g, %g]",
            pl.pl_PositionVector(1),   pl.pl_PositionVector(2),   pl.pl_PositionVector(3),
            pl.pl_OrientationAngle(1), pl.pl_OrientationAngle(2), pl.pl_OrientationAngle(3));
        }

        case E_VAL_BOX: {
          const FLOATaabbox3D &box = ((Box_t *)_content)->_value;
          return CTString(0, "b[%g, %g, %g;  %g, %g, %g]",
            box.Min()(1), box.Min()(2), box.Min()(3), box.Max()(1), box.Max()(2), box.Max()(3));
        }

        case E_VAL_QUAT: {
          const FLOATquat3D &q = ((Quat_t *)_content)->_value;
          return CTString(0, "q[%g, %g, %g, %g]", q.q_w, q.q_x, q.q_y, q.q_z);
        }

        case E_VAL_MATRIX: {
          const FLOATmatrix3D &m = ((Matrix_t *)_content)->_value;
          return CTString(0, "m[%g, %g, %g;  %g, %g, %g;  %g, %g, %g]",
            m(1, 1), m(1, 2), m(1, 3), m(2, 1), m(2, 2), m(2, 3), m(3, 1), m(3, 2), m(3, 3));
        }
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::ToString()");
      return "";
    };

    inline FLOAT3D ToVector(void) const {
      switch (GetType()) {
        case E_VAL_VECTOR: return ((Vector_t *)_content)->_value;

        // Plane normal
        case E_VAL_PLANE: return (FLOAT3D &)((Plane_t *)_content)->_value;

        // Placement position
        case E_VAL_PLACE: return ((Place_t *)_content)->_value.pl_PositionVector;

        // Matrix to rotation angles
        case E_VAL_MATRIX: {
          ANGLE3D v;
          DecomposeRotationMatrixNoSnap(v, ((Matrix_t *)_content)->_value);
          return v;
        }
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::ToVector()");
      return FLOAT3D(0, 0, 0);
    };

    inline FLOATplane3D ToPlane(void) const {
      switch (GetType()) {
        // Direction with 1 meter length
        case E_VAL_VECTOR: return FLOATplane3D(((Vector_t *)_content)->_value, 1.0f);

        case E_VAL_PLANE: return ((Plane_t *)_content)->_value;
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::ToPlane()");
      return FLOATplane3D(FLOAT3D(0, 1, 0), 1.0f);
    };

    inline CPlacement3D ToPlacement(void) const {
      switch (GetType()) {
        // Position without rotation
        case E_VAL_VECTOR: return CPlacement3D(((Vector_t *)_content)->_value, ANGLE3D(0, 0, 0));

        case E_VAL_PLACE: return ((Place_t *)_content)->_value;
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::ToPlacement()");
      return CPlacement3D(FLOAT3D(0, 0, 0), ANGLE3D(0, 0, 0));
    };

    inline FLOATaabbox3D ToBox(void) const {
      switch (GetType()) {
        case E_VAL_BOX: return ((Box_t *)_content)->_value;
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::ToBox()");
      return FLOATaabbox3D(FLOAT3D(0, 0, 0), 0.0f);
    };

    inline FLOATquat3D ToQuat(void) const {
      switch (GetType()) {
        case E_VAL_QUAT: return ((Quat_t *)_content)->_value;

        // Quaternion conversion
        case E_VAL_MATRIX: {
          FLOATquat3D q;
          q.FromMatrix(((Matrix_t *)_content)->_value);
          return q;
        }
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::ToQuat()");
      return FLOATquat3D(0, 0, 0, 0);
    };

    inline FLOATmatrix3D ToMatrix(void) const {
      switch (GetType()) {
        // Rotation angles to matrix
        case E_VAL_VECTOR: {
          FLOATmatrix3D m;
          MakeRotationMatrix(m, ((Vector_t *)_content)->_value);
          return m;
        }

        // Placement rotation to matrix
        case E_VAL_PLACE: {
          FLOATmatrix3D m;
          MakeRotationMatrix(m, ((Place_t *)_content)->_value.pl_OrientationAngle);
          return m;
        }

        // Quaternion conversion
        case E_VAL_QUAT: {
          FLOATmatrix3D m;
          ((Quat_t *)_content)->_value.ToMatrix(m);
          return m;
        }

        case E_VAL_MATRIX: return ((Matrix_t *)_content)->_value;
      }

      ASSERTALWAYS("Unknown value type in CAnyValue::ToMatrix()");
      return FLOATmatrix3D(0);
    };
};

#endif
