/* airport.cpp */

#include "graph.h"
#include "airport.h"

#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;



#include <stdlib.h>
using namespace std;

Flights::Flights(const string &airport_data, const string &routes_data) : g(true, true)
{
    readFlights(airport_data, routes_data);
    g.print();
}

/**
 * readFlights function.
 * 
 * @param data file
 * @return vector<string>
 */
map<string, pair<double, double>> Flights::readAirports(const string &filename) {
    //Main variable to return
    //Contains all the airport data with coords
    map<string, pair<double, double>> coordinateMap;

    //array to store all the airport data that is to be processed
    vector<string> out;

    //Opening file
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "error while opening the file" << endl;
    } else {
        string line;
        while (!file.eof()) {
            getline(file, line);
            out.push_back(line);
        }
    }

    for(unsigned i = 0; i < out.size(); i++) { //traverses line by line.
        string str = out[i];
        int count = 0;
        int fourthCommaIndex;
        int sixthCommaIndex;
        int seventhCommaIndex;
        int eighthCommaIndex;

        for (unsigned j = 0; j < str.length(); j++) { //traverses each line to find indexes of commas.
            if(str.at(j) == ',' && count <= 8) { //up until 8th comma because information after that is irrelevant.
                count++;
                if (count == 4 || count == 6 || count == 7 || count == 8) {
                    if (count == 4) {
                        fourthCommaIndex = j;
                    } else if (count == 6) {
                        sixthCommaIndex = j;
                    } else if (count == 7) {
                        seventhCommaIndex = j;
                    } else if (count == 8) {
                        eighthCommaIndex = j;
                    }
                }
            }
        }

        //finding the airport name(ex: "SIN"), longitude string and latitude string.
        string airport = str.substr(fourthCommaIndex+2, 3); //ex: ,"GKA",
        string latitude_str = str.substr(sixthCommaIndex+1, (seventhCommaIndex-sixthCommaIndex-1)); //ex: ,-6.081689834590001, 
        string longitude_str = str.substr(seventhCommaIndex+1, (eighthCommaIndex-seventhCommaIndex-1)); 

        //convert strings to doubles; works for negative too.
        double latitude = stringToDouble(latitude_str);
        double longitude = stringToDouble(longitude_str);
            
        //enter inside map (ex: myMap["SIN"] = pair<double, double>(1.35019, 103.994003);)
        coordinateMap[airport] = pair<double, double>(latitude, longitude);
        
    }

	return coordinateMap; //return the map of strings to pairs.

}


/**
 * readFlights function.
 * 
 * @param data file
 * @return vector<string>
 */
void Flights::readFlights(const string &filename1, const string &filename2) {
    ifstream file;
    file.open(filename1);
    vector<string> out;

    if (!file.is_open()) {
        cout << "error while opening the file" << endl;
    } else {
        string line;
        while (!file.eof()) {
            getline(file, line);
            //cout << line << endl; //ok so i think getline modifies the line var itself??
            out.push_back(line);
        }
    }

    map<string, pair<double, double>> airport = readAirports(filename2);
    string firstAirport;
    string secondAirport;
    for(unsigned i = 0; i < out.size(); i++) { //traverses line by line.
        string str = out[i];
        int count = 0;
        for(unsigned j = 0; j < str.length(); j++) { //traverses each line.
            if(str.at(j) == ',') {
                count++;
                if (count == 2) {
                    firstAirport = str.substr(j + 1, 3);
                }
                if (count == 4) {
                    secondAirport = str.substr(j + 1, 3);
                }
            }
        }
        g.insertEdge(firstAirport, secondAirport);
        double dist = distanceHaversine(airport[firstAirport].first, airport[firstAirport].second, airport[secondAirport].first, airport[secondAirport].second);
        g.setEdgeWeight(firstAirport, secondAirport, dist);
        
    }
}

/**
 * Helper function to convert a string into a double.
 * Tested that this works for negative numbers too.
 * @param string 
 * @return double
 */
double Flights::stringToDouble(string str) { 
    double d = strtod(str.c_str(), NULL);
    return d;
}

/**
 * Returns the distance between two points on the Earth using Haversine Formula.
 * https://www.movable-type.co.uk/scripts/latlong.html
 * Parameters all in degrees.
 * Returns distance between two points in kilometers.
 */
double Flights::distanceHaversine(double lat1_deg, double lon1_deg, double lat2_deg, double lon2_deg) {

    double lat1_rad = degToRad(lat1_deg);
    double lon1_rad = degToRad(lon1_deg);
    double lat2_rad = degToRad(lat2_deg);
    double lon2_rad = degToRad(lon2_deg);

    double latDiff = sin((lat2_rad - lat1_rad) / 2);
    double lonDiff = sin((lon2_rad - lon1_rad) / 2);
    cout << latDiff << " " << lonDiff << endl;
    double a = latDiff * latDiff   +   cos(lat1_rad) * cos(lat2_rad) * lonDiff * lonDiff;
    double earthRadius = 6371.0; //in KILOMETERS. https://en.wikipedia.org/wiki/Earth
    return 2.0 * earthRadius * asin(sqrt(a));

    // radius varies on Earth: 6356.752 km at the poles to 6378.137 km at the equator. 
    // computing SIN to ICN results in 4780.65
    // First iteration: 4627.36; Second iteration: 4780.65; Third iteration: 4627.37
}

/** 
 * Helper method for degrees to radian used in calculateDistance
 */
double Flights::degToRad(double deg) {
  return (deg * M_PI / 180);
}

/** 
 * Helper method for radian to degrees used in calculateDistance
 */
double Flights::radToDeg(double rad) {
  return (rad * 180 / M_PI);
}


int Flights::shortestPath(Vertex src, Vertex dest)
{
    queue<Vertex> queue;
    map<Vertex,int> dist;
    map<Vertex,string> pred;

    for (auto vertices : g.getVertices()) {
        dist[vertices] = numeric_limits<double>::infinity();
        // pred[vertices] = NULL;
    }
    dist[src] = 0;

    queue.push(src);

    while (!queue.empty()) {
        Vertex curr = queue.front();
        queue.pop();

        vector<Vertex> adj = g.getAdjacent(curr);
        for (auto it = adj.begin(); it != adj.end(); it++) {
            int distance = g.getEdgeWeight(src,(*it)); 
            if (distance + dist[curr] < dist[*it]) {
                dist[*it] = distance + dist[curr];
                pred[*it] = curr;
            }
        }
    }

    return dist[dest];

}


