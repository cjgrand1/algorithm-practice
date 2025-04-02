#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
using namespace std;

int** makeParticleMap(int, int, int, int, int, int, int, int);
bool moveExists(int**, int, int, int, int, int);
int findMax(int**, int, int);
void normalizeMap(int**, int, int, int);

int main(int argc, char** argv) {
  int width, height, windowX, windowY, winWidth, winHeight, numParticles,
      maxLife, waterLine;

  // get user input
  do {
    cout << "To begin, enter map width: ";
    cin >> width;
    cout << "now enter height: ";
    cin >> height;
  } while (!(width > 0 && height > 0));

  do {
    cout << "Enter drop-window x-coordinate (0 - " << width << "): ";
    cin >> windowX;
    cout << "Enter drop-window y-coordinate (0 - " << height << "): ";
    cin >> windowY;
    cout << "Enter drop-window width (>= 1): ";
    cin >> winWidth;
    cout << "Enter drop-window height (>= 1): ";
    cin >> winHeight;
  } while (
      !((windowX >= 0 && windowY >= 0) &&
        (windowX <= width && windowY <= height) &&
        (winWidth > 0 && winHeight > 0) &&
        ((winWidth + windowX) <= width && (winHeight + windowY) <= height)));

  do {
    cout << "Enter number of particles to drop: ";
    cin >> numParticles;
  } while (!(numParticles > 0));

  do {
    cout << "Enter max life of particles: ";
    cin >> maxLife;
  } while (!(maxLife > 0));

  do {
    cout << "Enter value for waterline (40-200): ";
    cin >> waterLine;
  } while (!(waterLine >= 40 && waterLine <= 200));

  // testing
  /* width = 5, height = 5, windowX = 0, windowY = 0, winWidth = 5, winHeight = 5,
  numParticles = 4, maxLife = 4, waterLine = 45; */

  // generate map
  int** map = makeParticleMap(width, height, windowX, windowY, winWidth,
                              winHeight, numParticles, maxLife);

  // print map
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      cout << map[i][j];
    }
    cout << endl;
  }
}

/*
 * This function builds the array for the map data and performs particle roll
 * algorithm to populate the array with map data. You can modifuy this function
 * to take the array as a parameter instead if you prefer to create the array
 * externally to the particle roll algorithm. In which case, this function would
 * become a void type.
 */
int** makeParticleMap(int width, int height, int windowX, int windowY,
                      int winWidth, int winHeight, int numParticles,
                      int maxLife) {
  // dynamically create map based on user input
  int** map = new int*[height];
  for (int i = 0; i < height; i++) map[i] = new int[width];

  // "drop" a particle at a random x,y location within the window
  int particleX, particleY;
  for (int i = 0; i < numParticles; i++) {
    particleX = windowX + (rand() % winWidth);
    particleY = windowY + (rand() % winHeight);

    // increment index by 1
    map[particleY][particleX]++;

    // repeat until current particle dies
    for (int j = 0; j < maxLife; j++) {
      // pick a move at random, see if it is a valid move
      // if not valid, pick another random move until out of moves
      int moves[8] = {0, 1, 2, 3, 4, 5, 6, 7};
      bool changed = false;

      // randomly shuffle list of moves
      random_shuffle(begin(moves), end(moves));

      for (int j = 0; j < 8; j++) {
        if (moveExists(map, width, height, particleX, particleY, moves[j])) {
          // update x,y coordinate
          switch (moves[j]) {
            case 0:
              particleY--;
              break;
            case 1:
              particleY--;
              particleX++;
              break;
            case 2:
              particleX++;
              break;
            case 3:
              particleY++;
              particleX++;
              break;
            case 4:
              particleY++;
              break;
            case 5:
              particleY++;
              particleX--;
              break;
            case 6:
              particleX--;
              break;
            case 7:
              particleY--;
              particleX--;
              break;
          }

          // increment index by 1
          map[particleY][particleX]++;
          changed = true;
          break;
        }
      }

      // if nothing changed, kill particle
      if (!changed) break;
    }
  }

  return map;
}

/*
 * This function looks at the 8 spots around x, y, and determines if a valid
 * move is possible. Return true if one is found.
 */
bool moveExists(int** map, int width, int height, int x, int y, int move) {
  switch (move) {
    case 0:  // top
      if ((y - 1) >= 0 && map[y - 1][x] <= map[y][x])
        return true;
      else
        return false;
    case 1:  // top right
      if (((y - 1) >= 0 && (x + 1) < width && map[y - 1][x + 1] <= map[y][x]))
        return true;
      else
        return false;
    case 2:  // right
      if ((x + 1) < width && map[y][x + 1] <= map[y][x])
        return true;
      else
        return false;
    case 3:  // bottom right
      if ((y + 1) < height && (x + 1) < width && map[y + 1][x + 1] <= map[y][x])
        return true;
      else
        return false;
    case 4:  // bottom
      if ((y + 1) < height && map[y + 1][x] <= map[y][x])
        return true;
      else
        return false;
    case 5:  // bottom left
      if ((y + 1) < height && (x - 1) >= 0 && map[y + 1][x - 1] <= map[y][x])
        return true;
      else
        return false;
    case 6:  // left
      if ((x - 1) >= 0 && map[y][x - 1] <= map[y][x])
        return true;
      else
        return false;
    case 7:  // top left
      if ((y - 1) >= 0 && (x - 1) >= 0 && map[y - 1][x - 1] <= map[y][x])
        return true;
      else
        return false;
    default:
      return false;
  }
}

/*
 * This function finds the max valud in the map and returns it
 */
int findMax(int** map, int width, int height) { return 0; }

/*
 * Performs the normalization operation on the map data. You could have this
 * return a new array instead if you want to hold onto the og map data for some
 * reason.
 */
void normalizeMap(int** map, int width, int height, int maxVal) {}