#pragma once
#include "graph.h"


#include <string>
#include <vector>

using namespace std;


class Flights
{
    public:
    /**
     * Constructor
     */
    Flights();

    /**
     * Function to read data from file
     */
    vector<string> readData(const string &filename);

    /**
     * Function to calculate dist between airports.
     * @param latitude latitude of the airport
     * @param longitide longitude of the airport
     * @return The distcance between airports.
     */
    double calculateDist(const double latitude, const double longitude);

    
    private:
        Graph g;
        vector<vector<string>> list;

        string code;
        map<string, string> routes;

        



};