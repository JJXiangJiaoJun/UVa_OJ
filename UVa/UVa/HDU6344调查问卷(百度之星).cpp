#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1000 + 10;
const int maxquestion = 10 + 5;
int T;
int n, m, k;
char Q[maxn][maxquestion];
int P[maxquestion];
int is_del[maxquestion];
int select[maxquestion];
//����ÿ������ж��ٿ���
int my_set[1 << 12];
int id[maxn];

int exist[maxn];


int Cn2;


//�������Ϊ index�� �ʾ��id
inline int get_id(int index)
{
	int id = 0;
	for (int i = 0; i < m; i++)
		if (!is_del[i])  id = id << 1 | (Q[index][i] - 'A');
	return id;
}



//�жϺ�����cur��ʾ��ǰ�� cur-1 �� �����Ѿ�����������Ҫö�ٶ��� cur ������
bool need_cut(int cur)
{
	//�����Լ�֦,��ǰ����ܲ����� ��ͬ�ʾ�Ķ���Ϊ
	int max_select = m - cur - 2;
	int max_set = pow(2, m - cur - 1);
	max_select = pow(4, max_select);
	//printf("max_select = %d\n", max_select);
	//
	if (n>max_set)
	{
		if ((max_select*(n / max_set+1)*(n / max_set+1)) < k)
			return true;
	}

	return false;
}

bool judge(int cur)
{
	memset(is_del, 0, sizeof(is_del));
	memset(my_set, 0, sizeof(my_set));
	int count = 0;
	//�����ж�
	for (int i = 0; i < cur; i++)
		is_del[P[i]] = 1;
	//���ÿ�������id,��ͳ�Ƽ���
	for (int i = 0; i < n; i++)
	{
		id[i] = get_id(i);
		//�ж��Ƿ��ظ�
		if (my_set[id[i]] == 0)
		{
			exist[count] = id[i];
			count++;
		}
		//ͳ�ƴ���+1
		my_set[id[i]] += 1;
	}
	int ans = 0;
	for (int i = 0; i<count - 1; i++)
		for (int j = i + 1; j < count; j++)
		{
			ans += my_set[exist[i]] * my_set[exist[j]];
			if (ans >= k)
				return true;
		}
	return false;
}

int problem_set = 0;


//ö��ѡ�����⼯�ϣ���ǰö�ٵ��ǵ� cur �� Ԫ��
void generate_subset(int m,int cur,int mini_index)
{
	//�����Ҫ��֦�򲻼���ö��
	//if (need_cut(cur))   return;
	//printf("cur = %d  need_cut return false\n",cur);

	//��������ж�
	if (!judge(cur)) return;
	problem_set++;

	//if (need_cut(cur))   return;

	//ö�����⼯��
	for (int i = mini_index; i < m; i++)
	{
		P[cur] = i;
		//if (need_cut(cur))   return;
		//ö����һ����ѡ����Ӽ�
		generate_subset(m, cur + 1, i + 1);

	}
	//if (need_cut(cur))   return;
}


void solve()
{
	if (Cn2 < k)
	{
		printf("0\n");
		return;
	}
	problem_set = 0;
	generate_subset(m, 0, 0);
	printf("%d\n", problem_set);
}

int main()
{
	
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	int kcase = 1;
	while (T--)
	{
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 0; i < n; i++)
			scanf("%s", Q[i]);
		Cn2 = n*(n - 1) / 2;
		printf("Case #%d: ", kcase++);
		solve();
	}
	
	return 0;
}

