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

#ifndef XGIZMO_INCL_VANILLAEVENTS_H
#define XGIZMO_INCL_VANILLAEVENTS_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Entities/EntityEvent.h>

// [Cecil] NOTE: Define 'VANILLA_EVENTS_ENTITY_ID' before including this file to use entity IDs instead of pointers
#ifdef VANILLA_EVENTS_ENTITY_ID
  typedef ULONG CVanillaEventEntity;
#else
  typedef CEntityPointer CVanillaEventEntity;
#endif

#define CLEAR_TO_DEFAULT(_EventClass) inline void ClearToDefault(_EventClass &e) { e = _EventClass(); }
#define DEFINE_MAKE_COPY(_EventClass) CEntityEvent *MakeCopy(void) { return new _EventClass(*this); }

// Trigger events

// Stop event
static const SLONG EVENTCODE_VNL_EStop = 0x00000000;
class VNL_EStop : public CEntityEvent {
  public:
    VNL_EStop() : CEntityEvent(EVENTCODE_VNL_EStop) {};
    DEFINE_MAKE_COPY(VNL_EStop);
};
CLEAR_TO_DEFAULT(VNL_EStop);

// Start event
static const SLONG EVENTCODE_VNL_EStart = 0x00000001;
class VNL_EStart : public CEntityEvent {
  public:
    CVanillaEventEntity penCaused;

    VNL_EStart() : CEntityEvent(EVENTCODE_VNL_EStart) {
      ClearToDefault(penCaused);
    };

    DEFINE_MAKE_COPY(VNL_EStart);
};
CLEAR_TO_DEFAULT(VNL_EStart);

// Activate event
static const SLONG EVENTCODE_VNL_EActivate = 0x00000002;
class VNL_EActivate : public CEntityEvent {
  public:
    VNL_EActivate() : CEntityEvent(EVENTCODE_VNL_EActivate) {};
    DEFINE_MAKE_COPY(VNL_EActivate);
};
CLEAR_TO_DEFAULT(VNL_EActivate);

// Deactivate event
static const SLONG EVENTCODE_VNL_EDeactivate = 0x00000003;
class VNL_EDeactivate : public CEntityEvent {
  public:
    VNL_EDeactivate() : CEntityEvent(EVENTCODE_VNL_EDeactivate) {};
    DEFINE_MAKE_COPY(VNL_EDeactivate);
};
CLEAR_TO_DEFAULT(VNL_EDeactivate);

// Environment Start event
static const SLONG EVENTCODE_VNL_EEnvironmentStart = 0x00000004;
class VNL_EEnvironmentStart : public CEntityEvent {
  public:
    VNL_EEnvironmentStart() : CEntityEvent(EVENTCODE_VNL_EEnvironmentStart) {};
    DEFINE_MAKE_COPY(VNL_EEnvironmentStart);
};
CLEAR_TO_DEFAULT(VNL_EEnvironmentStart);

// Environment Stop event
static const SLONG EVENTCODE_VNL_EEnvironmentStop = 0x00000005;
class VNL_EEnvironmentStop : public CEntityEvent {
  public:
    VNL_EEnvironmentStop() : CEntityEvent(EVENTCODE_VNL_EEnvironmentStop) {};
    DEFINE_MAKE_COPY(VNL_EEnvironmentStop);
};
CLEAR_TO_DEFAULT(VNL_EEnvironmentStop);

// End event
static const SLONG EVENTCODE_VNL_EEnd = 0x00000006;
class VNL_EEnd : public CEntityEvent {
  public:
    VNL_EEnd() : CEntityEvent(EVENTCODE_VNL_EEnd) {};
    DEFINE_MAKE_COPY(VNL_EEnd);
};
CLEAR_TO_DEFAULT(VNL_EEnd);

// Trigger event
static const SLONG EVENTCODE_VNL_ETrigger = 0x00000007;
class VNL_ETrigger : public CEntityEvent {
  public:
    CVanillaEventEntity penCaused;

    VNL_ETrigger() : CEntityEvent(EVENTCODE_VNL_ETrigger) {
      ClearToDefault(penCaused);
    };

    DEFINE_MAKE_COPY(VNL_ETrigger);
};
CLEAR_TO_DEFAULT(VNL_ETrigger);

// Teleport Moving Brush event
static const SLONG EVENTCODE_VNL_ETeleportMovingBrush = 0x00000008;
class VNL_ETeleportMovingBrush : public CEntityEvent {
  public:
    VNL_ETeleportMovingBrush() : CEntityEvent(EVENTCODE_VNL_ETeleportMovingBrush) {};
    DEFINE_MAKE_COPY(VNL_ETeleportMovingBrush);
};
CLEAR_TO_DEFAULT(VNL_ETeleportMovingBrush);

// Reminder event
static const SLONG EVENTCODE_VNL_EReminder = 0x00000009;
class VNL_EReminder : public CEntityEvent {
  public:
    INDEX iValue;

    VNL_EReminder() : CEntityEvent(EVENTCODE_VNL_EReminder) {
      ClearToDefault(iValue);
    };

