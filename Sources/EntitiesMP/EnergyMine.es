9200
%{
#include "StdH.h"
%}

// [WW] Energy mine dropped by the Minelayer (ported from Seriously Warped Deathmatch v3.0).
//
// A mine is thrown forward, bounces until it settles and arms itself once it lands
// (or one second after it was dropped). It explodes when:
//  - a player touches it after it has been armed (its owner included),
//  - it is destroyed by damage,
//  - its owner detonates all of his mines with the Minelayer's secondary fire (EStart).

uses "EntitiesMP/BasicEffects";

// drop a new mine
event EDropEnergyMine {
  CEntityPointer penLauncher,   // who dropped it
  FLOAT fSpeed,                 // initial forward speed
};

// sent to the owner when a mine is gone
event EBlowUpEnergyMine {
  CEntityPointer penMine,       // the mine that exploded
};

%{
// mine model collision boxes (Models\Weapons\Mine\Mine.mdl)
#define MINE_COLLISION_BOX_WIDE 2

// mines collide with brushes, models and solid projectiles, and are solid projectiles themselves
#define ECF_ENERGYMINE ( \
  ((ECBI_BRUSH|ECBI_MODEL|ECBI_PROJECTILE_SOLID|ECBI_MODEL_HOLDER)<<ECB_TEST) | \
  ((ECBI_PROJECTILE_SOLID)<<ECB_IS))

#define MINE_ARM_DELAY        1.0f    // seconds before a flying mine reacts to players
#define MINE_HEALTH           10.0f
#define MINE_DAMAGE           60.0f
#define MINE_DAMAGE_HOTSPOT   6.0f
#define MINE_DAMAGE_FALLOFF   12.0f
#define MINE_SOUND_RANGE      50.0f

void CEnergyMine_OnPrecache(CDLLEntityClass *pdec, INDEX iUser)
{
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_GRENADE);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_EXPLOSIONSTAIN);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_SHOCKWAVE);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_GRENADE_PLANE);
  pdec->PrecacheModel(MODEL_MINE);
  pdec->PrecacheTexture(TEXTURE_MINE);
}
%}

class CEnergyMine : CMovableModelEntity {
name      "EnergyMine";
thumbnail "";
features  "ImplementsOnPrecache", "CanBePredictable";

properties:
  1 CEntityPointer m_penLauncher,     // who dropped the mine
  2 FLOAT m_tmArmed = 0.0f,           // when the mine starts reacting to players
  3 FLOAT m_fSpeed  = 0.0f,           // initial forward speed

{
  CLightSource m_lsLightSource;
}

components:
  1 class   CLASS_BASIC_EFFECT  "Classes\\BasicEffect.ecl",
 10 model   MODEL_MINE          "Models\\Weapons\\Mine\\Mine.mdl",
 11 texture TEXTURE_MINE        "Models\\Weapons\\Mine\\Mine.tex",

functions:

  // dynamic light of the mine
  CLightSource *GetLightSource(void)
  {
    if (!IsPredictor()) {
      return &m_lsLightSource;
    } else {
      return NULL;
    }
  }

  // light sources are not saved, so restore it after loading
  void Read_t(CTStream *istr)
  {
    CMovableModelEntity::Read_t(istr);
    SetupLightSource();
  }

  void SetupLightSource(void)
  {
    CLightSource lsNew;
    lsNew.ls_ulFlags = LSF_NONPERSISTENT|LSF_DYNAMIC;
    lsNew.ls_rHotSpot = 0.1f;
    lsNew.ls_rFallOff = 1.0f;
    lsNew.ls_colColor = 0x1F1F1F00;
    lsNew.ls_plftLensFlare = &_lftYellowStarRedRingFar;
    lsNew.ls_ubPolygonalMask = 0;
    lsNew.ls_paoLightAnimation = NULL;

    m_lsLightSource.ls_penEntity = this;
    m_lsLightSource.SetLightSource(lsNew);
  }

  void InitializeMine(void)
  {
    InitAsModel();
    SetPhysicsFlags(EPF_MODEL_BOUNCING|EPF_ORIENTEDBYGRAVITY);
    SetCollisionFlags(ECF_ENERGYMINE);
    GetModelObject()->StretchModel(FLOAT3D(1.0f, 1.0f, 1.0f));
    ChangeCollisionBoxIndexNow(MINE_COLLISION_BOX_WIDE);
    ModelChangeNotify();
    SetModel(MODEL_MINE);
    SetModelMainTexture(TEXTURE_MINE);

    // throw it
    LaunchAsFreeProjectile(FLOAT3D(0.0f, 0.0f, -m_fSpeed), (CMovableEntity*)(CEntity*)m_penLauncher);
    SetDesiredRotation(ANGLE3D(0, 0, 0));
    en_fJumpControlMultiplier = 0.0f;
    en_fBounceDampNormal   = 0.7f;
    en_fBounceDampParallel = 0.7f;
    en_fCollisionSpeedLimit = 45.0f;
    en_fCollisionDamageFactor = 5.0f;
    SetHealth(MINE_HEALTH);
  }

