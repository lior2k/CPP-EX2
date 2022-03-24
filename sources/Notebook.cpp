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
    row.at(index) = toWrite;
}

void Row::writeAt(const unsigned int index, const string &toWrite) {
    for (unsigned int i = 0; i < toWrite.size(); i++) {
        row.at(index + i) = toWrite[i];
    }
}

void Row::deleteAt(const unsigned int index) {
    row.at(index) = DELETE;
}

void Row::deleteAt(const unsigned int index, const unsigned int toErase) {
    for (unsigned int i = 0; i < toErase; i++) {
        row.at(index + i) = DELETE;
    }
}

char Row::readAt(const unsigned int index) {
    return row.at(index);
}

string Row::readAt(const unsigned int index, const unsigned int toRead) {
    string read;
    for (unsigned int i = 0; i < toRead; i++) {
        read += row.at(index + i);
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
    if (dir == Direction::Horizontal) {
        if (Page.size() <= row) {
            Page.resize(row + 1);
        }
        Page.at(row).writeAt(col, toWrite);
    }

    if (dir == Direction::Vertical) {
        if (Page.size() <= row + toWrite.size()) {
            Page.resize(row + toWrite.size());
        }
        unsigned int k = 0;
        for (unsigned int i = row; i < row + toWrite.size(); i++) {
            Page.at(i).writeAt(col, toWrite[k]);
            k += 1;
        }
    }
}

void Page::deleteAt(const unsigned int row, const unsigned int col, Direction dir, const unsigned int toErase) {
    if (dir == Direction::Horizontal) {
        if (Page.size() <= row) {
            Page.resize(row + 1);
        }
        Page.at(row).deleteAt(col, toErase); 
    } else {
        if (Page.size() <= row + toErase) {
            Page.resize(row + 1 + toErase);
        }
        for (unsigned int i = row; i < row + toErase; i++) {
            Page.at(i).deleteAt(col);
        }
    }
}

string Page::readAt(const unsigned int row, const unsigned int col, Direction dir, const unsigned int toRead) {
    string result;
    if (dir == Direction::Horizontal) {
        if (Page.size() <= row) {
            Page.resize(row + 1);
        }
        result = Page.at(row).readAt(col, toRead);
    } else {
        if (Page.size() <= row + toRead) {
            Page.resize(row + toRead);
        }
        for (unsigned int i = row; i < row + toRead; i++) {
            result += Page.at(i).readAt(col);
        }
    }
    return result;
}

void Page::printPage() {
    for (unsigned int i = 0; i < Page.size(); i++) {
        cout << Page.at(i).readAt(0, MAXROWLENGTH) << endl;
    }
}

unsigned int Page::size() {
    return Page.size(); 
}

// ------------------------ End Class Page -------------------------------------  

//---------------------------- Class Notebook---------------------------------

void Notebook::check_errors(const unsigned int page, const unsigned int row, const unsigned int col, Direction dir, const string &toWrite,
const unsigned int length, NotebookThrows func) {
    if (col >= MAXROWLENGTH) {
        throw logic_error("Col cannot be greater or equal to 100");
    }

    if (func == NotebookThrows::Write) {
        if (col + toWrite.size() >= MAXROWLENGTH) {
            throw out_of_range("Cannot write more than 100 characters per row");
        }
        string st = this->read(page, row, col, dir, toWrite.size());
        for (unsigned int i = 0; i < toWrite.size(); i++) {
            if (st.at(i) != EMPTYSPACE) {
                if (st.at(i) == DELETE) {
                    throw logic_error("Cannot rewrite after erasing");
                }
                throw logic_error("Cannot rewrite on written places");
            }
        }
    }
    
    if (func == NotebookThrows::Read) {
        if (col + length >= MAXROWLENGTH) {
            throw out_of_range("Cannot read after max row length (100)");
        }
    }

    if (func == NotebookThrows::Erase) {
        if (col + length >= MAXROWLENGTH) {
            throw out_of_range("Cannot erase after max row length (100)");
        }
    }
}

void Notebook::write(const unsigned int page, const unsigned int row, const unsigned int col, Direction dir, const string &toWrite) {
    Notebook::check_errors(page, row, col, dir, toWrite, 0, NotebookThrows::Write);
    if (pages.size() <= page) {
        pages.resize(page + 1);
    }
    pages.at(page).writeAt(row, col, dir, toWrite);
}

void Notebook::erase(const unsigned int page, const unsigned int row, const unsigned int col, Direction dir, const unsigned int toErase) {
    Notebook::check_errors(page, row, col, dir, "", toErase, NotebookThrows::Erase);
    if (pages.size() <= page) {
        pages.resize(page + 1);
    }
    pages.at(page).deleteAt(row, col, dir, toErase);
}

string Notebook::read(const unsigned int page, const unsigned int row, const unsigned int col, Direction dir, const unsigned int toRead) {
    Notebook::check_errors(page, row, col, dir, "", toRead, NotebookThrows::Read);
    if (pages.size() <= page) {
        pages.resize(page + 1);
    }
    return pages.at(page).readAt(row, col, dir, toRead);
}

void Notebook::show(const unsigned int page) {
    string toPrint;
    Page currentPage = pages.at(page);
    for (unsigned int i = 0; i < currentPage.size(); i++) {
        string s = to_string(i);
        toPrint.append(s + ": ");
        toPrint.append(currentPage.readAt(i, 0, Direction::Horizontal, MAXROWLENGTH));
        toPrint += '\n';
    }
    cout << toPrint << endl;
}
//--------------------------- End Class Notebook -----------------------------------
