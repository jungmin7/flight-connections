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

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;



#include <stdlib.h>
using namespace std;

Flights::Flights() : g(true, true) {
    
}

/**
 * readFlights function.
 * 
 * @param data file
 * @return vector<string>
 */
map<string, pair<double, double>> Flights::readAirports(const string &filename) {
    map<string, pair<double, double>> myMap;
    return myMap;
}


/**
 * readFlights function.
 * 
 * @param data file
 * @return vector<string>
 */
vector<string> Flights::readFlights(const string &filename) {
	ifstream text(filename);
	vector<string> out;

	if (text.is_open()) {
		istream_iterator<string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}

    //string airport;

    string firstAirport;
    string secondAirport;
    for(unsigned i = 0; i < out.size(); i++) { //traverses line by line.
        string str = out[i];
        int count = 0;
        for(unsigned j = 0; j < str.length(); j++) { //traverses each line.
            if(str.at(j) == ',') {
                count++;
                if (count == 2) {
                    firstAirport = str.substr(j+1, 3);
                    cout << firstAirport << " ";
                }
                if (count == 4) {
                    secondAirport = str.substr(j+1, 3);
                    cout << secondAirport << " " << endl;
                }
            }
        }
        //cout << "\n" << out[i] << endl;
        
    }
	return out;

}

double Flights::calculateDist(const double latitude, const double longitude) {

    return 5; //compiler issues
}


double Flights::stringToDouble(string str) { // tested that this works for negative numbers too.
    double d = strtod(str.c_str(), NULL);
    return d;
}