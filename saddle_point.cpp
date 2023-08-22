#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <fstream>
#include <conio.h>

using namespace std;

int findSumQuadrant(int** matrix, int row_start, int row_finish, int column_start, int column_finish) {			
	//учитывая индексы расположения чисел в квадранте,суммируются элементы нужного квадранта 
	int sum = 0;

	for (int i = row_start; i < row_finish; i++) {
		for (int j = column_start; j < column_finish; j++) {
			sum += matrix[i][j];
		}
	}
	return sum;
}

int findLargestQuadrant(int** matrix, int n, int m, int& i_saddle, int& j_saddle) {

	int max_quadrant = 0;
	int max_sum = -INT_MAX;

	int sum_1 = findSumQuadrant(matrix, 0, i_saddle, 0, j_saddle);
	if (!(sum_1 == 0 && (i_saddle == 0 || j_saddle == 0))) {
		if (sum_1 > max_sum) {
			max_sum = sum_1;
			max_quadrant = 1;
		}
	}

	int sum_2 = findSumQuadrant(matrix, 0, i_saddle, j_saddle + 1, m);
	if (!(sum_2 == 0 && (i_saddle == 0 || j_saddle + 1 == m))) {
		if (sum_2 > max_sum) {
			max_sum = sum_2;
			max_quadrant = 2;
		}
	}

	int sum_3 = findSumQuadrant(matrix, i_saddle + 1, n, j_saddle + 1, m);
	if (!(sum_3 == 0 && (i_saddle + 1 == n || j_saddle + 1 == m))) {
		if (sum_3 > max_sum) {
			max_sum = sum_3;
			max_quadrant = 3;
		}
	}

	int sum_4 = findSumQuadrant(matrix, i_saddle + 1, n, 0, j_saddle);
	if (!(sum_4 == 0 && (i_saddle + 1 == n || j_saddle == 0))) {
		if (sum_4 > max_sum) {
			max_sum = sum_4;
			max_quadrant = 4;
		}
	}

	cout << "Largest quadrant - " << max_quadrant << "." << endl;
	cout << endl;
	cout << "Maximum sum of quadrant elements = " << max_sum << "." << endl;

	return max_quadrant;
}