    DEFINE_MAKE_COPY(VNL_EReminder);
};
CLEAR_TO_DEFAULT(VNL_EReminder);

// Start Attack event
static const SLONG EVENTCODE_VNL_EStartAttack = 0x0000000a;
class VNL_EStartAttack : public CEntityEvent {
  public:
    VNL_EStartAttack() : CEntityEvent(EVENTCODE_VNL_EStartAttack) {};
    DEFINE_MAKE_COPY(VNL_EStartAttack);
};
CLEAR_TO_DEFAULT(VNL_EStartAttack);

// Stop Attack event
static const SLONG EVENTCODE_VNL_EStopAttack = 0x0000000b;
class VNL_EStopAttack : public CEntityEvent {
  public:
    VNL_EStopAttack() : CEntityEvent(EVENTCODE_VNL_EStopAttack) {};
    DEFINE_MAKE_COPY(VNL_EStopAttack);
};
CLEAR_TO_DEFAULT(VNL_EStopAttack);

// Stop Blindness event
static const SLONG EVENTCODE_VNL_EStopBlindness = 0x0000000c;
class VNL_EStopBlindness : public CEntityEvent {
  public:
    VNL_EStopBlindness() : CEntityEvent(EVENTCODE_VNL_EStopBlindness) {};
    DEFINE_MAKE_COPY(VNL_EStopBlindness);
};
CLEAR_TO_DEFAULT(VNL_EStopBlindness);

// Stop Deafness event
static const SLONG EVENTCODE_VNL_EStopDeafness = 0x0000000d;
class VNL_EStopDeafness : public CEntityEvent {
  public:
    VNL_EStopDeafness() : CEntityEvent(EVENTCODE_VNL_EStopDeafness) {};
    DEFINE_MAKE_COPY(VNL_EStopDeafness);
};
CLEAR_TO_DEFAULT(VNL_EStopDeafness);

// Receive Score event
static const SLONG EVENTCODE_VNL_EReceiveScore = 0x0000000e;
class VNL_EReceiveScore : public CEntityEvent {
  public:
    INDEX iPoints;

    VNL_EReceiveScore() : CEntityEvent(EVENTCODE_VNL_EReceiveScore) {
      ClearToDefault(iPoints);
    };

    DEFINE_MAKE_COPY(VNL_EReceiveScore);
};
CLEAR_TO_DEFAULT(VNL_EReceiveScore);

// Killed Enemy event
static const SLONG EVENTCODE_VNL_EKilledEnemy = 0x0000000f;
class VNL_EKilledEnemy : public CEntityEvent {
  public:
    VNL_EKilledEnemy() : CEntityEvent(EVENTCODE_VNL_EKilledEnemy) {};
    DEFINE_MAKE_COPY(VNL_EKilledEnemy);
};
CLEAR_TO_DEFAULT(VNL_EKilledEnemy);

// Secret Found event
static const SLONG EVENTCODE_VNL_ESecretFound = 0x00000010;
class VNL_ESecretFound : public CEntityEvent {
  public:
    VNL_ESecretFound() : CEntityEvent(EVENTCODE_VNL_ESecretFound) {};
    DEFINE_MAKE_COPY(VNL_ESecretFound);
};
CLEAR_TO_DEFAULT(VNL_ESecretFound);

// Other global events

// Notify about a sound from something
static const SLONG EVENTCODE_VNL_ESound = 0x00000011;
class VNL_ESound : public CEntityEvent {
  public:
    INDEX EsndtSound; // SoundType enum
    CVanillaEventEntity penTarget;

    VNL_ESound() : CEntityEvent(EVENTCODE_VNL_ESound) {
      ClearToDefault(EsndtSound);
      ClearToDefault(penTarget);
    };

    DEFINE_MAKE_COPY(VNL_ESound);
};
CLEAR_TO_DEFAULT(VNL_ESound);

// Trigger ScrollHolder
static const SLONG EVENTCODE_VNL_EScroll = 0x00000012;
class VNL_EScroll : public CEntityEvent {
  public:
    BOOL bStart;
    CVanillaEventEntity penSender;

    VNL_EScroll() : CEntityEvent(EVENTCODE_VNL_EScroll) {
      ClearToDefault(bStart);
      ClearToDefault(penSender);
    };

    DEFINE_MAKE_COPY(VNL_EScroll);
};
CLEAR_TO_DEFAULT(VNL_EScroll);

// Trigger TextFXHolder
static const SLONG EVENTCODE_VNL_ETextFX = 0x00000013;
class VNL_ETextFX : public CEntityEvent {
  public:
    BOOL bStart;
    CVanillaEventEntity penSender;

    VNL_ETextFX() : CEntityEvent(EVENTCODE_VNL_ETextFX) {
      ClearToDefault(bStart);
      ClearToDefault(penSender);
    };

    DEFINE_MAKE_COPY(VNL_ETextFX);
};
CLEAR_TO_DEFAULT(VNL_ETextFX);

