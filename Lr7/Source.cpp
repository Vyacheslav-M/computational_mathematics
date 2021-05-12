#include <iostream>
#include "Gauss.h"
#include "bisection.h"
using namespace std;

// ��������� ������
// a[4][4] - 1-�� �������
// b[4] - 2-�� �������
// Y[4] - ���������
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

// ���������� �������� Y
// �[4][4] - �������� �������
// Y[4][5] - ���������
void vectorComputation(double M[4][4], double Y[4][5])
{
	double Y0[4] = { 1, 0, 0, 0 };
	double Y1[4], Y2[4], Y3[4], Y4[4];

	// ���������� �������� Y
	multiplicationMatrix(M, Y0, Y1);
	multiplicationMatrix(M, Y1, Y2);
	multiplicationMatrix(M, Y2, Y3);
	multiplicationMatrix(M, Y3, Y4);

	// ��������� �������� Y � ����� �������
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

// ���������� ����������� ����� �������
// *p - ����� ������� �������� ���������
// *a - ���������
void calculationEigenvalues(double *p, double *a)
{
	double f1 = 0, f2, x = -50;
	int j = 0;

	// ���������� ���������� � �������
	for (int i = 0; i < 100; i++)
	{
		f2 = f(x, p);
		// �������� �� ������� ������ 
		if (f1 * f2 < 0)
		{
			// ����� ���������
			bisectionMethod(x - 1, x, p, &a[j]);
			j++;
		}
		x++;
		f1 = f2;
	}

	cout << "����������� �����\n\n";
	for (int i = 0; i < 4; i++)
	{
		cout << "a" << i << ": " << a[i] << endl;
	}
	cout << endl;
}

// ���������� ����������� �������� �������
// Y[4][5] - ������� �
// *p - ����� ������� �������� ���������
// *a - ����������� �����
void calculationEigenvectors(double Y[4][5], double *p, double *a)
{
	cout << "����������� �������.\n\n";

	for (int i = 0; i < 4; i++)
	{
		double q[5];
		q[0] = 1;

		// ���������� ������� q
		// �� ������� q(j) = a(i)*q(j-1) + p(j-1)
		for (int j = 1; j < 5; j++)
		{
			q[j] = a[i] * q[j - 1] + p[j - 1];
		}

		double X[4] = { 0, 0, 0, 0 }, temp[4];

		// ���������� ������������ �������
		// �� ������� X = q(0)*Y(3) + q(1)*Y(2) + q(2)*Y(1) + q(3)*Y(0)
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
	
	// ���������� �������� Y
	double Y[4][5];
	vectorComputation(M, Y);

	// ���������� ������ ������� �������� ���������
	double p[5];
	GaussMethod(Y, p);
	
	// ���������� ����������� �����
	double a[4];
	calculationEigenvalues(p, a);

	// ���������� ����������� ��������
	calculationEigenvectors(Y, p, a);
	return 0;
}