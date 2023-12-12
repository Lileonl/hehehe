#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

double* Gauss(double** Array_A, double* Array_B, int n);
// variant 8
int main()
{
	// 1
	/*double x[10] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
	double y[10] = { 0.957, 0.969, 0.976, 0.978, 0.975, 0.968, 0.954, 0.939, 0.918, 0.894 };*/
	double x[6] = { 0, 20, 40, 60, 80, 100 };
	double y[6] = { 29.5, 18.4, 11.9, 8.6, 5.0, 3.3 };
	for (int i = 0; i < 6; i++) {
		y[i] = log10(y[i]);
		cout << y[i] << "  ";
	}
	cout << endl;
	// 2
	const int N = 6;
	const int m = 1;
	// 3
	double* POWERX = new double[2 * m];
	cout << "POWERX: ";
	for (int k = 0; k < 2 * m; k++)
	{
		POWERX[k] = 0;
		for (int i = 0; i < N; i++)
		{
			POWERX[k] += pow(x[i], k + 1);
		}
		cout << POWERX[k] << "  ";
	}
	cout << endl << endl;
	// 4
	double** SUMX = new double* [m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		SUMX[i] = new double[m + 1];
	}

	for (int l = 0; l < m + 1; l++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			if (j + l)
			{
				SUMX[l][j] = POWERX[l + j - 1];
			}
			else
			{
				SUMX[l][j] = N;
			}
		}
	}
	// 5
	double* PRAW = new double[m + 1];
	for (int l = 0; l < m + 1; l++)
	{
		PRAW[l] = 0;
		for (int i = 0; i < N; i++)
		{
			PRAW[l] += y[i] * pow(x[i], l);
		}
	}
	// 6
	double* a = Gauss(SUMX, PRAW, m + 1);
	// 7
	double S2 = 0;
	for (int i = 0; i < N; i++)
	{
		double sum = y[i];
		for (int j = 0; j < m + 1; j++)
		{
			sum -= a[j] * pow(x[i], j);
		}
		S2 += pow(sum, 2);
	}
	S2 /= N - m - 1;
	double sigma = sqrt(S2);
	// 8
	cout << "Coefficients 'a': " << a[0] << endl;
	for (int i = 1; i < m + 1; i++)
	{
		cout << setw(26) << a[i] << endl;
	}
	cout << "\nStandard deviation: " << sigma << endl;
}

double* Gauss(double** Array_A, double* Array_B, int n)
{
	double* X = new double[n];
	for (int k = 0; k < n; k++)
	{
		for (int i = k + 1; i < n; i++)
		{
			if (abs(Array_A[i][k]) > abs(Array_A[k][k]))
			{
				swap(Array_A[i], Array_A[k]);
				swap(Array_B[i], Array_B[k]);
			}
		}
		double A_Main = Array_A[k][k];
		if (A_Main == 0)
		{
			cout << "error\n";
			system("pause");
			exit(0);
		}
		for (int i = k; i < n; i++)
		{
			Array_A[k][i] /= A_Main;
		}
		Array_B[k] /= A_Main;
		for (int i = k + 1; i < n; i++)
		{
			double s = Array_A[i][k];
			for (int j = k; j < n; j++)
			{
				Array_A[i][j] -= s * Array_A[k][j];
			}
			Array_B[i] -= s * Array_B[k];
		}
	}
	for (int k = n - 1; k >= 0; k--)
	{
		X[k] = Array_B[k];
		for (int i = n - 1; i > k; i--)
		{
			X[k] -= Array_A[k][i] * X[i];
		}
	}
	return X;
}