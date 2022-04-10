#!/bin/bash
downloadRapidXML() {
    wget -q --show-progress -O rapidxml.zip https://sourceforge.net/projects/rapidxml/files/latest/download
    unzip -q -o rapidxml.zip -d libs
    rm -f rapidxml.zip
}

downloadImGUI() {
    wget -q --show-progress -O imgui.zip https://github.com/ocornut/imgui/archive/refs/tags/v1.86.zip
    unzip -q -o imgui.zip -d libs
    rm -f imgui.zip
}

downloadImGUI-SFML() {
    wget -q --show-progress -O imgui-sfml.zip https://github.com/eliasdaler/imgui-sfml/archive/refs/tags/v2.5.zip
    unzip -q -o imgui-sfml.zip -d libs
    rm -f imgui-sfml.zip
    cp -f libs/imgui-sfml-2.5/imconfig-SFML.h libs/imgui-1.86/imconfig.h
}

if [ ! -d "libs/rapidxml-1.13" ]; then
    downloadRapidXML
fi

if [ ! -d "libs/imgui-1.86" ]; then
    downloadImGUI
fi

if [ ! -d "libs/imgui-sfml-2.5" ]; then
    downloadImGUI-SFML
fi

for var in "$@"
do
    if [ "$var" == "-g" ]
    then
        downloadRapidXML
        downloadImGUI
        downloadImGUI-SFML
    fi
done

mkdir -p Release
cd Release
cmake ../2DGame
make -j
if [ "$?" -ne "0" ]; then
   exit 2
fi
for var in "$@"
do
    if [ "$var" == "-s" ]
    then
        ./2DGame
    fi
done

