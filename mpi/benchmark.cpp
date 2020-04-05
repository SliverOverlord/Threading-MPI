// Author:Joshua DeNio
// Date: 8/8/19

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

void mat_mult(int mat1[100][100], int mat2[100][100], int output_mat[100][100]);

int main(){
    int list_mat[100][100];
    int list_mat2[100][100];
    int output_mat[100][100];
    
    int currentTime;
    
    int rowCount = 0;
    int colCount = 0;
    
    ifstream inFile("100x100_matrix.txt");
    if (inFile.is_open()){
        
        for (int i = 0; i < 100; i++){
            //
            for (int j =0; j < 100; j++){
                inFile >> list_mat[i][j];
            }
        }
    }
    inFile.close();
    
    ifstream inFile2("100x100_matrix.txt");
    if (inFile2.is_open()){
        
        for (int i = 0; i < 100; i++){
            //
            for (int j =0; j < 100; j++){
                inFile2 >> list_mat[i][j];
            }
        }
    }
    inFile2.close();
    /*
    for (i = 0; i < 100**100; i++){
        mat_mult(list_mat, list_mat2, output_mat);
    }
    */
    mat_mult(list_mat, list_mat2, output_mat);
    
    return 0;
}

void mat_mult(int mat1[100][100], int mat2[100][100], int output_mat[100][100]){
    
    int row = 100;
    int col = 100;
    
    auto startTime = chrono::high_resolution_clock::now();
    
    for (int r = 0; r < row; r++){
        for (int c = 0; c < col; c++){
            for (int r_iter = 0; r_iter < row; r_iter++){                
                output_mat[r][c] += mat1[r][r_iter] * mat2[r_iter][c];
            }
        }
    }
    
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> timeElapsed = endTime - startTime;
    
    cout << "Matrix multiplication of two" << endl;
    cout << "Integer matrix of type matrix[100][100]" << endl;
    cout << "\n";
    
    cout << "The processing time is: ";
    cout << timeElapsed.count() << " in seconds" << endl;
}
