#include<iostream>
#include<vector>
#include<cmath>
#include<map>

#include "fr.h"

using namespace std;

vector<int> booleanVectorMultiplication(vector<vector<int>>& mat, vector<int>& vec){
    vector<int> out;
    int size = mat.size();
    for(int i = 0; i < size; i++){
        int res = 0;
        for(int j = 0; j < size; j++){
            res = res || (mat[i][j] && vec[j]);
        }
        out.push_back(res);
    }
    return out;
}

vector<vector<int>> calculateProducts(vector<vector<int>>& mat){
    vector<vector<int>> lut;
    int size = mat.size();
    long num_combinations = pow(2, size);
    for(long i = 0; i < num_combinations; i++){
        vector<int> temp;
        for(int j = size-1; j >= 0; j--){
            temp.push_back((i & (0x01 << j)) ? 1 : 0);
        }
        vector<int> t = booleanVectorMultiplication(mat, temp);
        lut.push_back(t);
    }
    return lut;
}

vector<vector<int>> fourRussians(vector<vector<int>>& a, vector<vector<int>>& b){
    int T = 5;
    int size = a.size();
    // Preprocess A matrix
    map<vector<int>, vector<vector<int>>> LUT;
    for(int I = 0; I < size; I+=T){
        for(int J = 0; J < size; J+=T){
            vector<vector<int>> current_matrix(T, vector<int>(T,0));
            for(int i = 0; i < T; i++){
                for(int j = 0; j < T; j++){
                    current_matrix[i][j] = a[I+i][J+j];
                }
            }
            LUT[{I/T,J/T}] = calculateProducts(current_matrix);
        }
    }
    // Preprocess B matrix
    vector<vector<int>> pre_b(b.size()/T, vector<int>(b.size(), 0));
    for(int j = 0; j < b.size(); j++){
        int i = 0;
        int k = 0;
        while(i < b.size()){
            int k = 0;
            int res = 0;
            while(k < b.size() && k < T){
                res = (res << 1) | b[i][j];
                k++;
                i++;
            }
            pre_b[(i-1)/T][j] = res; 
        }
    }
    #if 0
    // Print the LUT
    for(auto i: LUT){
        cout << i.first[0] << " " << i.first[1] << ":\n";
        for(auto j: i.second){
            for(auto k: j){
                cout << k << " ";
            }
            cout << "\n";
        }
    }
    #endif
    #if 0
    // Print preprocessed B matrix
    cout << "Preprocessed B:\n";
    for(auto i : pre_b){
        for(auto j: i){
            cout << j << " ";
        }
        cout << "\n";
    }
    #endif

    vector<vector<int>> output(size,vector<int>(size, 0));
    
    for(int j = 0; j < size; j++){
        for(int i = 0; i < size/T; i++){
            cout << "Current index info: " << j/T << " " << i
                 << " Index : "  << i << " " << j  << " " << pre_b[i][j] << endl; 
            vector<int> req = LUT[{j/T,i}][pre_b[i][j]];
            for(int k = i*T; k < T; k++){
                output[k][j] = req[k];
            }
        }
    }
    return output;
}
