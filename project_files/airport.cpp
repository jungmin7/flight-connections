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
 * Constructor saves names of routes and airports data files as instance variables.
 * Calls readAirports where the graph constructing happens.
 * Text files need to be in the same format as the provided examples such as routes.txt and airports.txt in order for data to be correctly parsed.
 * @param routes.txt and airports.txt files
 */
Flights::Flights(const string &routes_data, const string &airport_data) : g(true, true) {
    /** Saves names of files as instance variables so it can be used in readAirports and readFlights */
    routes_filename = routes_data;
    airports_filename = airport_data;
    
    /** Immediately calls readFlights because the graph is constructed in the readFlights function */
    readFlights();
}

/**
 * readAirports function to read longitude/latitude data from flight routes dataset that was previously saved through the constructor call.
 * The main purpose of this function is so that we can later calculate the distances between airports using the longitude/latitude values.
 * @return a map<string, pair<double, double>> mapping an airport name to its corresponding pair of longitude and latitude values from the airports_data file.
 */
map<string, pair<double, double>> Flights::readAirports() {
    //Main variable to return
    //Contains all the airport data with coords
    map<string, pair<double, double>> coordinateMap;

    //array to store all the airport data that is to be processed
    vector<string> out;

    //Opening file
    ifstream file;
    file.open(airports_filename);
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
 * readFlights function to read data from flight paths data set that was previously saved through the constructor call.
 * Also calls readAirports and uses the longitude/latitude values that were returned from readAirports to call distanceHaversine in order to
 * calculate distance between two airports.
 * @return a map<pair<Vertex, Vertex>, int> where two values in the pair represent the flight path between the first airport to the second airport and int represents the distance between them.
 */
map<pair<Vertex, Vertex>, int> Flights::readFlights() {

    //opening and reading file
    ifstream file;
    file.open(routes_filename);
    vector<string> out;
    map<pair<Vertex, Vertex>, int> flight_routes;

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
    map<string, pair<double, double>> airport = readAirports();
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
        int dist = distanceHaversine(airport[firstAirport].first, airport[firstAirport].second, airport[secondAirport].first, airport[secondAirport].second);

        flight_routes[{firstAirport, secondAirport}] = dist;

        //sets the edge weight as the distance
        g.setEdgeWeight(firstAirport, secondAirport, dist);    
    }

    return flight_routes;
}

/**
 * Returns the distance between two points on the Earth using Haversine Formula.
 * Haversine formula resource used: https://www.movable-type.co.uk/scripts/latlong.html
 * Website used to test if our function works correctly: https://www.airmilescalculator.com/distance/sin-to-icn/
 * @param double latitude and longitude values for the source and destination airport
 * @return distance between two points in kilometers.
 */
int Flights::distanceHaversine(double lat1_deg, double lon1_deg, double lat2_deg, double lon2_deg) {

    double lat1_rad = degToRad(lat1_deg);
    double lon1_rad = degToRad(lon1_deg);
    double lat2_rad = degToRad(lat2_deg);
    double lon2_rad = degToRad(lon2_deg);

    double latDiff = sin((lat2_rad - lat1_rad) / 2);
    double lonDiff = sin((lon2_rad - lon1_rad) / 2);
    double a = latDiff * latDiff   +   cos(lat1_rad) * cos(lat2_rad) * lonDiff * lonDiff;
    double earthRadius = 6371.0; //in KILOMETERS. https://en.wikipedia.org/wiki/Earth
    return (int) (2.0 * earthRadius * asin(sqrt(a)));

    // radius varies on Earth: 6356.752 km at the poles to 6378.137 km at the equator. 
    // computing SIN to ICN results in 4780.65
    // First iteration: 4627.36; Second iteration: 4780.65; Third iteration: 4627.37
}


/**
* Function to find strongly connected sets of airports (components) on the Graph saved as an instance variable
* @return 2D vector list for strongly connected components of graph
*/
vector<vector<Vertex>> Flights::stronglyConnected()
{
    //get all the vertices
    vector<Vertex> list = g.getVertices();

    stack<Vertex> stack;
    map<Vertex, bool> visited;

    //set each node to false in visited
    for(Vertex vertex : list)
    {
        visited[vertex] = false;
    }

    //start of strongly connected algorithm
    //If node is visited then skip it,
    //else tranverse through node using DFS helper
    for(Vertex vertex : list)
    {
        if(visited[vertex])
        {
            continue;
        }
        DFS(vertex, visited, stack);
    }

    //get the reverse of the graph
    Graph reverse(true, true);
    reverse = getReverse();

    //store current graph in temp variable
    Graph temp(true, true);
    temp = g;

    g = reverse;
  
    //go through map again and making each node false
    //this is start of second pass of algorithm
    for(Vertex v : list)
    {
        visited[v] = false;
    }

    vector<vector<Vertex>> result;

    //go through the stack and for each set of nodes that are visited through DFS,
    //store in result and continue
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

    //printing code
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

    //restore original graph
    g = temp;

    return result;
}