// Trigger HudPicHolder
static const SLONG EVENTCODE_VNL_EHudPicFX = 0x00000014;
class VNL_EHudPicFX : public CEntityEvent {
  public:
    BOOL bStart;
    CVanillaEventEntity penSender;

    VNL_EHudPicFX() : CEntityEvent(EVENTCODE_VNL_EHudPicFX) {
      ClearToDefault(bStart);
      ClearToDefault(penSender);
    };

    DEFINE_MAKE_COPY(VNL_EHudPicFX);
};
CLEAR_TO_DEFAULT(VNL_EHudPicFX);

// Trigger CreditsHolder
static const SLONG EVENTCODE_VNL_ECredits = 0x00000015;
class VNL_ECredits : public CEntityEvent {
  public:
    BOOL bStart;
    CVanillaEventEntity penSender;

    VNL_ECredits() : CEntityEvent(EVENTCODE_VNL_ECredits) {
      ClearToDefault(bStart);
      ClearToDefault(penSender);
    };

    DEFINE_MAKE_COPY(VNL_ECredits);
};
CLEAR_TO_DEFAULT(VNL_ECredits);

// Display center message
static const SLONG EVENTCODE_VNL_ECenterMessage = 0x00000016;
class VNL_ECenterMessage : public CEntityEvent {
  public:
    CTString strMessage;
    TIME tmLength;
    INDEX mssSound; // MessageSound enum

    VNL_ECenterMessage() : CEntityEvent(EVENTCODE_VNL_ECenterMessage) {
      ClearToDefault(strMessage);
      ClearToDefault(tmLength);
      ClearToDefault(mssSound);
    };

    DEFINE_MAKE_COPY(VNL_ECenterMessage);
};
CLEAR_TO_DEFAULT(VNL_ECenterMessage);

// Receive computer message
static const SLONG EVENTCODE_VNL_EComputerMessage = 0x00000017;
class VNL_EComputerMessage : public CEntityEvent {
  public:
    CTFileName fnmMessage;

    VNL_EComputerMessage() : CEntityEvent(EVENTCODE_VNL_EComputerMessage) {
      ClearToDefault(fnmMessage);
    };

    DEFINE_MAKE_COPY(VNL_EComputerMessage);
};
CLEAR_TO_DEFAULT(VNL_EComputerMessage);

// Play voice message
static const SLONG EVENTCODE_VNL_EVoiceMessage = 0x00000018;
class VNL_EVoiceMessage : public CEntityEvent {
  public:
    CTFileName fnmMessage;

    VNL_EVoiceMessage() : CEntityEvent(EVENTCODE_VNL_EVoiceMessage) {
      ClearToDefault(fnmMessage);
    };

    DEFINE_MAKE_COPY(VNL_EVoiceMessage);
};
CLEAR_TO_DEFAULT(VNL_EVoiceMessage);

// Get hit by the spaceship's beam
static const SLONG EVENTCODE_VNL_EHitBySpaceShipBeam = 0x00000019;
class VNL_EHitBySpaceShipBeam : public CEntityEvent {
  public:
    VNL_EHitBySpaceShipBeam() : CEntityEvent(EVENTCODE_VNL_EHitBySpaceShipBeam) {};
    DEFINE_MAKE_COPY(VNL_EHitBySpaceShipBeam);
};
CLEAR_TO_DEFAULT(VNL_EHitBySpaceShipBeam);

// Specific entity events

// AmmoItem: Receive ammo
static const SLONG EVENTCODE_VNL_EAmmoItem = 0x03230000;
class VNL_EAmmoItem : public CEntityEvent {
  public:
    INDEX EaitType; // AmmoItemType enum
    INDEX iQuantity;

    VNL_EAmmoItem() : CEntityEvent(EVENTCODE_VNL_EAmmoItem) {
      ClearToDefault(EaitType);
      ClearToDefault(iQuantity);
    };

    DEFINE_MAKE_COPY(VNL_EAmmoItem);
};
CLEAR_TO_DEFAULT(VNL_EAmmoItem);

// AmmoPack: Receive ammo pack
static const SLONG EVENTCODE_VNL_EAmmoPackItem = 0x03260000;
class VNL_EAmmoPackItem : public CEntityEvent {
  public:
    INDEX iShells;
    INDEX iBullets;
    INDEX iRockets;
    INDEX iGrenades;
    INDEX iNapalm;
    INDEX iElectricity;
    INDEX iIronBalls;
    INDEX iSniperBullets;

    VNL_EAmmoPackItem() : CEntityEvent(EVENTCODE_VNL_EAmmoPackItem) {
      ClearToDefault(iShells);
      ClearToDefault(iBullets);
      ClearToDefault(iRockets);
      ClearToDefault(iGrenades);
      ClearToDefault(iNapalm);
      ClearToDefault(iElectricity);
      ClearToDefault(iIronBalls);
      ClearToDefault(iSniperBullets);
    };

    DEFINE_MAKE_COPY(VNL_EAmmoPackItem);
};
CLEAR_TO_DEFAULT(VNL_EAmmoPackItem);

