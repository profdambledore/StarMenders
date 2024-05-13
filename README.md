# StarMenders

 A time-manipulation puzzle game created in Unreal Engine 5

 <p align="center">
  <img src="https://github.com/profdambledore/StarMenders/blob/main/Images/logov1.PNG" />
</p>

 In this project, I am creating a space themed time-manipulating puzzle game.  Players have to record their movement and actions on different tracks and play back their recordings to complete puzzles and stop black holes from forming.

## Project Document
 
 [Link](https://github.com/profdambledore/StarMenders/blob/main/Docs/Star_Menders.pdf)

 ## Latest Update
<table><tr><td valign="center" width="100%">
 
### v0.Ma - Main Menu Start<br>
Added Assets from PolygonShops<br>
Created new level for the main menu<br>
Created v1 of the Logo (see Images/logov1)<br>

---------------------------------------------------------<br>

### v0.8i - Level Select

 <p align="center">
  <img src="https://github.com/profdambledore/StarMenders/blob/main/Images/v8-014.PNG" />
</p>

-- RecordPad --<br>
Fixed a playback bug by moving the player to the record pad on recording start<br>

-- MechanicObject - Parent --<br>
Added a ObjectToSpawn property, used by certain Output mechanics to spawn WorldObjects<br>

-- MechanicObject - WorldObjectStart --<br>
Swapped the parent class from MechanicObject_Parent to MechanicObject_Output<br>

-- MechanicObject - WorldObjectSpawner --<br>
Now overrides ResetToDefault from MechanicObject_Parent, which simply moves the object under the map<br>

-- LevelData --<br>
Added a ObjectToSpawn property<br>

-- SelectorData --<br>
Added FPlanetData struct, used to store data about a planet in the LevelSelector<br>
Added FSectorStruct, used to store a collection of planets together<br>
Added FPlanetVisualsData, used to store the components of each planet spawned in the LevelSelector<br>

-- LevelDoor --<br>
Moved UpdateClipPlane from protected to public<br>

-- LevelController --<br>
No longer calls SetupLevel on BeginPlay<br>
SetupLevel now clears the level before searching the data table<br>
Also updates the clip plane of the Entrance and Exit doors and sets ObjectToSpawn on the OutputMechanics<br>
Implemented ClearLevel, which simply destroys all objects in each mechanic array (excluding the ExitDoor) and then empties the arrays<br>
Updated StartLevelPlayback from "AMechanicObject_Parent* j : ActiveRoom->GetMechanicObjects()" to "AMechanicObject_Output* j : OutputMechanics"<br>

-- LevelSelector --<br>
Implemented class, added a camera used to blend the player's view target between<br>
On BeginPlay, find and store a pointer to the LevelController<br>
Implemented PrimaryInteract, which fires a trace from the player's mouse position in the mouse direction. The trace is then checked to see if it hits a component. If it does, it queries the PlanetVisuals array to find a matching component, then calls SetupLevel based on the component found.<br>
Implemented SetActiveSector, which finds the data table row of the inputted parameter. If one is found, then spawns component sets to match the amount of PlanetIDs in the sector via recursion, then updates the planet sets to match the visuals in the found row (Images/v8-014)<br>
Implemented SetActive and EndInteraction, which simply set/clear a pointer to the player interaction with the selector<br>
Added AddNewPlanetVisual, which spawns a spring arm component, static mesh component and rotating movement component set until the target is reached<br>

</td></tr></tr></table> 
<!---
## Overview Videos

<!---<table><tr><td valign="center" width="100%">
 
[![IMAGE ALT TEXT](http://img.youtube.com/vi/XMy0BoMvCBQ/0.jpg)](https://youtu.be/XMy0BoMvCBQ "Tileset Generator Overview") 

[![IMAGE ALT TEXT](http://img.youtube.com/vi/gtHHQCKSiKg/0.jpg)](https://youtu.be/gtHHQCKSiKg "Example of Tileset Generator") 

</td></tr></tr></table> 
-->
 ## Assets Used:
- Polygon Sci-Fi Space by SyntyStudios
- Polygon Shops by SyntyStudios

## Programs Used:
- Unreal Engine 5.2 - Game Engine.
- Visual Studio 2022 - Code Editing.
- Overleaf with LaTeX - Document Creation
- GitHub Desktop - Git Control. 
