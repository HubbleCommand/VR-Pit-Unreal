# VR Pit Unreal
Project code for the Unreal Engine version of the VR Pit. Made in 4.22.

## Use of timers
In the Unity version of the project, Coroutines were used to handle the timing and sequence of the trials.

For the Unreal version, I used Timers (in PitWorkHorse_AC.cpp) to achieve the same effect. However, there is another system in Unreal that is much closer to Unity's Coroutines: AsyncTasks. AsyncTasks weren't used as there was nothing to do during the routines except wait, then execute some functions, which is exactly what Unreal's Timers were used to achieve. However, if there is a need, eventually, to execute other functions while the Timers are running, it would probably be better to look at using AsyncTasks.

## Packaged project
A packaged, executable version of the project can be found at:

https://sourceforge.net/projects/vrpit-unreal/

### Controls
- Escape closes the program
- F11 changes between Windowed and Fullscreen
- R starts the trials

## Functionalities
### Define Trials
In the project directory there is a "tests.txt" file. It is organised by: 
1. falling enabled (true for falling, false for no falling), 
1. platform type (track or plank),
1. platform length, 
1. platform width, 
1. platform space (only changes for track type platform), 
1. pre-exposure phase duration (seconds), 
1. exposure phase duration (seconds), 
1. post-exposure phase duration (seconds), 
1. pit depth (meters)

### Start Trials
While the participant is looking at the target (by default the cylinder on the far wall), hit "R".

### Parallel Port Output
There are currently two versions of working with Parallel Ports: the Inpoutx64 dll from HighRez Studios, and a custom code using CreateFile() with DBC settings with a seperate thread for continuous writing. 

## Using the project
### Files to add after downloading
Be sure to put the Inpoutx64.dll in the UE4 generated Binaries folder and make the necessary changes to Build.cs.

### Changing the Target

### Changing port number

### 

## Warnings
Changing the PitMaker.cpp code may break the project! Make sure you know how to work with the UE4 Asset Browser in C++.