// ArmorItem: Receive armor
static const SLONG EVENTCODE_VNL_EArmor = 0x03240000;
class VNL_EArmor : public CEntityEvent {
  public:
    FLOAT fArmor;
    BOOL bOverTopArmor;

    VNL_EArmor() : CEntityEvent(EVENTCODE_VNL_EArmor) {
      ClearToDefault(fArmor);
      ClearToDefault(bOverTopArmor);
    };

    DEFINE_MAKE_COPY(VNL_EArmor);
};
CLEAR_TO_DEFAULT(VNL_EArmor);

// HealthItem: Receive health
static const SLONG EVENTCODE_VNL_EHealth = 0x03210000;
class VNL_EHealth : public CEntityEvent {
  public:
    FLOAT fHealth;
    BOOL bOverTopHealth;

    VNL_EHealth() : CEntityEvent(EVENTCODE_VNL_EHealth) {
      ClearToDefault(fHealth);
      ClearToDefault(bOverTopHealth);
    };

    DEFINE_MAKE_COPY(VNL_EHealth);
};
CLEAR_TO_DEFAULT(VNL_EHealth);

// KeyItem: Receive key
static const SLONG EVENTCODE_VNL_EKey = 0x03250000;
class VNL_EKey : public CEntityEvent {
  public:
    INDEX kitType; // KeyItemType enum

    VNL_EKey() : CEntityEvent(EVENTCODE_VNL_EKey) {
      ClearToDefault(kitType);
    };

    DEFINE_MAKE_COPY(VNL_EKey);
};
CLEAR_TO_DEFAULT(VNL_EKey);

// MessageItem: Receive message
static const SLONG EVENTCODE_VNL_EMessageItem = 0x03270000;
class VNL_EMessageItem : public CEntityEvent {
  public:
    CTFileName fnmMessage;

    VNL_EMessageItem() : CEntityEvent(EVENTCODE_VNL_EMessageItem) {
      ClearToDefault(fnmMessage);
    };

    DEFINE_MAKE_COPY(VNL_EMessageItem);
};
CLEAR_TO_DEFAULT(VNL_EMessageItem);

// PowerUpItem: Receive powerup
static const SLONG EVENTCODE_VNL_EPowerUp = 0x03280000;
class VNL_EPowerUp : public CEntityEvent {
  public:
    INDEX puitType; // PowerUpItemType enum

    VNL_EPowerUp() : CEntityEvent(EVENTCODE_VNL_EPowerUp) {
      ClearToDefault(puitType);
    };

    DEFINE_MAKE_COPY(VNL_EPowerUp);
};
CLEAR_TO_DEFAULT(VNL_EPowerUp);

// WeaponItem: Receive weapon
static const SLONG EVENTCODE_VNL_EWeaponItem = 0x03220000;
class VNL_EWeaponItem : public CEntityEvent {
  public:
    INDEX iWeapon;
    INDEX iAmmo;
    BOOL bDropped;

    VNL_EWeaponItem() : CEntityEvent(EVENTCODE_VNL_EWeaponItem) {
      ClearToDefault(iWeapon);
      ClearToDefault(iAmmo);
      ClearToDefault(bDropped);
    };

    DEFINE_MAKE_COPY(VNL_EWeaponItem);
};
CLEAR_TO_DEFAULT(VNL_EWeaponItem);

// EnemyBase: Restart attack
static const SLONG EVENTCODE_VNL_ERestartAttack = 0x01360000;
class VNL_ERestartAttack : public CEntityEvent {
  public:
    VNL_ERestartAttack() : CEntityEvent(EVENTCODE_VNL_ERestartAttack) {};
    DEFINE_MAKE_COPY(VNL_ERestartAttack);
};
CLEAR_TO_DEFAULT(VNL_ERestartAttack);

// EnemyBase: Reconsider behavior
static const SLONG EVENTCODE_VNL_EReconsiderBehavior = 0x01360001;
class VNL_EReconsiderBehavior : public CEntityEvent {
  public:
    VNL_EReconsiderBehavior() : CEntityEvent(EVENTCODE_VNL_EReconsiderBehavior) {};
    DEFINE_MAKE_COPY(VNL_EReconsiderBehavior);
};
CLEAR_TO_DEFAULT(VNL_EReconsiderBehavior);

// EnemyBase: Force wound animation
static const SLONG EVENTCODE_VNL_EForceWound = 0x01360002;
class VNL_EForceWound : public CEntityEvent {
  public:
    VNL_EForceWound() : CEntityEvent(EVENTCODE_VNL_EForceWound) {};
    DEFINE_MAKE_COPY(VNL_EForceWound);
};
CLEAR_TO_DEFAULT(VNL_EForceWound);

// PlayerWeapons: Select new weapon
static const SLONG EVENTCODE_VNL_ESelectWeapon = 0x01920001;
class VNL_ESelectWeapon : public CEntityEvent {
  public:
    INDEX iWeapon;

