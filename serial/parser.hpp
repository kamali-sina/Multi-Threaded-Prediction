#ifndef H_PASER
#define H_PASER
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream> 
#include <algorithm>
#include <dirent.h>
#include <fstream>

using namespace std;

vector<string> get_items_in_folder(string path);
int date_to_timestamp(string date);
vector<string> parse_line(string line, char split_by);
vector<vector<double>> parse_file(string path);
string replace_char(string line,char replace, char orig);

#endif