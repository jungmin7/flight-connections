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

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////// Reading airports.txt Test Cases ////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("test_readAirports1", "[readAirports]")
{
    cout << "[test_readAirports1]" << endl;
    Flights air("routes_test.txt", "airports_test.txt");
    map<string, pair<double, double>> myMap = air.readAirports();
    
    // expected value from data file: "SIN", 1.35019, 103.994003
    // actual value printed from function: 1.35019, 103.994

    double expected_long = 1.35019;
    double expected_lat = 103.994003;

    double actual_long = myMap["SIN"].first;
    double actual_lat = myMap["SIN"].second;

    bool test = true;
    if (!(expected_long - 0.001 < actual_long && expected_long + 0.001 > actual_long)) {
        test = false;
    }
    if (!(expected_lat - 0.001 < actual_lat && expected_lat + 0.001 > actual_lat)) {
        test = false;
    }

    cout << "Expected longitude and latitude for SIN: " << expected_long << ", " << expected_lat <<endl;
    cout << "Actual longitude and latitude for SIN: " << actual_long << ", " << actual_lat << endl;
    cout << " " << endl;

    REQUIRE(test);
}

TEST_CASE("test_readAirports2", "[readAirports]")
{
    cout << "[test_readAirports2]" << endl;
    Flights air("routes_test.txt", "airports_test.txt");
    map<string, pair<double, double>> myMap = air.readAirports();
    
    // expected value from data file: "ICN", 37.46910095214844,126.45099639892578
    // actual value printed from function: 37.4691, 126.451

    double expected_long = 37.46910095214844;
    double expected_lat = 126.45099639892578;

    double actual_long = myMap["ICN"].first;
    double actual_lat = myMap["ICN"].second;

    bool test = true;
    if (!(expected_long - 0.001 < actual_long && expected_long + 0.001 > actual_long)) {
        test = false;
    }
    if (!(expected_lat - 0.001 < actual_lat && expected_lat + 0.001 > actual_lat)) {
        test = false;
    }

    cout << "Expected longitude and latitude for ICN: " << expected_long << ", " << expected_lat <<endl;
    cout << "Actual longitude and latitude for ICN: " << actual_long << ", " << actual_lat << endl;
    cout << " " << endl;

    REQUIRE(test);

}

TEST_CASE("test_readAirports3", "[readAirports]")
{
    cout << "[test_readAirports3]" << endl;
    Flights air("routes_test.txt", "airports.txt");
    map<string, pair<double, double>> myMap = air.readAirports();
    
    // expected value from data file: "JFK", 40.63980103, -73.77890015
    // actual value printed from function: 40.6398 -73.7789

    double expected_long = 40.63980103;
    double expected_lat = -73.77890015;

    double actual_long = myMap["JFK"].first;
    double actual_lat = myMap["JFK"].second;

    bool test = true;
    if (!(expected_long - 0.001 < actual_long && expected_long + 0.001 > actual_long)) {
        test = false;
    }
    if (!(expected_lat - 0.001 < actual_lat && expected_lat + 0.001 > actual_lat)) {
        test = false;
    }

    cout << "Expected longitude and latitude for JFK: " << expected_long << ", " << expected_lat <<endl;
    cout << "Actual longitude and latitude for JFK: " << actual_long << ", " << actual_lat << endl;
    cout << " " << endl;

    REQUIRE(test);

}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////// Reading routes.txt Test Cases ////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("test_readFlights1", "[readFlights]")
{
    cout << "[test_readFlights1]" << endl;
    Flights air("routes_test.txt", "airports_test.txt");
    map<pair<Vertex, Vertex>, int> m = air.readFlights();

    int expected = m[{"SIN", "ICN"}];
    int actual = 4613;
    cout << "Expected distance between SIN and ICN: " << expected << " km" <<endl;
    cout << "Actual distance between SIN and ICN: " << actual << " km" << endl;
    bool check = actual - 30 < expected && actual + 30 > expected;
    if(check && actual != expected)
    {
        cout << "(Within margin of error)" << endl;
    }

    cout << " " << endl;
    REQUIRE(check);
}

