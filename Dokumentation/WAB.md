# WAB Projektpraktium

Still needs to be added for the Documentation that will be printed as PDF (according to lecture on the 12th January):
- How to use: compilation, tutorial on how to use game (kind of done)
- Design Descisions should be Documented (ex. why SFML, why Engine Desing like Engine is Designed, why Perlin Noise, why Render how we Render)
- Rest is up to us
- Should be 10-12 Pages (including Images and Stuff)

## Game Tutorial

| Button | Function |
| ----------- | ----------- |
| Space | Jump |
| A | Move Left |
| S | Move Right |
| D | Move Down |
| Left Click | Place Block |
| Middle Click | Select a new Block to place |
| Right Click | Spawn Slime |
| R | Zoom Out |
| T | Zoom In |
| E | Reset Zoom to Default |

## Compilation
### Windows
0. Visual Studio is needed with the ```Desktop development with C++``` workload installed
1. Open the ```2DGame.sln``` with Visual Studio
2. Select the ```Release Windows``` configuration
3. Build the Solution, needed dependencies will be automatically downloaded.

### Debian
Install Dependencies
```
sudo apt install gcc cmake libsfml-dev
```
Execute build script
```
chmod +x cmake_build.sh
./cmake_build.sh
```

Build script options:  
```-s``` : Start the game automatically after building  
```-g``` : Force (re)download of libraries

Explanation:  
The build script will automatically download needed libraries that aren't available on repositories. They will only be downloaded automatically if their corresponding folder in the ```libs``` directory is missing. Then using cmake the project will be built into the Release folder.

### Mac OS
Install XCode command line tools
```
xcode-select --install
```
then use the same build script as for Debian

## Code Guidelines
### Variable Naming
```g_variable```: global (outside of a class)  
```m_variable```: member (in a class)  
```l_variable```: local (defined in a class / on the fly)  

```x_p_variable```: pointer

### Case
Camelcase  
Example: ```m_p_firstWordSecondWord```

### Namespace
Every class should be encapsulated within the ```gp``` namespace

## Debugging and Developing with VS Code (Only for Debian and Mac OS)
### Install LLDB Debugger 
On Debian:
```
sudo apt install lldb
```
On Mac OS it should come with the XCode command line tools if not in a Terminal enter:
```
lldb
```

### Install needed VS Code Extensions
```
code --install-extension ms-vscode.cpptools 
code --install-extension ms-vscode.cpptools-themes
code --install-extension twxs.cmake 
code --install-extension ms-vscode.cmake-tools
```

## Generating Doxygen Documentation
### Installing Doxygen and dependencies
#### Debian 
Since the version on the Debian repository is too old to be used with the Doxygen Awesome Stylesheet it needs to be compiled manually 
```
sudo apt install flex bison graphviz
git clone https://github.com/doxygen/doxygen.git
cd doxygen
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
sudo make install
```

#### Windows
Download doxygen version 1.9.3 from [here](https://www.doxygen.nl/files/doxygen-1.9.3-setup.exe)  
Download graphviz from [here](https://gitlab.com/api/v4/projects/4207231/packages/generic/graphviz-releases/3.0.0/windows_10_cmake_Release_graphviz-install-3.0.0-win64.exe) 

### Generating the Documentation
```
cd Dokumentation/Doxygen
doxygen
```

## Design Decisions
### CMake for Debian Build (and desicion to support Debian and MacOS)
Since only Nils uses Windows and Visual Studio to compile and develop we needed a way to easily compile the Game on Debian and MacOS, since calling gcc with all the needed arguments manually would be too much work.  
CMake provides an easy way to compile C++ code on Debian with a lot of customization options. The only downside is that it is a bit complicated to use if you're only getting started with C++ and it's your first time using CMake. This wasn't a problem for us though since Chloe already had experience using CMake, and once the CMakeLists.txt was properly setup the compiling itself is very easy.

### SFML Framework
### Engine Design
### World generation using Perlin Noise
### Design of the ManagerRenderer

## Project identification process

wanted to make a game

different game ideas
- Terraria-Clone
- Pokemon-Clone
- Imperium der Ameisen-Clone

custom engine

C++

## Tools 
trello --> tasks

discord, whatsapp --> communication

git (github) --> code share

## Game development 

game basis together (group programming via discord)



## Game art

# Design Decisions