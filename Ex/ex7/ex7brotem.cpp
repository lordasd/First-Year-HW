#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::swap;

const int MAX_STR_LEN = 1000;
const int ENCRYPT = 1;
const int DECRYPT = 2;

void change_letter(char str[], int n);
void switch_letter(char str[], int n);
void add_letter(char str[], int n);
void less_letter(char str[], int n);


int main()
{
	int option;
	cin >> option;
	char str[MAX_STR_LEN];
	cin.ignore();
	cin.getline(str, MAX_STR_LEN);

	srand(17);
	int n = rand() % 3 + 2;

	switch (option)
	{
	case ENCRYPT:
	{
		change_letter(str, n);
		switch_letter(str, n);
		add_letter(str, n);
		break;
	}
	case DECRYPT:
	{
		less_letter(str, n);
		break;
	}

	}

	return EXIT_SUCCESS;
}

void change_letter(char str[], int n)
{
	int len = strlen(str);

	for (int i = 0; i < len; i++)
	{
		if (isalpha(str[i]))
		{

			if (isupper(str[i]))
			{
				if (str[i] + n > 'Z')
					str[i] = 'A' + n - (('Z' - str[i]) + 1);
				else
					str[i] = str[i] + n;
			}
			else if (islower(str[i]))
			{
				if (str[i] + n > 'z')
					str[i] = 'a' + n - (('z' - str[i]) + 1);

				else
					str[i] += n;
			}
		}
		else
			str[i] = str[i];

	}
	cout << str << endl;
}


void switch_letter(char str[], int n)
{
	int len = strlen(str);
	for (int j = 0; j + n <= len; j += n)
	{
		int c = j;
		int temp = (j + n) - 1;
		while (c != temp || c < temp)
		{
			swap(str[c], str[temp]);
				c++;
				temp--;
		}
	}
	
	cout << str << endl;
}

void add_letter(char str[], int n)
{
	char random = rand() % ('z' - 'a'+1) + 'a';
	char temp1;
	int len = strlen(str);
	for (int k = n; k < len; k+=(n+1))
	{
		temp1 = str[k];
		str[k] = random;
		len++;
		int l = k;
		while (str[l] != '\0')
		{
			char temp2 = str[l + 1];
			str[l + 1] = temp1;
			temp1 = temp2;
			l++;
		}
	
	}
	cout << str <<n<< endl;

} 

void less_letter(char str[], int n)
{
	char temp1;
	int len = strlen(str);
	for (int k = n; k < len; k += (n + 1))
	{ 
		temp1 = str[k];
		len--;
		int l = k;
		while (str[l] != '\0')
		{
			char temp2 = str[l + 1];
			str[l + 1] = temp1;
			temp1 = temp2;
			l--;
		}

	}
	cout << str << endl;
}