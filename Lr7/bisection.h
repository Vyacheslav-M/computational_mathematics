#pragma once

// ���������� �������� ������� � �������� �����
// x - ��������
// *p - ������������ ���������
double f(double x, double *p)
{
	double f;
	f = x * x * x * x + p[0] * x * x * x + p[1] * x * x + p[2] * x + p[3];
	return f;
}

// ����� ���������
// � - ����� �������
// b - ������ �������
// *p - ������������ ���������
// *res - ���������
void bisectionMethod(double a, double b, double* p, double *res)
{
	double e = 0.001, c;

	// ���������� ����� ��������� 
	// � �������� ���������
	do
	{
		// ���������� �������� �������
		c = (a + b) / 2;
		// ����������� ������ � �������
		// ��������� ������
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