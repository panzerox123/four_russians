#include<iostream>
#include<vector>
#include<map>
#include "naive.h"
#include "omp.h"

#define CLOCK 1

using namespace std;

vector<vector<int>> booleanMatrixMultiplication(vector<vector<int>>& a, vector<vector<int>>& b){
    vector<vector<int>> c;
    long start = clock();
    for (int i = 0; i < a.size(); i++) {
        vector<int> temp;
        for (int j = 0; j < a[i].size(); j++) {
            int res = 0;
            for (int k = 0; k < a[i].size(); k++) {
                res = res || (a[i][k] && b[k][j]);
            }
            temp.push_back(res);
        }
        c.push_back(temp);
    }
    long end = clock();
    #if CLOCK
    cout << "Naive time taken: " << (double) (end-start)/CLOCKS_PER_SEC << "\n";
    #endif
    return c;
}

vector<vector<int>> parallel_booleanMatrixMultiplication(vector<vector<int>>& a, vector<vector<int>>& b){
    vector<vector<int>> c;
    long start = clock();
    #pragma omp for
    for (int i = 0; i < a.size(); i++) {
        vector<int> temp;
        #pragma omp for
        for (int j = 0; j < a[i].size(); j++) {
            int res = 0;
            #pragma omp for
            for (int k = 0; k < a[i].size(); k++) {
                res = res || (a[i][k] && b[k][j]);
            }
            temp.push_back(res);
        }
        c.push_back(temp);
    }
    long end = clock();
    #if CLOCK
    cout << "Naive time taken: " << (double) (end-start)/CLOCKS_PER_SEC << "\n";
    #endif
    return c;
}