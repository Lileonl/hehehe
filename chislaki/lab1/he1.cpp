#include <iostream>
#include<algorithm>
#include<math.h>

using namespace std;

const int n = 3;
void directCourse(double[n][n], const int, double[]);
void triangularForm(double[n][n], const int, double[]);
void reverseCourse(double[n][n], const int, double[], double[]);
void vF(double[n][n], double[], double[], const int size, double[]);
void norma(double*, const int);
void display(double[n][n], const int, double[]);
void bGauss(double[n][n], const int, double[], double[]);
void relativeError(double[], double[], const int);


int main() {
	const int size = 3;
	double X[size] = { 0 };
	double newB[size] = { 0 };
	double newX[size] = { 0 };
	double vectorF[size] = { 0 };
	double mA[size][size] = {
		{21.547,-95.510, -96.121 },
		{10.223,-91.065,-7.343},
		{-51.218,12.124,86.457}
	};
	double cB[size] = { -49.930, -12.465, 60.812 };

	cout << "Initial matrix:" << endl;
	display(mA, size, cB);


	directCourse(mA, size, cB);
	cout << "First matrix:" << endl;
	display(mA, size, cB);

	cout << "Second matrix:" << endl;

	triangularForm(mA, size, cB);
	display(mA, size, cB);

	cout << "Solution:" << endl;
	reverseCourse(mA, size, cB, X);

	cout << "vector F : " << endl;
	vF(mA, cB, X, size, vectorF);

	cout << "norma:" << endl;
	norma(vectorF, size);
	cout << endl;
	cout << "Solution(x`): " << endl;
	bGauss(mA, size, X, newB);
	directCourse(mA, size, newB);
	triangularForm(mA, size, newB);
	reverseCourse(mA, size, newB, newX);
	relativeError(X, newX, size);

}

void display(double mA[n][n], const int size, double* cB) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << mA[i][j] << "\t";
		}
		cout << "=\t" << cB[i];
		cout << "\n";
	}
	cout << endl;
};

void directCourse(double mA[n][n], const int size, double cB[]) {
	for (int i = 0; i < size; i++) {
		int maxIndex = i;
		double max = mA[i][i];
		for (int j = i + 1; j < size; j++) {
			if (abs(max) < abs(mA[j][i])) { //поиск максимального по модулю элемента
				maxIndex = j;
				max = mA[j][i];
			}
		}

		//перестановка строк местами

		if (i != maxIndex) {
			double root = cB[i];
			cB[i] = cB[maxIndex];
			cB[maxIndex] = root;
			for (int j = 0; j < size; j++) {
				double x = mA[i][j];
				mA[i][j] = mA[maxIndex][j];
				mA[maxIndex][j] = x;
			}
		}
	}

}

void triangularForm(double mA[n][n], const int size, double* cB) {

	for (int i = 0; i < size; i++)
	{
		double a = mA[i][i];
		for (int j = i; j < size; j++)
		{
			mA[i][j] /= a;
		}
		cB[i] /= a;
		for (int j = i + 1; j < size; j++)
		{
			double s = mA[j][i];
			for (int k = i; k < size; k++)
			{
				mA[j][k] -= s * mA[i][k];
			}
			cB[j] -= s * cB[i];
		}
	}
}

void reverseCourse(double mA[n][n], const int size, double* cB, double* X) {

	for (int k = size - 1; k >= 0; k--)
	{
		X[k] = cB[k];
		for (int i = size - 1; i > k; i--)
		{
			X[k] -= mA[k][i] * X[i];
		}
	}
	for (int i = 0; i < size; i++) {
		cout << X[i] << "\t";
	}
	cout << endl;

}
void vF(double mA[n][n], double* cB, double* X, const int size, double* vectorF) {


	for (int i = 0; i < size; i++)
	{
		vectorF[i] = cB[i];
		for (int j = 0; j < size; j++)
		{
			vectorF[i] -= mA[i][j] * X[j];
		}
		cout << vectorF[i] << "\t";
	}
	cout << endl;
}

void norma(double* vF, const int size) {
	double n = abs(vF[0]);
	for (int i = 0; i < size; i++) {
		n = max(vF[i], n);
	}
	cout << n;
}

void bGauss(double arr[n][n], const int size, double x[], double g[]) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			g[j] = arr[i][j] * x[j];
	}
}

void relativeError(double x1[], double x2[], const int size) {
	double res[n] = { 0 };
	cout << "relative error:" << endl;
	for (int i = 0; i < size; i++) {
		res[i] = (x2[i] - x1[i]) / x1[i];
		cout << res[i] << ' ';
	}

}
