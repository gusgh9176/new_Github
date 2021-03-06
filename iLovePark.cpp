// iLovePark.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int m, n;
	int **road;
	int **temp;
	int **temp2;
	int count;

	road = new int*[m];
	for (int i = 0; i < m; ++i) { road[i] = new int[n]; }
	temp = new int*[m];
	for (int i = 0; i < m; ++i) { temp[i] = new int[n]; }
	temp2 = new int*[m];
	for (int i = 0; i < m; ++i) { temp2[i] = new int[n]; }

	cout << "공원 가로 갯수 : ";
	cin >> m;
	cout << "공원 세로 갯수 : ";
	cin >> n;

	//공원 구조 입력
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) { cin >> road[i][j]; }
	//temp에 구조 전달
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) { temp[i][j] = road[i][j]; }
	//temp2에 구조 전달
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) { temp2[i][j] = road[i][j]; }

	//인형 최대 갯수 구하는과정 
	for (int j = 2; j < m; j++) { temp[0][j] += temp[0][j - 1]; } // 첫 행 계산
	for (int i = 2; i < n; i++) { temp[i][0] += temp[i - 1][0]; } // 첫 열 계산
	for (int i = 1; i < n; i++) // 나머지 행렬 계산
	{
		for (int j = 1; j < m; j++)
		{
			if (i == n - 1 && j == m - 1) { temp[i][j] = 0; temp[0][0] = 0; } // 시작지점과 끝지점 숫자(2, 3)을 0으로 만듬
			if (temp[i - 1][j] >= temp[i][j - 1]) temp[i][j] += temp[i - 1][j];
			else if(temp[i - 1][j] < temp[i][j - 1]) temp[i][j] += temp[i][j-1];
		}
	}
	//과정 출력
	cout << "인형 최대 갯수 구하는 과정" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << temp[i][j] << " ";
		}
		cout << endl;
	}

	// 경로 탐색 코드
	count = temp[n - 1][m - 1];
	cout << "경로" << endl;
	road[n - 1][m - 1] = count;
	int k = n-1, l = m-1;
	while (1) 
	{
		if (k == 0 && l == 0) break;

		if (k > 0 && (temp[k][l] == temp[k - 1][l] || ((temp[k][l] == (temp[k - 1][l] + 1)) && temp2[k][l]==1)))
		{
			road[k - 1][l] = temp[n - 1][m - 1]; k--;
		}
		else if (l > 0 && ((temp[k][l] - temp[k][l - 1]) * (temp[k][l] - (temp[k][l - 1] + 1)) == 0)) { road[k][l - 1] = temp[n - 1][m - 1]; l--; }
		else { k = 0; l = 0; road[0][0] = temp[n - 1][m - 1]; }
	}

	// 경로 출력
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < m; j++)
		{
			cout << road[i][j]<<" ";
		}
		cout << endl;
	}
	cout << "최대로 주울수 있는 인형 개수 : ";
	cout << count << endl;

    return 0;
}

