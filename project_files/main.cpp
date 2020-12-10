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
    Flights air("routes_test.txt", "airports.txt");
    map<pair<Vertex, Vertex>, int> temp = air.readFlights();

    cout << temp[{"SIN", "ICN"}] << endl;
    cout << temp[{"ICN", "SIN"}] << endl;

}