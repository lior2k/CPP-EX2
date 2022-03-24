

#include "Notebook.hpp"
#include "Direction.hpp"
using ariel::Direction;
using namespace ariel;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    Notebook nb;
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

    nb.show(0);

    nb.show(1);

    nb.show(2);

    nb.write(2, 2, 0, Direction::Horizontal, "ddadadadad");
    nb.show(2);

    nb.write(3, 0, 90, Direction::Horizontal, "writing this will result in line being longer then 100");
    nb.show(3);
}
    

