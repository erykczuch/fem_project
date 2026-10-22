#include <iostream>
#include <cmath>
using namespace std;

double function_value(double a, double b, double c, double x)
{
	return a * x * x + b * x + c;
}

double rect(double a, double b, double c, double i_start, double i_end, int rect_amount)
{
	double length = i_end - i_start;
	double x = 0;
	double area = 0;

	double rect_size = length / rect_amount;

	for (int i = 0; i < rect_amount; i++)
	{
		x = i_start + rect_size * (i + 0.5);
		
		area += rect_size * function_value(a, b, c, x);
	}

	return area;
}

double gauss(double a, double b, double c, double i_start, double i_end, int point_amount)
{

	double* x_positions = new double[point_amount];
	double* x_values = new double[point_amount];
	double* x_weights = new double[point_amount];
	double length = i_end - i_start;

	double area = 0;

	switch (point_amount)
	{
	case 1:
	{
		x_positions[0] = 0.0;

		x_weights[0] = 2.0;
		break;
	}
	case 2:
	{
		x_positions[0] = -(1.0 / sqrt(3.0));
		x_positions[1] = (1.0 / sqrt(3.0));

		x_weights[0] = 1.0;
		x_weights[1] = 1.0;
		break;
	}
	case 3:
	{
		x_positions[0] = -sqrt(3.0 / 5.0);
		x_positions[1] = 0.0;
		x_positions[2] = sqrt(3.0 / 5.0);

		x_weights[0] = (5.0 / 9.0);
		x_weights[1] = (8.0 / 9.0);
		x_weights[2] = (5.0 / 9.0);
		break;
	}
	}

	double N_values[2];

	for (int i = 0; i < point_amount; i++)
	{
		N_values[0] = 0.5 * (1 - x_positions[i]);
		N_values[1] = 0.5 * (1 + x_positions[i]);

		x_values[i] = N_values[0] * i_start + N_values[1] * i_end;

		area += x_weights[i] * function_value(a, b, c, x_values[i]);
	}

	area *= (length / 2);

	return area;
}

int main()
{
	double a = 5;
	double b = 3;
	double c = 6;

	double i_start = -2;
	double i_end = 6;

	cout << "Metoda prostokatow: " << endl;
	cout << "\t5 przedzialow " << rect(a, b, c, i_start, i_end, 5) << endl;
	cout << "\t10 przedzialow " << rect(a, b, c, i_start, i_end, 10) << endl;
	cout << "\t20 przedzialow " << rect(a, b, c, i_start, i_end, 20) << endl;
	cout << "\t50 przedzialow " << rect(a, b, c, i_start, i_end, 50) << endl;
	cout << "\t100 przedzialow " << rect(a, b, c, i_start, i_end, 100) << endl;


	cout << endl << "Metoda Gaussa: " << endl;
	cout << "\t1 punktowy schemat " << gauss(a, b, c, i_start, i_end, 1) << endl;
	cout << "\t2 punktowy schemat " << gauss(a, b, c, i_start, i_end, 2) << endl;
	cout << "\t3 punktowy schemat " << gauss(a, b, c, i_start, i_end, 3) << endl;


	return 0;
}
