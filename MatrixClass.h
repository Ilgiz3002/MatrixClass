#pragma once
#include <stdexcept>
#include <random>
#include <iostream>
#include <String>
#include <iomanip> 
class Matrix {
private:
	int rows;
	int cols;
	int *pMatrix;
	
public:
	
	Matrix(int size) {
		this->rows = size;
		this->cols = size;
		pMatrix = new int[size * size];
		for (int i = 0; i < size * size; i++) {
			pMatrix[i] = 0;
		}
	}

	Matrix(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
		pMatrix = new int[rows * cols];
		for (int i = 0; i < rows * cols; i++) {
			pMatrix[i] = 0;
		}
	}

	Matrix(const Matrix& other) {
		rows = other.rows;
		cols = other.cols;
		pMatrix = new int[rows*cols];
		for (int i = 0; i < rows * cols; i++) {
			pMatrix[i] = other.pMatrix[i];
		}
	}

	Matrix& operator=(const Matrix& other) { // перегрзка =, чтобы освободить старую память pMatrix
		if (this == &other) {
			return *this; 
		}

		delete[] pMatrix;

		rows = other.rows;
		cols = other.cols;

		pMatrix = new int[rows * cols];

		for (int i = 0; i < rows * cols; ++i) {
			pMatrix[i] = other.pMatrix[i];
		}

		return *this;
	}

	~Matrix() {
		delete[] pMatrix;
	}
	
	Matrix Addition(const Matrix& other) const{
		if (this->rows != other.rows || this->cols != other.cols) {
			throw std::invalid_argument("Данные матрицы нельзя складывать: разные размеры!");
		}

		Matrix resultAdd(rows, cols);
		
		for (int i = 0; i < rows * cols; i++) {
			resultAdd.pMatrix[i] = this->pMatrix[i] + other.pMatrix[i]; 
		}
		return resultAdd;
	}

	Matrix Multi(const Matrix& other) const{
		if (this->cols != other.rows) {
			throw std::invalid_argument("Данные матрицы нельзя перемножать!");
		}
		
		
		Matrix resultMulti(rows, other.cols);

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < other.cols; ++j) {
				resultMulti.pMatrix[i * other.cols + j] = 0;
				for (int k = 0; k < this->cols; ++k) {
					resultMulti.pMatrix[i * other.cols + j] += this->pMatrix[i * this->cols + k] * other.pMatrix[k * other.cols + j];
				}
			}
		}
		return resultMulti;
	}

	static Matrix CreateRandomMatrix(int rows, int cols, int minimum, int maximum) {
		if (rows <= 0 || rows >= 100 || cols <= 0 || cols >= 100) {
			throw std::invalid_argument("Матрицу размера больше 99 и ментьше 0 создать нельзя!");
		}
			
		if (minimum > maximum) {
			throw std::invalid_argument("Минимум не может быть больше максимума!");
		}
			
		Matrix resultRandomMatrix(rows, cols);

		for (int i = 0; i < rows * cols; i++) {
			resultRandomMatrix.pMatrix[i] = minimum + std::rand() % (maximum - minimum + 1);
		}

		return resultRandomMatrix;
	}

	void Print() const {
		int maxWidth = 0;
		for (int i = 0; i < rows * cols; ++i) {
		int numWidth = std::to_string(pMatrix[i]).length();
			if (numWidth > maxWidth) {
				maxWidth = numWidth;
			}
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				std::cout << std::setw(maxWidth + 1) << pMatrix[i * cols + j];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void InputMatrix() {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				int value;
				do {
					std::cout << "Введите элемент [" << i << "][" << j << "] (от -50 до 49): ";
					std::cin >> value;

					if (value < -50 || value > 49) {
						std::cout << "Ошибка: число должно быть в диапазоне от -50 до 49. Повторите ввод.\n";
					}
				} while (value < -50 || value > 49); 

				pMatrix[i * cols + j] = value;
			}
		}
	}

};