This program is designed to work with the Unix/Linux compiler. This program procedurally generates an island of characters on the terminal screen.
This program was designed as practice with c/c++, and uses int** instead of vectors for the arrays.

Compiling: use a cpp compiler like
g++ -g -Wall IslandGen.cpp -o IslandGen

Upon running the program, you will encounter the following parameters to fill in:
do you want to use a preset?
'y': will use a preset defined below
'n': will allow for custom parameter filling

enter map width and height
recommended: 30 - 70

enter drop window x & y coordinates, enter drop window width and length:
This will create a subwindow of the array where particles will appear.
recommended: create a window roughly 50% of the chosen width and height for the entire array

enter number of particles to drop and max life:
This will determine how many particles are used to make the island; the more particles, the taller the mountains, the larger the max life, the bigger the island.
recommended: 50, 500

enter value for water line:
This will affect the size of the island versus the size of the water body.
recommended: 60

do you want to print in color:
'y': will print color to the terminal (may not work, based on terminal configuration)
'n': will print in black and white