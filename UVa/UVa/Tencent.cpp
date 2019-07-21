#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;



int main()
{
	int N, K;
	while (scanf("%d%d", &N, &K) == 2 && N&&K) {
		int temp = N;
		int cnt = 0;
		for (int i = 1; i <= K; i++) {
			if (temp == 1) { break; }
			temp = (temp + 1) / 2;
			cnt++;
		}
		
		cnt += temp;

		printf("%d\n", cnt);
	}
	return 0;
}