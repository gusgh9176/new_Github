#pragma once
#include "stdafx.h"
class counts
{
private:
	int size;
	int capacity;
	int coin;
	int *pay;
	int tmoney;
	int *m;
	int *n;
	bool b=true;
	void push(int n);
public:
	counts(int c, int *n);
	void solve(int money);
	int minReturn();
};