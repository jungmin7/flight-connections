#include "graph.h"
#include "airport.h"
#include <iostream>

using namespace std;

#include "edge.h"
#include <map>
#include <utility> // for pair
#include <cmath>
// #define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

    class testing {
        public:
            // double toRad(double degree);
            // double calculateDistance(double lat1, double long1, double lat2, double long2);

            double deg2rad(double deg);
            double rad2deg(double rad);

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
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = degToRad(lat1d);
  lon1r = degToRad(lon1d);
  lat2r = degToRad(lat2d);
  lon2r = degToRad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


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


    map<string, pair<double, double>> myMap;

    //SIN lat=1.35019, long=103.994003
    //ICN lat = 37.46910095214844 long= 126.45099639892578       
    // truncate decimals in case of error? nah nvm double does it for u.

    myMap["SIN"] = pair<double, double>(1.35019, 103.994003);
    myMap["ICN"] = pair<double, double>(37.46910095214844, 126.45099639892578);

    double SINtoICNDistance = distanceEarth(myMap["SIN"].first, myMap["SIN"].second, myMap["ICN"].first, myMap["ICN"].second);

    cout << SINtoICNDistance << endl;



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

}

