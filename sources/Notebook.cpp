#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
using ariel::Direction;
using ariel::NotebookThrows;
using namespace ariel;
using namespace std;
unsigned int const MAXROWLENGTH = 100;
char const EMPTYSPACE = '_';
char const DELETE = '~';
int const MIN_CHAR = 32;
int const MAX_CHAR = 126;

/*------------------------------ Class Row -----------------------------------------
Initiallize a vector of chars to size 100 each spot with that char '_'.
Functions: we have 2 of each write, read and erase functions to easily handle vertical and horizontal use cases for each function.
For example, if we want to write vertically we will use the first write function which receives a single character rather than a string. 
we will call this function on a different row each time at our Page class.
Same logic for delete(erase) and read functions. 
*/
Row::Row() {
    for (int i = 0; i < MAXROWLENGTH; i++) {
        row.push_back(EMPTYSPACE);
    }
}

void Row::writeAt(const unsigned int index, const char toWrite) {
    row[index] = toWrite;
}

void Row::writeAt(const unsigned int index, const string &toWrite) {
    for (unsigned int i = 0; i < toWrite.size(); i++) {
        row[index + i] = toWrite[i];
    }
}

void Row::deleteAt(const unsigned int index) {
    row[index] = DELETE;
}

void Row::deleteAt(const unsigned int index, const unsigned int toErase) {
    for (unsigned int i = 0; i < toErase; i++) {
        row[index + i] = DELETE;
    }
}

char Row::readAt(const unsigned int index) {
    return row[index];
}

string Row::readAt(const unsigned int index, const unsigned int toRead) {
    string read;
    for (unsigned int i = 0; i < toRead; i++) {
        read += row[index + i];
    }
    return read;
}

void Row::printRow() {
    for (const auto c : row) {
        std::cout << c;
    }
    cout << '\n';
}

//------------------------- End Class Row --------------------------------------


// --------------------------- Class Page --------------------------------------  

// ariel::Page::Page() {
    
// }

// ariel::Page::~Page() {
//     for (Row r : page) {
//         r.~Row();
//     }
// }

void Page::writeAt(const unsigned int row, const unsigned int col, Direction dir, const string &toWrite) {
    Page::resize(row, col, dir, toWrite.size());
    if (dir == Direction::Horizontal) {    
        Page[row].writeAt(col, toWrite);
    }
    if (dir == Direction::Vertical) {   
        unsigned int k = 0;
        for (unsigned int i = row; i < row + toWrite.size(); i++) {
            Page[i].writeAt(col, toWrite[k]);
            k += 1;
        }
    }
}

void Page::deleteAt(const unsigned int row, const unsigned int col, Direction dir, const unsigned int toErase) {
    Page::resize(row, col, dir, toErase);
    if (dir == Direction::Horizontal) {
        Page[row].deleteAt(col, toErase); 
    }
    if (dir == Direction::Vertical) {
        for (unsigned int i = row; i < row + toErase; i++) {
            Page[i].deleteAt(col);
        }
    }
}

string Page::readAt(const unsigned int row, const unsigned int col, Direction dir, const unsigned int toRead) {
    Page::resize(row, col, dir, toRead);
    string result;
    if (dir == Direction::Horizontal) {
        result = Page[row].readAt(col, toRead);
    }
    if (dir == Direction::Vertical) {
        for (unsigned int i = row; i < row + toRead; i++) {
            result += Page[i].readAt(col);
        }
    }
    return result;
}

void Page::printPage() {
    for (unsigned int i = 0; i < Page.size(); i++) {
        cout << Page[i].readAt(0, MAXROWLENGTH) << endl;
    }
}

unsigned int Page::size() {
    return Page.size(); 
}

void Page::resize(const unsigned int row, const unsigned int col, Direction dir, const unsigned int length) {
    if (dir == Direction::Horizontal) {
        if (Page.size() <= row) {
            Page.resize(row + 1);
        }
    }
    if (dir == Direction::Vertical) {
        if (Page.size() <= row + length) {
            Page.resize(row + length);
        }
    }
}

