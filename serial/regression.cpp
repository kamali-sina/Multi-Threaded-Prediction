#include "regression.hpp"

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

int findMaxIndex(vector<double> values){
    int maxIndex = 0;
    for (int i = 0; i < values.size(); i++){
        if (values[maxIndex] < values[i]) maxIndex = i;
    }
    return maxIndex;
}

int run_one_line(vector<double> csv, vector<vector<double>> minMaxs, vector<vector<double>> weights){
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

float runRegression(vector<vector<double>> csv, vector<vector<double>> minMaxs, vector<vector<double>> weights){
    int numOfCorrects = 0;
    for (int i = 0; i < csv.size(); i++){
        numOfCorrects += run_one_line(csv[i], minMaxs, weights);
    }
    float accuracy = (float)numOfCorrects / (float)csv.size();
    float rounded_down = floorf(accuracy * 10000) / 100;
    return rounded_down;
}