    VNL_ESelectWeapon() : CEntityEvent(EVENTCODE_VNL_ESelectWeapon) {
      ClearToDefault(iWeapon);
    };

    DEFINE_MAKE_COPY(VNL_ESelectWeapon);
};
CLEAR_TO_DEFAULT(VNL_ESelectWeapon);

// PlayerWeapons: Play boring animation
static const SLONG EVENTCODE_VNL_EBoringWeapon = 0x01920002;
class VNL_EBoringWeapon : public CEntityEvent {
  public:
    VNL_EBoringWeapon() : CEntityEvent(EVENTCODE_VNL_EBoringWeapon) {};
    DEFINE_MAKE_COPY(VNL_EBoringWeapon);
};
CLEAR_TO_DEFAULT(VNL_EBoringWeapon);

// PlayerWeapons: Start firing current weapon
static const SLONG EVENTCODE_VNL_EFireWeapon = 0x01920003;
class VNL_EFireWeapon : public CEntityEvent {
  public:
    VNL_EFireWeapon() : CEntityEvent(EVENTCODE_VNL_EFireWeapon) {};
    DEFINE_MAKE_COPY(VNL_EFireWeapon);
};
CLEAR_TO_DEFAULT(VNL_EFireWeapon);

// PlayerWeapons: Stop firing current weapon
static const SLONG EVENTCODE_VNL_EReleaseWeapon = 0x01920004;
class VNL_EReleaseWeapon : public CEntityEvent {
  public:
    VNL_EReleaseWeapon() : CEntityEvent(EVENTCODE_VNL_EReleaseWeapon) {};
    DEFINE_MAKE_COPY(VNL_EReleaseWeapon);
};
CLEAR_TO_DEFAULT(VNL_EReleaseWeapon);

// PlayerWeapons: Reload current weapon
static const SLONG EVENTCODE_VNL_EReloadWeapon = 0x01920005;
class VNL_EReloadWeapon : public CEntityEvent {
  public:
    VNL_EReloadWeapon() : CEntityEvent(EVENTCODE_VNL_EReloadWeapon) {};
    DEFINE_MAKE_COPY(VNL_EReloadWeapon);
};
CLEAR_TO_DEFAULT(VNL_EReloadWeapon);

// PlayerWeapons: When the weapon has been changed
static const SLONG EVENTCODE_VNL_EWeaponChanged = 0x01920006;
class VNL_EWeaponChanged : public CEntityEvent {
  public:
    VNL_EWeaponChanged() : CEntityEvent(EVENTCODE_VNL_EWeaponChanged) {};
    DEFINE_MAKE_COPY(VNL_EWeaponChanged);
};
CLEAR_TO_DEFAULT(VNL_EWeaponChanged);

// Specific initialization events

// AirShockwave
static const SLONG EVENTCODE_VNL_EAirShockwave = 0x015d0000;
class VNL_EAirShockwave : public CEntityEvent {
  public:
    CVanillaEventEntity penLauncher;
    FLOAT fHeight;
    FLOAT fEndWidth;
    FLOAT fDuration;

    VNL_EAirShockwave() : CEntityEvent(EVENTCODE_VNL_EAirShockwave) {
      ClearToDefault(penLauncher);
      ClearToDefault(fHeight);
      ClearToDefault(fEndWidth);
      ClearToDefault(fDuration);
    };

    DEFINE_MAKE_COPY(VNL_EAirShockwave);
};
CLEAR_TO_DEFAULT(VNL_EAirShockwave);

// AirWave
static const SLONG EVENTCODE_VNL_EAirWave = 0x01fe0000;
class VNL_EAirWave : public CEntityEvent {
  public:
    CVanillaEventEntity penLauncher;

    VNL_EAirWave() : CEntityEvent(EVENTCODE_VNL_EAirWave) {
      ClearToDefault(penLauncher);
    };

    DEFINE_MAKE_COPY(VNL_EAirWave);
};
CLEAR_TO_DEFAULT(VNL_EAirWave);

// BasicEffect
static const SLONG EVENTCODE_VNL_ESpawnEffect = 0x02590000;
class VNL_ESpawnEffect : public CEntityEvent {
  public:
    INDEX betType; // BasicEffectType enum
    FLOAT3D vNormal;
    FLOAT3D vDirection;
    FLOAT3D vStretch;
    COLOR colMuliplier;

    VNL_ESpawnEffect() : CEntityEvent(EVENTCODE_VNL_ESpawnEffect) {
      ClearToDefault(betType);
      ClearToDefault(vNormal);
      ClearToDefault(vDirection);
      ClearToDefault(vStretch);
      ClearToDefault(colMuliplier);
    };

    DEFINE_MAKE_COPY(VNL_ESpawnEffect);
};
CLEAR_TO_DEFAULT(VNL_ESpawnEffect);

// BloodSpray
static const SLONG EVENTCODE_VNL_ESpawnSpray = 0x025b0000;
class VNL_ESpawnSpray : public CEntityEvent {
  public:
    INDEX sptType; // SprayParticlesType enum
    FLOAT fDamagePower;
    FLOAT fSizeMultiplier;
    FLOAT3D vDirection;
    CVanillaEventEntity penOwner;
    COLOR colCentralColor;
    FLOAT fLaunchPower;
    COLOR colBurnColor;

