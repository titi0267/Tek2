rm -f arcade
rm -f lib/arcade_ncurses.so
rm -f lib/arcade_sfml.so
rm -f lib/arcade_sdl2.so
rm -f lib/arcade_nibbler.so
cd build/
cmake ..
cmake --build .
