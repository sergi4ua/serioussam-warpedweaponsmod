# Functions
```
Message.Fatal(message_string)
```
**Arguments:**
- `message_string` - String containing the error message to display.

**Return value:** `null`

**Remarks:** Displays a dialog with a fatal error message and immediately terminates the running game. Equivalent to the engine's `FatalError()` function.

---

```
Message.Warning(message_string)
```
**Arguments:**
- `message_string` - String containing the warning message to display.

**Return value:** `null`

**Remarks:** Displays a dialog with a warning message. Only visible in tool applications or in game with `con_bNoWarnings = 0`. Equivalent to the engine's `WarningMessage()` function.

---

```
Message.Info(message_string)
```
**Arguments:**
- `message_string` - String containing the info message to display.

**Return value:** `null`

**Remarks:** Displays a dialog with an info message. Equivalent to the engine's `InfoMessage()` function.

---

```
Message.Question(message_string)
```
**Arguments:**
- `message_string` - String containing the question to display.

**Return value:** `bool` with the answer depending on the selected dialog button.

**Remarks:** Displays a dialog with a yes-or-no question. Equivalent to the engine's `YesNoQuestion()` function.

---

```
Message.Log(message_string)
```
**Arguments:**
- `message_string` - String containing the message to print.

**Return value:** `null`

**Remarks:** Prints a message in console for debugging purposes. Equivalent to the engine's `CPutString()` function.
