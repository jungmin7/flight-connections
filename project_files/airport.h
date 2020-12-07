#pragma once
#include "graph.h"


#include <string>
#include <vector>

#include <map>



using namespace std;
#include <utility> // for pair
#include <cmath>
#include "edge.h"

#include <stdlib.h>
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


    /**
     * Function to find the shortest path using Dijkstra's algorithm
     * @param src the departure airport
     * @param dest the arrival airport
     * @return the shortest distance path between two airports
     */
    int shortestPath(Vertex src, Vertex dest);



    private:
        Graph g;
        vector<vector<string>> list;

        vector<string> code;
        map<string, double> latitude;
        map<string, double> longitude;

};