void findSaddlePoints(int** matrix, int n, int m, int& i_saddle, int& j_saddle) {

	int i, j, a, b, count;
	count = 0;

	for (i = 0; i < n; i++) {
		int min = matrix[i][0];
		for (a = 1; a < m; a++) {	// находится минимум i-й строки 
			if (matrix[i][a] < min) {
				min = matrix[i][a];
			}
		}
		for (j = 0; j < m; j++) {
			if (matrix[i][j] == min) {
				int max = matrix[0][j];
				for (b = 1; b < n; b++) {	// находится максимум j-го столбца 
					if (matrix[b][j] > max) {
						max = matrix[b][j];
					}
				}
				if (matrix[i][j] == max) {	// в случае равенства минимума и максимума выводится седловая точка и ее координаты
					cout << endl;
					i_saddle = i;
					j_saddle = j;
					cout << "Saddle point [" << i << "]" << "[" << j << "] = " << matrix[i][j] << "." << endl;
					cout << endl;
					count++;
				}
			}
		}
	}

	if (count == 0) {
		cout << endl;
		cout << "No saddle points found." << endl;
	}
}

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 3,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void colorQuadrant(int** matrix, int max_quadrant, int i_saddle, int j_saddle, int n, int m) {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	int i = 0;
	int j = 0;
	int row_start, row_finish, column_start, column_finish;
	row_start = 0;  row_finish = 0; column_start = 0; column_finish = 0;

	cout << endl;

	if (max_quadrant == 1) {
		row_start = 0,
		row_finish = i_saddle,
		column_start = 0,
		column_finish = j_saddle;
	}
	if (max_quadrant == 2) {
		row_start = 0,
		row_finish = i_saddle,
		column_start = j_saddle + 1,
		column_finish = m;
	}
	if (max_quadrant == 3) {
		row_start = i_saddle + 1,
		row_finish = n,
		column_start = j_saddle + 1,
		column_finish = m;
	}
	if (max_quadrant == 4) {
		row_start = i_saddle + 1,
		row_finish = n,
		column_start = 0,
		column_finish = j_saddle;
	}

	for (i = 0; i < n; i++) {	// вывод матрицы
		for (j = 0; j < m; j++) {
			if (i >= row_start && i < row_finish && j >= column_start && j < column_finish) {	
				// в случае, если индексы расположения чисел чисел совпадают с индексами большего квадранта, консоль окрашивается
				SetConsoleTextAttribute(console, (WORD)((Magenta << 4) | Yellow));	
				cout.width(3);
				cout << setw(3) << right << matrix[i][j];
				SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			}

			else {																						
				if (i == i_saddle && j == j_saddle) {	// окрашивается седловая точка
					SetConsoleTextAttribute(console, (WORD)((DarkGray << 4) | White));
					cout.width(3);
					cout << setw(3) << right << matrix[i][j];
					SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
				else {	// иначе выводится без окрашивания
					cout.width(3);
					cout << setw(3) << right << matrix[i][j];
				}
			}
		}
		cout << endl;
	}
}

int main() {

	int n = 0;
	int m = 0;
	int max_quadrant = 0;
	int i_saddle = -1;
	int j_saddle = -1;
	int x = 0;
	int c = 0;
	int e = 0;
	bool exit_while = false;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	int** matrix = nullptr;
	cout << "1. Enter the matrix from the keyboard.\n2. Read the matrix from the file." << endl;

	while (exit_while == false)
	{
		if (exit_while) {
			break;
		}
		switch (c=_getch()) {
			case 72: {
				system("cls");
				SetConsoleTextAttribute(console, (WORD)((LightMagenta << 4) | Yellow));
				cout << "1. Enter the matrix from the keyboard." << endl;
				SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "2. Read the matrix from the file." << endl;
				e = _getch();
				if (e == 13){
					exit_while = true;
					system("cls");
					cout << "Enter the number of rows in the matrix:  ";
					cin >> n;
					if (!cin) {
						cout << "Number of rows is not a number!" << endl;
						return 0;
					}
					if (n <= 0) {
						cout << "Number of rows <= 0!" << endl;
						return 0;
					}
					cout << "Enter the number of columns in the matrix:  ";
					cin >> m;
					if (!cin) {
						cout << "Number of columns is not a number!" << endl;
						return 0;
					}
					if (m <= 0) {
						cout << "Number of columns <= 0!" << endl;
						return 0;
					}
					cout << endl;
					cout << "Enter the matrix" << endl;
					cout << endl;

					matrix = new int* [n];
					for (int i = 0; i < n; i++) {
						matrix[i] = new int[m];
					}

					for (int i = 0; i < n; i++) {
						for (int j = 0; j < m; j++) {
							cin >> matrix[i][j];
							if (!cin) {
								cout << "The element [" << i << "][" << j << "] is not a number!" << endl;
								return 0;
							}
						}
					}
				}
				break;
			}
			case 80: {
				system("cls");
				cout << "1. Enter the matrix from the keyboard." << endl;
				SetConsoleTextAttribute(console, (WORD)((LightMagenta << 4) | Yellow));
				cout << "2. Read the matrix from the file." << endl;
				SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				e = _getch();
				if (e == 13) {
					exit_while = true;
					fstream file;
					file.open("matrix.txt");

					file >> n;
					if (!file) {
						cout << "Number of rows is not a number!" << endl;
						return 0;
					}
					if (n <= 0) {
						cout << "Number of rows <= 0!" << endl;
						return 0;
					}

					file >> m;
					if (!file) {
						cout << "Number of columns is not a number!" << endl;
						return 0;
					}
					if (m <= 0) {
						cout << "Number of columns <= 0!" << endl;
						return 0;
					}

					cout << endl;
					cout << "Number of rows = " << n << endl;
					cout << "Number of columns = " << m << endl;

					matrix = new int* [n];

					for (int i = 0; i < n; i++) {
						matrix[i] = new int[m];
					}

					for (int i = 0; i < n; i++) {
						for (int j = 0; j < m; j++) {
							file >> matrix[i][j];
							if (!file) {
								cout << "The element [" << i << "][" << j << "] is not a number!" << endl;
								return 0;
							}
						}
					}

					file.close();
				}
				break;
			}
		} 
	}

	cout << endl;
	system("cls");
	cout << "The entered matrix." << endl;
	cout << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout.width(3);
			cout << setw(3) << right << matrix[i][j];
		}
		cout << endl;
	}

	findSaddlePoints(matrix, n, m, i_saddle, j_saddle);

	if (!(i_saddle == -1 && j_saddle == -1)) {
		max_quadrant = findLargestQuadrant(matrix, n, m, i_saddle, j_saddle);
	}
	if (!(max_quadrant == 0)) {
		colorQuadrant(matrix, max_quadrant, i_saddle, j_saddle, n, m);
	}

	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

	return 0;
}

