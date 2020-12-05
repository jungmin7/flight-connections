#pragma once
#include "graph.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class flights
{
    public:
    flights();
    vector<string> readData(const string &filename);

    private:
    Graph g;
    vector<vector<string>> list;
};