#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
const int DIVIDER = 11;
const int N = 10;
bool cheack_if_divided(long long num, bool even, int& sum_even,
	int& sum_odd);
long long find_hiest_divided();
bool cheack_digits(long long num);

int main()
{
	cout<<find_hiest_divided()<<endl;

	int sum_even = 0;
	int sum_odd = 0;
	bool even = true;
	long long num = 987654201;
	if (cheack_if_divided(num, even, sum_even, sum_odd))
		cout << "yes";
	return EXIT_SUCCESS;
}	
long long find_hiest_divided()
{
	int sum_even = 0;
	int sum_odd = 0;
	bool even = true;
	for (long long i = 987654321; i > 123456789; i--)
	{
		if (cheack_digits(i))
		{
			if(cheack_if_divided(i, even, sum_even, sum_odd))
			{
				return i;
			}
			else
			{
				sum_even = sum_odd = 0;
				even = true;
			}
		}
	}
}
bool cheack_if_divided(long long num, bool even, int &sum_even,
int &sum_odd)
{
	if (num == 0)
	{
		int d = (sum_odd - sum_even);
		if (d % DIVIDER != 0)
			return false;
		else return true;
	}
	if (even)
	{
			sum_even += (num % 10);
			even = false;
	}
	else
	{
		sum_odd += (num % 10);
		even = true;
	}
	num = num/10;
	return cheack_if_divided(num, even, sum_even, sum_odd);

}

bool cheack_digits(long long num)
{
	int arr[N]={0};
	for (long long j = num; j > 0; j /= 10)
	{
		int temp = j % 10;
		arr[temp]++;
	}
	for (int i = 0; i < N; i++)
	{
		if (arr[i] > 1)
			return false;
	}
	return true;
} 