    VNL_ESpawnSpray() : CEntityEvent(EVENTCODE_VNL_ESpawnSpray) {
      ClearToDefault(sptType);
      ClearToDefault(fDamagePower);
      ClearToDefault(fSizeMultiplier);
      ClearToDefault(vDirection);
      ClearToDefault(penOwner);
      ClearToDefault(colCentralColor);
      ClearToDefault(fLaunchPower);
      ClearToDefault(colBurnColor);
    };

    DEFINE_MAKE_COPY(VNL_ESpawnSpray);
};
CLEAR_TO_DEFAULT(VNL_ESpawnSpray);

// Bullet
static const SLONG EVENTCODE_VNL_EBulletInit = 0x01f60000;
class VNL_EBulletInit : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;
    FLOAT fDamage;

    VNL_EBulletInit() : CEntityEvent(EVENTCODE_VNL_EBulletInit) {
      ClearToDefault(penOwner);
      ClearToDefault(fDamage);
    };

    DEFINE_MAKE_COPY(VNL_EBulletInit);
};
CLEAR_TO_DEFAULT(VNL_EBulletInit);

// CannonBall
static const SLONG EVENTCODE_VNL_ELaunchCannonBall = 0x01fa0000;
class VNL_ELaunchCannonBall : public CEntityEvent {
  public:
    CVanillaEventEntity penLauncher;
    INDEX cbtType; // CannonBallType enum
    FLOAT fLaunchPower;
    FLOAT fSize;

    VNL_ELaunchCannonBall() : CEntityEvent(EVENTCODE_VNL_ELaunchCannonBall) {
      ClearToDefault(penLauncher);
      ClearToDefault(cbtType);
      ClearToDefault(fLaunchPower);
      ClearToDefault(fSize);
    };

    DEFINE_MAKE_COPY(VNL_ELaunchCannonBall);
};
CLEAR_TO_DEFAULT(VNL_ELaunchCannonBall);

// CyborgBike
static const SLONG EVENTCODE_VNL_ECyborgBike = 0x014b0000;
class VNL_ECyborgBike : public CEntityEvent {
  public:
    FLOAT fSpeed;

    VNL_ECyborgBike() : CEntityEvent(EVENTCODE_VNL_ECyborgBike) {
      ClearToDefault(fSpeed);
    };

    DEFINE_MAKE_COPY(VNL_ECyborgBike);
};
CLEAR_TO_DEFAULT(VNL_ECyborgBike);

// Debris
static const SLONG EVENTCODE_VNL_ESpawnDebris = 0x025a0000;
class VNL_ESpawnDebris : public CEntityEvent {
  public:
    INDEX Eeibt; // EntityInfoBodyType enum
    CModelData *pmd;
    FLOAT fSize;
    CTextureData *ptd;
    CTextureData *ptdRefl;
    CTextureData *ptdSpec;
    CTextureData *ptdBump;
    INDEX iModelAnim;
    INDEX dptParticles; // DebrisParticlesType enum
    INDEX betStain; // BasicEffectType enum
    COLOR colDebris;
    BOOL bCustomShading;
    ANGLE3D aShadingDirection;
    COLOR colCustomAmbient;
    COLOR colCustomDiffuse;
    BOOL bImmaterialASAP;
    FLOAT fDustStretch;
    FLOAT3D vStretch;
    CVanillaEventEntity penFallFXPapa;

    VNL_ESpawnDebris() : CEntityEvent(EVENTCODE_VNL_ESpawnDebris) {
      ClearToDefault(Eeibt);
      ClearToDefault(pmd);
      ClearToDefault(fSize);
      ClearToDefault(ptd);
      ClearToDefault(ptdRefl);
      ClearToDefault(ptdSpec);
      ClearToDefault(ptdBump);
      ClearToDefault(iModelAnim);
      ClearToDefault(dptParticles);
      ClearToDefault(betStain);
      ClearToDefault(colDebris);
      ClearToDefault(bCustomShading);
      ClearToDefault(aShadingDirection);
      ClearToDefault(colCustomAmbient);
      ClearToDefault(colCustomDiffuse);
      ClearToDefault(bImmaterialASAP);
      ClearToDefault(fDustStretch);
      ClearToDefault(vStretch);
      ClearToDefault(penFallFXPapa);
    };

    DEFINE_MAKE_COPY(VNL_ESpawnDebris);
};
CLEAR_TO_DEFAULT(VNL_ESpawnDebris);

// DevilProjectile
static const SLONG EVENTCODE_VNL_EDevilProjectile = 0x01ff0000;
class VNL_EDevilProjectile : public CEntityEvent {
  public:
    CVanillaEventEntity penLauncher;
    CVanillaEventEntity penTarget;

