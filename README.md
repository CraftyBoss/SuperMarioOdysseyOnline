# Super Mario Odyssey - Online Multiplayer Mod

Welcome to the official repository for the Super Mario Odyssey Online mod! Have fun exploring kingdoms with friends, playing gamemodes, or beating the game as fast as possible! This mod is still early in development, so expect bugs and un-refined aspects as we work hard to improve it and make the mod as polished as possible.

## Features

* Explore Kingdoms together with up to 10 People
* Almost every capture in the game is synced between players
* Full 2D and Costume models syncing
* Moon Collection is shared between all players
* Custom Configuration Menu (Accessible by holding ZL and selecting any option in the pause/start menu)
* Support for custom gamemodes (WIP)
### Available Gamemodes
* Hide and Seek

## SMO Version Support

* 1.0

## Installation Tutorial

Before installing, Ensure that your switch is hacked. If not, follow [This Guide](https://switch.homebrew.guide/) to get your switch setup for modding. Make sure you set up a way to block Nintendo's servers as you will need to have your switch connected to the internet for this mod to work!

1. Download the latest mod build from either [Gamebanana](https://gamebanana.com/mods/384214) or from the [Releases](https://github.com/CraftyBoss/SuperMarioOdysseyOnline/releases) tab. (Alternatively, build from source)
2. Extract the downloaded zip onto the root of your Switch's SD card.
3. If you need to host an online server, head over to the [Super Mario Odyssey Online Server](https://github.com/Sanae6/SmoOnlineServer) repository and follow the instructions there to set up the server.
4. Launch the game! Upon first time bootup, the mod should ask for a server IP to save to the games common save file. This IP address will be the server you wish to connect to every time you launch the game with the mod installed. (Note: un-installing the mod and launching the game will remove the server IP from the common save file.)

## Gamemode Info
### Hide and Seek
* Depending on Group size, select who will start as seekers at the beginning of each round and a kingdom to hide in. 
* Each player has a timer on the top right of the screen that will increase while they are hiding during a round. 
* When a seeker gets close enough to a player, the player will die and respawn as a seeker.
* During the round, hiders who die by other means will also become seekers upon respawning.
* If a hider loads into a new stage (via a pipe, door, etc.) the hider will get 5 seconds of tag invincibility to prevent spawn point camping.
* The player with the most time at the end of a round (or set of rounds) is considered the winner.
* While not a concrete rule, it's generally agreed upon that hiding should not be done out of bounds, inside objects that don't sync across games yet, and inside objects that completely conceal a player from others (such as trees).

## Gamemode Controls
### Hide and Seek
- Left D-Pad: Decrease time
- Right D-Pad: Increase Time
- L + D-Pad Down: Reset Time
- D-Pad Up: Switch from Hider/Seeker

## Building Prerequisites

- [devkitPro](https://devkitpro.org/) 
- Python 3
- The [Keystone-Engine](https://www.keystone-engine.org/) Python Module

## Building

Build has only been tested on WSL2 running Ubuntu 20.04.1.

Just run:
```
DEVKITPRO={path_to_devkitpro} make
```

On Ubuntu (and other Debian-based systems), devkitPro will be installed to `/opt/devkitpro` by default:

```
DEVKITPRO=/opt/devkitpro/ make
```

## Installing (Atmosphère)

After a successful build, simply transfer the `atmosphere` folder located inside `starlight_patch_100` to the root of your switch's SD card.

---

# Contributors

- [Sanae](https://github.com/sanae6) Wrote the majority of the server code
- [Shadow](https://github.com/shadowninja108) original author of starlight, the tool used to make this entire mod possible
- [GRAnimated](https://github.com/GRAnimated)

# Credits
- [OdysseyDecomp](https://github.com/shibbo/OdysseyDecomp)
- [OdysseyReversed](https://github.com/shibbo/OdysseyReversed)
- [open-ead](https://github.com/open-ead/sead) sead Headers
