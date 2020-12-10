#pragma once
#include "graph.h"
#include "edge.h"

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cmath>
#include <stdlib.h>
#include <stack>

using namespace std;

class Flights
{
    public:
    /**
     * Constructor
     * Initializes flight graph with given routes and airports file
     */
    Flights(const string &, const string &);

    /**
     * Function to read longitude/latitude data from flights dataset.
     */
    map<string, pair<double, double>> readAirports(const string &filename);

    /**
     * Function to read data from flight paths data set.
     * Also uses readAirports to assist in creating the fligh graph
     */
    map<Vertex, Vertex> readFlights(const string &, const string &);

    /**
    * Function to find strngly connected sets of airports (components)
    * @return 2D vector list for strongly connected components of graph
    */
    vector<vector<Vertex>> stronglyConnected();

    /**
     * Function to find the shortest path using Dijkstra's algorithm
     * @param src the departure airport
     * @param dest the arrival airport
     * @return the shortest distance path between two airports
     */
    int shortestPath(Vertex src, Vertex dest);
  
    /**
     * Function to find the shortest path using Dijkstra's algorithm
     * @param vertex takes a starting vertex and performs BFS
     * @return vector list with nodes tranversed in order
     */
    vector<Vertex> BFS(Vertex start);

    /**
     * Function to calculate distance between airports. Computes using Haversine formula using latitude and longitudes.
     * @param latitude latitude of the airport in degrees.
     * @param longitide longitude of the airport in degrees.
     * @return The distcance between airports.
     */
    double distanceHaversine(double lat1_deg, double lon1_deg, double lat2_deg, double lon2_deg);

    /**
     * Public instance variable storing our graph.
     * Public so that you can change the graph when testing
     */
    Graph g;

    private:
        // Graph g;


    /*
    *   Start of helper fuctions section
    */

    /**
     * Helper function perform DFS on graph
     * @param vertex, visited map, and stack with vertices
     */
    void DFS(Vertex vertex, map<Vertex, bool> &visited, stack<Vertex> &stack);

    /**
     * Helper function perform DFS on reversed graph
     * @param vertex, visited map, and set to add all the connected components
     */
    void DFS(Vertex vertex, map<Vertex, bool> &visited, vector<Vertex> &set);
    
    /**
    * Function to reverse graph
    * @return reversed graph
    */
    Graph getReverse();

    /**
     * Helper function to convert a string into a double.
     * Tested that this works for negative numbers too.
     * @param string 
     * @return double
     */
    double stringToDouble(string str);

    /** 
     * Helper method to convert degrees to radian used in calculateDistance
     */
    double degToRad(double deg);

    /**
     *  Helper method to convert radian to degrees used in calculateDistance
     */
    double radToDeg(double rad);
};