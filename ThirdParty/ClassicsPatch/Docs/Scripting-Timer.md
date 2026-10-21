# Constants
- `TickQuantum` - Contains length of a single game tick in seconds. Equivalent to the engine's `CTimer::TickQuantum` constant.

# Classes

## Timer.Value
Class for holding timer values measured in CPU cycles.

### Metamethods
| Method      | Arguments     | Return value | Description |
| ----------- | ------------- | ------------ | ----------- |
| Constructor | `float` (opt) | N/A          | Constructs a timer value instance with the specified value in seconds. If left unspecified, defaults to 0 CPU cycles. |

### Variables
| Variable | Type      | Description |
| -------- | --------- | ----------- |
| `msec`   | `integer` | Read-only variable of the current timer value in milliseconds. |
| `sec`    | `float`   | Read-only variable of the current timer value in seconds. |

# Functions
```
Timer.GetRealTimeTick()
```
**Return value:** `float` with the current game time in seconds since the beginning.

**Remarks:** Consistent across the entire game. Equivalent to the engine's `CTimer::GetRealTimeTick()` function.

---

```
Timer.CurrentTick()
```
**Return value:** `float` with the current game tick in seconds.

**Remarks:** Contains different values at any given time depending on context, e.g. rendering of the game menu, NETRICSA or the world. Affected by the speed of the current world. Equivalent to the engine's `CTimer::CurrentTick()` function.

---

```
Timer.GetLerpedCurrentTick()
```
**Return value:** `float` with the current frame time in seconds.

**Remarks:** Contains different values at any given time depending on context, e.g. rendering of the game menu, NETRICSA or the world. Affected by the speed of the current world. Equivalent to the engine's `CTimer::GetLerpedCurrentTick()` function.

---

```
Timer.GetLerpFactor()
```
**Return value:** `float` with the lerp factor of the current frame between two game ticks.

**Remarks:** Equivalent to the engine's `CTimer::GetLerpFactor()` function.

---

```
Timer.GetLerpFactor2()
```
**Return value:** `float` with the secondary lerp factor of the current frame between two game ticks.

**Remarks:** Equivalent to the engine's `CTimer::GetLerpFactor2()` function.

---

```
Timer.GetHighPrecisionTimer()
```
**Return value:** `Timer.Value` instance with the current CPU time.

**Remarks:** Consistent across all running instances of the game on the same computer. Equivalent to the engine's `CTimer::GetHighPrecisionTimer()` function.
