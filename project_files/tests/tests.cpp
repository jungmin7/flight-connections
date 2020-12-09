//tests
#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../airport.h"

#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

// #include <stdlib.h>
#include <algorithm>
#include <utility>
#include <string>
#include <set>

using namespace std;

static map<string, pair<double, double>> airport_results = {

    {"GKA",{-6.081689834590001,145.391998291}},
    {"MAG",{-5.20707988739,145.789001465}},
    {"HGU",{-5.826789855957031,144.29600524902344,}},
    {"LAE",{-6.569803,146.725977}},
    {"POM",{-9.443380355834961,147.22000122070312,}},
    {"WWK",{-3.58383011818,143.669006348}}

};




// static map<pair<string,string>, double> dist_results = {
    

// };

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


// need to change since the constructor changed

TEST_CASE("test_shortestPath", "")
{
    Flights air("routes_test.txt","airports_test.txt");
    double path = air.shortestPath("EGO","KGD");
    int path_result = (int)air.distanceHaversine(50.643798828125,36.5900993347168,54.88999938964844,20.592599868774414);
    REQUIRE(path == path_result);

}



