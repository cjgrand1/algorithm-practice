#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <time.h>
using namespace std;

int** makeParticleMap(int, int, int, int, int, int, int, int);
bool moveExists(int**, int, int, int, int, int);
int findMax(int**, int, int);
void normalizeMap(int**, int, int, int, int, char);
void clearIntArray(int**, int);
void clearChaArray(char**, int);

int main(int argc, char** argv) {
  int width, height, windowX, windowY, winWidth, winHeight, numParticles,
      maxLife, waterLine;
  char presetVal, colorVal;
  bool preset;

  srand(time(NULL)); // seed the random number generator

  // use preset or not
  do {
    cout << "Do you wish to use a preset? y or n: ";
    cin >> presetVal;
  } while (!(presetVal == 'y' || presetVal == 'Y' || presetVal == 'n' ||
             presetVal == 'N'));

  if (presetVal == 'y' || presetVal == 'Y')
    preset = true;
  else
    preset = false;

  // get user input
  if (preset) {
    width = 50, height = 50, windowX = 20, windowY = 20, winWidth = 10,
    winHeight = 10, numParticles = 50, maxLife = 500, waterLine = 50;
  } else {
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
  }

  do {
    cout << "Do you wish to print in color? y or n: ";
    cin >> colorVal;
  } while (!(colorVal == 'y' || colorVal == 'Y' || colorVal == 'n' ||
             colorVal == 'N'));

  // generate map
  int** map = makeParticleMap(width, height, windowX, windowY, winWidth,
                              winHeight, numParticles, maxLife);

  // find max
  int max = findMax(map, width, height);

  // normalize map and print
  normalizeMap(map, width, height, max, waterLine, colorVal);
}

/*
 * This function builds the array for the map data and performs particle roll
 * algorithm to populate the array with map data.
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
      random_device rd;
      mt19937 g(rd());
      shuffle(begin(moves), end(moves), g);

      for (int j = 0; j < 8; j++) {
        if (moveExists(map, width, height, particleX, particleY, moves[j])) {
          // update x,y coordinate based on move
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
 * This function takes in a move to one of the 8 spots aroudn x, y, and
 * determines if a valid move is possible. Return true if move is valid.
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
int findMax(int** map, int width, int height) {
  int max = 0;
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      if (map[i][j] > max) max = map[i][j];

  return max;
}

/*
 * Performs the normalization operation on the map data. You could have this
 * return a new array instead if you want to hold onto the og map data for some
 * reason.
 */
void normalizeMap(int** map, int width, int height, int maxVal, int waterLine,
                  char colorVal) {
  // normalize the map to be constant values between 0 - 255
  // divide each value by the largest, and multiply by 255
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      map[i][j] = (double)map[i][j] / (double)maxVal * 255;
    }
  }

  // calculate land-zone
  int landzone = 255 - waterLine;

  // output array using char instead of numbers
  char** output = new char*[height];
  for (int i = 0; i < height; i++) output[i] = new char[width];

  // fill in output array based on the numbers from map
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int temp = map[i][j];
      if (temp <= floor(landzone / 2))
        output[i][j] = '#';  // deep water
      else if (temp <= waterLine)
        output[i][j] = '~';  // shallow water
      else if (temp < (waterLine + ((landzone * 15) / 100)))
        output[i][j] = '.';  // coast/beach
      else if (temp < (waterLine + ((landzone * 40) / 100)))
        output[i][j] = '-';  // plains/grass
      else if (temp < (waterLine + ((landzone * 80) / 100)))
        output[i][j] = '*';  // forests
      else
        output[i][j] = '^';  // mountains
    }
  }

  // print results
  if (colorVal == 'n' || colorVal == 'N') {
    // print without color
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        printf("%c ", output[i][j]);
      }
      cout << endl;
    }
  } else {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        // printf("%c ", output[i][j]);
        char val = output[i][j];
        switch (val) {
          case '#':
            printf("\033[36m%c ", val);  // blue = deep water
            break;
          case '~':
            printf("\033[36m%c ", val);  // cyan = shallow water
            break;
          case '.':
            printf("\033[33m%c ", val);  // color = shore
            break;
          case '-':
            printf("\033[92m%c ", val);  // light green = field
            break;
          case '*':
            printf("\033[32m%c ", val);  // green = forests
            break;
          case '^':
            printf("\033[97m%c ", val);  // white = mountains
            break;
        }
        printf("\033[0m");  // reset color
      }
      cout << endl;
    }
  }

  // clear memory
  clearIntArray(map, height);
  clearChaArray(output, height);
}

/*
 * Deletes content from a double int array to free up memory.
 */
void clearIntArray(int** array, int height) {
  for (int i = 0; i < height; i++) delete[] array[i];
  delete[] array;
}

/*
 * Deletes content from a double char array to free up memory.
 */
void clearChaArray(char** array, int height) {
  for (int i = 0; i < height; i++) delete[] array[i];
  delete[] array;
}