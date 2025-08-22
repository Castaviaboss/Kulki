Configs:
All available configuration files are located at /Content/Core/Data.

Please note that some fields have ToolTips.

DT_PlayerData – Player settings
DT_LevelData – Game level settings
DT_GameStateData – Settings for the number of enemies that must be absorbed to win are stored here

There are also configs like DT_GameData and DT_InputData, but they are primarily used for global changes to the 
entire game state and are not relevant for your current testing or modifications.

AI:

DT_AiSpawnData – Settings for enemy spawn logic. Here you can configure both the number of
spawned enemies and their radius relative to the spawn center (the player), as well as the chances of
specific AI appearing and their behavior configs.

DT_AiGoalData – Standard enemy behavior settings. The enemy will chase the player if stronger or flee if weaker.

AI → CharacterData
This folder stores configs for different enemy types. You can adjust their visual properties and set up their 
attribute configurations. I created three presets – red, yellow, and purple enemies.

AI → HeroData
Three presets similar to CharacterData. This folder contains configs for enemy attribute settings.


Known Issues:

An enemy may fail to spawn if it cannot find a point on the navmesh, and a warning will appear in the console.

An enemy might spawn, get pushed by the capsule from the plane, and end up in a position where any movement tasks are
unreachable, causing it to stand in one place for the entire game session (but don’t worry, it still poses a threat :)

On some PCs, particularly with RTX 40-series GPUs, there can be an issue where any entities other than the plane are not
visible in the level at certain viewport sizes. The simplest and quickest solution is to scale the viewport until the 
entities appear on the screen.
On my RTX 2080, for example, this problem does not occur, so it may be a peculiarity on Unreal’s side.
Otherwise, the issue could be related to my spawn logic, specifically placement along the Z-axis.