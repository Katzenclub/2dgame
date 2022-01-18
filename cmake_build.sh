mkdir Release
cd Release
cmake ../2DGame
make
if [ $# -gt 0 ]
then
    if [ $@ == "-s" ]
    then
        ./2DGame
    fi
fi