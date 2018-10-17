#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 16384 + 1000;
double scores[maxn][3];
double max_score[maxn];
int max_score_int[maxn];

int ranked[maxn];
int n;
int kcase=1;

double sorted_sc[maxn][10];

int scores_int[maxn][3];
int sorted_sc_int[maxn][10];

void calculate(int index)
{
	//��һ����۵ķ���
	int cnt = 0;
	for (; cnt < 3; cnt++)
		sorted_sc[index][cnt] = scores[index][cnt];
	//��������Ŀ�۵ķ���
	for(int i=0;i<3;i++)
		for (int j = i + 1; j < 3; j++)
		{
			sorted_sc[index][cnt++] = scores[index][i] + scores[index][j];
		}
	sorted_sc[index][cnt++] = max_score[index];

	sort(sorted_sc[index], sorted_sc[index] + cnt);
}


void calculate_int(int index)
{
	//��һ����۵ķ���
	int cnt = 0;
	for (; cnt < 3; cnt++)
		sorted_sc_int[index][cnt] = scores_int[index][cnt];
	//��������Ŀ�۵ķ���
	for (int i = 0; i<3; i++)
		for (int j = i + 1; j < 3; j++)
		{
			sorted_sc_int[index][cnt++] = scores_int[index][i] + scores_int[index][j];
		}
	sorted_sc_int[index][cnt++] = max_score_int[index];

	sort(sorted_sc_int[index], sorted_sc_int[index] + cnt);
}



void solve()
{
	//�����ο�ʼ����
	//double max_sc=max_score[ranked[1]];

	int max_sc_int = max_score_int[ranked[1]];
	//printf("max_sc[%d] = %.2lf  ranked[%d]=%d\n", 1, max_sc, 1, ranked[1]);
	for (int i = 2; i <= n; i++)
	{
		
		if (max_sc_int == 0) {
			//printf("��һ����0 ����: %d \n", ranked[i]);
			if (ranked[i] < ranked[i - 1]) {
				printf("Case %d: No solution\n", kcase++); return;
			}
		}
		else {
			//ǰID�Ƚϴ�,��ôֻ��
			if (ranked[i] < ranked[i - 1])
			{
				//double temp_max = max_score[ranked[i]];

				int temp_max_int = max_score_int[ranked[i]];

				int index = 0;
				while (temp_max_int >= max_sc_int&&index<7)
				{
					temp_max_int = max_score_int[ranked[i]]-sorted_sc_int[ranked[i]][index++];
				}
				//����������
				max_sc_int = temp_max_int;
				//printf("index = %d ", index);
			}
			else
			{
				//double temp_max = max_score[ranked[i]];
				//int index = 0;
				//while (temp_max > max_sc&&index<7)
				//{
				//	temp_max = max_score[ranked[i]] - sorted_sc[ranked[i]][index++];
				//}
				////����������
				//max_sc = temp_max;
				int temp_max_int = max_score_int[ranked[i]];

				int index = 0;
				while (temp_max_int > max_sc_int&&index<7)
				{
					temp_max_int = max_score_int[ranked[i]] - sorted_sc_int[ranked[i]][index++];
				}
				//����������
				max_sc_int = temp_max_int;
				//printf("index = %d ", index);
			}
		}
		//printf("max_sc[%d] = %.2lf  ranked[%d]=%d max_score[%d] = %.2lf\n", i, max_sc, i, ranked[i],i,max_score[ranked[i]]);
	}

	printf("Case %d: %.2lf\n", kcase++, (double)max_sc_int/100);
}


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	while (scanf("%d", &n) == 1 && n)
	{
		//printf("n = %d\n", n);
		for (int i = 1; i <= n; i++)
		{
			double max = 0;
			int max_int = 0;
			for (int j = 0; j < 3; j++)
			{
				scanf("%lf", &scores[i][j]);
				//!!!!!!!!!!!!!!!!!!!!!!!�����������ȣ�����Ҫ��û���ⲽ�𰸳�����
				scores_int[i][j] = (int)round(scores[i][j] * (100.0));
				/////////////////////////////////////////////////////////////////
				max_int += scores_int[i][j];
				max += scores[i][j];
			}
			//sort(scores[i], scores[i]+3);
			max_score[i] = max;
			max_score_int[i] = max_int;
			calculate(i);
			calculate_int(i);
		}
		for (int i = 1; i <= n; i++)
			scanf("%d", &ranked[i]);
		//printf("max_score[166] = %.2lf\n", max_score[166]);
		//for (int i = 0; i <7; i++)
		//	printf("%.2lf ", sorted_sc[ranked[61]][i]);

		//printf("\n");
		solve();
	}
}