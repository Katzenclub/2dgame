mkdir Release
cd Release
cmake ../2DGame
make
if [ $1 == "-s" ]
then
    ./2DGame
fi