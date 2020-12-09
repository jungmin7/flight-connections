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
     */
    Flights(const string &, const string &);

    /**
     * Function to read longitude/latitude data from flights dataset.
     */
    map<string, pair<double, double>> readAirports(const string &filename);

    /**
     * Function to read data from flight paths data set.
     */
    void readFlights(const string &, const string &);

    /**
    * Function to find strngly connected sets of airports (components)
    * @return components
    */
    void stronglyConnected();

    /**
    * Function to reverse graph
    * @return reversed graph
    */
    Graph getReverse();
  
    /*Comment here about functionality*/
    vector<Vertex> BFS(Vertex start);

    private:
        Graph g;


    /*
    *   Helper fuctions
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
     * Helper function to convert a string into a double.
     * Tested that this works for negative numbers too.
     * @param string 
     * @return double
     */
    double stringToDouble(string str);

    /**
     * Function to calculate distance between airports. Computes using Haversine formula using latitude and longitudes.
     * @param latitude latitude of the airport in degrees.
     * @param longitide longitude of the airport in degrees.
     * @return The distcance between airports.
     */
    // double calculateDist(const double latitude, const double longitude);
    double distanceHaversine(double lat1_deg, double lon1_deg, double lat2_deg, double lon2_deg);

    /** 
     * Helper method to convert degrees to radian used in calculateDistance
     */
    double degToRad(double deg);

    /**
     *  Helper method to convert radian to degrees used in calculateDistance
     */
    double radToDeg(double rad);
};