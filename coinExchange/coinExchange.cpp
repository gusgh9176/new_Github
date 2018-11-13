// coinExchange.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
class counts;
int main()
{
	int coin;
	int *pay;
	int money;
	int temp;
	
	//cout << "동전갯수 : ";
	cin >> coin;
	pay = new int[coin];

	//cout << "교환받으려는 돈 : " << endl;
	cin >> money;

	//cout << "값 입력" << endl;
	for (int i = 0; i < coin; i++)
	{
		cin >> pay[i];
	}

	//내림차순 버블정렬
	for (int i = 0; i < coin; i++)
	{
		for (int j = i; j < coin; j++)
		{
			if (pay[i] < pay[j])
			{
				temp = pay[i];
				pay[i] = pay[j];
				pay[j] = temp;
			}
		}
	}
	counts counts(coin,pay);
	counts.solve(money);
	//cout << "교환동전 : ";
	cout << counts.minReturn() << endl;

    return 0;
}

