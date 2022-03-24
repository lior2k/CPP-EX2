#include "Direction.hpp"
#include "vector"
#include <string>
using namespace std;

namespace ariel {

    class Row {
        private:
            vector<char> row;
        public:
            Row();
            // ~Row();
            void writeAt(unsigned int index, char toWrite);
            void writeAt(unsigned int index, string toWrite);
            void deleteAt(unsigned int index);
            void deleteAt(unsigned int index, unsigned int toErase);
            char readAt(unsigned int index);
            string readAt(unsigned int index, unsigned int toRead);
            void printRow();
    };

    class Page {
        private:
            vector<Row> Page;
        public:
            // ~Page();
            void writeAt(unsigned int row, unsigned int col, Direction dir, string toWrite);
            void deleteAt(unsigned int row, unsigned int col, Direction dir, unsigned int toErase);
            string readAt(unsigned int row, unsigned int col, Direction dir, unsigned int toRead);
            void printPage();
            unsigned int size();
    };

    class Notebook {
        private:
            vector<Page> pages;
        public:
            void write(unsigned int page, unsigned int row, unsigned int col, Direction dir, std::string toWrite);
            void erase(unsigned int page, unsigned int row, unsigned int col, Direction dir, unsigned int toErase);
            std::string read(unsigned int page, unsigned int row, unsigned int col, Direction dir, unsigned int toRead);
            void show(unsigned int page);
            void check_errors(unsigned int page, unsigned int row, unsigned int col, ariel::Direction dir, const std::string &toWrite);
    };

}