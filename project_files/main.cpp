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
    //Flights air("routes_test.txt", "airports_test.txt");
    //return 0;

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

    bfsGraph.insertVertex(v0);
    bfsGraph.insertVertex(v1);
    bfsGraph.insertVertex(v2);
    bfsGraph.insertVertex(v3);
    bfsGraph.insertVertex(v4);
    bfsGraph.insertVertex(v5);
    bfsGraph.insertVertex(v6);
    bfsGraph.insertVertex(v7);
    bfsGraph.insertVertex(v8);

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
    
    /** change the graph of airports to being this one of integers for testing purposes*/
    // air.changeGraph(bfsGraph);
    air.g = bfsGraph;

    /** call BFS to output traversal */
    air.BFS("2");

}