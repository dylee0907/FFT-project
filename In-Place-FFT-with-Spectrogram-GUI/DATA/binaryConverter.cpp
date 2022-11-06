#include <iostream>
#include <fstream>
#include <cmath>

#define length 321
#define exponentBit 6
#define significandBit 1

void exponentbinary(int* exponent, int exponent_deci);
void significandbinary(int* significand, float temp_d);

int main(void)
{
	int bias = pow(2, (exponentBit - 1)) - 1;
	int cnt_error = 0;

	float temp_f = 0;
	
	int temp_b = 0;
	float temp_c = 0;
	float temp_d = 0;

	int cnt_b;

	int exponent_deci = 0;
	int exponent_max = 0;
	int exponent_min = 0;

	int sign;
	int exponent[exponentBit];
	int significand[significandBit];

	std::ifstream INFILE;
	INFILE.open("C:\\PROJECT\\FFT\\STFT\\GUI\\.resampler\\sample1.txt");

	std::ofstream OFILE;
	OFILE.open("C:\\PROJECT\\FFT\\STFT\\GUI\\.resampler\\o_sample1.txt");

	if (!INFILE.is_open())
	{
		std::cout << "Fail to Open";
		return -1;
	}
	
	for (int i = 0; i < length; i++)
	{
		cnt_b = 0;
		INFILE >> temp_f;

		// sign bit
		if (temp_f > 0) sign = 0;
		else sign = 1;
		
		// absolute float
		temp_f = abs(temp_f);

		// exponent and significand bit calculation
		// exception zero
		if (temp_f == 0)
		{
			for (int i = exponentBit - 1; i >= 0; i--)
				exponent[i] = 0;
			for (int i = 0; i < significandBit; i++)
				significand[i] = 0;
		}
		// normal case
		else
		{
			if (temp_f >= 1)
			{
				temp_b = temp_f;
				while (1)
				{
					if (temp_b)
					{
						break;
					}
					temp_b /= 2;
					cnt_b++;
				}
			}
			else
			{
				temp_c = temp_f;
				while (1)
				{
					if (temp_c >= 1 || temp_c == 0)
					{
						break;
					}
					temp_c *= 2;
					cnt_b--;
				}
			}
			// exponen_deci range
			exponent_deci = bias + cnt_b;
			if (exponent_deci < 0 || exponent_deci > 2*bias+1)
				cnt_error++;

			// temp_d is significand decimal
			temp_d = temp_f / pow(2, cnt_b) - 1.0;

			// convert to binary
			exponentbinary(exponent, exponent_deci);
			significandbinary(significand, temp_d);
		}
		OFILE << sign;
		for (int j = 0; j < exponentBit; j++)
			OFILE << exponent[j];
		for (int j = 0; j < significandBit; j++)
			OFILE << significand[j];
		OFILE << "\n";
	}
	
	std::cout << "Total Exponent bit error: " << cnt_error << "\n";
	OFILE.close();
	INFILE.close();
	
	return 0;
}

void exponentbinary(int* exponent, int exponent_deci)
{
	for (int i = exponentBit - 1; i >= 0; i--)
	{
		exponent[i] = exponent_deci % 2;
		exponent_deci /= 2;
	}
}

void significandbinary(int* significand, float temp_d)
{

	for (int i = 0; i < significandBit; i++)
	{
		temp_d *= 2;
		if (temp_d >= 1)
		{
			significand[i] = 1;
			temp_d--;
		}
		else
		{
			significand[i] = 0;
		}
	}
}