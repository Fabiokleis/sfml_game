# SFML GAME

A mario-game project using sfml, tiled editor to create tilemaps and rapidjson to parse.

To run this source u already installed cmake, a c++ compiler
and two libs [sfml](https://en.sfml-dev.org/) and (already in include directory)[rapidjson](https://github.com/Tencent/rapidjson)
# compile and run:
```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B ./build # if needs compile_commands.json
cmake -S . -B ./build # to generate cmake conf normally
cmake --build ./build/  # to build target

./game
```
