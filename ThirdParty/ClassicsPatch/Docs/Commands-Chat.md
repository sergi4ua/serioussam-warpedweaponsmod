> These commands are available to all clients on a server (even the ones without the patch) and they are executed by sending chat messages with a command prefix set into `ser_strCommandPrefix` by the server.

> By default, the chat command prefix is `!`.

# Everyone
- `!map` - Displays name of the current level and its world file.
- `!login <password>` - Authorize as a server administrator using the password from `ser_strAdminPassword` or an operator using the password from `ser_strOperatorPassword`.

## Voting system
- `!votemap [index]` - Initiates voting process to change the current map to another one from the current map pool. If no index is specified, it lists available maps in the current pool.
- `!votekick [index]` - Initiates voting process to kick some client under a specific index. If no index is specified, it lists current server clients with their players.
- `!votemute [index]` - Initiates voting process to mute some client under a specific index. If no index is specified, it lists current server clients with their players.
- `!voteskip` - Initiates voting process to skip current round on a dedicated server and restart on the next one.
> [!NOTE]
> Only works on servers launched via dedicated server application!
- `!y` - Vote yes during active voting. Cannot change your vote afterwards.
- `!n` - Vote no during active voting. Cannot change your vote afterwards.

# Admins only
- `!log [index] [index]` - Display log of clients that have ever joined the server by their client identity index. These indices are used in other commands.
  - First index is for displaying information about a specific client identity (starting from `0`).
  - Second index is for displaying information about a specific character of a specific client identity (starting from `1`).
- `!ban <index> [time]` - Ban all clients under some identity index for a specific amount of time. Time set to less than `0` sets an indefinite time.
  - Example: `!ban 1 3600` - Bans all clients under the second identity index for 1 hour.
- `!mute <index> [time]` - Mute all clients under some identity index for a specific amount of time. Time set to less than `0` sets an indefinite time.
  - Example: `!mute 2` - Mutes clients under the third identity index for 5 minutes.
- `!kick <index> [reason]` - Kick all clients under some identity index with an optional reason.
  - Example: `!kick 1 You are a headless freak!` - Kicks all clients under the second identity index with a reason.

# Operators only
- `!rcon <command>` - Execute any console commands on the server side, as if they're directly entered by the server client.
  - Example: `!rcon Quit()` - Remotely shuts down dedicated server.
- `!save [filename]` - Save the game on the dedicated server's computer under the `SaveGame/Network` directory. If filename is left empty, it defaults to `RemoteSave`.
