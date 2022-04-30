#include<iostream>
#include<vector>
#include<map>

#include "naive.h"
#include "fr.h"

#define NUM_ELEMENTS 20
#define SPARSITY 22

using namespace std;

int RAND_SETTING = 90000;

vector<vector<int>> a1 = {
    {1,0,0,0,1}, 
    {0,1,0,1,0},
    {0,0,0,1,0},
    {1,0,0,0,0},
    {0,0,0,0,1}
};

vector<vector<int>> b1 = {
    {1,0,0,1,0}, 
    {0,0,0,0,0},
    {1,1,0,0,0},
    {0,0,1,0,0},
    {0,0,0,0,1}
};

void printMatrix(vector<vector<int>>& m, const string str = "Output"){
    cout << str << '\n';
    for(auto i : m){
        for(auto j : i){
            cout << j << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

void printLut(vector<vector<int>>& m, const string str = "LUT:"){
    cout << str << '\n';
    for(int i = 0; i < m.size(); i++){
        cout << i << ": ";
        for(auto j : m[i]){
            cout << j << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

void testMatrix(vector<vector<int>>& m1, vector<vector<int>>& m2){
    for(int i = 0; i < m1.size(); i++){
        for(int j = 0; j < m1[i].size(); j++){
            if(m1[i][j] != m2[i][j]){
                cout << "Mismatch @ " << i << " " << j << '\n'; 
            }
        }
    }
}

vector<vector<int>> generateSparseMatrix(int n, int sparsity) {
    srand(time(0)+RAND_SETTING);
    vector<vector<int>> m_1;
    for (int j = 0; j < n; j++) {
        vector<int> m_2;
        for (int i = 0; i < n; i++) {    
            if (rand() % sparsity == 0) {
                m_2.push_back(1);
            }

            else {
                m_2.push_back(0);
            }
        }

        m_1.push_back(m_2);
    }
    RAND_SETTING += 100;

    return m_1;
}

int main(){
    vector<vector<int>> a = generateSparseMatrix(NUM_ELEMENTS, SPARSITY);
    vector<vector<int>> b = generateSparseMatrix(NUM_ELEMENTS, SPARSITY);
    printMatrix(a, "A:");
    printMatrix(b, "B:");
    vector<vector<int>> c;
    c = booleanMatrixMultiplication(a,b);
    cout << "Tested Correct Output -->\n";
    for(auto i: c){
        for(auto j: i){
            cout << j << " ";
        }
        cout << "\n";
    }
    //vector<vector<int>> lut1 = calculateProducts(a);
    //printLut(lut1, "Look up table:");
    vector<vector<int>> res(NUM_ELEMENTS, vector<int>(NUM_ELEMENTS,0));
    #if 0
    /*
    Runs the lookup table on the entire matrix
    */
    for(int i = 0; i < a.size(); i++){
        int index = 0;
        for(int j = 0; j < a.size(); j++){
            index = index << 1;
            index = index | b[j][i];
        }
        //cout << "Index : " << index << '\n';
        vector<int> required = lut1[index];
        for(int j = 0; j < a.size(); j++){
            res[j][i] = required[j];
        }
    }
    #endif
    res = fourRussians(a, b);
    printMatrix(res, "Result:");
    testMatrix(c, res);
}