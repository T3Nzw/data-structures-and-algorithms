#include "doctest.h"  // относителния път до doctest.h
#include "comparator.hpp"

TEST_CASE("Less") {
  int x = 10, y = 11;

  less<int> cmp;

  SUBCASE("Returns true for x<y") {
    CHECK(cmp(x,y));
  }

  SUBCASE("Returns false for x<y") {
    CHECK(!cmp(y,x));
  }
}

TEST_CASE("Finding extrema in a vector of ints") {
  std::vector<int> v{5,1,6,-1,-12,10,15};
  CHECK_EQ(extremum<int>(v), -12);
  CHECK_EQ(extremum<int, greater>(v), 15);
}
