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


Flights::Flights() : g(true, true)
{
    

}

vector<string> Flights::readData(const string &filename)
{
	ifstream text(filename);
	vector<string> out;

	if (text.is_open()) {
		istream_iterator<string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}

    string ext;
    for(unsigned i = 0; i < out.size(); i++)
    {
        string str = out[i];
        int c = 0;
        for(unsigned j = 0; j < str.length(); j++)
        {
            if(str.at(j) == ',')
            {
                c++;
                if(c == 2 || c == 4)
                {
                    ext = str.substr(j+1, 3);
                    cout << ext << " ";
                }
            }
        }
        cout << "\n" << out[i] << endl;
    }
	return out;
}

double Flights::calculateDist(const double latitude, const double longitude) {


}

