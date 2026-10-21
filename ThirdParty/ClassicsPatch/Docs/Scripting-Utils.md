# Classes

## FLOAT3D
Class for holding a position or a rotation in 3D space and performing operations on it.

### Metamethods
| Method | Arguments | Return value | Description |
| ------ | --------- | ------------ | ----------- |
| Constructor | `float` (opt), `float` (opt), `float` (opt) | N/A | Constructs a vector value instance with the specified values for each axis. Unspecified axis values are defaulted to 0. |
| `+` operator        | `FLOAT3D` | `FLOAT3D` | Adds two vectors together. |
| `-` operator        | `FLOAT3D` | `FLOAT3D` | Subtracts another vector from the first one. |
| `-` operator(unary) | N/A       | `FLOAT3D` | Inverts the value of each axis. |
| `*` operator(1)     | `FLOAT3D` | `FLOAT3D` | Calculates cross product between two vectors. |
| `*` operator(2)     | `float`   | `FLOAT3D` | Multiplies each axis value by the specified number. |
| `/` operator        | `float`   | `FLOAT3D` | Divides each axis value by the specified number. |
| `%` operator        | `FLOAT3D` | `FLOAT3D` | Calculates dot product between two vectors. |
| `tostring`          | N/A       | `string`  | Returns vector values formatted as `[%g, %g, %g]`. |

### Methods
| Method | Arguments | Return value | Description |
| ------ | --------- | ------------ | ----------- |
| `Length`        | N/A | `float` | Returns length of the vector in meters. Equivalent to the engine's `FLOAT3D::Length()`. |
| `ManhattanNorm` | N/A | `float` | Returns manhattan norm of the vector in meters. Equivalent to the engine's `FLOAT3D::ManhattanNorm()`. |
| `MaxNorm`       | N/A | `float` | Returns maximum norm of the vector in meters. Equivalent to the engine's `FLOAT3D::MaxNorm()`. |
| `Normalize`     | N/A | `FLOAT3D` (itself) | Normalizes the vector in some direction by dividing it by its length, resulting in 1m length. Equivalent to the engine's `FLOAT3D::Normalize()`. |
| `SafeNormalize` | N/A | `FLOAT3D` (itself) | Same as `Normalize` but resets it to a forward vector (`FLOAT3D(0, 0, -1)`) if its current length is close to 0m. Equivalent to the engine's `FLOAT3D::SafeNormalize()`. |
| `Flip`          | N/A | `FLOAT3D` (itself) | Inverts the value of each axis. Equivalent to the engine's `FLOAT3D::Flip()`. |

### Variables
| Variable | Type    | Description |
| -------- | ------- | ----------- |
| `x`/`h`  | `float` | First axis value. "X" signifies the physical position on the East-West axis; "H" signifies the "heading" rotation angle. |
| `y`/`p`  | `float` | Second axis value. "Y" signifies the physical position on the Up-Down axis; "P" signifies the "pitch" rotation angle. |
| `z`/`b`  | `float` | Third axis value. "Z" signifies the physical position on the North-South axis; "B" signifies the "banking" rotation angle. |

# Functions
```
Utils.NormFloatToByte(number)
```
**Arguments:**
- `number` - Float value to convert from `0.0 .. 1.0` range to `0x00 .. 0xFF`.

**Return value:** `integer`

**Remarks:** Equivalent to the engine's `NormFloatToByte()` function.

---

```
Utils.NormByteToFloat(number)
```
**Arguments:**
- `number` - Integer value to convert from `0x00 .. 0xFF` range to `0.0 .. 1.0`.

**Return value:** `float`

**Remarks:** Equivalent to the engine's `NormByteToFloat()` function.

---

```
Utils.WrapAngle(number)
```
**Arguments:**
- `number` - Float value with the angle in degrees to wrap.

**Return value:** `float` with the specified angle wrapped around to the `+0 .. +360` range.

**Remarks:** Equivalent to the engine's `WrapAngle()` function.

---

```
Utils.NormalizeAngle(number)
```
**Arguments:**
- `number` - Float value with the angle in degrees to normalize.

**Return value:** `float` with the specified angle wrapped around to the `-180 .. +180` range.

**Remarks:** Equivalent to the engine's `NormalizeAngle()` function.

---

```
Utils.RadToDeg(number)
```
**Arguments:**
- `number` - Float value to convert from radians to degrees.

**Return value:** `float` with the specified angle in degrees.

**Remarks:** Equivalent to the engine's `AngleRad()` function.

---

```
Utils.DegToRad(number)
```
**Arguments:**
- `number` - Float value to convert from degrees to radians.

**Return value:** `float` with the specified angle in radians.

**Remarks:** Equivalent to the engine's `RadAngle()` function.

---

```
IncludeScript(path_string)
```
**Arguments:**
- `path_string` - Path to another script file to include and evaluate at runtime.

**Return value:** Return value from the specified script or `null` if nothing is returned.

**Remarks:** This function keeps track of the current script depth and will throw a runtime error if nested scripts go deeper than 16 to avoid a potential stack overflow error.

---

```
CompileScript(path_string)
```
**Arguments:**
- `path_string` - Path to another script file to compile at runtime.

**Return value:** `function` with the compiled script for executing at any point.

**Remarks:** This function **does not** keep track of the current script depth and may lead to a stack overflow error, if used improperly.
