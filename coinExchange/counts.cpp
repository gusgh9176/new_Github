#include"stdafx.h"

counts::counts(int c, int *value)
{
	coin = c; // 받은 갯수
	m = new int[coin]; // 각각 동전 갯수 저장 배열
	capacity = 5;
	size = 0;
	pay = value;
	n = new int[capacity];
}

void counts::push(int count)
{
	if (capacity == size)
	{
		int* temp = new int[capacity*2];
		for (int i = 0; i < capacity; i++)
		{
			temp[i] = n[i];
		}
		delete n;
		n = new int[capacity*2];
		for (int i = 0; i < capacity; i++)
		{
			n[i] = temp[i];
		}
		capacity = capacity * 2;
		delete temp;
	}
	n[size] = count;
	size++;
}

void counts::solve(int money)
{
	int count = 0;
	for (int j = 0; j<coin; count=0)
	{
		if (b)
		{
			m[j] = money / pay[j]; // 가장큰 동전 갯수
			b = false;
		}
		tmoney = money;
		tmoney -= pay[j] * m[j];
		count += m[j];

		for (int i = j+1; i < coin; i++)
		{
			m[i] = tmoney / pay[i];
			tmoney -= pay[i] * m[i];
			count += m[i];
			
		}
		m[j]--;
		if (m[j] == 0)
		{
			j++;
			b = true;
		}
		if (m[j] != 0 && tmoney % m[j] == 0) { push(count); }
		if (m[coin - 2] == 0 && m[j] != 0 && m[coin-1]==m[j]) break;
	}
}

int counts::minReturn()
{
	int min = n[0];
	
	for (int i = 0; i < size; i++)
	{
		if (min > n[i])
			min = n[i];
	}
	return min;
}