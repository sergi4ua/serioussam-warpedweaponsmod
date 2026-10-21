> **Serious Sam Classics Patch** implements a custom system of modular plugins that can be automatically loaded every time the patch is initialized. These plugins can be used to extend or modify many aspects of the game right on top of it, independent from traditional mods.

> See `Extensions/Sample` project for the example of a plugin library with descriptions of each event that plugins can handle.

> Features and special techniques described here should be considered when developing custom user plugins.

# What are plugins?

Plugins are essentially mods that work across the entire game instead of being limited to a specific sphere. They come in a form of extra DLL files that the patch loads up automatically upon starting the game and lets them execute any code without having to start any level or user-made modification.

Plugins can be separated into two distinct categories:

1. **Standalone plugins** - Smaller scale plugins that typically add new features that are managed by the plugin itself.  
For example: new HUD interface or custom server gamemodes.
2. **Classics Patch extensions** - Heavier plugins that work hand in hand with the patch or even the engine itself. These plugins may be explicitly used by the patch to extend certain functionality instead of letting the plugin do everything on its own.  
For example: full support of modern controllers or a new sound API (if you're brave enough to code such a thing).

# Plugin registration

In order for the patch to utilize the plugin, it should be recognized as such and provide methods for starting it up and shutting it down.

## Defining plugin data
First things first, plugin needs to define its metadata to be able to tell the patch exactly what it is and what it's used for.

For that, a `CLASSICSPATCH_DEFINE_PLUGIN` macro should be used like this:
```cpp
CLASSICSPATCH_DEFINE_PLUGIN(
  k_EPluginFlagGame | k_EPluginFlagServer, // Utility flags mask using EPluginFlags enum values
  MakeVersion(1, 0, 0), // Plugin version
  "SAM_IS_AWESOME", // Plugin author
  "Fundomizer", // Plugin name
  "Cool plugin for randomizing various gameplay aspects. Works on dedicated servers too!" // Brief description of the plugin
);
```

If you wish to register an extension, use `CLASSICSPATCH_DEFINE_EXTENSION` macro instead:
```cpp
CLASSICSPATCH_DEFINE_EXTENSION(
  "PATCH_EXT_fundomizer", // Unique extension identifier for retrieving this plugin
  k_EPluginFlagGame | k_EPluginFlagServer, // Utility flags mask using EPluginFlags enum values
  MakeVersion(1, 0, 0), // Plugin version
  "SAM_IS_AWESOME", // Plugin author
  "Fundomizer", // Plugin name
  "Cool plugin for randomizing various gameplay aspects. Works on dedicated servers too!" // Brief description of the plugin
);
```

## Extension features
If you're creating an extension, you may add extra features to it to allow other code to communicate or interact with it.

### Extension module handle
\<placeholder\>

### Extension properties
\<placeholder\>

### Extension signals
\<placeholder\>

## Plugin initialization and cleanup
Plugin entry point and cleanup are defined using two macros that declare special functions with appropriate names and calling conventions: `CLASSICSPATCH_PLUGIN_STARTUP` and `CLASSICSPATCH_PLUGIN_SHUTDOWN`.

Both functions take an INI config that contains plugin properties loaded from an `.ini` file next to the plugin library of the same name. It can be used to check specific properties that have been set (if any) for futher customization of the plugin behavior (e.g. by mods).

The initialization function takes an additional argument for specifying custom plugin events that are called at certain points by the patch.

```cpp
// Module entry point
CLASSICSPATCH_PLUGIN_STARTUP(HIniConfig props, PluginEvents_t &events) {
  // ...startup code and optional interaction with plugin properties...
};

// Module cleanup
CLASSICSPATCH_PLUGIN_SHUTDOWN(HIniConfig props) {
  // ...shutdown code and optional interaction with plugin properties...
};
```

> [!WARNING]
> If you don't specify the correct arguments for the functions, the linker will throw errors about undefined methods, the pointers to which are exported via these macros.

# Plugin event registering

Plugin events can be registered by assigning functions to specific interface pointers of a `PluginEvents_t` structure that's passed into the plugin startup method.

It isn't necessary to define every single plugin event, since all pointers are set to `NULL` by default for forward compatibility with future versions of Classics Patch. No need to assign empty functions.

For the ease of defining functions with appropriate calling conventions (for compatibility with different compilers), a list of pre-declared plugin events is included in the `API/include/plugineventfunctions.h` header file, which is included inside the main API header.

```cpp
// Include Classics Patch API that declares plugin event functions
#include <API/include/classicspatch_api.h>

// Define processing events for the plugin
void IProcessingEvents_OnStep(void) {
  // ...function code...
};

void IProcessingEvents_OnFrame(CDrawPort *pdp) {
  // ...function code...
};

// Registering inside module's entry point
CLASSICSPATCH_PLUGIN_STARTUP(HIniConfig props, PluginEvents_t &events) {
  // Access function pointers under some event interface and assign defined functions to them
  events.m_processing->OnStep  = &IProcessingEvents_OnStep;
  events.m_processing->OnFrame = &IProcessingEvents_OnFrame;
};
```

# Shell symbol registering

When registering custom shell symbols to use within your plugins, be aware that you **cannot** define variables for the symbols within the plugin's memory space.

Plugins are released from memory automatically right before cleaning up Serious Engine, which is supposed to save symbols marked as `persistent` into the `Scripts/PersistentSymbols.ini`. Since plugins are getting erased from memory, values of the plugin symbols become inaccessible, leading to crashes related to memory access violation upon quitting the game or tool applications, potentially messing up your game files.

## Variable symbols
How to properly register plugin variables in console.

```cpp
// DON'T do this (using local variable)
//   This stores the symbol in the global scope of the plugin's memory
static INDEX _bRedScreen = TRUE;

// DO this (using plugin symbol class)
//   This stores only a reference to the symbol in the global scope of the plugin's memory
static CPluginSymbol _psRedScreen(SSF_PERSISTENT | SSF_USER, INDEX(1));

// Registering inside module's entry point
CLASSICSPATCH_PLUGIN_STARTUP(HIniConfig props, PluginEvents_t &events)
{
  // DON'T do this (using Serious Engine method)
  //   This declares the symbol directly in the shell with the pointer to the variable
  _pShell->DeclareSymbol("persistent user INDEX sam_bRedScreenOnDamage;", &_bRedScreen);

  // DO this (using plugin API method)
  //   This registers the symbol through the API and stores it in memory space of a library/executable that initialized the Core library
  _psRedScreen.Register("sam_bRedScreenOnDamage");
};
```

`CPluginSymbol` constructor arguments are as follows:

| Argument | Description | Example |
| --- | --- | --- |
| 1. **Symbol flags** | These are the flags used by the shell itself to see what this symbol is supposed to be. | The flags may only be `SSF_PERSISTENT` (saves values in "Scripts/PersistentSymbols.ini" upon quitting the game), `SSF_USER` (listed in the console) and `SSF_CONSTANT` (values cannot be changed via the console/shell). |
| 2. **Default value** | The default value that's going to be set to the symbol upon registering. If it's been loaded from `PersistentSymbols.ini`, the value won't be rewritten upon registering it again. | It can either be an `INDEX`, a `FLOAT` or a `const char *` value. |

`CPluginSymbol::Register()` arguments are as follows:

| Argument | Description | Example |
| --- | --- | --- |
| 1. **Symbol name** | The name that will be used to access the symbol value, i.e. the console command name. | `"iMySymbol"` |
| 2. **Pre-function** | Shell function to call before modifying the symbol (the only argument the C++ function under that shell symbol has is a pointer to the registered symbol value). Can be left empty (`""`) or unspecified altogether (only if **post-function** isn't specified). | `"MyPreFunc"` |
| 3. **Post-function** | Shell function to call after modifying the symbol (the only argument the C++ function under that shell symbol has is a pointer to the registered symbol value). Can be left empty (`""`) or unspecified altogether. | `"MyPostFunc"` |

To retrieve a value from the symbol, use `GetIndex()`, `GetFloat()` or `GetString()` of `CPluginSymbol`, depending on which type the default value is. Calling the wrong method causes undefined behavior!

## Function symbols

### Shell functions in code
How to properly define plugin functions for use by the shell.

```cpp
// Shell function definition
static void SetHealth(SHELL_FUNC_ARGS)
{
  BEGIN_SHELL_FUNC;
  INDEX iHealth = NEXT_ARG(INDEX);

  // Gather all local players and change their health
  CDynamicContainer<CPlayerEntity> cenPlayers;
  IWorld::GetLocalPlayers(cenPlayers);

  FOREACHINDYNAMICCONTAINER(cenPlayers, CPlayerEntity, iten) {
    iten->SetHealth(iHealth);
    CPrintF(TRANS("Set %s^r health to %d\n"), iten->GetName(), iHealth);
  }
};
```

Note the usage of `SHELL_FUNC_ARGS` and `BEGIN_SHELL_FUNC` macros in the function. These are platform-specific macros for properly accessing arguments that are passed into the C++ function by the game shell.

It's done this way due to how arrays of arguments are being passed depending on the compiler used. For example, in engine versions 1.05 and 1.07 (built with **MSVC6.0**) the arguments can be accessed directly, like `void MyFunction(INDEX iInteger, FLOAT fNumber, const CTString &strString)`, while in 1.10 (built with **MSVC10.0** or newer) the arguments need to be accessed from a pointer to the array of arguments, like `void MyFunction(void *pArgs)`. These macros take care of compiler-dependent behavior and make it work like in 1.10 engine version.

In order to get values of a specific type one after another, use `NEXT_ARG()` macro function as follows:

| Desired type | Macro function usage | Description |
| --- | --- | --- |
| `INDEX` | `INDEX i = NEXT_ARG(INDEX);` | Shell passes a raw integer value as an argument upon calling the function. |
| `FLOAT` | `FLOAT f = NEXT_ARG(FLOAT);` | Shell passes a raw float value as an argument upon calling the function. |
| `CTString` | `const CTString &str = *NEXT_ARG(CTString *);` or `CTString str = *NEXT_ARG(CTString *);` | Shell passes a pointer to a `CTString` as an argument upon calling the function. |

### Shell function registering
How to properly register plugin functions in console.

```cpp
// Registering inside module's entry point
CLASSICSPATCH_PLUGIN_STARTUP(HIniConfig props, PluginEvents_t &events)
{
  // DON'T do this (using Serious Engine method)
  _pShell->DeclareSymbol("user void cht_SetHealth(INDEX);", &SetHealth);

  // DO this (using plugin API method)
  GetPluginAPI()->RegisterMethod(TRUE, "void", "cht_SetHealth", "INDEX", &SetHealth);
};
```

`CPluginAPI::RegisterMethod()` arguments are as follows:

| Argument | Description | Example |
| --- | --- | --- |
| 1. **User visibility** | Marks the symbol function as "user", making it visible in the symbol list in the console upon typing a part of its name and pressing `Tab`. | `TRUE` or `FALSE` |
| 2. **Function return type** | The value of which type will be returned from the function upon executing it. | May only be `"void"`, `"INDEX"`, `"FLOAT"` or `"CTString"` (matching the C++ types). |
| 3. **Symbol name** | The name that will be used to call the function, i.e. the console command name. | `"MyCommand"` |
| 4. **Function arguments** | Argument types that should be passed into the C++ function upon call. It can either be `"void"` for no arguments or a sequence of `INDEX`, `FLOAT` and `CTString`. | `"FLOAT"`, `"INDEX, INDEX"`, `"CTString, INDEX, FLOAT, FLOAT"` etc. |
| 5. **Pointer to the function** | Here you specify a pointer to the function that will be called upon executing the shell command. It should have matching return type and argument types! | `&MyCommand` |

# Function patching

Plugins may create custom function patches to override logic of specific functions.

One key feature of function patches within plugins is that it's not necessary to manually destroy them on plugin cleanup. All function patches created during plugin initialization are added to plugin's local patch registry that automatically destroys all of them on shutdown.

```cpp
// Original function pointer
static void (CSoundObject::*pPlayFunc)(CSoundData *, SLONG) = NULL;

// Define new class method that will replace the original one
class CSoundPatch : public CSoundObject {
  public:
    // Play every 3D sound twice as fast
    void P_Play(CSoundData *pCsdLink, SLONG slFlags)
    {
      // Permanently change pitch of all 3D sounds
      so_sp3.sp3_fPitch = 2.0f;

      // Proceed to the original function
      (this->*pPlayFunc)(pCsdLink, slFlags);
    };
};

// Patching inside module's entry point
CLASSICSPATCH_PLUGIN_STARTUP(HIniConfig props, PluginEvents_t &events)
{
  // Patch sound playing function
  pPlayFunc = &CSoundObject::Play;
  CreatePatch(pPlayFunc, &CSoundPatch::P_Play, "CSoundObject::Play(...)");
};
```
