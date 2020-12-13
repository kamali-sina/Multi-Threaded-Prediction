#include "parser.hpp"

/* 
returns a vector of all files and folders in a given path
*/
vector<string> get_items_in_folder(string path){
    vector<string> result;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (strcmp (ent->d_name,".") != 0 &&
                strcmp (ent->d_name,"..") != 0)
                result.push_back(ent->d_name);
        }
        closedir(dir);
    }else {
        cout<<"directory "<<path<<" did not exist" <<endl;
        exit(-1);
    }
    return result;
}

/* 
converts YYYY/MM/DD format to an int
*/
int date_to_timestamp(string date){
    date.erase(remove(date.begin(), date.end(), '/'), date.end());
    return stoi(date);
}

vector<double> parse_csv_line(string line, char split_by){
    vector<double> result;
    stringstream line_stream(line);
    string segment;
    int i = 0;
    while(getline(line_stream, segment, split_by)){
        result.push_back(stof(segment));
    }
    return result;
}

/* 
splits a string bu the given char
*/
vector<string> parse_line(string line, char split_by){
    vector<string> result;
    stringstream line_stream(line);
    string segment;
    int i = 0;
    while(getline(line_stream, segment, split_by))
    {
        result.push_back(segment);
    }
    return result;
}

vector<vector<double>> parse_file(string path){
    vector<vector<double>> table;
    string line;
    fstream file;
    file.open(path, ios::in | ios::app);
    getline(file,line);
    while(getline(file,line)){
        table.push_back(parse_csv_line(line, ','));
    }
    return table;
}

/* 
replaces a char called orig in the string by replace
*/
string replace_char(string line,char replace, char orig){
    for (int i = 0; i < line.length(); i++){
        if (line[i] == orig){
            line[i] = replace;
        }
    }
    return line;
}