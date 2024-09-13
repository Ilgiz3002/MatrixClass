#include <iostream>
#include "MatrixClass.h"
#include <random>
#include <stdexcept>
#include <random>
#include <iostream>
#include <String>
#include <iomanip> 

int main()
{
    std::srand(std::time(0));
    try {


        Matrix m1(5, 5);

        Matrix m2 = Matrix::CreateRandomMatrix(3, 3, 2, 5);
        Matrix m3 = Matrix::CreateRandomMatrix(3, 3, 95, 100);

        Matrix m4 = Matrix::CreateRandomMatrix(5, 5, 0, 20);
        Matrix m5 = Matrix::CreateRandomMatrix(5, 5, -10, 10);

        m2.Print();
        m3.Print();
        m4.Print();
        m5.Print();
   
        Matrix m6 = m2.Addition(m3);

        m6.Print();

        Matrix m7 = m4.Multi(m5);
        
        m7.Print();

    }

    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

}
    

