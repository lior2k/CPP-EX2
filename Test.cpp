#include "doctest.h"
#include <string>
#include "Notebook.hpp"
#include "Direction.hpp"
using namespace ariel;
using namespace std;


// TEST_CASE("Good input") {
// 	CHECK(nospaces(mat(9, 7, '@', '-')) == nospaces("@@@@@@@@@\n"
// 													"@-------@\n"
// 													"@-@@@@@-@\n"
// 													"@-@---@-@\n"
// 													"@-@@@@@-@\n"
// 													"@-------@\n"
// 													"@@@@@@@@@"));

TEST_CASE("GI") {
    Notebook nb;
    CHECK(nb.read(10,10,10,Direction::Horizontal, 5) == "nices");
}