#pragma once

// Метод Гаусса
// Arr[4][5] - массив, хранящий систему уравнений
// *p - результат
void GaussMethod(double Arr[4][5], double *p)
{
	double a;
	double M[4][5];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			M[i][j] = Arr[i][j];
		}
	}

	// делим первую строку на коэффициет а11
	a = M[0][0];
	for (int i = 0; i < 5; i++)
	{
		M[0][i] = M[0][i] / a;
	}

	// вычитаем из второй строки первую умноженную на коэффициет а21
	a = M[1][0];
	for (int i = 0; i < 5; i++)
	{
		M[1][i] = M[1][i] - a * M[0][i];
	}

	// вычитаем из третей строки первую умноженную на коэффициет а31
	a = M[2][0];
	for (int i = 0; i < 5; i++)
	{
		M[2][i] = M[2][i] - a * M[0][i];
	}

	// вычитаем из четвертой строки первую умноженную на коэффициет а41
	a = M[3][0];
	for (int i = 0; i < 5; i++)
	{
		M[3][i] = M[3][i] - a * M[0][i];
	}

	// делим вторую строку на коэффициет а22
	a = M[1][1];
	for (int i = 1; i < 5; i++)
	{
		M[1][i] = M[1][i] / a;
	}

	// вычитаем из третей строки вторую умноженную на коэффициет а32
	a = M[2][1];
	for (int i = 1; i < 5; i++)
	{
		M[2][i] = M[2][i] - a * M[1][i];
	}

	// вычитаем из четвертой строки вторую умноженную на коэффициет а42
	a = M[3][1];
	for (int i = 1; i < 5; i++)
	{
		M[3][i] = M[3][i] - a * M[1][i];
	}

	// делим третью строку на коэффициет а33
	a = M[2][2];
	for (int i = 2; i < 5; i++)
	{
		M[2][i] = M[2][i] / a;
	}

	// вычитаем из четвертой строки третью умноженную на коэффициет а43
	a = M[3][2];
	for (int i = 1; i < 5; i++)
	{
		M[3][i] = M[3][i] - a * M[2][i];
	}

	// делим четвертую строку на коэффициет а44
	a = M[3][3];
	for (int i = 2; i < 5; i++)
	{
		M[3][i] = M[3][i] / a;
	}

	// вычисляем х1, х2, х3, x4
	p[3] = M[3][4];
	p[2] = M[2][4] - M[2][3] * p[3];
	p[1] = M[1][4] - M[1][2] * p[2] - M[1][3] * p[3];
	p[0] = M[0][4] - M[0][1] * p[1] - M[0][2] * p[2] - M[0][3] * p[3];
}