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

    
    vector<string> out;
    /** Hemank's original code that didn't pull lines properly.
    ifstream text(filename);

	if (text.is_open()) {
		istream_iterator<string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}
    */

    map<string, pair<double, double>> coordinateMap; //mapping airport to <longitude, latitude>

    /** Jay: TESTING IFSTREAM GETLINE() 12/07. 
     * https://www.youtube.com/watch?v=Ru7Tump8fKY&ab_channel=LearningLad
     */
    ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        cout << "error while opening the file" << endl;
    } else {
        string line;
        while (!file.eof()) {
            getline(file, line);
            cout << line << endl; //ok so i think getline modifies the line var itself??
            out.push_back(line);
        }
    }
    // return coordinateMap;

    /** IMPORTANT POINT: if you use my way of opening files using getline, if you have an extra line at the end
     * then it will treat that as a line, it will getline(), increase the size of your vector, and terminate with an uncaught exception.
     * but Hemank's code can leave extra lines at the end? Why is that?
     */
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

        //cout << fourthCommaIndex << " " <<sixthCommaIndex << " " << seventhCommaIndex << endl;
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
	/*ifstream text(filename);
	vector<string> out;

	if (text.is_open()) {
		istream_iterator<string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}*/

    cout << "entered readFlights function" << endl;
    ifstream file;
    file.open(filename);
    vector<string> out;

    if (!file.is_open()) {
        cout << "error while opening the file" << endl;
    } else {
        string line;
        while (!file.eof()) {
            getline(file, line);
            cout << line << endl; //ok so i think getline modifies the line var itself??
            out.push_back(line);
        }
    }

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