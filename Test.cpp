#include "doctest.h"
#include <string>
#include "Notebook.hpp"
#include "Direction.hpp"
using namespace ariel;
using namespace std;

TEST_CASE("Good Input") {    
    Notebook nb;
    CHECK(nb.read(3, 5, 10, Direction::Horizontal, 10) == "__________");
    CHECK(nb.read(4, 10, 10, Direction::Vertical, 10) == "__________");

    nb.write(0, 0, 0, Direction::Horizontal, "Yo, listen up heres a story");
    nb.write(0, 1, 0, Direction::Horizontal, "About a little guy");
    nb.write(0, 2, 0, Direction::Horizontal, "That lives in a blue world");
    nb.write(0, 3, 0, Direction::Horizontal, "And all day and all night");
    nb.write(0, 4, 0, Direction::Horizontal, "And everything he sees is just blue");
    nb.write(0, 5, 0, Direction::Horizontal, "Like him inside and outside");
    nb.write(1, 0, 0, Direction::Horizontal, "Blue his house");
    nb.write(1, 1, 0, Direction::Horizontal, "With a blue little window");
    nb.write(1, 2, 0, Direction::Horizontal, "And a blue corvette");
    nb.write(1, 3, 0, Direction::Horizontal, "And everything is blue for him");
    nb.write(1, 4, 0, Direction::Horizontal, "And himself and everybody around");
    nb.write(1, 5, 0, Direction::Horizontal, "Cause he ain't got nobody to listen to");
    nb.write(2, 0, 0, Direction::Horizontal, "I'm blue");
    nb.write(2, 1, 0, Direction::Horizontal, "Da ba dee da ba di");
    nb.write(2, 2, 0, Direction::Horizontal, "Da ba dee da ba di");
    CHECK(nb.read(0, 0, 4, Direction::Horizontal, 6) == "listen");
    CHECK(nb.read(0, 0, 0, Direction::Vertical, 5) == "YATAA");
    CHECK(nb.read(2, 0, 0, Direction::Horizontal, 8) == "I'm blue");
    CHECK(nb.read(2, 1, 0, Direction::Horizontal, 18) == "Da ba dee da ba di");
    CHECK(nb.read(2, 1, 0, Direction::Horizontal, 18) == nb.read(2, 2, 0, Direction::Horizontal, 18));
    CHECK(nb.read(1, 2, 0, Direction::Vertical, 3) == "AAA");
    CHECK(nb.read(1, 1, 7, Direction::Horizontal, 4) == nb.read(1, 2, 6, Direction::Horizontal, 4));

    nb.erase(2, 1 ,0, Direction::Horizontal, 18);
    CHECK(nb.read(2, 1, 0, Direction::Horizontal, 18) == "~~~~~~~~~~~~~~~~~~");
    nb.erase(2, 2, 2, Direction::Horizontal, 14);
    CHECK(nb.read(2, 2, 0, Direction::Horizontal, 18) == "Da~~~~~~~~~~~~~~di");
    nb.erase(1, 1, 7, Direction::Vertical, 4);
    CHECK(nb.read(1, 0, 7, Direction::Vertical, 6) == "s~~~~e");

    nb.write(3, 3, 3, Direction::Horizontal, "nice");
    CHECK(nb.read(3, 3, 3, Direction::Horizontal, 4) == "nice");

}

TEST_CASE("Bad Input") {
    Notebook nb;

    
    nb.write(0, 0, 0, Direction::Horizontal, "abcde");
    CHECK_THROWS(nb.write(0, 0, 4, Direction::Horizontal, "fghij")); // e and f intersects

    nb.erase(0, 0, 0, Direction::Horizontal, 2);
    CHECK_THROWS(nb.write(0, 0, 0, Direction::Horizontal, "ab")); // cant overwrite ~
    CHECK_THROWS(nb.write(0, 0, 0, Direction::Vertical, "ab"));
    nb.erase(3, 3, 3, Direction::Horizontal, 3);
    nb.erase(3, 3, 3, Direction::Vertical, 3);
    CHECK_THROWS(nb.write(3, 2, 3, Direction::Vertical, "abc"));
    CHECK_THROWS(nb.write(3, 3, 1, Direction::Horizontal, "xyz"));
    
    CHECK_THROWS(nb.write(0, 0, 90, Direction::Horizontal, "writing this will result in line being longer then 100"));
    CHECK_THROWS(nb.write(0, 0, 101, Direction::Horizontal, "abc")); // col has to be 0 <= col <= 99
    CHECK_THROWS(nb.erase(0, 0, 201, Direction::Horizontal, 10));
    CHECK_THROWS(nb.read(0, 0, 301, Direction::Horizontal, 20));
    
}