// ------------------------ End Class Page -------------------------------------  

//---------------------------- Class Notebook---------------------------------

void Notebook::check_errors(const int page, const int row, const int col, Direction dir, const string &toWrite,
const int length, NotebookThrows func) {
    if (page < 0 or row < 0 or col < 0) {
        throw out_of_range("Page Row and Col must be 0 or positive");
    }
    if (col >= MAXROWLENGTH) {
        throw logic_error("Col cannot be greater or equal to 100");
    }
    
    if (func == NotebookThrows::Write) {
        if (toWrite.find('~') != string::npos) {
            throw logic_error("Cannot write '~'");
        }
        if (dir == Direction::Horizontal) {
            if ((unsigned int) col + toWrite.size() - 1 >= MAXROWLENGTH) {
                throw out_of_range("Cannot write more than 100 characters per row");
            }
        }
        string st = this->read(page, row, col, dir, toWrite.size());
        for (unsigned int i = 0; i < toWrite.size(); i++) {
            // check if we are trying to write over '~' or already written text
            if (st[i] != EMPTYSPACE) {
                if (st[i] == DELETE) {
                    throw logic_error("Cannot rewrite after erasing");
                }
                throw logic_error("Cannot rewrite on written places");
            }
            // check if toWrite contains invalid characters
            if ((int) toWrite[i] < MIN_CHAR or (int) toWrite[i] > MAX_CHAR) {
                throw invalid_argument("Invalid character");
            }
        }
    }
    
    if (func == NotebookThrows::Read) {
        if (dir == Direction::Horizontal) {
            if (col + length - 1 >= MAXROWLENGTH) {
                throw out_of_range("Cannot read after max row length (100)");
            }
        }   
    }

    if (func == NotebookThrows::Erase) {
        if (dir == Direction::Horizontal) {
            if (col + length - 1 >= MAXROWLENGTH) {
                throw out_of_range("Cannot erase after max row length (100)");
            }
        }      
    }
}

void Notebook::resize(const unsigned int page) {
    if (notebook.size() <= page) {
        notebook.resize(page + 1);
    }
}

void Notebook::write(const int page, const int row, const int col, Direction dir, const string &toWrite) {
    Notebook::check_errors(page, row, col, dir, toWrite, 0, NotebookThrows::Write);
    Notebook::resize((unsigned int) page);
    notebook[(unsigned int) page].writeAt((unsigned int) row, (unsigned int) col, dir, toWrite);
}

void Notebook::erase(const int page, const int row, const int col, Direction dir, const int toErase) {
    Notebook::check_errors(page, row, col, dir, "", toErase, NotebookThrows::Erase);
    Notebook::resize((unsigned int) page);
    notebook[(unsigned int) page].deleteAt((unsigned int)row, (unsigned int) col, dir, (unsigned int) toErase);
}

string Notebook::read(const int page, const int row, const int col, Direction dir, const int toRead) {
    Notebook::check_errors(page, row, col, dir, "", toRead, NotebookThrows::Read);
    Notebook::resize((unsigned int) page);
    return notebook[(unsigned int) page].readAt((unsigned int) row, (unsigned int) col, dir, (unsigned int) toRead);
}

void Notebook::show(const int page) {
    if (page < 0) {
        throw out_of_range("Page must be greater or equal to 0");
    }
    if (notebook.size() <= page) {
        cout << "Page number " << page << " is empty" << endl;
        return;
    }
    Page currentPage = notebook[(unsigned int) page];
    for (int i = 0; i < currentPage.size(); i++) {
        cout << to_string(i) << ": " << currentPage.readAt((unsigned int) i, 0, Direction::Horizontal, MAXROWLENGTH) << endl;
    }
}
//--------------------------- End Class Notebook -----------------------------------