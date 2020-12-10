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
         * Constructor saves names of routes and airports data files as instance variables.
         * Calls readAirports where the graph constructing happens.
         * Text files need to be in the same format as the provided examples such as routes.txt and airports.txt in order for data to be correctly parsed.
         * @param routes.txt and airports.txt files
         */
        Flights(const string & routes_data, const string & airports_data);

        /**
         * readAirports function to read longitude/latitude data from flight routes dataset that was previously saved through the constructor call.
         * The main purpose of this function is so that we can later calculate the distances between airports using the longitude/latitude values.
         * @return a map<string, pair<double, double>> mapping an airport name to its corresponding pair of longitude and latitude values from the airports_data file.
         */
        map<string, pair<double, double>> readAirports();

        /**
         * readFlights function to read data from flight paths data set that was previously saved through the constructor call.
         * Also calls readAirports and uses the longitude/latitude values that were returned from readAirports to call distanceHaversine in order to
         * calculate distance between two airports.
         * @return a map<pair<Vertex, Vertex>, int> where two values in the pair represent the flight path between the first airport to the second airport and int represents the distance between them.
         */
        map<pair<Vertex, Vertex>, int> readFlights();

        /**
        * Function to find strongly connected sets of airports (components) on the Graph saved as an instance variable
        * @return 2D vector list for strongly connected components of graph
        */
        vector<vector<Vertex>> stronglyConnected();

        /**
         * Function to find the shortest path using Dijkstra's algorithm on the Graph saved as an instance variable
         * @param src the departure airport
         * @param dest the arrival airport
         * @return the shortest distance path between two airports rounded to an integer.
         */
        int shortestPath(Vertex src, Vertex dest);
    
        /**
         * Function that performs a BFS on graph on the Graph saved as an instance variable
         * @param vertex takes a starting vertex and performs BFS
         * @return vector list with nodes tranversed in order
         */
        vector<Vertex> BFS(Vertex start);

        /**
         * Function to calculate distance between airports. Computes using Haversine formula using latitude and longitudes.
         * Website used to test if our function works correctly: https://www.airmilescalculator.com/distance/sin-to-icn/
         * @param latitude latitude of the airport in degrees.
         * @param longitide longitude of the airport in degrees.
         * @return The distcance between airports, rounded to an integer.
         */
        int distanceHaversine(double lat1_deg, double lon1_deg, double lat2_deg, double lon2_deg);

        /**
         * Public instance variable storing our graph.
         * Public so that you can change the graph when testing.
         */
        Graph g;

    private:
        /** Private instance variables that takes in routes_data and airport_data from the constructor */
        string routes_filename;
        string airports_filename;

        /* Start of helper fuctions section */

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
         * Helper method for degrees to radian used in calculateDistance
         * @param deg
         * @return radian equiv
         */
        double degToRad(double deg);

        /** 
         * Helper method for radian to degrees used in calculate
         * @param radian
         * @return deg equiv
         */
        double radToDeg(double rad);
};