TEST_CASE("test_readFlights2", "[readFlights]")
{
    cout << "[test_readFlights2]" << endl;
    Flights air("routes_test.txt", "airports_test.txt");
    map<pair<Vertex, Vertex>, int> m = air.readFlights();

    int expected = m[{"KZN", "CEK"}];
    int actual = 773;

    cout << "Expected distance between KZN and CEK: " << expected << " km" << endl;
    cout << "Actual distance between KZN and CEK: " << actual << " km" << endl;
    bool check = actual - 30 < expected && actual + 30 > expected;
    if(check && actual != expected)
    {
        cout << "(Within margin of error)" << endl;
    }

    cout << " " << endl;
    REQUIRE(check);
}

TEST_CASE("test_readFlights3", "[readFlights]")
{
    cout << "[test_readFlights3]" << endl;
    Flights air("routes_test.txt", "airports_test.txt");
    map<pair<Vertex, Vertex>, int> m = air.readFlights();

    int expected = m[{"DME", "TGK"}];
    int actual = 916;

    cout << "Expected distance between DME and TGK: " << expected << " km" << endl;
    cout << "Actual distance between DME and TGK: " << actual << " km" << endl;

    bool check = actual - 30 < expected && actual + 30 > expected;
    if(check && actual != expected)
    {
        cout << "(Within margin of error)" << endl;
    }

    cout << " " << endl;
    REQUIRE(check);
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

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//////////////////////// Shortest Path Tests ////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

TEST_CASE("test_sample_simple_shortestPath", "[shortestPath]") {
    cout << "[test_sample_simple_shortestPath]" << endl;

    //Creating test graph
    Flights air("routes_test.txt","airports_test.txt");
    Graph pathTest(true, true);
    
    Vertex v0 = "0";
    Vertex v1 = "1";
    Vertex v2 = "2";
    Vertex v3 = "3";
    Vertex v4 = "4";
    Vertex v5 = "5";
    Vertex v6 = "6";
    Vertex v7 = "7";
    Vertex v8 = "8";

    pathTest.insertVertex(v0);
    pathTest.insertVertex(v1);
    pathTest.insertVertex(v2);
    pathTest.insertVertex(v3);
    pathTest.insertVertex(v4);
    pathTest.insertVertex(v5);
    pathTest.insertVertex(v6);
    pathTest.insertVertex(v7);
    pathTest.insertVertex(v8);

    pathTest.insertEdge("1", "2");
    pathTest.insertEdge("2", "3");
    pathTest.insertEdge("3", "0");
    pathTest.insertEdge("0", "1");
    pathTest.insertEdge("2", "4");
    pathTest.insertEdge("4", "5");
    pathTest.insertEdge("5", "6");
    pathTest.insertEdge("6", "4");
    pathTest.insertEdge("7", "6");
    pathTest.insertEdge("7", "8");

    pathTest.setEdgeWeight("1", "2", 2);
    pathTest.setEdgeWeight("2", "3", 3);
    pathTest.setEdgeWeight("3", "0", 1);
    pathTest.setEdgeWeight("0", "1", 4);
    pathTest.setEdgeWeight("2", "4", 6);
    pathTest.setEdgeWeight("4", "5", 2);
    pathTest.setEdgeWeight("5", "6", 7);
    pathTest.setEdgeWeight("6", "4", 2);
    pathTest.setEdgeWeight("7", "6", 9);
    pathTest.setEdgeWeight("7", "8", 2);

    air.g = pathTest;

    int dist = 17;
    int dist_result = air.shortestPath("1", "6");

    cout << "Expected distace: " << dist << endl;
    cout << "Actual distace: " << dist_result << endl;
    cout << " " << endl;
  
    REQUIRE(dist == dist_result);
}

TEST_CASE("test_sample_complex_shortestPath", "[shortestPath]") {
    cout << "[test_sample_complex_shortestPath]" << endl;

    //Creating test graph
    Flights air("routes_test.txt","airports_test.txt");
    Graph pathTest(true, true);
    Vertex v0 = "0";
    Vertex v1 = "1";
    Vertex v2 = "2";
    Vertex v3 = "3";
    Vertex v4 = "4";
    Vertex v5 = "5";
    Vertex v6 = "6";
    Vertex v7 = "7";
    Vertex v8 = "8";

    pathTest.insertVertex(v0);
    pathTest.insertVertex(v1);
    pathTest.insertVertex(v2);
    pathTest.insertVertex(v3);
    pathTest.insertVertex(v4);
    pathTest.insertVertex(v5);
    pathTest.insertVertex(v6);
    pathTest.insertVertex(v7);
    pathTest.insertVertex(v8);

    pathTest.insertEdge("1", "2");
    pathTest.insertEdge("2", "3");
    pathTest.insertEdge("3", "0");
    pathTest.insertEdge("0", "1");
    pathTest.insertEdge("2", "4");
    pathTest.insertEdge("4", "5");
    pathTest.insertEdge("5", "6");
    pathTest.insertEdge("4", "6");
    pathTest.insertEdge("7", "6");
    pathTest.insertEdge("7", "8");
    pathTest.insertEdge("2", "5");

    pathTest.setEdgeWeight("1", "2", 2);
    pathTest.setEdgeWeight("2", "3", 3);
    pathTest.setEdgeWeight("3", "0", 1);
    pathTest.setEdgeWeight("0", "1", 4);
    pathTest.setEdgeWeight("2", "4", 6);
    pathTest.setEdgeWeight("4", "5", 2);
    pathTest.setEdgeWeight("5", "6", 7);
    pathTest.setEdgeWeight("4", "6", 9);
    pathTest.setEdgeWeight("7", "6", 9);
    pathTest.setEdgeWeight("7", "8", 2);
    pathTest.setEdgeWeight("2", "5", 1);
    air.g = pathTest;
    int dist = 10;
    int dist_result = air.shortestPath("1", "6");
  
    cout << "Expected distace: " << dist << endl;
    cout << "Actual distace: " << dist_result << endl;
    cout << " " << endl;
  
    REQUIRE(dist == dist_result);
}


TEST_CASE("test_flights_shortestPath", "[shortestPath]")
{
    cout << "[test_flights_shortestPath]" << endl;
    Flights air("routes_test.txt","airports_test.txt");

    int path = air.shortestPath("EGO","KGD");
    int path_result = air.distanceHaversine(50.643798828125,36.5900993347168,54.88999938964844,20.592599868774414);
    
    cout << "Expected distace: " << path_result << endl;
    cout << "Actual distace: " << path << endl;
    cout << " " << endl;
    
    REQUIRE(path == path_result);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//////////////// Strongly Connected Components Tests ////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

TEST_CASE("test_sample_simple_stronglyConnected", "[stronglyConnected]") {
    cout << "[test_sample_simple_stronglyConnected]" << endl;

    //Creating test graph
    Flights air("routes_test.txt","airports_test.txt");
    Graph pathTest(true, true);
    Vertex v0 = "0";
    Vertex v1 = "1";
    Vertex v2 = "2";
    Vertex v3 = "3";
    Vertex v4 = "4";
    Vertex v5 = "5";
    Vertex v6 = "6";
    Vertex v7 = "7";
    Vertex v8 = "8";
    pathTest.insertVertex(v0);
    pathTest.insertVertex(v1);
    pathTest.insertVertex(v2);
    pathTest.insertVertex(v3);
    pathTest.insertVertex(v4);
    pathTest.insertVertex(v5);
    pathTest.insertVertex(v6);
    pathTest.insertVertex(v7);
    pathTest.insertVertex(v8);
    pathTest.insertEdge("1", "2");
    pathTest.insertEdge("2", "3");
    pathTest.insertEdge("3", "0");
    pathTest.insertEdge("0", "1");
    pathTest.insertEdge("2", "4");
    pathTest.insertEdge("4", "5");
    pathTest.insertEdge("5", "6");
    pathTest.insertEdge("6", "4");
    pathTest.insertEdge("7", "6");
    pathTest.insertEdge("7", "8");
    pathTest.setEdgeWeight("1", "2", 2);
    pathTest.setEdgeWeight("2", "3", 3);
    pathTest.setEdgeWeight("3", "0", 1);
    pathTest.setEdgeWeight("0", "1", 4);
    pathTest.setEdgeWeight("2", "4", 6);
    pathTest.setEdgeWeight("4", "5", 2);
    pathTest.setEdgeWeight("5", "6", 7);
    pathTest.setEdgeWeight("6", "4", 2);
    pathTest.setEdgeWeight("7", "6", 9);
    pathTest.setEdgeWeight("7", "8", 2);
    air.g = pathTest;

    //Creating actual and expected variables
    vector<vector<Vertex>> actual = air.stronglyConnected();

    vector<vector<Vertex>> expected;
    vector<Vertex> list;
    list.push_back("7");
    expected.push_back(list);
    list.clear();
    list.push_back("8");
    expected.push_back(list);
    list.clear();
    list.push_back("0");
    list.push_back("3");
    list.push_back("2");
    list.push_back("1");
    expected.push_back(list);
    list.clear();
    list.push_back("4");
    list.push_back("6");
    list.push_back("5");
    expected.push_back(list);

    cout << " " << endl;
    REQUIRE(actual == expected);
}

TEST_CASE("test_sample_complex_stronglyConnected", "[stronglyConnected]") {
    cout << "[test_sample_complex_stronglyConnected]" << endl;

    //Creating test graph
    Flights air("routes_test.txt","airports_test.txt");
    Graph pathTest(true, true);
    Vertex v0 = "0";
    Vertex v1 = "1";
    Vertex v2 = "2";
    Vertex v3 = "3";
    Vertex v4 = "4";
    Vertex v5 = "5";
    Vertex v6 = "6";
    Vertex v7 = "7";
    Vertex v8 = "8";
    pathTest.insertVertex(v0);
    pathTest.insertVertex(v1);
    pathTest.insertVertex(v2);
    pathTest.insertVertex(v3);
    pathTest.insertVertex(v4);
    pathTest.insertVertex(v5);
    pathTest.insertVertex(v6);
    pathTest.insertVertex(v7);
    pathTest.insertVertex(v8);
    pathTest.insertEdge("1", "2");
    pathTest.insertEdge("2", "3");
    pathTest.insertEdge("3", "0");
    pathTest.insertEdge("0", "1");
    pathTest.insertEdge("2", "4");
    pathTest.insertEdge("4", "5");
    pathTest.insertEdge("5", "6");
    pathTest.insertEdge("4", "6");
    pathTest.insertEdge("6", "7");
    pathTest.insertEdge("7", "8");
    pathTest.insertEdge("8", "6");
    pathTest.insertEdge("2", "5");
    pathTest.setEdgeWeight("1", "2", 2);
    pathTest.setEdgeWeight("2", "3", 3);
    pathTest.setEdgeWeight("3", "0", 1);
    pathTest.setEdgeWeight("0", "1", 4);
    pathTest.setEdgeWeight("2", "4", 6);
    pathTest.setEdgeWeight("4", "5", 2);
    pathTest.setEdgeWeight("5", "6", 7);
    pathTest.setEdgeWeight("4", "6", 9);
    pathTest.setEdgeWeight("6", "7", 9);
    pathTest.setEdgeWeight("7", "8", 2);
    pathTest.setEdgeWeight("8", "6", 3);
    pathTest.setEdgeWeight("2", "5", 1);
    air.g = pathTest;

    ////Creating actual and expected variables
    vector<vector<Vertex>> actual = air.stronglyConnected();

    vector<vector<Vertex>> expected;
    vector<Vertex> list;
    list.push_back("0");
    list.push_back("3");
    list.push_back("2");
    list.push_back("1");
    expected.push_back(list);
    list.clear();
    list.push_back("4");
    expected.push_back(list);
    list.clear();
    list.push_back("5");
    expected.push_back(list);
    list.clear();
    list.push_back("6");
    list.push_back("8");
    list.push_back("7");
    expected.push_back(list);

    cout << " " << endl;
    REQUIRE(actual == expected);
}

TEST_CASE("test_flights_stronglyConnected", "[stronglyConnected]") {
    cout << "[test_flights_stronglyConnected]" << endl;

    //Creating test graph
    Flights air("routes_test.txt","airports_test.txt");

    //Creating actual and expected variables
    vector<vector<Vertex>> actual = air.stronglyConnected();

    vector<vector<Vertex>> expected;
    vector<Vertex> list;
    list.push_back("GYD");
    expected.push_back(list);
    list.clear();
    list.push_back("KGD");
    list.push_back("EGO");
    list.push_back("KZN");
    list.push_back("ASF");
    list.push_back("AER");
    list.push_back("CEK");
    list.push_back("DME");
    expected.push_back(list);
    list.clear();
    list.push_back("MRV");
    expected.push_back(list);
    list.clear();
    list.push_back("OVB");
    expected.push_back(list);
    list.clear();
    list.push_back("NBC");
    expected.push_back(list);
    list.clear();
    list.push_back("TGK");
    expected.push_back(list);
    list.clear();
    list.push_back("UUA");
    expected.push_back(list);
    list.clear();
    list.push_back("LED");
    expected.push_back(list);
    list.clear();
    list.push_back("SVX");
    expected.push_back(list);
    list.clear();
    list.push_back("ICN");
    list.push_back("SIN");
    expected.push_back(list);

    cout << " " << endl;
    REQUIRE(actual == expected);
}