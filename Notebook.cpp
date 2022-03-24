#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
using ariel::Direction;
using namespace ariel;
using namespace std;
unsigned int const MAXROWLENGTH = 100;
char const EMPTYSPACE = '_';
char const DELETE = '~';

//---------------------------- Class Notebook---------------------------------

void ariel::Notebook::check_errors(unsigned int page, unsigned int row, unsigned int col, ariel::Direction dir, const std::string &toWrite) {
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

void ariel::Notebook::write(unsigned int page, unsigned int row, unsigned int col, ariel::Direction dir, std::string toWrite) {
    if (pages.size() <= page) {
        pages.resize(page + 1);
    }
    ariel::Notebook::check_errors(page, row, col, dir, toWrite);
    pages.at(page).writeAt(row, col, dir, std::move(toWrite));
}

void ariel::Notebook::erase(unsigned int page, unsigned int row, unsigned int col, ariel::Direction dir, unsigned int toErase) {
    if (pages.size() <= page) {
        pages.resize(page + 1);
    }
    pages.at(page).deleteAt(row, col, dir, toErase);
}

std::string ariel::Notebook::read(unsigned int page, unsigned int row, unsigned int col, ariel::Direction dir, unsigned int toRead) {
    if (pages.size() <= page) {
        pages.resize(page + 1);
    }
    return pages.at(page).readAt(row, col, dir, toRead);
}

void ariel::Notebook::show(unsigned int page) {
    string toPrint;
    Page currentPage = pages.at(page);
    for (unsigned int i = 0; i < currentPage.size(); i++) {
        std::string s = std::to_string(i);
        toPrint.append(s + ": ");
        toPrint.append(currentPage.readAt(i, 0, Direction::Horizontal, MAXROWLENGTH));
        toPrint += '\n';
    }
    std::cout << toPrint << endl;
}
//--------------------------- End Class Notebook -----------------------------------

//------------------------------ Class Row -----------------------------------------

ariel::Row::Row() {
    for (int i = 0; i < MAXROWLENGTH; i++) {
        row.push_back(EMPTYSPACE);
    }
}

// ariel::Row::~Row() {
//     delete[] st;
// }

void ariel::Row::writeAt(unsigned int index, char toWrite) {
    row.at(index) = toWrite;
}

void ariel::Row::writeAt(unsigned int index, string toWrite) {
    for (unsigned int i = 0; i < toWrite.size(); i++) {
        row.at(index + i) = toWrite[i];
    }
}

void ariel::Row::deleteAt(unsigned int index) {
    row.at(index) = DELETE;
}

void ariel::Row::deleteAt(unsigned int index, unsigned int toErase) {
    for (unsigned int i = 0; i < toErase; i++) {
        row.at(index + i) = DELETE;
    }
}

char ariel::Row::readAt(unsigned int index) {
    return row.at(index);
}

std::string ariel::Row::readAt(unsigned int index, unsigned int toRead) {
    string read;
    for (unsigned int i = 0; i < toRead; i++) {
        read += row.at(index + i);
    }
    return read;
}

void ariel::Row::printRow() {
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

void ariel::Page::writeAt(unsigned int row, unsigned int col, Direction dir, string toWrite) {
    if (dir == Direction::Horizontal) {
        if (Page.size() <= row) {
            Page.resize(row + 1);
        }
        Page.at(row).writeAt(col, toWrite);
    }

    if (dir == Direction::Vertical) {
        if (Page.size() <= row + toWrite.size()) {
            Page.resize(row + 1 + toWrite.size());
        }
        unsigned int k = 0;
        for (unsigned int i = row; i < row + toWrite.size(); i++) {
            Page.at(i).writeAt(col, toWrite[k]);
            k += 1;
        }
    }
}

void ariel::Page::deleteAt(unsigned int row, unsigned int col, Direction dir, unsigned int toErase) {
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

std::string ariel::Page::readAt(unsigned int row, unsigned int col, Direction dir, unsigned int toRead) {
    string result;
    if (dir == Direction::Horizontal) {
        if (Page.size() <= row) {
            Page.resize(row + 1);
        }
        result = Page.at(row).readAt(col, toRead);
    } else {
        if (Page.size() <= row + toRead) {
            Page.resize(row + 1 + toRead);
        }
        for (unsigned int i = row; i < row + toRead; i++) {
            result += Page.at(i).readAt(col);
        }
    }
    return result;
}

void ariel::Page::printPage() {
    for (unsigned int i = 0; i < Page.size(); i++) {
        std::cout << Page.at(i).readAt(0, MAXROWLENGTH) << endl;
    }
}

unsigned int ariel::Page::size() {
    return Page.size(); 
}

// ------------------------ End Class Page -------------------------------------  


