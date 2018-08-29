#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define mem(a,b)  memset(a,b,sizeof(a))
#define FOR(a,max)   for(int a=0;a<max;a++)
const int maxn = 10000;
int num_of_stick;
int length[maxn];

int max_length;
int sum = 0;
int len_per_stick = 0;
int select_num = 0;
int sticknum = 0;
int is_selected[maxn];

//ö�ٵ� cur ��ľ���� ö��Сľ��������Ϊ index �� ö���ܺ�Ϊ cnt
bool dfs(int cur, int index, int cnt,int sel_num)
{
	if (cur*len_per_stick == sum) return true;
	

	//ö��ľ��
	for (int i = index; i < num_of_stick; i++)
	{
		//���֮ǰû��ѡ��ͬ����Сľ�����������ͬ���ȵ�Сľ������ѡ��
		if (i&& !is_selected[i-1] && (length[i - 1] == length[i])) continue;

		//�����ǰľ����ѡ���ˣ���ô����
		if (is_selected[i]) continue;

		//ѡ��󳤶ȴ��ڹ涨ֵ
		if (cnt + length[i] > len_per_stick) continue;

		if (cnt + length[i] == len_per_stick) {
			is_selected[i] = 1;
			if (dfs(cur + 1, 0, 0, 0)) return true;
			is_selected[i] = 0;
			return false;
		}

		//����ѡ��ǰСľ��
		is_selected[i] = 1;
		if (dfs(cur, i + 1, cnt + length[i],sel_num+1)) return true;
		//�����ǰ���û�гɹ�

		//����ǵ�ǰ����ľ������
		is_selected[i] = 0;

		//����ƥ���cnt + 1��ľ��ʱ������Ǹ�ľ��stick���һ����ѡ��
		//����ʱ��cnt + 1���ȳ�ľ��ƥ��ʧ�ܣ����cnt + 1���ȳ�ľ���������ƥ��
		//�����ص�cnt���ȳ�ľ����ƥ�伴�ɣ���Ϊ��stick�ڴ˴�ƥ��ʱƥ��Ŀ�ѡľ����ΧҪ���Ժ����
		//�˴ζ�ƥ�䲻�ɣ��Ժ��ƥ�䲻�ɣ�Ҫ����ƥ���cnt��ľ�������Բ����µ��ľ��stick�������ɴ˳���ƥ���cnt + 1���ȳ�ľ����
		//if (sel_num == 0 && length[i] == length[index]) return false;
		if (sel_num == 0) return false;


	}
	return false;
}

void solve() {

	
	for (len_per_stick = max_length;len_per_stick<=sum/2; len_per_stick++)
	{
		mem(is_selected, 0);
		//����������������������ô������ö��ѡ��
		if (sum%len_per_stick) continue;
		//printf("sum%%len_per_stick=%d\n", sum%len_per_stick);
		sticknum = sum / len_per_stick;
		//printf("sticknum=%d len_per_stick=%d\n\n",sticknum,len_per_stick);

		if (dfs(0,0,0,0)) { printf("%d\n", len_per_stick); return; }
		//printf("�˳�dfs\n");
	}
	printf("%d\n", sum);

}

bool cmp(const int &a, const int &b) {
	     return a > b;
	
}


int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	
	while (scanf("%d", &num_of_stick) == 1 && num_of_stick)
	{
		sum = 0;
		mem(length, 0);
		for (int i = 0; i < num_of_stick; i++)
		{
			scanf("%d", &length[i]);
			sum += length[i];
		}
		//sort(length, length + num_of_stick);
		
		//���ս�������
		sort(length, length + num_of_stick,cmp);

		//FOR(i, num_of_stick)
		//{
		//	printf("%d ", length[i]);
		//}
		//printf("\n\nnum_of_stick=%d\n", num_of_stick);
		//printf("\n\n");
		//max_length = length[num_of_stick - 1];
		max_length = length[0];
		//printf("max_len = %d sum=%d\n", max_length,sum);
		solve();
	}
	
	
	return 0;
}

