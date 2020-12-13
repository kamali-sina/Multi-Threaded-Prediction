#include <iostream>
#include <vector>
#include <string>
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
	vector<vector<double>> trainCsv = parse_file(trainPath);
	vector<vector<double>> weightsCsv = parse_file(weightsPath);
	vector<vector<double>> minMaxs = getMinMaxs(trainCsv);
	float accuracy = runRegression(trainCsv, minMaxs, weightsCsv);
	cout<<"Accuracy: "<<accuracy<<"%"<<endl;
	return 0;
}