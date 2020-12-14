#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include "parser.hpp"
#include "regression.hpp"

#define RESET_COLOR_INDEX 4
#define TRAINPOSTFIX "/train.csv"
#define WEIGHTSPOSTFIX "/weights.csv"

using namespace std;

char COLOR_CODES[5][255] =
{
	"\033[1m\033[30m",		// Bold BLACK
	"\033[1m\033[31m",		// Bold RED
	"\033[1m\033[32m",		// Bold GREEN
	"\033[1m\033[34m",		// Bold BLUE
	"\x1B[0m"				// Reset
};

int main (int argc, char *argv[])
{
    if (argc < 2){
		printf("Usage: ./PhonePricePrediction.out pathToData/");
		exit(0);
	}
	string trainPath = (string)argv[1] + TRAINPOSTFIX;
	string weightsPath = (string)argv[1] + WEIGHTSPOSTFIX;
	// clock_t start, end;
	// double cpu_time_used;
	// start = clock();

	vector<vector<double>> trainCsv = parse_file(trainPath);

	// end = clock();
	// cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	// cout<<"time of parsing traincsv: "<<cpu_time_used<<" seconds"<<endl;
	// start = clock();

	vector<vector<double>> weightsCsv = parse_file(weightsPath);

	// end = clock();
	// cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	// cout<<"time of parsing weightscsv: "<<cpu_time_used<<" seconds"<<endl;
	// start = clock();

	vector<vector<double>> minMaxs = getMinMaxs(trainCsv);

	// end = clock();
	// cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	// cout<<"time of making minmaxs: "<<cpu_time_used<<" seconds"<<endl;
	// start = clock();

	float accuracy = runRegression(trainCsv, minMaxs, weightsCsv);

	// end = clock();
	// cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	// cout<<"time of running regression: "<<cpu_time_used<<" seconds"<<endl;
	// start = clock();
	cout<<"Accuracy: "<<accuracy<<"%"<<endl;
	return 0;
}