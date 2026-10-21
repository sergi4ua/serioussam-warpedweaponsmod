# Functions
```
Shell.Execute(shell_script_string)
```
**Arguments:**
- `shell_script_string` - String containing a Serious Engine 1 shell script to execute.

**Return value:** `null`

**Remarks:** Equivalent to the engine's `CShell::Execute()` function.

---

```
Shell.GetFloat(symbol_name_string)
```
**Arguments:**
- `symbol_name_string` - String containing the name of a variable symbol.

**Return value:** `float` with the current value of the specified variable.

**Remarks:** Equivalent to the engine's `CShell::GetFLOAT()` function.

---

```
Shell.SetFloat(symbol_name_string, number_value)
```
**Arguments:**
- `symbol_name_string` - String containing the name of a variable symbol.
- `number_value` - Integer or float containing the value to set.

**Return value:** `null`

**Remarks:** Equivalent to the engine's `CShell::SetFLOAT()` function.

---

```
Shell.GetIndex(symbol_name_string)
```
**Arguments:**
- `symbol_name_string` - String containing the name of a variable symbol.

**Return value:** `integer` with the current value of the specified variable.

**Remarks:** Equivalent to the engine's `CShell::GetINDEX()` function.

---

```
Shell.SetIndex(symbol_name_string, number_value)
```
**Arguments:**
- `symbol_name_string` - String containing the name of a variable symbol.
- `number_value` - Integer or bool containing the value to set.

**Return value:** `null`

**Remarks:** Equivalent to the engine's `CShell::SetINDEX()` function.

---

```
Shell.GetString(symbol_name_string)
```
**Arguments:**
- `symbol_name_string` - String containing the name of a variable symbol.

**Return value:** `string` with the current value of the specified variable.

**Remarks:** Equivalent to the engine's `CShell::GetString()` function.

---

```
Shell.SetString(symbol_name_string, string_value)
```
**Arguments:**
- `symbol_name_string` - String containing the name of a variable symbol.
- `string_value` - String containing the value to set.

**Return value:** `null`

**Remarks:** Equivalent to the engine's `CShell::SetString()` function.

---

```
Shell.GetValue(symbol_name_string)
```
**Arguments:**
- `symbol_name_string` - String containing the name of a variable symbol.

**Return value:** `string` with the current value of the specified variable.

**Remarks:** Equivalent to the engine's `CShell::GetValue()` function.

---

```
Shell.SetValue(symbol_name_string, string_value)
```
**Arguments:**
- `symbol_name_string` - String containing the name of a variable symbol.
- `string_value` - String containing the value to set, e.g. a number if the variable is of `INDEX`/`FLOAT` type.

**Return value:** `null`

**Remarks:** Equivalent to the engine's `CShell::SetValue()` function.
