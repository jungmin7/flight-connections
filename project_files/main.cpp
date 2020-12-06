#include "graph.h"
#include "airport.h"
#include <iostream>

#include "edge.h"

#include <map>

#include <utility> // for pair

using namespace std;

int main()
{   
    /*
    Flights air;
    air.readData("routes_test.txt");
    return 0;
    */


    Graph g1 = Graph(true, true);
    g1.insertEdge("SIN", "ICN");
    g1.insertEdge("ICN", "JFK");
    g1.setEdgeWeight("SIN", "ICN", 10); 
    g1.setEdgeWeight("ICN", "JFK", 20);

    //ex: "SIN", pair<10.40, 20.20>
    //    "ICN", pair<5.4, 5.0>
    map<string, pair<double, double>> map1;
    map1.insert(pair<string, pair<double, double>>("SIN", )

    )

    pair<double, double>(10.40, 20.2);

}