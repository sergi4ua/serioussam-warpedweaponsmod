> [!IMPORTANT]
> Input polling is currently only possible during an active game, i.e. when you can control the player and **not** when the menu/console/NETRICSA is open.

# Constants
- `Button` enum - Contains constants for every `KID_*` value from the engine, e.g. `Button.KID_A` for "A" letter key or `Button.KID_ENTER` for Return/Enter key.
- `Axis` enum - Contains indices and offsets of available input axes:
  - `Axis.None` - The first/unused axis.
  - `Axis.X1` - Horizontal mouse axis.
  - `Axis.Y1` - Vertical mouse axis.
  - `Axis.Z1` - Scroll wheel axis.
  - `Axis.X2` - Horizontal axis of the second mouse.
  - `Axis.Y2` - Vertical axis of the second mouse.
  - `Axis.Joysticks` - Amount of available joysticks.
  - `Axis.PerJoystick` - Amount of axes per joystick for offsetting.
  - `Axis.FirstJoystick` - Index of the first axis of the first joystick for offsetting.
  - `Axis.Count` - Total amount of available axes.

# Functions
```
Input.GetAxisCount()
```
**Return value:** `integer`

**Remarks:** Returns amount of available axes. Equivalent to the engine's `CInput::GetAxisCount()` function.

---

```
Input.GetButtonsCount()
```
**Return value:** `integer`

**Remarks:** Returns amount of available buttons. Equivalent to the engine's `CInput::GetButtonsCount()` function.

---

```
Input.GetAxisName(axis_index)
```
**Arguments:**
- `axis_index` - Index of an axis from the `Axis` enum.

**Return value:** `string`

**Remarks:** Returns internal name of the specified axis. Equivalent to the engine's `CInput::GetAxisName()` function.

---

```
Input.GetAxisTransName(axis_index)
```
**Arguments:**
- `axis_index` - Index of an axis from the `Axis` enum.

**Return value:** `string`

**Remarks:** Returns localized name of the specified axis. Equivalent to the engine's `CInput::GetAxisTransName()` function.

---

```
Input.GetAxisValue(axis_index)
```
**Arguments:**
- `axis_index` - Index of an axis from the `Axis` enum.

**Return value:** `float`

**Remarks:** Returns current value of the specified axis. For joystick axes, this value is always in the `-1.0 .. +1.0` range. Equivalent to the engine's `CInput::GetAxisValue()` function.

---

```
Input.GetButtonName(button_index)
```
**Arguments:**
- `button_index` - Index of a button from the `Button` enum.

**Return value:** `string`

**Remarks:** Returns internal name of the specified button. Equivalent to the engine's `CInput::GetButtonName()` function.

---

```
Input.GetButtonTransName(button_index)
```
**Arguments:**
- `button_index` - Index of a button from the `Button` enum.

**Return value:** `string`

**Remarks:** Returns localized name of the specified button. Equivalent to the engine's `CInput::GetButtonTransName()` function.

---

```
Input.GetButtonState(button_index)
```
**Arguments:**
- `button_index` - Index of a button from the `Button` enum.

**Return value:** `bool`

**Remarks:** Checks whether the specified button is currently held down. Equivalent to the engine's `CInput::GetButtonState()` function.

---

```
Input.GetAxisByName(axis_name)
```
**Arguments:**
- `axis_index` - Internal name of the axis (the kind returned by `Input.GetAxisName()`).

**Return value:** `integer` with the index of the associated axis.

**Remarks:** Returns axis index by its internal name, otherwise `Axis.None`.

---

```
Input.GetButtonByName(button_name)
```
**Arguments:**
- `button_name` - Internal name of the button (the kind returned by `Input.GetButtonName()`).

**Return value:** `integer` with the index of the associated button.

**Remarks:** Returns button index by its internal name, otherwise `Button.KID_NONE`.
