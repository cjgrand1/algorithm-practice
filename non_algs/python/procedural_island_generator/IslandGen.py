#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import random
import math

def main():  
    width, height = 50, 50
    windowX, windowY = 20, 20
    winWidth, winHeight = 10, 10
    numParticles, maxLife = 50, 500
    waterLine = 50

    # generate map
    map = makeParticleMap(width, height, windowX, windowY, winWidth, winHeight, numParticles, maxLife)

    # find max
    max = findMax(map, width, height)

    # normalize map and print
    normalizeMap(map, width, height, max, waterLine)


def makeParticleMap(width, height, windowX, windowY, winWidth, winHeight, numParticles, maxLife):
    """This function builds the array for the map data and performs particle roll algorithm to populate
    the array with map data.

    Args:
        width: Width of 2D array
        height: Height of 2D array
        windowX: Starting/Minimum x point for the particle drop window
        windowY: Starting/Minimum y point for the particle drop window
        winWidth: Width of particle drop window (<= width - windowX)
        winHeight: Height of particle drop window (<= height - windowY)
        numParticles: Number of unique particles to drop in the drop window
        maxLife: Maximum life of each particle
    """

    # create map based on user input
    map = []
    for _ in range(height):
        row = [0] * width
        map.append(row)

    # "drop" a particle at a random x,y location within the window
    for _ in range(numParticles):
        particleX = random.randrange(0, winWidth) + windowX
        particleY = random.randrange(0, winHeight) + windowY

        # increment index by 1
        map[particleY][particleX] += 1

        # repeat until current particle dies
        for _ in range(maxLife):
            # pick a move at random, see if it is a valid move
            # if not valid, pick another random move until out of moves
            moves = [0, 1, 2, 3, 4, 5, 6, 7]
            changed = False

            # randomly shuffle list of moves
            random.shuffle(moves)

            for j in range(8):
                if moveExists(map, width, height, particleX, particleY, moves[j]):
                    # update x,y coordinate based on move
                    match moves[j]:
                        case 0:
                            particleY -= 1
                        case 1:
                            particleY -= 1
                            particleX += 1
                        case 2:
                            particleX += 1
                        case 3:
                            particleY += 1
                            particleX += 1
                        case 4:
                            particleY += 1
                        case 5:
                            particleY += 1
                            particleX -= 1
                        case 6:
                            particleX -= 1
                        case 7:
                            particleY -= 1
                            particleX -= 1

                    # increment index by 1
                    map[particleY][particleX] += 1
                    changed = True
                    break

            # if nothing changed, kill particle
            if changed == False:
                break

    return map

def moveExists(map, width, height, x, y, move) -> bool:
    """This function takes in a move to one of the 8 spots around x, y, and determines
    if a valid move is possible. Return true if move is valid.

    Args:
        map: The 2D array
        width: Width of the 2D array
        height: Height of the 2D array
        x: Given x coordinate
        y: Given y coordinate
        move: Tells which of the 8 surrounding indices to check
    """
    match move:
        case 0: # top
            if (y - 1) >= 0 and map[y - 1][x] <= map[y][x]:
                return True
            else:
                return False
        case 1: # top right
            if (y - 1) >= 0 and (x + 1) < width and map[y - 1][x + 1] <= map[y][x]:
                return True
            else:
                return False
        case 2: # right
            if (x + 1) < width and map[y][x + 1] <= map[y][x]:
                return True
            else:
                return False
        case 3: # bottom right
            if (y + 1) < height and (x + 1) < width and map[y + 1][x + 1] <= map[y][x]:
                return True
            else:
                return False
        case 4: # bottom
            if (y + 1) < height and map[y + 1][x] <= map[y][x]:
                return True
            else:
                return False
        case 5: # bottom left
            if (y + 1) < height and (x - 1) >= 0 and map[y + 1][x - 1] <= map[y][x]:
                return True
            else:
                return False
        case 6: # left
            if (x - 1) >= 0 and map[y][x - 1] <= map[y][x]:
                return True
            else:
                return False
        case 7: # top left
            if (y - 1) >= 0 and (x - 1) >= 0 and map[y - 1][x - 1] <= map[y][x]:
                return True
            else:
                return False
        case _:
            return False


# This function finds the max value in the map and returns it
def findMax(map, width, height) -> int:
    """"This function finds the max value in the map and returns it.

    Args:
        map: 2D array
        width: Width of 2D array
        height: Height of 2D array    
    """
    max = 0
    for i in range(height):
        for j in range(width):
            if map[i][j] > max:
                max = map[i][j]
            
    return max

def normalizeMap(map, width, height, maxVal, waterLine):
    """"Performs the normalization operation on the map data.

    Args:
        map: 2D array
        width: Width of 2D array
        height: Height of 2D array
        maxVal: Largest value in 2D array
        waterLine: Given waterLine value for map gen    
    """

    # normalize the map to be constant values between 0 - 255
    # divide each value by the largest, and multiply by 255
    for i in range(height):
        for j in range(width):
            map[i][j] = float(map[i][j]) / float(maxVal) * 255

    # calculate land-zone
    landzone = 255 - waterLine

    # output array using char instead of numbers
    output = []
    for _ in range(height):
        row = [' '] * width
        output.append(row)

    # fill in output array based on the numbers from map
    for i in range(height):
        for j in range(width):
            temp = map[i][j]
            if temp <= math.floor(landzone / 2):
                output[i][j] = '#' # deep water
            elif temp <= waterLine:
                output[i][j] = '~' # shallow water
            elif temp < (waterLine + ((landzone * 15) / 100)):
                output[i][j] = '.' # coast/beach
            elif temp < (waterLine + ((landzone * 40) / 100)):
                output[i][j] = '-' #plains/grass
            elif temp < (waterLine + ((landzone * 80) / 100)):
                output[i][j] = '*' # forests
            else:
                output[i][j] = '^' # mountains
    
    # print results
    for i in range(height):
        for j in range(width):
            print(output[i][j], end='  ')
        print()

if __name__ == "__main__":
    main()