/**
 * Function to find the shortest path using Dijkstra's algorithm on the Graph saved as an instance variable
 * @param src the departure airport
 * @param dest the arrival airport
 * @return the shortest distance path between two airports rounded to an integer.
 */
int Flights::shortestPath(Vertex src, Vertex dest)
{
    queue<Vertex> queue;
    map<Vertex,double> dist;

    //map used for storing previous nodes
    map<Vertex,string> pred;

    //set all current nodes infinity and source node to 0
    for (auto vertices : g.getVertices()) {
        dist[vertices] = numeric_limits<double>::infinity();
    }
    dist[src] = 0.0;

    queue.push(src);

    //start of shortest path algorithm
    while (!queue.empty()) {

        //get current visited node in queue
        Vertex curr = queue.front();
        queue.pop();

        int distfromCurr = -1;
        
        //get adjacent nodes to current nodes
        vector<Vertex> adj = g.getAdjacent(curr);

        //iterate through each adjacent node and check if distance of current node
        //plus the weight of the edge is lower than the current distance of the
        //adjacent node
        for (auto it = adj.begin(); it != adj.end(); it++) {
            if (g.edgeExists(curr, (*it)))
            {
                distfromCurr = g.getEdgeWeight(curr,(*it));
            
                if (dist[curr] + distfromCurr < dist[*it]) {
                    dist[*it] = distfromCurr + dist[curr];

                    //also store the previous node from which the lowest distance was recorded
                    pred[*it] = curr;

                    //update queue
                    queue.push(*it);
                }
            }
        }
    }

    //printing stuff
    if(dist[dest] == numeric_limits<double>::infinity())
    {
        cout << "No path found between entered source and destination." << endl;
        return -1;
    }

    //string variable that goes through all the 3-letter airport codes
    string temp = dest;

    //stack to reverse order of flight path
    stack<string> temp2;

    //rest of printing code
    while(temp != src)
    {
        temp = pred[temp];
        temp2.push(temp);
    }
    cout << "Shortest flight path: ";
    while(!temp2.empty())
    {
        cout << temp2.top() << "->";
        temp2.pop();
    }
    cout << dest << endl;


    return (int)dist[dest];
}

/**
 * Function that performs a BFS on graph on the Graph saved as an instance variable
 * @param vertex takes a starting vertex and performs BFS
 * @return vector list with nodes tranversed in order
 */
vector<Vertex> Flights::BFS(Vertex start)
{
    /** Vector to be returned that contains vertices that were visited in order */
    vector<Vertex> outputBFS;

    int numVertices = g.getVertices().size();
    // cout << "numVertices: " << numVertices << endl;
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
    cout << "< BFS for Graph with " << numVertices << "-vertices starting at Vertex = " 
        << start << " >" << endl;
    int returnCounter = 1;
    while (!queue.empty()) {
        temp = queue.front(); // Gets airport at front of queue.
        queue.pop(); // Pops the airport from the queue.
        cout << returnCounter << ") " << temp << endl; //print the visited vertex.
        returnCounter++; // counter is just for cout purposes.
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


/* Start of helper fuctions section */

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
 * Helper method for degrees to radian used in calculateDistance
 * @param deg
 * @return radian equiv
 */
double Flights::degToRad(double deg) {
  return (deg * M_PI / 180);
}

/** 
 * Helper method for radian to degrees used in calculateDistance
 * @param radian
 * @return deg equiv
 */
double Flights::radToDeg(double rad) {
  return (rad * 180 / M_PI);
}

/**
* Helper function for stronglyConnected()
* @param vertex, visited map, and stack
* @return stack in DFS ordered by visiting time
*/
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

/**
* Helper function for stronglyConnected()
* @param vertex, visited map, and set list
*/
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

/**
* Helper function for stronglyConnected()
* @return reverse of graph
*/
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