  void SpawnEffect(const CPlacement3D &plEffect, const ESpawnEffect &eSpawnEffect)
  {
    CEntityPointer penEffect = CreateEntity(plEffect, CLASS_BASIC_EFFECT);
    penEffect->Initialize(eSpawnEffect);
  }

  // visual part of the explosion (same as a grenade)
  void ExplosionEffects(void)
  {
    ESpawnEffect ese;
    FLOAT3D vPoint;
    FLOATplane3D vPlaneNormal;
    FLOAT fDistanceToEdge;

    ese.colMuliplier = C_WHITE|CT_OPAQUE;
    ese.betType = BET_GRENADE;
    ese.vStretch = FLOAT3D(1,1,1);
    SpawnEffect(GetPlacement(), ese);
    // spawn sound event in range
    if (IsDerivedFromClass(m_penLauncher, "Player")) {
      SpawnRangeSound(m_penLauncher, this, SNDT_PLAYER, MINE_SOUND_RANGE);
    }

    // on plane
    if (GetNearestPolygon(vPoint, vPlaneNormal, fDistanceToEdge)) {
      if ((vPoint-GetPlacement().pl_PositionVector).Length() < 3.5f) {
        // wall stain
        ese.betType = BET_EXPLOSIONSTAIN;
        ese.vNormal = FLOAT3D(vPlaneNormal);
        SpawnEffect(CPlacement3D(vPoint, ANGLE3D(0, 0, 0)), ese);
        // shock wave
        ese.betType = BET_SHOCKWAVE;
        ese.vNormal = FLOAT3D(vPlaneNormal);
        SpawnEffect(CPlacement3D(vPoint, ANGLE3D(0, 0, 0)), ese);
        // second explosion on plane
        ese.betType = BET_GRENADE_PLANE;
        ese.vNormal = FLOAT3D(vPlaneNormal);
        SpawnEffect(CPlacement3D(vPoint+ese.vNormal/50.0f, ANGLE3D(0, 0, 0)), ese);
      }
    }
  }

  // damage part of the explosion
  void InflictExplosionDamage(void)
  {
    const FLOAT3D &vPos = GetPlacement().pl_PositionVector;
    InflictRangeDamage(m_penLauncher, DMT_CANNONBALL_EXPLOSION, MINE_DAMAGE, vPos,
                       MINE_DAMAGE_HOTSPOT, MINE_DAMAGE_FALLOFF);
    // let enemies hear it
    ESound eSound;
    eSound.EsndtSound = SNDT_EXPLOSION;
    eSound.penTarget = m_penLauncher;
    SendEventInRange(eSound, FLOATaabbox3D(vPos, 50.0f));
  }

procedures:

  // wait until something sets the mine off
  WaitForDetonation()
  {
    wait() {
      on (EBegin) : { resume; }
      // detonated by the owner (Minelayer secondary fire) or by a trigger
      on (EStart) : {
        InflictExplosionDamage();
        stop;
      }
      on (ETouch eTouch) : {
        // landed - from now on it reacts to players
        if (eTouch.penOther->GetRenderType() & RT_BRUSH) {
          m_tmArmed = 0.0f;
          resume;
        }
        if (_pTimer->CurrentTick() > m_tmArmed && IsDerivedFromClass(eTouch.penOther, "Player")) {
          InflictExplosionDamage();
          stop;
        }
        resume;
      }
      // shot down
      on (EDeath) : {
        InflictExplosionDamage();
        stop;
      }
    }
    return EEnd();
  }

  Main(EDropEnergyMine eDrop)
  {
    m_penLauncher = eDrop.penLauncher;
    m_fSpeed = eDrop.fSpeed;

    InitializeMine();
    SetupLightSource();
    m_tmArmed = _pTimer->CurrentTick() + MINE_ARM_DELAY;

    autocall WaitForDetonation() EEnd;

    ExplosionEffects();

    // tell the owner that this mine is gone
    EBlowUpEnergyMine eBlowUp;
    eBlowUp.penMine = this;
    if (m_penLauncher!=NULL) {
      m_penLauncher->SendEvent(eBlowUp);
    }

    Destroy();
    return;
  }
};
