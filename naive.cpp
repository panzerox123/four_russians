#include<iostream>
#include<vector>
#include<map>
#include "naive.h"

using namespace std;

vector<vector<int>> booleanMatrixMultiplication(vector<vector<int>>& a, vector<vector<int>>& b){
    vector<vector<int>> c;
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
    return c;
}