#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

class Matrix{
private:
    int size;
    std::vector<double> matrix_vector;

public:

explicit Matrix(int N) : size(N) {}

void set_values(std::ifstream& inputFile){
    matrix_vector.resize(size*size);
    for(int x = 0; x < size; ++x){
        for(int y = 0; y<size; ++y){
            inputFile >> matrix_vector[x*size+y];
        }
    }
}

void read(const std::string& title){
    std::cout << "----" << title << "----" << std::endl;
    for(int x = 0; x < size; ++x){
        for(int y = 0; y<size; ++y){
            std::cout << std::setw(6) << matrix_vector[x*size+y];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix operator+(const Matrix& other){
    Matrix matrixsum(size);
    matrixsum.matrix_vector.resize(size*size);
    
    
    for(int x = 0; x < size; ++x){
        for(int y = 0; y<size; ++y){
            matrixsum.matrix_vector[x*size+y] = matrix_vector[x*size+y]+other.matrix_vector[x*size+y];
        }
    }
    return matrixsum;
}
Matrix operator*(const Matrix& other){
    Matrix matrixdot(size);
    matrixdot.matrix_vector.resize(size*size);
    
    
    for(int x = 0; x < size; ++x){
        for(int y = 0; y<size; ++y){
            double sum = 0.0;
            for (int k = 0; k < size; ++k) {
                sum += matrix_vector[x * size + k] * other.matrix_vector[k * size + y];
            }
            matrixdot.matrix_vector[x*size+y] = sum;
        }
    }
    return matrixdot;
}

void add_diagonal(const std::string& title){

    double sum = 0;
    
    for(int k = 0; k < size; ++k){

        sum += matrix_vector[k*size+k];
    }
    std::cout << "Diagonal sum of "<< title << ": " << sum << "\n";

    sum = 0.0;

    for(int k = 0; k < size; ++k){
        
        sum += matrix_vector[k*size+size-(k+1)];
        
    }
    std::cout << "Secondary diagonal sum: " << sum << "\n";
}
static Matrix swaprows(Matrix matrixswap,int indexA = 0,int indexB = 1){
    int size = matrixswap.size;
    
    if (0<= indexA && indexA <=size && 0 <= indexB && indexB <=size){
        for(int x = 0; x < size; ++x){
            std::swap(matrixswap.matrix_vector[indexA*size+x], matrixswap.matrix_vector[indexB*size+x]);
            }
    }
    return matrixswap;
}
};



int main(){
    std::string filename;
    

    std::cout << "Tell me the file name (or the path to the file) here: ";
    std::cin >> filename;

    //matrix variables/vectors
    int N;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
            std::cerr << "Error: Could not open " << filename << std::endl;
            return 1; 
        }
    inputFile >> N;
    Matrix MatrixA(N);
    Matrix MatrixB(N);

    MatrixA.set_values(inputFile);
    MatrixB.set_values(inputFile);

    
    inputFile.close();

    //the code is impleented using overloaded operations here
    MatrixA.read("Matrix A");
    MatrixB.read("Matrix B");

    Matrix Matrixsum = MatrixA + MatrixB;
    Matrixsum.read("Matrix A + B");

    Matrix Matrixdot = MatrixA * MatrixB;
    Matrixdot.read("Matrix A * B");

    MatrixA.add_diagonal("Matrix A");

    Matrix alteredMatrix = Matrix::swaprows(MatrixA);
    alteredMatrix.read("Swapped rows:");








    



    return 0;
}