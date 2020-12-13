#ifndef H_REGR
#define H_REGR
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream> 
#include <algorithm>
#include <dirent.h>
#include <limits>
#include <math.h>
#include <fstream>

#define MIN 0
#define MAX 1

using namespace std;

vector<vector<double>> getMinMaxs(vector<vector<double>> csv);
float runRegression(vector<vector<double>> csv, vector<vector<double>> minMaxs, vector<vector<double>> weights);

#endif