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
    // map<string, pair<double, double>> myMap;
    // return myMap;

    ifstream text(filename);
	vector<string> out;
    
    map<string, pair<double, double>> coordinateMap; //mapping airport to <longitude, latitude>

	if (text.is_open()) {
		istream_iterator<string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}

    for(unsigned i = 0; i < out.size(); i++) { //traverses line by line.
        string str = out[i];
        int count = 0;
        int fourthCommaIndex;
        int sixthCommaIndex;
        int seventhCommaIndex;
        int eighthCommaIndex;

        cout << str << endl;

        for (unsigned j = 0; j < str.length(); j++) { //traverses each line to find indexes of commas.
            if(str.at(j) == ',' && count <= 8) { //up until 8th comma because information after that is irrelevant.
                count++;
                if (count == 4 || count == 6 || count == 7 || count == 8) {
                    // firstAirport = str.substr(j+2, 3); //ex: ,"GKA",
                    //cout << firstAirport << " ";
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
                /**
                if (count == 4 || count == 6 || ) {
                    secondAirport = str.substr(j+1, 3);
                    cout << secondAirport << " " << endl;
                }
                */
                
            }
        }

        cout << fourthCommaIndex << " " <<sixthCommaIndex << " " << seventhCommaIndex << endl;
        //cout << "\n" << out[i] << endl;

        //finding the airport name(ex: "SIN"), longitude string and latitude string.
            string airport = str.substr(fourthCommaIndex+2, 3); //ex: ,"GKA",
            string latitude_str = str.substr(sixthCommaIndex+1, (seventhCommaIndex-sixthCommaIndex-1)); //ex: ,-6.081689834590001, 
            string longitude_str = str.substr(seventhCommaIndex+1, (eighthCommaIndex-seventhCommaIndex-1)); 

            //convert strings to doubles; works for negative too.
            double latitude = stringToDouble(latitude_str);
            double longitude = stringToDouble(longitude_str);

            cout << airport << " " << latitude << " " << longitude << endl;
            
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