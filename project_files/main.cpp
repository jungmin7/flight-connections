#include "graph.h"
#include "airport.h"
#include <iostream>

using namespace std;

#include "edge.h"
#include <map>
#include <utility> // for pair
#include <cmath>
#include <queue>
// #define pi 3.14159265358979323846

    class testingHaversine {
        public:
            // double toRad(double degree);
            // double calculateDistance(double lat1, double long1, double lat2, double long2);

            double degTorad(double deg);
            double radTodeg(double rad);

            double distanceHaversine(double lat1_deg, double lon1_deg, double lat2_deg, double lon2_deg);

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
double distanceHaversine(double lat1_deg, double lon1_deg, double lat2_deg, double lon2_deg) {

  
  double lat1_rad = degToRad(lat1_deg);
  double lon1_rad = degToRad(lon1_deg);
  double lat2_rad = degToRad(lat2_deg);
  double lon2_rad = degToRad(lon2_deg);

  double latDiff = sin((lat2_rad - lat1_rad) / 2);
  double lonDiff = sin((lon2_rad - lon1_rad) / 2);
  // cout << latDiff << " " << lonDiff << endl;
  double a = latDiff * latDiff   +   cos(lat1_rad) * cos(lat2_rad) * lonDiff * lonDiff;
  double earthRadius = 6371.0; //in KILOMETERS. https://en.wikipedia.org/wiki/Earth
  return 2.0 * earthRadius * asin(sqrt(a));

  // radius varies on Earth: 6356.752 km at the poles to 6378.137 km at the equator. 
  // computing SIN to ICN results in 4780.65
  // First iteration: 4627.36; Second iteration: 4780.65; Third iteration: 4627.37

}

double shortestPath(Vertex src, Vertex dest, Graph g)
{
  queue<Vertex> queue;
  map<Vertex,double> dist;
  map<Vertex,string> pred;

  for (auto vertices : g.getVertices()) {
      dist[vertices] = numeric_limits<double>::infinity();
  }
  dist[src] = 0.0;

  queue.push(src);

  while (!queue.empty()) {
      Vertex curr = queue.front();
      queue.pop();

      vector<Vertex> adj = g.getAdjacent(curr);
      for (auto it = adj.begin(); it != adj.end(); it++) {
        int distfromCurr = g.getEdgeWeight(curr,(*it));
        
        cout << "curr: " << curr << ", " << "curr's adjacent: " << (*it) << " dist: " << dist[curr] + distfromCurr << endl; 

        if (dist[curr] + distfromCurr < dist[*it]) {
          dist[*it] = distfromCurr + dist[curr];
          pred[*it] = curr;
          queue.push(*it);
        }
      }
  }
  return dist[dest];

}


int main()
{   
    
    Flights air("routes_test.txt", "airports_test.txt");
    // air.g.print();
    air.BFS("AER");
    //cout << air.stringToDouble("-45.040");
    //air.readFlights("routes_test.txt");




    // map<string, pair<double, double>> mainTest = air.readAirports("airports_test.txt");
    // return 0;ss
    
    
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

    double SINtoICNDistance = distanceHaversine(myMap["SIN"].first, myMap["SIN"].second, myMap["ICN"].first, myMap["ICN"].second);

    // cout << "exp: " << SINtoICNDistance << " obs: " << shortestPath("SIN","ICN",g1) << endl;


    
    //testing shortest path using Flights class
    myMap["ASF"] = pair<double,double>(46.2832984924,48.0063018799);
    myMap["KZN"] = pair<double, double>(55.606201171875,49.278701782227);

    // Flights air("routes_test.txt","airports_test.txt");
    // double exp_dist = air.distanceHaversine(myMap["ASF"].first,myMap["ASF"].second,myMap["KZN"].first,myMap["KZN"].second);


    Graph g2 = Graph(true, true);

    g2.insertEdge("ICN", "SIN");
    g2.insertEdge("SIN", "HKG");
    g2.insertEdge("HKG", "ORD");
    g2.insertEdge("ICN", "ORD");

    g2.setEdgeWeight("ICN", "SIN",1);
    g2.setEdgeWeight("SIN", "HKG",3);
    g2.setEdgeWeight("HKG", "ORD",2); 
    g2.setEdgeWeight("ICN", "ORD",10);




    double obs_dist = shortestPath("ICN","ORD",g2);
    cout << "direct " << 10 << "obs " << obs_dist << endl; 
    

    // g1.print();



   /** TRASH CODE:
    //cout << myMap["SIN"].first << endl;
    // g1.print();

    map1.insert(pair<string, pair<double, double>>("SIN", pair<double,double>(10.40, 20.20)));
    map1.insert(pair<string, pair<double, double>>("ICN", pair<double,double>(5.4, 5)));

    cout << map1[0].first << endl;

    //ex: "SIN", pair<10.40, 20.20>
    //    "ICN", pair<5.4, 5.0>
    */



    /**
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

    g2.print();
    */
  
    
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

