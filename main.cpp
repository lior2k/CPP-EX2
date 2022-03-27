#include "sources/Notebook.hpp"
#include "sources/Direction.hpp"
using ariel::Direction;
using namespace ariel;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    Notebook nb;
    char func;
    int page;
    unsigned int row;
    unsigned int col;
    string toWrite;
    unsigned int length;
    char dir;
    
    while (true) {
        func = 0;
        cout << "To write enter 'w', to read enter 'r', to erase enter 'e', to show a specific page enter 's', to exit enter 'q': " << endl;
        cin >> func;

        if (func == 'q') {
            break;
        }

        cout << "Enter page number (0 or positive number): " << endl;
        cin >> page;

        if (func == 's') {
            nb.show(page);
            continue;
        }
        
        cout << "Enter row number (0 or positive number): " << endl;
        cin >> row;
        cout << "Enter column number (0 or positive number): " << endl;
        cin >> col;
        cout << "To write/read/erase horizontally enter 'h', for vertically enter 'v': " << endl;
        cin >> dir;

        if (func == 'w') {
            cout << "Enter exactly what you want to write: " << endl;
            toWrite = "";
            while (toWrite == "") {
                getline(cin, toWrite);
            }
            try {
                if (dir == 'h') {
                    nb.write(page, row, col, Direction::Horizontal, toWrite);
                }
                if (dir == 'v') {
                    nb.write(page, row, col, Direction::Vertical, toWrite);
                }
            } catch (exception &ex) {
                cout << "caught exception: " << ex.what() << endl;
            }
        }

        if (func == 'r') {
            cout << "Enter the length you want to read: " << endl;
            cin >> length;
            try {
                if (dir == 'h') {
                    cout << endl << nb.read(page, row, col, Direction::Horizontal, length);
                }
                if (dir == 'v') {
                    cout << endl << nb.read(page, row, col, Direction::Vertical, length);
                }
            } catch (exception &ex) {
                cout << "caught exception: " << ex.what() << endl;
            }
        }

        if (func == 'e') {
            cout << "Enter the length you want to erase: " << endl;
            cin >> length;
            try {
                if (dir == 'h') {
                    nb.erase(page, row, col, Direction::Horizontal, length);
                }
                if (dir == 'v') {
                    nb.erase(page, row, col, Direction::Vertical, length);
                }
            } catch (exception &ex) {
                cout << "caught exception: " << ex.what() << endl;
            }
        }
    }
}
    
