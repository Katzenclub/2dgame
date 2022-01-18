# 2D-Spieleentwicklung für das Projektpraktikum im 5. Semester



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


## Linux Build
If not already installed please install with the following commands:

```
sudo apt install cmake
sudo apt install libsfml-dev
```

Build project with following command:
```
./cmake_build.sh
```

Build and immediatly project with following command:
```
./cmake_build.sh -s
```



## Windows Build
clone and select "Release / Windows"

## Mac Build

## Code Guidelines
g_variable = global variable (it is in no class)
m_variable = member variable (it is in a class)
l_variable = local variable (it is mostly defined in a class and on the fly)

x_pvariable = pointer variable

Case: Camelcase

Example:
m_pfirstWordSecondWord = member as a pointer with multiple words

Every class should be encapsulated with
```
namespace gp {
    Class xxx
}
```