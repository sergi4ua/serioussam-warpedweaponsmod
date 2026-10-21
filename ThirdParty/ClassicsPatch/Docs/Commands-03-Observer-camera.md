> Descriptions for commands that are modifiable through the **OPTIONS** -> **CLASSICS PATCH** -> **Observer camera & photo mode** menu.

# Camera properties
These commands are a part of the "CAM" system for detaching camera from the player for flying around the world.

- `ocam_iShowInfo` - Display current properties and default controls of the observer camera (`2` by default).
  - `0` - Disabled
  - `1` - Only relevant properties for playback and free-fly camera
  - `2` - Relevant properties and default controls for free-fly camera
- `ocam_bPlaybackSpeedControl` - Allow camera to change demo playback speed during recording playback (OFF by default).
- `ocam_bSmoothPlayback` - Make camera during recording playback move smoothly along a curve instead of stiffly shifting from one position to another.
- `ocam_fSmoothTension` - Tension value for smooth movement during recording playback. Values up to `1.0` control how much the camera will ease-in and ease-out from positions (`0.0` by default).

- `ocam_fFOV` - Current camera FOV during free-fly movement (`90.0` by default).
- `ocam_fSpeed` - Free-fly camera speed multiplier.
- `ocam_fTiltAngleMul` - Tilt angle multiplier for instant rotation or speed factor for smooth rotation (`1.0` by default).
- `ocam_fFOVChangeMul` - Multiply speed for changing the FOV using `ocam_bZoomIn` and `ocam_bZoomOut` buttons (`1.0` by default).
- `ocam_fSmoothMovement` - Factor for smooth camera movement. `1.0` and above make the camera move instantly without any acceleration or deceleration (`1.0` by default).
- `ocam_fSmoothRotation` - Factor for smooth camera rotation. `1.0` and above make the camera rotate instantly without any acceleration or deceleration (`1.0` by default).
- `ocam_fFollowDist` - Values starting from `0.0` make the free-fly camera automatically close in on the currently selected player if they're further from the camera than the set distance (`-1.0` by default).

# Camera controls
Commands for controling free-fly camera. These are not the same as the key binds in the actual settings but rather additional commands that can be manually added to common/player controls or modified externally by a script.

> [!NOTE]
> Old `cam_` commands can also be used as aliases for some `ocam_` commands but this feature is only supported by the custom mod from **Classics Patch**.

- `ocam_bDefaultControls` - Toggle usage of built-in controls for the free-fly camera. Should be disabled if control commands are being manually binded (ON by default).
- `ocam_bActive` - Dynamic toggling of free-fly camera during demo playback, while observing multiplayer games or while dead in Cooperative mode.

- `ocam_bTurnBankingLeft` - Tilt camera angle to the left. Snaps to 10 degrees if `ocam_fSmoothRotation` is set to `1.0`.
- `ocam_bTurnBankingRight` - Tilt camera angle to the right. Snaps to 10 degrees if `ocam_fSmoothRotation` is set to `1.0`.
- `ocam_bZoomIn` - Zoom in by 1 degree of FOV per second. Maximum zoom-in limit is 10 degrees.
- `ocam_bZoomOut` - Zoom out by 1 degree of FOV per second. Maximum zoom-out limit is 170 degrees.
- `ocam_bResetToPlayer` - Teleport to the viewpoint of a currently selected player (using `gam_iObserverOffset`).
- `ocam_bFollowPlayer` - Make camera automatically turn towards currently selected player. Useful for tracking player movement.
- `ocam_bSnapshot` - Records current camera position in the recording file during demo playback. Creates a new file or overwrites an old one upon taking the first snapshot.
- `ocam_iScreenshotW` - Resolution width for taking high quality screenshots (`1920` by default).
- `ocam_iScreenshotH` - Resolution height for taking high quality screenshots (`1080` by default).
> [!TIP]
> When taking global/Steam screenshots while in "photo mode" (F12 key by default), it saves a high quality screenshot from the camera's point of view with custom resolution specified by these commands.

- `ocam_bMoveForward` - Make free-fly camera move forward.
- `ocam_bMoveBackward` - Make free-fly camera move backward.
- `ocam_bMoveLeft` - Make free-fly camera move to the left.
- `ocam_bMoveRight` - Make free-fly camera move to the right.
- `ocam_bMoveUp` - Make free-fly camera move upward.
- `ocam_bMoveDown` - Make free-fly camera move downward.

> [!WARNING]
> Binding mouse buttons or Space to any observer camera controls would not do anything in demos because pressing them interrupts demo playback.
