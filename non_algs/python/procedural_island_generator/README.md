This program is designed to work with the Unix/Linux compiler. This program procedurally generates an island of characters on the terminal screen.
This program was originally designed as practice with c/c++, and then converted into python.

There are no user inputs for this program, so any changes will have to be made directly to the code itself.

The program creates a 2D array of numbers, randomly 'drops' a point on the grid---which increments the array index at that spot--and then the point moves around on the grid until it runs out of moves. This creates a 2D array of values that are then converted into characters to resemble a map/island.

'#' = deep water
'~' = shallow water
'.' = coast/beach
'-' = plains/grass
'*' = forests
'^' = mountains