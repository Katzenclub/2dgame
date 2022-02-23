# Terraria-Clone
         *                  *
             __                *
          ,db'    *     *
         ,d8/       *        *    *
         888
         `db\       *     *
           `o`_                    **
      *               *   *    _      *
            *                 / )
         *    (\__/) *       ( (  *
       ,-.,-.,)    (.,-.,-.,-.) ).,-.,-.
      | @|  ={      }= | @|  / / | @|o |
     _j__j__j_)     `-------/ /__j__j__j_
     ________(               /___________
      |  | @| \              || o|O | @|
      |o |  |,'\       ,   ,'"|  |  |  |  
     vV\|/vV|`-'\  ,---\   | \Vv\hjwVv\//v
                _) )    `. \ /
               (__/       ) )
                         (_/

# Build Guides
## Linux
If not already installed please install with the following commands:

```
sudo apt install cmake
sudo apt install libsfml-dev
```

Build game with following command:
```
./cmake_build.sh
```

Build and immediately start game with following command:
```
./cmake_build.sh -s
```

To forcefully redownload and move the needed libraries run the command with -g:
```
./cmake_build.sh -g
```

## Windows
1. Clone Repository
2. Select "Release / Windows" and start debugger (it downloads and sets up everything)

## Mac
Install Xcode Command Line Tools
```
xcode-select --install
```
then follow build guide for Linux, but skip installing dependencies

# Code Guidelines
g_variable = global variable (it is in no class)  
m_variable = member variable (it is in a class)  
l_variable = local variable (it is mostly defined in a class and on the fly)  

x_p_variable = pointer variable

Case: Camelcase

Example:
m_p_firstWordSecondWord = member as a pointer with multiple words

Every class should be encapsulated with
```
namespace gp {
    Class uwu
}
```

# Debugging and Developing with VS Code (Linux and Mac OS only)

## Install LLDB Debugger 
Linux:
```
sudo apt install lldb
```
Mac OS, in a Terminal enter:
```
lldb
```

## Install needed VS Code Extensions
```
code --install-extension ms-vscode.cpptools 
code --install-extension ms-vscode.cpptools-themes
code --install-extension twxs.cmake 
code --install-extension ms-vscode.cmake-tools
```