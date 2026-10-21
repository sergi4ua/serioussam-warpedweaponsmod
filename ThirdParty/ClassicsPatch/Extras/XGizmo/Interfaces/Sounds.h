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

#ifndef XGIZMO_INCL_SOUNDSINTERFACE_H
#define XGIZMO_INCL_SOUNDSINTERFACE_H

#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Sound/SoundData.h>

// Interface of methods for sounds
namespace ISounds {

// Set playback offset of a sound object, since CSoundObject::SetOffset() disables this functionality
inline void SetOffset(CSoundObject &so, FLOAT fOffsetLeft, FLOAT fOffsetRight) {
  // Synchronize access to sounds
  CTSingleLock slSounds(&_pSound->sl_csSound, TRUE);

  // Get prediction tail
  #define EVENT_SOUNDSETOFFSET 0x0103
  CSoundObject *psoTail = so.GetPredictionTail(EVENT_SOUNDSETOFFSET, 0);

  // Event is predicted
  if (psoTail == NULL) return;

  // Sound isn't playing
  if (psoTail->so_pCsdLink == NULL) return;

  // Safety checks
  ASSERT(fOffsetLeft >= 0.0f && fOffsetRight >= 0.0f);

  if (fOffsetLeft < 0.0f) {
    CPrintF("BUG: Trying to set negative left offset (%.2g) in sound '%s' !\n", fOffsetLeft, psoTail->so_pCsdLink->GetName().str_String);
    fOffsetLeft = 0.0f;
  }

  if (fOffsetRight < 0.0f) {
    CPrintF("BUG: Trying to set negative right offset (%.2g) in sound '%s' !\n", fOffsetRight, psoTail->so_pCsdLink->GetName().str_String);
    fOffsetRight = 0.0f;
  }

  psoTail->so_fLeftOffset  = psoTail->so_pCsdLink->sd_wfeFormat.nSamplesPerSec * fOffsetLeft;
  psoTail->so_fRightOffset = psoTail->so_pCsdLink->sd_wfeFormat.nSamplesPerSec * fOffsetRight;
};

}; // namespace

#endif
