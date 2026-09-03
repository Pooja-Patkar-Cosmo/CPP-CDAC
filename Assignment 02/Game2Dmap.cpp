#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Seed the random number generator
    srand(time(0));

    int R, C;
    cout << "Enter number of rows (R): ";
    cin >> R;
    cout << "Enter number of columns (C): ";
    cin >> C;
    cout << endl;

    // Requirement 1: Allocate 2D array dynamically using int**
    int** map = new int*[R];
    for (int i = 0; i < R; ++i) {
        map[i] = new int[C];
    }

    // Requirement 2: Fill the grid using rand() % 5
    // Track counts of each tile type (0=grass, 1=water, 2=mountain, 3=forest, 4=dungeon)
    int tileCounts[5] = {0};

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            map[i][j] = rand() % 5;
            tileCounts[map[i][j]]++;
        }
    }

    // Requirement 3: Display the grid with a legend
    cout << "===== GAME MAP (" << R << " x " << C << ") =====" << endl;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Legend: 0=Grass  1=Water  2=Mountain  3=Forest  4=Dungeon" << endl;
    cout << endl;

    // Requirement 4: Print the count of each tile type
    cout << "Tile Count:" << endl;
    cout << "  Grass    : " << tileCounts[0] << endl;
    cout << "  Water    : " << tileCounts[1] << endl;
    cout << "  Mountain : " << tileCounts[2] << endl;
    cout << "  Forest   : " << tileCounts[3] << endl;
    cout << "  Dungeon  : " << tileCounts[4] << endl;

    // Requirement 5: Deallocate memory properly
    for (int i = 0; i < R; ++i) {
        delete[] map[i]; // Delete each row
    }
    delete[] map; // Delete outer array of pointers
    map = nullptr;

    return 0;
}