    VNL_EDevilProjectile() : CEntityEvent(EVENTCODE_VNL_EDevilProjectile) {
      ClearToDefault(penLauncher);
      ClearToDefault(penTarget);
    };

    DEFINE_MAKE_COPY(VNL_EDevilProjectile);
};
CLEAR_TO_DEFAULT(VNL_EDevilProjectile);

// Effector
static const SLONG EVENTCODE_VNL_ESpawnEffector = 0x02600000;
class VNL_ESpawnEffector : public CEntityEvent {
  public:
    INDEX eetType; // EffectorEffectType enum
    FLOAT3D vDamageDir;
    FLOAT3D vDestination;
    FLOAT tmLifeTime;
    FLOAT fSize;
    INDEX ctCount;
    CVanillaEventEntity penModel;
    CVanillaEventEntity penModel2;

    VNL_ESpawnEffector() : CEntityEvent(EVENTCODE_VNL_ESpawnEffector) {
      ClearToDefault(eetType);
      ClearToDefault(vDamageDir);
      ClearToDefault(vDestination);
      ClearToDefault(tmLifeTime);
      ClearToDefault(fSize);
      ClearToDefault(ctCount);
      ClearToDefault(penModel);
      ClearToDefault(penModel2);
    };

    DEFINE_MAKE_COPY(VNL_ESpawnEffector);
};
CLEAR_TO_DEFAULT(VNL_ESpawnEffector);

// Flame
static const SLONG EVENTCODE_VNL_EFlame = 0x01f80000;
class VNL_EFlame : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;
    CVanillaEventEntity penAttach;

    VNL_EFlame() : CEntityEvent(EVENTCODE_VNL_EFlame) {
      ClearToDefault(penOwner);
      ClearToDefault(penAttach);
    };

    DEFINE_MAKE_COPY(VNL_EFlame);
};
CLEAR_TO_DEFAULT(VNL_EFlame);

// LarvaOffspring
static const SLONG EVENTCODE_VNL_ELaunchLarvaOffspring = 0x01610000;
class VNL_ELaunchLarvaOffspring : public CEntityEvent {
  public:
    CVanillaEventEntity penLauncher;

    VNL_ELaunchLarvaOffspring() : CEntityEvent(EVENTCODE_VNL_ELaunchLarvaOffspring) {
      ClearToDefault(penLauncher);
    };

    DEFINE_MAKE_COPY(VNL_ELaunchLarvaOffspring);
};
CLEAR_TO_DEFAULT(VNL_ELaunchLarvaOffspring);

// PlayerAnimator
static const SLONG EVENTCODE_VNL_EAnimatorInit = 0x01960000;
class VNL_EAnimatorInit : public CEntityEvent {
  public:
    CVanillaEventEntity penPlayer;

    VNL_EAnimatorInit() : CEntityEvent(EVENTCODE_VNL_EAnimatorInit) {
      ClearToDefault(penPlayer);
    };

    DEFINE_MAKE_COPY(VNL_EAnimatorInit);
};
CLEAR_TO_DEFAULT(VNL_EAnimatorInit);

// PlayerView
static const SLONG EVENTCODE_VNL_EViewInit = 0x01930000;
class VNL_EViewInit : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;
    CVanillaEventEntity penCamera;
    INDEX vtView; // ViewType enum
    BOOL bDeathFixed;

    VNL_EViewInit() : CEntityEvent(EVENTCODE_VNL_EViewInit) {
      ClearToDefault(penOwner);
      ClearToDefault(penCamera);
      ClearToDefault(vtView);
      ClearToDefault(bDeathFixed);
    };

    DEFINE_MAKE_COPY(VNL_EViewInit);
};
CLEAR_TO_DEFAULT(VNL_EViewInit);

// PlayerWeapons
static const SLONG EVENTCODE_VNL_EWeaponsInit = 0x01920000;
class VNL_EWeaponsInit : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;

    VNL_EWeaponsInit() : CEntityEvent(EVENTCODE_VNL_EWeaponsInit) {
      ClearToDefault(penOwner);
    };

    DEFINE_MAKE_COPY(VNL_EWeaponsInit);
};
CLEAR_TO_DEFAULT(VNL_EWeaponsInit);

// PlayerWeaponsEffects
static const SLONG EVENTCODE_VNL_EWeaponEffectInit = 0x01950000;
class VNL_EWeaponEffectInit : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;
    INDEX EwetEffect; // WeaponEffectType enum

    VNL_EWeaponEffectInit() : CEntityEvent(EVENTCODE_VNL_EWeaponEffectInit) {
      ClearToDefault(penOwner);
      ClearToDefault(EwetEffect);
    };

    DEFINE_MAKE_COPY(VNL_EWeaponEffectInit);
};
CLEAR_TO_DEFAULT(VNL_EWeaponEffectInit);

// Projectile
static const SLONG EVENTCODE_VNL_ELaunchProjectile = 0x01f50000;
class VNL_ELaunchProjectile : public CEntityEvent {
  public:
    CVanillaEventEntity penLauncher;
    INDEX prtType; // ProjectileType enum
    FLOAT fSpeed;
    FLOAT fStretch;

