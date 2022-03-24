#include "Direction.hpp"
#include "vector"
#include <string>

namespace ariel {

    /*
    This class is used only for the function 'Notebook::check_errors', each function (erase,write,read) passes their
    matching enum to indicate which function called 'check_errors', that way we can have 1 generic error's function.
   */
    enum class NotebookThrows {
        Erase,
        Write,
        Read
    };

    class Row {
        private:
            std::vector<char> row;
        public:
            Row();
            // ~Row();
            void writeAt(const unsigned int index, const char toWrite);
            void writeAt(const unsigned int index, const std::string &toWrite);
            void deleteAt(const unsigned int index);
            void deleteAt(const unsigned int index, const unsigned int toErase);
            char readAt(const unsigned int index);
            std::string readAt(const unsigned int index, const unsigned int toRead);
            void printRow();
    };

    class Page {
        private:
            std::vector<Row> Page;
        public:
            // ~Page();
            void writeAt(const unsigned int row, const unsigned int col, Direction dir, const std::string &toWrite);
            void deleteAt(const unsigned int row, const unsigned int col, Direction dir, const unsigned int toErase);
            std::string readAt(const unsigned int row, const unsigned int col, Direction dir, const unsigned int toRead);
            void printPage();
            unsigned int size();
    };

    class Notebook {
        private:
            std::vector<Page> pages;
        public:
            void write(const unsigned int page, const unsigned int row, const unsigned int col, Direction dir, const std::string &toWrite);
            void erase(const unsigned int page, const unsigned int row, const unsigned int col, Direction dir, const unsigned int toErase);
            std::string read(const unsigned int page, const unsigned int row, const unsigned int col, Direction dir, const unsigned int toRead);
            void show(const unsigned int page);
            
            void check_errors(const unsigned int page, const unsigned int row, const unsigned int col, Direction dir, const std::string &toWrite,
             const unsigned int length, NotebookThrows func);
    };

}