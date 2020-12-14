#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <string>
#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <sstream> 
#include <math.h>

using namespace std;

#define NUMBER_OF_THREADS 10
#define TRAINPOSTFIX "/train.csv"
#define WEIGHTSPOSTFIX "/weights.csv"
#define MIN 0
#define MAX 1
pthread_t threads[NUMBER_OF_THREADS];
pthread_mutex_t mutex_tillregre;
pthread_mutex_t mutex_regre;
vector<vector<string>> trainCsv_string;
vector<vector<double>> data;
vector<vector<double>> weights;
vector<vector<double>> minMaxs;
int correctSum = 0;

#define RESET_COLOR_INDEX 4
char COLOR_CODES[5][255] =
{
	"\033[1m\033[30m",		// Bold BLACK
	"\033[1m\033[31m",		// Bold RED
	"\033[1m\033[32m",		// Bold GREEN
	"\033[1m\033[34m",		// Bold BLUE
	"\x1B[0m"				// Reset
};

vector<vector<string>> read_csv(string path);
vector<vector<double>> parse_file(string path);
void* untillRegression(void* arg);
void* regression(void* arg);

int main (int argc, char *argv[])
{
	if (argc < 2){
		printf("Usage: ./PhonePricePrediction.out <pathToData>");
		exit(0);
	}
	string trainPath = (string)argv[1] + TRAINPOSTFIX;
	string weightsPath = (string)argv[1] + WEIGHTSPOSTFIX;
	pthread_mutex_init(&mutex_tillregre, NULL);
    pthread_mutex_init(&mutex_regre, NULL);

	weights = parse_file(weightsPath);
	trainCsv_string = read_csv(trainPath);
	for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&threads[i], NULL, untillRegression, (void*)i); 

	/* Wait on the other threads */
	for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], NULL);
	
    /* doing regression */
    for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&threads[i], NULL, regression, (void*)i);
    
    /* Wait on the other threads */
	for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], NULL);
    
    float accuracy = (float)correctSum / (float)trainCsv_string.size();
    float rounded_down = floorf(accuracy * 10000) / 100;
    cout<<"Accuracy: "<<rounded_down<<"%"<<endl;

	/* After joining, print out the results and cleanup */
	pthread_mutex_destroy(&mutex_tillregre);
    pthread_mutex_destroy(&mutex_regre);
	pthread_exit(NULL);
}


/* ******************FUNCTIONS****************** */

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

vector<vector<string>> read_csv(string path){
	vector<vector<string>> table;
    string line;
    fstream file;
    file.open(path, ios::in | ios::app);
    getline(file,line);
    while(getline(file,line)){
        table.push_back(parse_line(line, ','));
    }
    return table;
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

vector<double> getMinMaxOfCol(vector<vector<double>> csv, int col){
    double min = numeric_limits<double>::max();
    double max = numeric_limits<double>::min();
    for (int i = 0; i < csv.size(); i++){
        if (csv[i][col] < min) min = csv[i][col];
        if (csv[i][col] > max) max = csv[i][col];
    }
    vector<double> temp;
    temp.push_back(min);
    temp.push_back(max);
    return temp;
}

/* each line of vector is a tuple of (min,max)*/
vector<vector<double>> getMinMaxs(vector<vector<double>> csv){
    vector<vector<double>> minmaxs;
    for (int i = 0; i < csv[0].size(); i++){
        minmaxs.push_back(getMinMaxOfCol(csv, i));
    }
    return minmaxs;
}

void updateMinMax(vector<vector<double>> localMinMax){
    for (int i = 0; i < localMinMax.size(); i++){
        if (minMaxs[i][MIN] > localMinMax[i][MIN])
            minMaxs[i][MIN] = localMinMax[i][MIN];
        if (minMaxs[i][MAX] < localMinMax[i][MAX])
            minMaxs[i][MAX] = localMinMax[i][MAX];
    }
}

void* untillRegression(void* arg){
	long index = (long)arg;
	int part = trainCsv_string.size() / NUMBER_OF_THREADS;
    vector<vector<double>> mData;
    for (int i = index*part; i < (index+1)*part ; i++){
        vector<double> line;
        for (int j = 0; j < trainCsv_string[i].size(); j++){
            line.push_back(stof(trainCsv_string[i][j]));
        }
        mData.push_back(line);
    }
    vector<vector<double>> Mminmaxs = getMinMaxs(mData);

    pthread_mutex_lock (&mutex_tillregre);
    for (int i = 0; i < mData.size(); i++){
        data.push_back(mData[i]);
    }
    if (minMaxs.size() == 0){
        minMaxs = Mminmaxs;
    }else{
        updateMinMax(Mminmaxs);
    }
    pthread_mutex_unlock (&mutex_tillregre);
    pthread_exit(NULL);
}

int findMaxIndex(vector<double> values){
    int maxIndex = 0;
    for (int i = 0; i < values.size(); i++){
        if (values[maxIndex] < values[i]) maxIndex = i;
    }
    return maxIndex;
}

int run_one_line(vector<double> csv){
    vector<double> values(weights.size(), 0.0);
    for (int i = 0; i < csv.size() - 1; i++){
        double x = (csv[i] - minMaxs[i][MIN])/(minMaxs[i][MAX] - minMaxs[i][MIN]);
        for (int j = 0; j < values.size(); j++){
            values[j] += x * weights[j][i];
        }
    }
    //adding bias
    for (int j = 0; j < values.size(); j++){
        values[j] += weights[j][weights[0].size()-1];
    }
    int maxElementIndex = findMaxIndex(values);
    if (maxElementIndex == (int)csv[csv.size()-1]){
        return 1;
    }else{
        return 0;
    }
}

void* regression(void* arg){
    long index = (long)arg;
	int part = trainCsv_string.size() / NUMBER_OF_THREADS;
    int mysum = 0;
    for (int i = index*part; i < (index+1)*part ; i++){
        mysum += run_one_line(data[i]);
    }
    pthread_mutex_lock (&mutex_regre);
    correctSum += mysum;
    pthread_mutex_unlock (&mutex_regre);
    pthread_exit(NULL);
}