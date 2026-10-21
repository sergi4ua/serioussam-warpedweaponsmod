> Descriptions for commands that are modifiable through the **OPTIONS** -> **CLASSICS PATCH** -> **Server settings** menu.

# Server options
- `net_strVIPPassword` - Vanilla command for specifying the password for VIP clients that may join as players or observers over the max player limit (up to the engine-defined limit).
- `net_strConnectPassword` - Vanilla command for specifying the password for players that may connect under the max client limit.
- `net_strObserverPassword` - Vanilla command for specifying the password for observers that may connect under the max client limit.
- `ser_strAdminPassword` - Password for authorizing as a server administrator using the `!login` chat command. Leaving it blank prevents any non-server client from becoming an admin.
- `ser_strOperatorPassword` - Password for authorizing as a server operator using the `!login` chat command. Leaving it blank prevents any non-server client from becoming an operator.

### Anti-flood system
- `ser_bEnableAntiFlood` - Forbid clients from flooding the server with character change or chat message packets (ON by default).
- `ser_iPacketFloodThreshold` - Maximum amount of packets a client may send per second before kicking them (`10` by default).
  - `0` - Client is kicked immediately after trying to send a chat message or change the character.
  - Below `0` - Don't check for packet flood.
- `ser_iMaxMessagesPerSecond` - Maximum amount of chat messages a client may send per second. If this amount is exceeded, the server issues a warning to the client (`2` by default).
  - `0` - Chat messages are disabled altogether.
  - Below `0` - No chat message limit per second.

### Other options
- `ser_bMaskGUIDs` - Hide unique identifiers of player characters of other players from server clients to prevent them from being stolen (OFF by default).
> [!WARNING]
> This feature isn't the most efficient and may slow down the server by sending packets with a considerable delay under certain conditions.
> Due to engine limitations, if server saves a map with GUID masking on, reconnecting players will not be attached to their dummy player entities and will instead spawn as if they connected for the first time.
- `ser_bReportSyncBadToClients` - Notify clients about bad syncs whenever their game state doesn't sync with the server (OFF by default).
- `ser_bForbidVanilla` - Make the server exclusive to clients with the patch for better compatibility (OFF by default).
> [!NOTE]
> All clients should have the same version of the patch as the server in order to connect. If the client does not have the patch or has a different version of it, they will be prompted to download it.
- `sutl_iThirdPersonViewButton` - Prevents the usage of the third person view both as the button and as the "Prefer 3rd person view" option, if set to `7` in the vanilla game (`-1` by default).
> [!IMPORTANT]
> This functionality is part of the **Server Utilities** plugin and will not work if the plugin isn't loaded.
- `ser_strCommandPrefix` - What prefix should chat commands start with. Can be multiple characters or none (`!` by default).

# Voting system
- `ser_bVotingSystem` - Enables voting system as a whole (OFF by default).
- `ser_bPlayersStartVote` - Determines whether or not players can initiate any voting process (ON by default).
- `ser_bPlayersCanVote` - Determines whether or not players are allowed to vote during active voting process (ON by default).
- `ser_bObserversStartVote` - Determines whether or not spectators can initiate any voting process (OFF by default).
- `ser_bObserversCanVote` - Determines whether or not spectators are allowed to vote during active voting process (OFF by default).
- `ser_fVotingTime` - Sets how long each voting period lasts (`30.0` by default).
- `ser_fVotingTimeout` - How long to wait before being able to initiate another vote (`30.0` by default).
- `ser_bVoteMap` - Enables voting for changing maps (ON by default).
- `ser_bVoteKick` - Enables voting for kicking clients (ON by default).
- `ser_bVoteMute` - Enables voting for muting clients (ON by default).
- `ser_fVoteKickTime` - How long to ban kicked players for in seconds (`300.0` by default).
- `ser_fVoteMuteTime` - How long to mute players for in seconds (`300.0` by default).
- `ser_bVoteSkip` - Enables voting for skipping current round on a dedicated server (ON by default).

# Gameplay extensions
- `gex_bEnable` - Toggle usage of gameplay extensions. If disabled, sets all the settings underneath to vanilla-compatible values (ON by default).
> [!WARNING]
> This setting makes the game incompatible with vanilla. Launched servers, saved games and recorded demos with this setting turned on cannot be played without the patch afterwards.

## Global extensions
- `gex_bFixTimers` - Fixes slowdown bug by adjusting logic timers of entities (ON by default).
- `gex_fGravityAcc` - Multiply gravity acceleration on any level of any mod. Can be inverted by using negative values (`1.0` by default).

## Custom mod extensions
- `gex_bUnlimitedAirControl` - Let players move around indefinitely while still in air, e.g. for easier platforming (OFF by default).
- `gex_fMoveSpeed` - Multiply player movement speed (`1.0` by default).
- `gex_fJumpHeight` - Multiply player jump height (`1.0` by default).
- `gex_bFastKnife` - Increase movement speed in Cooperative mode while holding a knife instead of only in Deathmatch (OFF by default).

# Gameplay customization
Extra commands for gameplay customization can be found under the [**Server Utilities**](Commands-20-Plugin-settings#server-utilities) plugin.

# Extra commands
Relevant functionality that isn't usable or configurable via these options.

- `ser_iMaxPlayersPerClient` - Forbid clients from joining the server if they exceed this amount of local players (`4` by default).
  - `1` - Clients cannot join in split-screen mode at all.
