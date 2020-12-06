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
    Flights();


    /**
     * Function to read longitude/latitude data from flights dataset.
     */
    map<string, pair<double, double>> readAirports(const string &filename);

    /**
     * Function to read data from flight paths data set.
     */
    vector<string> readFlights(const string &filename);

    /**
     * Function to calculate dist between airports.
     * @param latitude latitude of the airport
     * @param longitide longitude of the airport
     * @return The distcance between airports.
     */
    double calculateDist(const double latitude, const double longitude);

    double stringToDouble(string str);
    private:
        Graph g;
        vector<vector<string>> list;

        vector<string> code;
        map<string, double> latitude;
        map<string, double> longitude;

};