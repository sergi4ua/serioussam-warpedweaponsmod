108
%{
#include "StdH.h"
%}

// [WW] This class exists in the retail 1.07 EntitiesMP.dll but is missing from the
// public 1.07 SDK. Recreated from the retail library so that every class referenced
// by Classes\TerrainEntity.ecl is available in this mod as well.

class CTerrainEntity : CEntity {
name      "Terrain";
thumbnail "Help\\SDK\\Models\\Blob\\Blob.tbn";

properties:

components:

functions:

procedures:

  Main()
  {
    InitAsTerrain();
    TerrainChangeNotify();
    SetCollisionFlags(ECF_BRUSH);
    return;
  }
};
