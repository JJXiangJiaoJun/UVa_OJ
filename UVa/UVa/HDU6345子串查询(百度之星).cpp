#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#define  mem(a,b) memset(a,b,sizeof(a))
#define  NUM_OF_CHAR  26
using namespace std;
const int maxn = 100000 + 1000;
char A[maxn];
int T;
int length,q;

//ע�� ��������������� + ��Ҫ�ı䱾�����
struct Sum {
	int number;
	char ch;
	Sum() {
		ch = 'Z'+1;
		number = 0;
	}
	Sum operator +(const Sum &rhs) {
		
		Sum temp;
		temp.number = number;
		temp.ch = ch;
		
		if(temp.ch==rhs.ch)
		temp.number= number+rhs.number;
	   else if (temp.ch > rhs.ch)
	   {
		   temp.number = rhs.number;
		   temp.ch = rhs.ch;
	   }

		return temp;
	}
	Sum& operator =(const Sum &rhs) {
		ch = rhs.ch;
		number = rhs.number;
		return *this;
	}

	bool operator >(const Sum &rhs) {
		return ch > rhs.ch;
	}
	bool operator <(const Sum &rhs)
	{
		return ch < rhs.ch;
	}
	bool operator == (const Sum &rhs)
	{
		return ch == rhs.ch;
	}
};


Sum sum[maxn << 2];

//���½ڵ�ĺ���
inline void PushUp(int rt)
{
	int left = rt << 1;
	int right = rt << 1 | 1;
	//ÿ����ĸ�ĸ����ֱ�Ϊ ��������������ÿ����ĸ�ĸ���֮��
	sum[rt] = sum[left] + sum[right];

	//printf("sum[%d] = sum[%d] + sum[%d]\n", rt, left, right);

}

//�����߶���
void Build(int l, int r, int rt)
{
	//printf("Build(l = %d ,r = %d, rt = %d)\n", l, r, rt);
	
	//�������Ҷ�ӽڵ���ô����ýڵ��ֵ
	if (l == r)
	{	
		//����ĸ����һ��
		sum[rt].number = 1;
		sum[rt].ch = A[l];
		//printf("����Ҷ�ӽڵ�rt = %d  sum[%d].number = %d sum[%d].ch = %c\n", rt, rt, sum[rt].number, rt, sum[rt].ch);
		return;
	}
	//�����е�
	int m = (l + r) >> 1;

	//�ݹ齨����������
	Build(l, m, rt << 1);
	Build(m + 1, r, rt << 1 | 1);
	//���������������֮�� �������ڵ�

	PushUp(rt);
}



//��ѯ������������(L,R)�е�ÿ����ĸ�ĺ�
Sum Query(int L, int R, int l, int r, int st)
{
	//printf("L = %d , R= %d, l= %d ,r = %d , st =%d \n", L, R, l, r, st);
	//�����Χ�� (L,R��֮�У���ôֱ�ӷ���ֵ
	if (L <= l&&R >= r)
	{
		//printf("return sum[%d]\n", st);
		//for (int i = 0; i < 5; i++)
		//	printf("sum[%d].ch[%d] = %d  ", st, i, sum[st].ch[i]);
		//printf("\n");
		return sum[st];
	}

	Sum ans;
	//mem(&ans, 0);
	//printf(" �ݹ����\n");
	//for (int i = 0; i < 5; i++)
	//	printf("��ʼ��ans.ch[%d] = %d  ", i, ans.ch[i]);
	//printf("\n");

	int m = (l + r) >> 1;
	//�������������Ƿ���ڲ�����������������ò���
	if (m >= L) ans = ans + Query(L, R, l, m, st << 1);
	if (m < R) ans = ans + Query(L, R, m + 1, r, st << 1 | 1);

	//for (int i = 0; i < 5; i++)
	//	printf("ans.ch[%d] = %d  ",i, ans.ch[i]);
	//printf("\n");
	//ͳ����Ϸ���
	return ans;

}

void solve()
{
	int left_bound;
	int right_bound;
	Sum my_ans;
	while (q--)
	{
		scanf("%d%d", &left_bound, &right_bound);

		//printf("left_bound = %d,right_bound = %d \n", left_bound, right_bound);
		my_ans = Query(left_bound, right_bound, 1, length, 1);
			
		//for (int i = 0; i < 5; i++)
		//	printf("my_ans.ch[%d] = %d   ", i, my_ans.ch[i]);
		//printf("\n");

		printf("%d\n", my_ans.number);
	}
}

int main()
{
	int kcase = 1;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d", &T);
	//mem(sum, 0);
	while (T--)
	{
		scanf("%d%d", &length, &q);
		scanf("%s", A+1);

		Build(1, length, 1);

		//for (int i = 1; i < 6; i++)
		//	printf("sum[%d].ch = %c sum[%d].number = %d  ", i, sum[i].ch, i, sum[i].number);
		//printf("\n");
		printf("Case #%d:\n", kcase++);
		solve();
	}
	return 0;
}