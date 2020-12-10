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

TEST_CASE("test_shortestPath", "[shortestPath]")
{
    cout << "[test_shortestPath]" << endl;
    Flights air("routes_test.txt","airports_test.txt");
    int path = air.shortestPath("EGO","KGD");
    int path_result = air.distanceHaversine(50.643798828125,36.5900993347168,54.88999938964844,20.592599868774414);
    cout << "Expected distace: " << path_result << endl;
    cout << "Actual distace: " << path << endl;
    cout << " " << endl;
    REQUIRE(path == path_result);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////////// BFS Test Cases ////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

/** To test all BFS cases, run ./test [BFS] 
 * To test only this test case, run ./test test_integerEasy_BFS
 */
TEST_CASE("test_integerEasy_BFS", "[BFS]")
{
    cout << "[test_integerEasy_BFS]" << endl;
    Flights air("routes_test.txt","airports_test.txt");

    Graph bfsGraph(true, true);
    
    Vertex v0 = "0";
    Vertex v1 = "1";
    Vertex v2 = "2";
    Vertex v3 = "3";
    Vertex v4 = "4";
    Vertex v5 = "5";
    Vertex v6 = "6";
    Vertex v7 = "7";
    Vertex v8 = "8";

    for (int i = 0; i <= 8; i++) {
        bfsGraph.insertVertex(to_string(i));
    }

    bfsGraph.insertEdge("0", "1");
    bfsGraph.insertEdge("1", "2");
    bfsGraph.insertEdge("2", "3");
    bfsGraph.insertEdge("3", "4");
    bfsGraph.insertEdge("4", "5");
    bfsGraph.insertEdge("5", "6");
    bfsGraph.insertEdge("6", "7");
    bfsGraph.insertEdge("7", "8");
    bfsGraph.insertEdge("8", "0");

    /** change the graph change the graph of airports to being this one of integers for testing purposes */
    air.g = bfsGraph;

    /** print the graph if needed */
    // air.g.print();

    /** call BFS to output traversal */
    vector<Vertex> returnVector = air.BFS("0");

    /** since BFS only returns a vector of string Vertices, to test the algorithm, convert integers to strings */
    vector<Vertex> testVector;
    for (int i = 0; i <= 8; i++) {
        testVector.push_back(to_string(i));
    }

    cout << "Expected number of vertices that should be visited: " << testVector.size() << " vertices \n";
    cout << "Actual number of vertices visited: " << returnVector.size() << " vertices \n";
    cout << "\n" << endl; //to create a line space between test case iterations.

    REQUIRE(returnVector == testVector);
}


TEST_CASE("test_integerMedium_BFS", "[BFS]")
{
    cout << "[test_integerMedium_BFS]" << endl;
    Flights air("routes_test.txt","airports_test.txt");

    Graph bfsGraph(true, true);
    
    Vertex v0 = "0";
    Vertex v1 = "1";
    Vertex v2 = "2";
    Vertex v3 = "3";
    Vertex v4 = "4";
    Vertex v5 = "5";
    Vertex v6 = "6";
    Vertex v7 = "7";
    Vertex v8 = "8";

    bfsGraph.insertEdge("1", "2");
    bfsGraph.insertEdge("2", "4");
    bfsGraph.insertEdge("3", "0");
    bfsGraph.insertEdge("0", "1");
    bfsGraph.insertEdge("2", "3");
    bfsGraph.insertEdge("4", "5");
    bfsGraph.insertEdge("5", "8");
    bfsGraph.insertEdge("6", "4");
    bfsGraph.insertEdge("7", "6");
    bfsGraph.insertEdge("7", "8");
    bfsGraph.insertEdge("8", "4");

    air.g = bfsGraph;

    /** call BFS to output traversal */
    vector<Vertex> returnVector = air.BFS("0");

    /** since BFS only returns a vector of string Vertices, to test the algorithm, convert integers to strings */
    /** this SOLUTION VECTOR was found via running a BFS simulation on https://visualgo.net/en/dfsbfs */
    vector<Vertex> testVector;
        testVector.push_back(to_string(0));
        testVector.push_back(to_string(1));
        testVector.push_back(to_string(2));
        testVector.push_back(to_string(3));
        testVector.push_back(to_string(4));
        testVector.push_back(to_string(5));
        testVector.push_back(to_string(8));

    cout << "Expected number of vertices that should be visited: " << testVector.size() << " vertices \n";
    cout << "Actual number of vertices visited: " << returnVector.size() << " vertices \n";
    cout << "\n" << endl; //to create a line space between test case iterations.

    REQUIRE(returnVector == testVector);
}

TEST_CASE("test_integerHard_1_BFS", "[BFS]")
{
    cout << "[test_integerHard_1_BFS]" << endl;
    Flights air("routes_test.txt","airports_test.txt");

    Graph bfsGraph(true, true);
    
    Vertex v0 = "0";
    Vertex v1 = "1";
    Vertex v2 = "2";
    Vertex v3 = "3";
    Vertex v4 = "4";
    Vertex v5 = "5";
    Vertex v6 = "6";
    Vertex v7 = "7";
    Vertex v8 = "8";

    bfsGraph.insertEdge("0", "1");
    bfsGraph.insertEdge("1", "0");

    bfsGraph.insertEdge("1", "2");
    bfsGraph.insertEdge("2", "0");

    bfsGraph.insertEdge("2", "3");
    bfsGraph.insertEdge("3", "0");

    bfsGraph.insertEdge("3", "4");
    bfsGraph.insertEdge("4", "2");

    bfsGraph.insertEdge("2", "7");
    bfsGraph.insertEdge("7", "4");

    bfsGraph.insertEdge("4", "5");
    bfsGraph.insertEdge("5", "8");

    bfsGraph.insertEdge("8", "6");
    bfsGraph.insertEdge("6", "7");


    air.g = bfsGraph;

    /** call BFS to output traversal */
    vector<Vertex> returnVector = air.BFS("2");

    /** since BFS only returns a vector of string Vertices, to test the algorithm, convert integers to strings */
    /** this SOLUTION VECTOR was found via running a BFS simulation on https://visualgo.net/en/dfsbfs */
    vector<Vertex> testVector;
        testVector.push_back(to_string(2));
        testVector.push_back(to_string(0));
        testVector.push_back(to_string(3));
        testVector.push_back(to_string(7));
        testVector.push_back(to_string(1));
        testVector.push_back(to_string(4));
        testVector.push_back(to_string(5));
        testVector.push_back(to_string(8));
        testVector.push_back(to_string(6));


    cout << "Expected number of vertices that should be visited: " << testVector.size() << " vertices \n";
    cout << "Actual number of vertices visited: " << returnVector.size() << " vertices \n";
    cout << "\n" << endl; //to create a line space between test case iterations.

    REQUIRE(returnVector == testVector);
}

/** Same code as test_integerHard_1_BFS, but starting point is changed, resulting in different search */
TEST_CASE("test_integerHard_2_BFS", "[BFS]") {
    cout << "[test_integerHard_2_BFS]" << endl;
    Flights air("routes_test.txt","airports_test.txt");

    Graph bfsGraph(true, true);
    
    Vertex v0 = "0";
    Vertex v1 = "1";
    Vertex v2 = "2";
    Vertex v3 = "3";
    Vertex v4 = "4";
    Vertex v5 = "5";
    Vertex v6 = "6";
    Vertex v7 = "7";
    Vertex v8 = "8";

    bfsGraph.insertEdge("0", "1");
    bfsGraph.insertEdge("1", "0");

    bfsGraph.insertEdge("1", "2");
    bfsGraph.insertEdge("2", "0");

    bfsGraph.insertEdge("2", "3");
    bfsGraph.insertEdge("3", "0");

    bfsGraph.insertEdge("3", "4");
    bfsGraph.insertEdge("4", "2");

    bfsGraph.insertEdge("2", "7");
    bfsGraph.insertEdge("7", "4");

    bfsGraph.insertEdge("4", "5");
    bfsGraph.insertEdge("5", "8");

    bfsGraph.insertEdge("8", "6");
    bfsGraph.insertEdge("6", "7");


    air.g = bfsGraph;

    /** call BFS to output traversal */
    vector<Vertex> returnVector = air.BFS("8");

    /** since BFS only returns a vector of string Vertices, to test the algorithm, convert integers to strings */
    /** this SOLUTION VECTOR was found via running a BFS simulation on https://visualgo.net/en/dfsbfs */
    vector<Vertex> testVector;
        testVector.push_back(to_string(8));
        testVector.push_back(to_string(6));
        testVector.push_back(to_string(7));
        testVector.push_back(to_string(4));
        testVector.push_back(to_string(5));
        testVector.push_back(to_string(2));
        testVector.push_back(to_string(0));
        testVector.push_back(to_string(3));
        testVector.push_back(to_string(1));

    cout << "Expected number of vertices that should be visited: " << testVector.size() << " vertices \n";
    cout << "Actual number of vertices visited: " << returnVector.size() << " vertices \n";
    cout << "\n" << endl; //to create a line space between test case iterations.

    REQUIRE(returnVector == testVector);
}



TEST_CASE("test_Flights_BFS", "[BFS]") {
    cout << "[test_Flights_BFS]" << endl;
    Flights air("routes_test.txt","airports_test.txt");

    /** call BFS to output traversal */
    vector<Vertex> returnVector = air.BFS("ASF");

    /** since BFS only returns a vector of string Vertices, to test the algorithm, convert integers to strings */
    /** this SOLUTION VECTOR was found via running a BFS simulation on https://visualgo.net/en/dfsbfs */
    vector<Vertex> testVector;
        testVector.push_back("ASF");
        testVector.push_back("MRV");
        testVector.push_back("KZN");
        testVector.push_back("SVX");
        testVector.push_back("DME");
        testVector.push_back("CEK");
        testVector.push_back("EGO");
        testVector.push_back("LED");
        testVector.push_back("AER");
        testVector.push_back("UUA");
        testVector.push_back("TGK");
        testVector.push_back("NBC");
        testVector.push_back("OVB");
        testVector.push_back("KGD");


    cout << "Expected number of vertices that should be visited: " << testVector.size() << " vertices \n";
    cout << "Actual number of vertices visited: " << returnVector.size() << " vertices \n";
    cout << "\n" << endl; //to create a line space between test case iterations.

    REQUIRE(returnVector == testVector);
}

TEST_CASE("test_mediumFlights_BFS", "[BFS]") {
}

