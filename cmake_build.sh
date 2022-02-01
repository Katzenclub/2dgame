for var in "$@"
do
    if [ "$var" == "-g" ]
    then
        wget -O rapidxml.zip https://sourceforge.net/projects/rapidxml/files/latest/download
        unzip -o rapidxml.zip -d libs
        rm -f rapidxml.zip

        wget -O imgui.zip https://github.com/ocornut/imgui/archive/refs/tags/v1.86.zip
        unzip -o imgui.zip -d libs
        rm -f imgui.zip

        wget -O imgui-sfml.zip https://github.com/eliasdaler/imgui-sfml/archive/refs/tags/v2.5.zip
        unzip -o imgui-sfml.zip -d libs
        rm -f imgui-sfml.zip

        cp -f libs/imgui-sfml-2.5/imconfig-SFML.h libs/imgui-1.86/imconfig.h
    fi
done

mkdir -p Release
cd Release
cmake ../2DGame
make
for var in "$@"
do
    if [ "$var" == "-s" ]
    then
        ./2DGame
    fi
done