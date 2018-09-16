#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 50 + 10;
int building[maxn][maxn];
int n;
int main() 
{
	while (scanf("%d", &n) == 1 && n)
	{
		printf("2 %d %d\n", n, n);
		int ch = 'A';
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				building[i][j] = ch;
			if (ch == 'Z') {
				ch = 'a';
			}
			else
				ch++;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
			{
				printf("%c", building[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		ch = 'A';
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < n; i++)
				building[i][j] = ch;
			if (ch == 'Z') {
				ch = 'a';
			}
			else
				ch++;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
			{
				printf("%c", building[i][j]);
			}
			printf("\n");
		}
		printf("\n");

	}
	
	return 0;
}