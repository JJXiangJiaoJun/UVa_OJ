#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int nodenum = 15;
const int maxn = 15+3;
const int maxdir = 4;  //ÿ�������ܹ���ת�������
const int maxnjumpnode = 4; //ÿ������һ����������Ĳ���
const int maxstate = 20 + 10;
int maxd;
int step = 0;
int state[maxn];
int end_state[maxn];
int start_state[maxn];
struct Node {
	int path;
	int space;
	int father;
	int dist;
};

Node node[maxstate];

//����ÿһ���ߵ��±�
int jump[maxn][maxdir][maxnjumpnode] = \
{
	{ {2,5,9,14}, {1,3,6,10}, {-1,-1,-1,-1}, {-1,-1,-1,-1}} ,  //0�ڵ�
	{ {4, 8, 13,-1}, { 3,6,10,-1 }, { -1,-1,-1,-1 }, { -1,-1,-1,-1 }} ,	 //1�ڵ�
	{ {5, 9, 14, -1}, { 4,7,11,-1 }, { -1,-1,-1,-1 }, { -1,-1,-1,-1 }},   //2�ڵ�
	{ {1, 0, -1, -1}, { 4,5,-1,-1 }, { 7,12,-1,-1 }, { 6,10,-1,-1 }},   //3�ڵ�
	{ { 8, 13, -1, -1 },{ 7,11,-1,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //4�ڵ�
	{ { 2, 0, -1, -1 },{ 9,14,-1,-1 },{ 8,12,-1,-1 },{ 4,3,-1,-1 } },   //5�ڵ�
	{ { 3, 1, 0, -1 },{ 7,8,9,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //6�ڵ�
	{ { 4, 2, -1, -1 },{ 8,9,-1,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //7�ڵ�
	{ { 7, 6, -1, -1 },{ 4,1,-1,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //8�ڵ�
	{ { 5, 2, 0, -1 },{ 8,7,6,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //9�ڵ�
	{ { 6, 3, 1, 0 },{ 11,12,13,14},{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //10�ڵ�
	{ { 7, 4, 2, -1 },{12,13,14,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //11�ڵ�
	{ { 8, 5, -1, -1 },{ 13,14,-1,-1 },{ 11,10,-1,-1 },{ 7,3,-1,-1 } },   //12�ڵ�
	{ { 8, 4, 1, -1 },{12,11,10,-1 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //13�ڵ�
	{ { 9,5,2,0},{ 13,12,11,10 },{ -1,-1,-1,-1 },{ -1,-1,-1,-1 } },   //14�ڵ�

};


int max_dir[maxn] = \
{
		2,     //0�ڵ�
		2,     //1�ڵ�
		2,     //2�ڵ�
		4,     //3�ڵ�
		2,     //4�ڵ�
		4,     //5�ڵ�
		2,     //6�ڵ�
		2,    //7�ڵ�
		2,    //8�ڵ�
		2,     //9�ڵ�
		2,    //10�ڵ�
		2,		//11�ڵ�
		4,		//12�ڵ�
		2,		//13�ڵ�
		2,     //14�ڵ�
};


int max_step[maxn] = \
{
		4,     //0�ڵ�
		3,     //1�ڵ�
		3,     //2�ڵ�
		2,     //3�ڵ�
		2,     //4�ڵ�
		2,     //5�ڵ�
		3,     //6�ڵ�
		2,    //7�ڵ�
		2,    //8�ڵ�
		3,     //9�ڵ�
		4,    //10�ڵ�
		3,		//11�ڵ�
		2,		//12�ڵ�
		3,		//13�ڵ�
		4,     //14�ڵ�
};

int is_line[maxn][maxn] = \
{
	{0,1,2,3,5,6,9,10,14},  //�ڵ�0
	{0,1,2,3,4,6,8,10,13},	//�ڵ�1
	{0,1,2,4,5,7,9,11,14},	//�ڵ�2
	{0,1,3,4,5,6,7,10,12},	//�ڵ�3
	{1,2,3,4,5,7,8,11,13}, //�ڵ�4
	{0,2,3,4,5,8,9,12,14}, //�ڵ�5
	{0,1,3,6,7,8,9,10,11}, //�ڵ�6
	{2,3,4,6,7,8,9,11,12}, //�ڵ�7
	{1,4,5,6,7,8,9,12,13}, //�ڵ�8
	{0,2,5,6,7,8,9,13,14}, //�ڵ�9
	{},
};

bool is_end(int *sta)
{
	for (int i = 0; i < nodenum; i++)
		if (sta[i] != end_state[i]) return false;
	return true;
}

int h()
{
	int cnt=0;

	for (int i = 0; i < nodenum; i++)
		cnt += state[nodenum];

	return cnt-1;
}

//�������� ����Ϊindex������



//������������,�����������13��
int dfs(int d)
{
	//����ﵽҪ��״̬
	//if (d == maxd) { if (is_end(state)) return true; return false; }
	if (is_end(state)) return true;

	if (d >maxd) return false;

	//����ʽ���������������Լ�֦,ÿ�����ȥ��3������
	if ((maxd - d)*3 < h()) return false;

	int sta_temp[maxn];
	//�����ƶ�ǰ��״̬
	memcpy(sta_temp, state, sizeof(state));

	//���ÿ�������ƶ�
	
	for (int index = 0; index < nodenum; index++)
	{
		//�����ǰλ�������������ö��
		if (state[index] == 1)
		{

			for (int i = 0; i < max_dir[index]; i++)
			{
				//�����Χ�ǿո�������Ծ,ֱ��Ѱ����һ������
				if (state[jump[index][i][0]] == 0)
				{
					//printf("�� index = %d state[jump[%d][%d][0]]==0 ������Ծ����Ϊ ��jump[%d][%d][0]=%d Ϊ%d\n", index, index, i, index, i, jump[index][i][0],state[jump[index][i][0]]);
					continue;
				}

				//printf("��Ծ�� index = %d state[jump[%d][%d][0]]==1 ������Ծ,��Ϊ ��jump[%d][%d][0]=%d Ϊ%d\n\n", index, index, i, index,i, jump[index][i][0],state[jump[index][i][0]]);

				//printf("��ʱ״̬Ϊ:\n");
				//for (int p = 0; p < nodenum; p++)
				//	printf("%d ", state[p]);
				//printf("\n");
				//
				//printf("��ʼ������Ծ·��.....\n");
				//�������ÿ�����������Ծ·��
				int jum_st = 1;
				bool have_space = false;
				for (; jum_st < max_step[index]; jum_st++)
				{
					//�ҵ���һ���ո�
					if (state[jump[index][i][jum_st]] == 0) { 
						//printf("С��� index= %d ��Ծ���ո�  space=%d ,�����%d��С��\n\n", index, jump[index][i][jum_st],jum_st);
						
						have_space = true; break; }
				}
				//����ҵ��ո�������ƶ�
				if (have_space)
				{
					//ԭ������������
					state[index] = 0;
					//�����ո�λ��
					state[jump[index][i][jum_st]] = 1;
					//;�е����Ӷ�����
					for (int k = 0; k < jum_st; k++)
						state[jump[index][i][k]] = 0;

					node[d].path = index;
					node[d].space = jump[index][i][jum_st];
					//if (d == 0) { printf("С��� index=%d ��Ծ���ո�  space=%d ,�����%d��С��\n\n", index, jump[index][i][jum_st], jum_st); }
					//printf("��Ծ���״̬Ϊ:\n");

					//for (int p = 0; p < nodenum; p++)
					//	printf("%d ", state[p]);
					//printf("\n");
					//printf("��ʱ���Ϊd = %d,��������һ������\n\n", d);
					//�Ѿ��ƶ�,������һ���������
					if (dfs(d + 1)) return true;
					//printf("ͨ����� d= %d , �ڵ�index =%dδ��ý������״̬\n", d, index);
					//��ԭ״̬
					memcpy(state, sta_temp, sizeof(state));
				}
				//printf("��Ծ��index = %d δ�ҵ��ո�����Ծ\n", index);

			}
		}
	}
	return false;
}

void print_ans(int max)
{
	for (int i = 0; i < max-1; i++)
		printf("%d %d ", node[i].path+1, node[i].space+1);
	printf("%d %d", node[max - 1].path + 1, node[max - 1].space + 1);
	printf("\n");
}


void inline init(int index)
{
	for (int i = 0; i < nodenum; i++)
		start_state[i] = 1;
	start_state[index] = 0;
	memset(end_state, 0, sizeof(end_state));
	end_state[index] = 1;
}

int kcase = 1;

void solve()
{
	int pos;
	scanf("%d", &pos);
	//��ʼ����������
	init(pos-1); 
	bool have_solution = false;
	memset(node, 0, sizeof(node));

	for (maxd = 1; maxd < 14; maxd++)
	{
		memcpy(state, start_state, sizeof(state));
	
		if (dfs(0)) { have_solution = true; break; }
	}
	if (have_solution)
	{
		printf("%d\n",maxd+1);
		print_ans(maxd+1);
	}
}

int main()
{
	int T;
	int ans = 0;
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);

	scanf("%d", &T);
	while (T--)
	{
		solve();
	}
	
	return 0;
}