#pragma once

// вычисление значения функции в заданной точке
// x - значение
// *p - коэффициенты уравнения
double f(double x, double *p)
{
	double f;
	f = x * x * x * x + p[0] * x * x * x + p[1] * x * x + p[2] * x + p[3];
	return f;
}

// Метод биссекции
// а - левая граница
// b - правая граница
// *p - коэффициенты уравнения
// *res - результат
void bisectionMethod(double a, double b, double* p, double *res)
{
	double e = 0.001, c;

	// нахождение корня уравнения 
	// с заданной точностью
	do
	{
		// нахождение середины отрезка
		c = (a + b) / 2;
		// определение границ в которых
		// находится корень
		if (f(a, p) * f(c, p) < 0)
		{
			b = c;
		}
		else
		{
			a = c;
		}
	} while (abs(f(c, p)) > e);
	*res = c;
}