    VNL_ELaunchProjectile() : CEntityEvent(EVENTCODE_VNL_ELaunchProjectile) {
      ClearToDefault(penLauncher);
      ClearToDefault(prtType);
      ClearToDefault(fSpeed);
      ClearToDefault(fStretch);
    };

    DEFINE_MAKE_COPY(VNL_ELaunchProjectile);
};
CLEAR_TO_DEFAULT(VNL_ELaunchProjectile);

// Reminder
static const SLONG EVENTCODE_VNL_EReminderInit = 0x02bf0000;
class VNL_EReminderInit : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;
    FLOAT fWaitTime;
    INDEX iValue;

    VNL_EReminderInit() : CEntityEvent(EVENTCODE_VNL_EReminderInit) {
      ClearToDefault(penOwner);
      ClearToDefault(fWaitTime);
      ClearToDefault(iValue);
    };

    DEFINE_MAKE_COPY(VNL_EReminderInit);
};
CLEAR_TO_DEFAULT(VNL_EReminderInit);

// SeriousBomb
static const SLONG EVENTCODE_VNL_ESeriousBomb = 0x01620000;
class VNL_ESeriousBomb : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;

    VNL_ESeriousBomb() : CEntityEvent(EVENTCODE_VNL_ESeriousBomb) {
      ClearToDefault(penOwner);
    };

    DEFINE_MAKE_COPY(VNL_ESeriousBomb);
};
CLEAR_TO_DEFAULT(VNL_ESeriousBomb);

// SpawnerProjectile
static const SLONG EVENTCODE_VNL_ESpawnerProjectile = 0x01fb0000;
class VNL_ESpawnerProjectile : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;
    CVanillaEventEntity penTemplate;

    VNL_ESpawnerProjectile() : CEntityEvent(EVENTCODE_VNL_ESpawnerProjectile) {
      ClearToDefault(penOwner);
      ClearToDefault(penTemplate);
    };

    DEFINE_MAKE_COPY(VNL_ESpawnerProjectile);
};
CLEAR_TO_DEFAULT(VNL_ESpawnerProjectile);

// Spinner
static const SLONG EVENTCODE_VNL_ESpinnerInit = 0x015c0000;
class VNL_ESpinnerInit : public CEntityEvent {
  public:
    CVanillaEventEntity penParent;
    CVanillaEventEntity penTwister;
    FLOAT3D vRotationAngle;
    FLOAT tmSpinTime;
    FLOAT fUpSpeed;
    BOOL bImpulse;
    FLOAT tmImpulseDuration;

    VNL_ESpinnerInit() : CEntityEvent(EVENTCODE_VNL_ESpinnerInit) {
      ClearToDefault(penParent);
      ClearToDefault(penTwister);
      ClearToDefault(vRotationAngle);
      ClearToDefault(tmSpinTime);
      ClearToDefault(fUpSpeed);
      ClearToDefault(bImpulse);
      ClearToDefault(tmImpulseDuration);
    };

    DEFINE_MAKE_COPY(VNL_ESpinnerInit);
};
CLEAR_TO_DEFAULT(VNL_ESpinnerInit);

// Twister
static const SLONG EVENTCODE_VNL_ETwister = 0x01fb0000;
class VNL_ETwister : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;
    FLOAT fSize;
    FLOAT fDuration;
    INDEX sgnSpinDir;
    BOOL bGrow;
    BOOL bMovingAllowed;

    VNL_ETwister() : CEntityEvent(EVENTCODE_VNL_ETwister) {
      ClearToDefault(penOwner);
      ClearToDefault(fSize);
      ClearToDefault(fDuration);
      ClearToDefault(sgnSpinDir);
      ClearToDefault(bGrow);
      ClearToDefault(bMovingAllowed);
    };

    DEFINE_MAKE_COPY(VNL_ETwister);
};
CLEAR_TO_DEFAULT(VNL_ETwister);

// Watcher
static const SLONG EVENTCODE_VNL_EWatcherInit = 0x02bc0000;
class VNL_EWatcherInit : public CEntityEvent {
  public:
    CVanillaEventEntity penOwner;

    VNL_EWatcherInit() : CEntityEvent(EVENTCODE_VNL_EWatcherInit) {
      ClearToDefault(penOwner);
    };

    DEFINE_MAKE_COPY(VNL_EWatcherInit);
};
CLEAR_TO_DEFAULT(VNL_EWatcherInit);

// Water
static const SLONG EVENTCODE_VNL_EWater = 0x01fc0000;
class VNL_EWater : public CEntityEvent {
  public:
    CVanillaEventEntity penLauncher;
    INDEX EwsSize; // WaterSize enum

    VNL_EWater() : CEntityEvent(EVENTCODE_VNL_EWater) {
      ClearToDefault(penLauncher);
      ClearToDefault(EwsSize);
    };

    DEFINE_MAKE_COPY(VNL_EWater);
};
CLEAR_TO_DEFAULT(VNL_EWater);

#endif
