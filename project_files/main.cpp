#include "graph.h"
#include "airport.h"
#include <iostream>

using namespace std;

#include "edge.h"
#include <map>
#include <utility> // for pair
#include <cmath>
// #define pi 3.14159265358979323846

    class testingHaversine {
        public:
            // double toRad(double degree);
            // double calculateDistance(double lat1, double long1, double lat2, double long2);

            double degTorad(double deg);
            double radTodeg(double rad);

            double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

    };

    /**
    double toRad(double degree) {
        return degree/180 * pi;
    }      
    double calculateDistance(double lat1, double long1, double lat2, double long2) {
        double dist;
        dist = sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(long1 - long2);
        dist = acos(dist);
        dist = (6371 * pi * dist) / 180;
        return dist;
    }
    */
    
// deg to rad
double degToRad(double deg) {
  return (deg * M_PI / 180);
}

// deg to rad
double radToDeg(double rad) {
  return (rad * 180 / M_PI);
}

/**
 * Returns the distance between two points on the Earth using Haversine Formula.
 * https://www.movable-type.co.uk/scripts/latlong.html
 * Parameters all in degrees.
 * Returns distance between two points in kilometers.
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {

  double lat1_rad = degToRad(lat1d);
  double lon1_rad = degToRad(lon1d);
  double lat2_rad = degToRad(lat2d);
  double lon2_rad = degToRad(lon2d);

  double latDiff = (lat2_rad - lat1_rad);
  double lonDiff = (lon2_rad - lon1_rad);
  
  double a = sin(latDiff / 2) * sin(latDiff / 2)   +   cos(lat1_rad) * cos(lat1_rad) * sin(lonDiff / 2) * sin(lonDiff / 2);
  double earthRadius = 6371.0; //in KILOMETERS. https://en.wikipedia.org/wiki/Earth
  return 2 * earthRadius * asin(sqrt(a));

  // radius varies on Earth: 6356.752 km at the poles to 6378.137 km at the equator. 
  // computing SIN to ICN results in 4780.65
}


int main()
{   
    /**
    Flights air;
    air.readData("routes_test.txt");
    //return 0;
    */
    


    Graph g1 = Graph(true, true);
    g1.insertEdge("SIN", "ICN");
    g1.insertEdge("ICN", "JFK");
    g1.setEdgeWeight("SIN", "ICN", 10); 
    g1.setEdgeWeight("ICN", "JFK", 20);


    map<string, pair<double, double>> myMap;

    //SIN lat=1.35019, long=103.994003
    //ICN lat = 37.46910095214844 long= 126.45099639892578       
    // truncate decimals in case of error? nah nvm double does it for u.

    myMap["SIN"] = pair<double, double>(1.35019, 103.994003);
    myMap["ICN"] = pair<double, double>(37.46910095214844, 126.45099639892578);

    double SINtoICNDistance = distanceEarth(myMap["SIN"].first, myMap["SIN"].second, myMap["ICN"].first, myMap["ICN"].second);

    cout << SINtoICNDistance << endl;

    // g1.print();



   // TRASH CODE:
   /**
    //cout << myMap["SIN"].first << endl;
    // g1.print();

    map1.insert(pair<string, pair<double, double>>("SIN", pair<double,double>(10.40, 20.20)));
    map1.insert(pair<string, pair<double, double>>("ICN", pair<double,double>(5.4, 5)));

    cout << map1[0].first << endl;
    */

    //ex: "SIN", pair<10.40, 20.20>
    //    "ICN", pair<5.4, 5.0>




    Graph g2 = Graph(true, true);
    g2.insertEdge("SIN", "ICN");
    g2.insertEdge("ICN", "NRT");
    g2.insertEdge("ICN", "JFK");
    g2.insertEdge("JFK", "NRT");
    // g2.insertEdge("NRT", "JFK"); //testing two paths to same vertices.
    g2.setEdgeWeight("SIN", "ICN", 10); 
    g2.setEdgeWeight("ICN", "NRT", 30);
    g2.setEdgeWeight("ICN", "JFK", 20);
    g2.setEdgeWeight("JFK", "NRT", 40);
    // g2.setEdgeWeight("NRT", "JFK", 40);

    // g2.print();
    /**
    class testingBFS {

    };

    int numVertices = getVertices().size(); //method that returns # of vertices

    bool * visited = new bool[numVertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    //queue
    list<double> queue;

    visited[s] = true;
    */


}

