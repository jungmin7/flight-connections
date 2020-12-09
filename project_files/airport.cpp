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
#include <stdlib.h>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;


using namespace std;

/**
 * Constructor for Flights
 * 
 * @param string for routes and airport data files respectively
 */
Flights::Flights(const string &routes_data, const string &airport_data) : g(true, true)
{
    readFlights(routes_data, airport_data);

    //DELETE AFTER TESTING, DEBUGGING, ETC...
    g.print();


}

/**
 * readFlights function.
 * 
 * @param map of data file
 * @return vector<string>
 */
map<string, pair<double, double>> Flights::readAirports(const string &filename)
{
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

    //Start of processing file
    for(unsigned i = 0; i < out.size(); i++) { //traverses line by line.
        string str = out[i];
        int count = 0;
        int fourthCommaIndex;
        int sixthCommaIndex;
        int seventhCommaIndex;
        int eighthCommaIndex;
        int fifthCommaIndex;

        for (unsigned j = 0; j < str.length(); j++) { //traverses each line to find indexes of commas.
            if(str.at(j) == ',' && count <= 8) { //up until 8th comma because information after that is irrelevant.
                count++;
                if (count == 4 || count == 6 || count == 7 || count == 8 || count == 5) {
                    if (count == 4) {
                        fourthCommaIndex = j;
                    } else if (count == 6) {
                        sixthCommaIndex = j;
                    } else if (count == 7) {
                        seventhCommaIndex = j;
                    } else if (count == 8) {
                        eighthCommaIndex = j;
                    } else if (count == 5) {
                        fifthCommaIndex = j;
                    }
                }
            }
        }

        if (fifthCommaIndex - fourthCommaIndex == 6) {
            //finding the airport name(ex: "SIN"), longitude string and latitude string.
            string airport = str.substr(fourthCommaIndex+2, 3); //ex: ,"GKA",
            string latitude_str = str.substr(sixthCommaIndex+1, (seventhCommaIndex-sixthCommaIndex-1)); //ex: ,-6.081689834590001, 
            string longitude_str = str.substr(seventhCommaIndex+1, (eighthCommaIndex-seventhCommaIndex-1)); 

            //convert strings to doubles; works for negative too.
            double latitude = stringToDouble(latitude_str);
            double longitude = stringToDouble(longitude_str);

            // cout << airport <<" " << latitude_str << " " << longitude_str << endl;
            
            //enter inside map (ex: myMap["SIN"] = pair<double, double>(1.35019, 103.994003);)
            coordinateMap[airport] = pair<double, double>(latitude, longitude);
        }

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

    //opening and reading file
    ifstream file;
    file.open(filename1);
    vector<string> out;

    if (!file.is_open()) {
        cout << "error while opening the file" << endl;
    } else {
        string line;
        while (!file.eof()) {
            getline(file, line);
            out.push_back(line);
        }
    }

    //start of processing file
    map<string, pair<double, double>> airport = readAirports(filename2);
    Vertex firstAirport;
    Vertex secondAirport;
    for(unsigned i = 0; i < out.size(); i++) { //traverses line by line.
        string str = out[i];
        int count = 0;
        for(unsigned j = 0; j < str.length(); j++) { //traverses each line.
            if(str.at(j) == ',') {
                count++;
                if (count == 2) { //if we see the 2nd comma, the next 3 letter word is the source airport code
                    firstAirport = str.substr(j + 1, 3);
                }
                if (count == 4) { //if we see the 4th comma, the next 3 letter word is the destination airport code
                    secondAirport = str.substr(j + 1, 3);
                }
            }
        }

        /** Fixed an error on 12/09 */
        if (!g.vertexExists(firstAirport)) {
            g.insertVertex(firstAirport);
        }
        if (!g.vertexExists(secondAirport)) {
            g.insertVertex(secondAirport);
        }

        //creates edge between the two airports
        g.insertEdge(firstAirport, secondAirport);

        //setting edge label as firstAiport->secondAirport
        string symbol = "->";
        string label = firstAirport + symbol + secondAirport;
        g.setEdgeLabel(firstAirport, secondAirport, label);

        //calculating distance using haversine method
        double dist = distanceHaversine(airport[firstAirport].first, airport[firstAirport].second, airport[secondAirport].first, airport[secondAirport].second);

        //sets the edge weight as the distance
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
 * @param double latitude and longitude values for the source and destination airport
 * @return distance between two points in kilometers.
 */
double Flights::distanceHaversine(double lat1_deg, double lon1_deg, double lat2_deg, double lon2_deg) {

    double lat1_rad = degToRad(lat1_deg);
    double lon1_rad = degToRad(lon1_deg);
    double lat2_rad = degToRad(lat2_deg);
    double lon2_rad = degToRad(lon2_deg);

    double latDiff = sin((lat2_rad - lat1_rad) / 2);
    double lonDiff = sin((lon2_rad - lon1_rad) / 2);
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

/**
* Function to find strongly connected sets of airports (components)
*/
void Flights::stronglyConnected()
{
    //REPLACE WITH DFS ALGORITHM
    vector<Vertex> list = g.getVertices();

    //start of strongly connected algorithm
    stack<Vertex> stack;
    map<Vertex, bool> visited;

    for(Vertex vertex : list)
    {
        visited[vertex] = false;
    }

    for(Vertex vertex : list)
    {
        if(visited[vertex])
        {
            continue;
        }
        DFS(vertex, visited, stack);
    }

    Graph reverse(true, true);
    reverse = getReverse();
    Graph temp2(true, true);
    temp2 = g;
    g = reverse;
  
    for(Vertex v : list)
    {
        visited[v] = false;
    }

    vector<vector<Vertex>> result;

    while(!stack.empty())
    {
        Vertex vertex = stack.top();
        stack.pop();
        if(visited[vertex])
        {
            continue;
        }
        vector<Vertex> set;
        DFS(vertex, visited, set);
        result.push_back(set);
    }

    cout << "Strongly connected components are as follows:" << endl; 
    for(unsigned i = 0; i < result.size(); i++)
    {
        cout << i+1 << ")" << " ";
        for(unsigned j = 0; j < result[i].size(); j++)
        {
            cout << result[i][j] <<  " ";
        }
        cout << "" << endl;
    }
    g = temp2;
}

void Flights::DFS(Vertex vertex, map<Vertex, bool> &visited, stack<Vertex> &stack)
{
    visited[vertex] = true;
    for(Vertex v : g.getAdjacent(vertex))
    {
        if(visited[v])
        {
            continue;
        }
        DFS(v, visited, stack);
    }
    stack.push(vertex);
}

void Flights::DFS(Vertex vertex, map<Vertex, bool> &visited, vector<Vertex> &set)
{
    visited[vertex] = true;
    set.push_back(vertex);
    for(Vertex v : g.getAdjacent(vertex))
    {
        if(visited[v])
        {
            continue;
        }
        DFS(v, visited, set);
    }
}

Graph Flights::getReverse()
{
    Graph reverse(true, true);
    vector<Vertex> vertices = g.getVertices();
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        for(Vertex each : g.getAdjacent(vertices[i]))
        {
            reverse.insertEdge(each, vertices[i]);
            reverse.setEdgeWeight(each, vertices[i], g.getEdgeWeight(vertices[i], each));
            reverse.setEdgeLabel(each, vertices[i], g.getEdgeLabel(vertices[i], each));
        }
    }
    return reverse;
}


double Flights::shortestPath(Vertex src, Vertex dest)
{
    typedef pair<double, Vertex> dist_pair;

    priority_queue<dist_pair, vector<dist_pair>, greater<dist_pair>> pq;
    map<Vertex,double> dist;
    map<Vertex,Vertex> pred;

    vector<Vertex> vertex_list = g.getVertices();
    for (size_t i = 0; i < vertex_list.size(); i++) {
        if (vertex_list[i]!=src) {
            pq.push(make_pair(numeric_limits<double>::infinity(),vertex_list[i]));
            dist[vertex_list[i]] = numeric_limits<double>::infinity();
            pred[vertex_list[i]] = "NONE";
        }
    }
    pq.push(make_pair(0.0,src));
    dist[src] = 0.0;

    while(!pq.empty()) {
        Vertex curr = pq.top().second; // vertex
        pq.pop();

        for (auto it = g.getAdjacent(curr).begin(); it != g.getAdjacent(curr).end(); it++) {
            double distfromCurr = g.getEdgeWeight(curr,(*it));
            if (dist[curr] + distfromCurr < dist[(*it)]) {
                dist[(*it)] = dist[curr] + distfromCurr;
                pred[(*it)] = curr;
                pq.push(make_pair(dist[*it],curr));
                
            }
        }
    }
    return dist[dest];


    /**
    queue<Vertex> queue;
    // map<Vertex,double> dist;
    map<Vertex,string> pred;

    queue.push(src);

    for (auto vertices : g.getVertices()) {
        dist[vertices] = numeric_limits<double>::infinity();
        pred[vertices] = "NONE";
        if (vertices!=src) {
            queue.push(vertices);
        }
        
    }
    dist[src] = 0.0;


    while (!queue.empty()) {
        Vertex curr = queue.front();
        vector<Vertex> adj = g.getAdjacent(curr);
        for (auto it = adj.begin(); it != adj.end(); it++) {
            double distfromCurr = g.getEdgeWeight(curr,(*it));

            cout << "src: " << src << ", " << "curr's adjacent: " << (*it) << " dist: " << distfromCurr << endl; 

            if (dist[curr] + distfromCurr < dist[*it]) {
                dist[*it] = distfromCurr + dist[curr];
                pred[*it] = curr;
            }
        }
        queue.pop();
    }
    */
}

vector<Vertex> Flights::BFS(Vertex start)
{
    /** Vector to be returned that contains vertices that were visited in order */
    vector<Vertex> outputBFS;

    int numVertices = g.getVertices().size();
    cout << "numVertices: " << numVertices << endl;
    /** Returns a vector containing all the vertices in our Graph, g */
    vector<Vertex> vertices = g.getVertices();

    /** Map that represents whether an airport was visited. */
    map<Vertex, bool> visited;
    visited[start] = false;

    /** Mark all vertices in visited Map as false. */
    for (auto v: vertices) {
        // cout << "testing vertices in map: " << v << endl;
        visited[v] = false;
    }

    /** Create queue */
    queue<Vertex> queue;

    // Marks start Airport as visited; adds to queue.
    visited[start] = true;
    queue.push(start);
    
    Vertex temp;
    cout << "BFS starting at Airport " << start << ":" << endl;
    while (!queue.empty()) {
        temp = queue.front(); // Gets airport at front of queue.
        queue.pop(); // Pops the airport from the queue.
        cout << temp << endl; //print the visited vertex.
        outputBFS.push_back(temp); //add the visited vertex to the output vector.

        vector<Vertex> adjacentVertices = g.getAdjacent(temp); //get all adjacentVertices.
        for (auto a: adjacentVertices) {
            if (visited[a] == false) {
                visited[a] = true;
                queue.push(a);
            }
        }
    }
    
    return outputBFS;
}