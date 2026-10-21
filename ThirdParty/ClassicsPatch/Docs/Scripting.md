> A guide to scripting within Classics Patch using its "Scripting Engine" plugin.

# Relevant resources
- Squirrel scripting language: http://squirrel-lang.org/
- Official documentation: http://squirrel-lang.org/squirreldoc/
- Valve Development Community documentation: https://developer.valvesoftware.com/wiki/Squirrel

# Scripting languages
Right now, the only scripting language **Classics Patch** supports is **Squirrel 3.2**.

**Squirrel** is a scripting language with C-like syntax designed for games.  
It can be used for implementing new mechanics (such as new gamemodes) without having to code your own plugins for the patch.

Scripts are much more efficient and versatile than the engine's shell language.

## Feature comparison
| Language  | Syntax | Object-oriented | Dynamic types | Integer type   | Float type       | Boolean type | String type | Arrays  | Type conversion    | Global variables | Local variables | Control flow statements                | Loop statements                       | Classes | Functions                      | Code nesting |
| --------- | ------ | --------------- | ------------- | -------------- | ---------------- | ------------ | ----------- | ------- | ------------------ | ---------------- | --------------- | -------------------------------------- | ------------------------------------- | ------- | ------------------------------ | ------------ |
| SE1 shell | C-like | No              | No            | Signed 32 bits | Single precision | Integer type | Yes         | Limited | Explicit           | Yes              | No              | `if`, `else`, `else if`                | N/A                                   | N/A     | Execution                      | Standard `include "path"` command; custom `IncludeScript(<path>)` function |
| Squirrel  | C-like | Yes             | Yes           | Signed 64 bits | Single precision | Yes          | Yes         | Yes     | Implicit, explicit | Yes              | Yes             | `if`, `else`, `else if`, `switch-case` | `while`, `do-while`, `for`, `foreach` | Yes     | Definition, execution, lambdas | Custom `IncludeScript(<path>)` function |

# Libraries
Scripting Engine extension implements specific libraries to allow interactions with the game and the engine via scripts.

| Library                             | Squirrel table | Purpose |
| ----------------------------------- | -------------- | ------- |
| [Entities](Scripting-Entities)      | `Entities`     | **\[UNFINISHED\]** ~~Interactions with entities in the world.~~ |
| [File system](Scripting-FileSystem) | `FileSystem`   | **\[UNFINISHED\]** ~~Working with game files and binary/text data within them.~~ |
| [Input](Scripting-Input)            | `Input`        | Input polling from keyboard, mouse and joysticks. |
| [Messages](Scripting-Message)       | `Message`      | Message boxes and other information output. |
| [Network](Scripting-Network)        | `Network`      | **\[UNFINISHED\]** ~~Interactions with the currently running game.~~ |
| [Shell](Scripting-Shell)            | `Shell`        | Interactions with the engine shell. |
| [Timer](Scripting-Timer)            | `Timer`        | Reading current game/frame time. |
| [Utilities](Scripting-Utils)        | `Utils`        | Helper classes and functions, not strictly under the library namespace (global). |
| [World](Scripting-World)            | `World`        | **\[UNFINISHED\]** ~~Interactions with the current world.~~ |
