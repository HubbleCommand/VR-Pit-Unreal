# VR Pit Unreal
Stuff for the Unreal version of the VR Pit. Made in 4.21.

## Functionalities

### Define Trials
In the project directory there is a "tests.txt" file. It is organised by: 
1. falling enabled (true for falling, flase for no falling), 
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

## Things to Add
Be sure to put the Inpoutx64.dll in the UE4 generated Binaries folder and make the necessary changes to Build.cs.

## Warnings
Be warned, changing the PitMaker.cpp code may break the project. Make sure you know how to work with the UE4 Asset Browser in C++.
