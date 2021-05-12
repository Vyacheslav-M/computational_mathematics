#include <iostream>
#include "Gauss.h"
#include "bisection.h"
using namespace std;

// умножение матриц
// a[4][4] - 1-ая матрица
// b[4] - 2-ая матрица
// Y[4] - результат
void multiplicationMatrix(double a[4][4], double b[4], double Y[4])
{
	for (int i = 0; i < 4; i++)
	{
		Y[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			Y[i] += a[i][j] * b[j];
		}
	}
}

// вычисление векторов Y
// М[4][4] - заданная матрица
// Y[4][5] - результат
void vectorComputation(double M[4][4], double Y[4][5])
{
	double Y0[4] = { 1, 0, 0, 0 };
	double Y1[4], Y2[4], Y3[4], Y4[4];

	// вычисление векторов Y
	multiplicationMatrix(M, Y0, Y1);
	multiplicationMatrix(M, Y1, Y2);
	multiplicationMatrix(M, Y2, Y3);
	multiplicationMatrix(M, Y3, Y4);

	// занесение векторов Y в общую матрицу
	for (int i = 0; i < 4; i++)
	{
		Y[i][0] = Y3[i];
	}
	for (int i = 0; i < 4; i++)
	{
		Y[i][1] = Y2[i];
	}
	for (int i = 0; i < 4; i++)
	{
		Y[i][2] = Y1[i];
	}
	for (int i = 0; i < 4; i++)
	{
		Y[i][3] = Y0[i];
	}
	for (int i = 0; i < 4; i++)
	{
		Y[i][4] = -Y4[i];
	}
}

// вычисление собственных чисел матрицы
// *p - корни системы линейных уравнений
// *a - результат
void calculationEigenvalues(double *p, double *a)
{
	double f1 = 0, f2, x = -50;
	int j = 0;

	// нахождение промежутка с корнями
	for (int i = 0; i < 100; i++)
	{
		f2 = f(x, p);
		// проверка на наличие корней 
		if (f1 * f2 < 0)
		{
			// Метод биссекции
			bisectionMethod(x - 1, x, p, &a[j]);
			j++;
		}
		x++;
		f1 = f2;
	}

	cout << "Собственные числа\n\n";
	for (int i = 0; i < 4; i++)
	{
		cout << "a" << i << ": " << a[i] << endl;
	}
	cout << endl;
}

// вычисление собственных векторов матрицы
// Y[4][5] - вектора у
// *p - корни системы линейных уравнений
// *a - собственные числа
void calculationEigenvectors(double Y[4][5], double *p, double *a)
{
	cout << "Собственные вектора.\n\n";

	for (int i = 0; i < 4; i++)
	{
		double q[5];
		q[0] = 1;

		// вычисление вектора q
		// по формуле q(j) = a(i)*q(j-1) + p(j-1)
		for (int j = 1; j < 5; j++)
		{
			q[j] = a[i] * q[j - 1] + p[j - 1];
		}

		double X[4] = { 0, 0, 0, 0 }, temp[4];

		// вычисление собственного вектора
		// по формуле X = q(0)*Y(3) + q(1)*Y(2) + q(2)*Y(1) + q(3)*Y(0)
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				X[k] += Y[k][j] * q[j];
			}
		}

		cout << "X" << i + 1 << ":\n";
		for (int i = 0; i < 4; i++)
		{
			cout << X[i] << endl;
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	double M[4][4] = { 1.2, 0.5,   2,   1,
					   0.5,   1, 0.6,   2,
					     2, 0.6,   1,   1,
					     1,   2,   1,   1
	};
	
	// вычисление векторов Y
	double Y[4][5];
	vectorComputation(M, Y);

	// нахождение корней системы линейных уравнений
	double p[5];
	GaussMethod(Y, p);
	
	// вычисление собственных чисел
	double a[4];
	calculationEigenvalues(p, a);

	// вычисление собственных векторов
	calculationEigenvectors(Y, p, a);
	return 0;
}