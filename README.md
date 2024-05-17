# StarMenders

 A time-manipulation puzzle game created in Unreal Engine 5

 <p align="center">
  <img src="https://github.com/profdambledore/StarMenders/blob/main/Images/logov2.PNG" />
</p>

 In this project, I am creating a space themed time-manipulating puzzle game.  Players have to record their movement and actions on different tracks and play back their recordings to complete puzzles and stop black holes from forming.

## Project Document
 
 [Link](https://github.com/profdambledore/StarMenders/blob/main/Docs/Star_Menders.pdf)

 ## Latest Update
<table><tr><td valign="center" width="100%">

### v0.9a - InGameLevel Part One

 <p align="center">
  <img src="https://github.com/profdambledore/StarMenders/blob/main/Images/v9-005.PNG" />
</p>

-- LevelSelect_Master  --<br>
Added two text box components, one for the name of the planet and one for the tagline<br>
Implemented UpdateWidgetData, which is called to update the two text boxes<br>
- This function will be updated in the future to update more information about the planet/level the player is hovering, such as best time and if completed<br>

-- LevelSelector  --<br>
Added WidgetComponent, used to display the Selector UI<br>
Added a pointer to the new PlanetDataTable and renamed the WorldMapDataTable to SectorDataTable<br>
Also added a new FObjectFinder to find and store the PlanetDataTable<br>
Updated SetActiveSector to now use the updated SectorData and PlanetData structs<br>
Implemented GetPlanetData function, which simply returns a FPlanetData row from the PlanetDataTable<br>
Added an additional FObjectFinder to find and set the LevelSelector widget class<br>
Updated Tick<br>
 - Now checks if the Selector is in use.  If so, fire a trace in an identical way to Interact
 - If the trace hits a component, make the WidgetComponent visible, get the hit planet's data, update the widgets text boxes and modify the components location and rotation<br>
 - Simply, when a planet is hovered, the widget rotates to face the player camera and displays the name and tagline of the planet (see Images/v9-005)<br>

-- SelectorData  --<br>
Removed FPlanetData TArray from SectorData, now a TArray of FNames<br>
Removed FPlanetData TArray from SectorData, now a TArray of FNames<br>
Added MainMenuUI element, currently has three buttons<br>
- Planets are now defined in the PlanetDataTable instead of the SectorDataTable.  Previous iterations only required the use of the level ID tied to the planet, such as spawning a new level.  However, more data is required by the LevelSelectorUI.<br>
 - Simply put, Sectors are still made up of FPlanetData but the FSectorData does not directly store the planets themselves, they are kept in a different data table.  This allows planet data to be collected more easily (via FindRow with the new table) and at a slight improvement to performance (dont need to get the current sector row then iterate over the planet array until the matching planet is found)<br>

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
