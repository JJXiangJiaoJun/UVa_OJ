#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 1000;
int T;
int songs[maxn];
int seq[maxn];
int num[maxn];
int s, n;

int solve()
{
	int ans = 0;
	int start_max=-1;
	memset(seq, 0, sizeof(seq));
	memset(num, 0, sizeof(num));

	//Ҫ����s>n�����
	if (s > n)
	{
		//ͳ�Ƶ�һ����������
		for (int k = 0; k < n; k++)
		{
			int sid = songs[k];
			if (num[sid] == 0) seq[0]++;
			else if (num[sid] == 1) { seq[0]--; if (start_max == -1) start_max = k; } //�ҵ�ö���������ֵ
			num[sid]++;
		}
		if (start_max == -1) { ans = s; return ans; }

		for (int k = 1; k < n; k++)
		{
			int del_sid = songs[k - 1];
			seq[k] = seq[k - 1];
			if (num[del_sid] == 1) seq[k]--;
			else if (num[del_sid] == 2) seq[k]++;
			num[del_sid]--;

		}
	}
	else {
		//ͳ�Ƶ�һ����������
		for (int k = 0; k < s; k++)
		{
			int sid = songs[k];
			if (num[sid] == 0) seq[0]++;
			else if (num[sid] == 1) { seq[0]--; if (start_max == -1) start_max = k; } //�ҵ�ö���������ֵ
			num[sid]++;
		}
		if (start_max == -1) start_max = s - 1;
		//printf("start_max = %d\n", start_max);
		//printf("seq[0]=%d\n", seq[0]);
		//�������еĻ�������
		for (int i = 1; i < n - s + 1; i++)
		{
			int del_sid = songs[i - 1];
			int add_sid = songs[i + s - 1];
			seq[i] = seq[i - 1];
			if (del_sid == add_sid) {/*printf("seq[%d]=%d\n", i, seq[i]);*/ continue; }

			if (num[del_sid] == 1) seq[i]--;
			else if (num[del_sid] == 2) seq[i]++;
			num[del_sid]--;
			if (num[add_sid] == 0) seq[i]++;
			else if (num[add_sid] == 1) seq[i]--;
			num[add_sid]++;

			//printf("seq[%d]=%d\n", i, seq[i]);
		}
		//�����յ�Ļ�������
		for (int k = n - s + 1; k < n; k++)
		{
			int del_sid = songs[k - 1];
			seq[k] = seq[k - 1];
			if (num[del_sid] == 1) seq[k]--;
			else if (num[del_sid] == 2) seq[k]++;
			num[del_sid]--;
			//printf("seq[%d]=%d\n", k, seq[k]);
		}
	}

		//ö����㲢�����ж�

		for (int index = 0; index <= start_max; index++)
		{
			int ok = true;
			int check;
			for (check = index; check < n; check += s)
			{
				//����ҵ���β�������ĵط���������ѭ��
				if (check + s - 1 >= n) break;

				if (seq[check] != s) { ok = false; break; }
			}
			if (ok)
			{
				//��������
				if ((n - check) == seq[check])
					ans++;
			}
		}

	
	return ans;
}


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &s, &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &songs[i]);
		int ans =solve();
		printf("%d\n", ans);
	}
	return 0;
}


