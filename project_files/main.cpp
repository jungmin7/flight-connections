#include "graph.h"
#include "airport.h"
#include "edge.h"

#include <iostream>
#include <map>
#include <utility>
#include <cmath>
#include <queue>

using namespace std;

int main()
{
    string routes = "routes.txt"; //replace text file name here if need be but format needs to be the same as used in OpenFlights routes.dat file
    string airports = "airports.txt"; //replace text file name here if need be but format needs to be the same as used in OpenFlights airports.dat file

    //uncomment the next two lines to run main under subset of the OpenFlights data set
    //string routes = "routes_test.txt";
    //string airports = "airports_test.txt";

    //intializing object
    Flights air(routes, airports);

    /*

    //start of BFS
    cout << " " << endl;
    string start = "KZN"; //replace with the desired 3-letter airport code for traversal
    air.BFS(start);
    //end of bfs

    */

    /*

    //start of shortest path
    cout << " " << endl;
    string source = "KZN"; //replace with 3-letter code for the desired source airport
    string destination = "DME"; //replace with 3-letter code for the desired destination airport
    int dist = air.shortestPath(source, destination);
    cout << "The distance between " << source <<  " " << "and " << destination << " is " << dist << " km" << endl;
    //end of shortest path

    */

    /*

    //start of strongly connected components
    //prints strongly connected component based on data files given from constructor
    cout << " " << endl;
    air.stronglyConnected();
    //end of strongly connected components

    */

    return 0;
}