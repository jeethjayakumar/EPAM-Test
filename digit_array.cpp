/*
 * digit_array.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: jjayakumar
 * Exercise: Given a number, e.g., 2789, as an array [2,7,8,9], increment it: change it to [2,7,9,0]
 */
#include <iostream>
#include <cctype>
using namespace std;

void arraydata_increment(int *a, int &num_dig);
int main()
{
	int num_digit, i, tmp_dig;
	int *a;
	string tmp;

	cout<<"Objective: Given a number, e.g., 2789, as an array [2,7,8,9], increment it: change it to [2,7,9,0]\n\n";
	cout<<"Enter number of digits for the input number: ";
	cin>>num_digit;
	a = new int [num_digit + 1];
	a[0] = 0;
	cout<<"Enter the input number (Press Enter key after typing each digit): ";
	for (i = 1; i <= num_digit; i++)
	{
		cin >> tmp;
		if (tmp.length()!= 1)
		{
			cout<<"Invalid input entered. Re-execute the binary and enter the digit from 0 to 9!!! Aborting!!!"<<endl;
			goto END;
		}
		tmp_dig = (int)tmp[0] - 48;
		//cout << "tmp = "<<tmp<<" , tmp_dig = "<<tmp_dig<<endl;
		if ((tmp_dig < 0) || (tmp_dig > 9))
		{
			cout<<"Invalid input entered. Re-execute the binary and enter the digit from 0 to 9!!! Aborting!!!"<<endl;
			goto END;
		}
		cin>>a[i];
	}

	arraydata_increment(a, num_digit);

	cout<<"After incrementing, new value = ";
	for (i = 0; i <= num_digit; i++)
	{
		if ((i == 0) && (a[i] == 0))
		{
			continue;
		}
		cout<<a[i];
	}
	cout<<endl;

END:
	return 0;
}

void arraydata_increment(int *a, int &num_dig)
{
	int i;

	for (i = num_dig; i >= 0 ; i--)
	{
		if (a[i] == 9)
		{
			a[i] = 0;
		}
		else
		{
			a[i]++;
			break;
		}
	}
}
