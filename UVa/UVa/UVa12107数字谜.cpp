#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
const int maxn = 5;
const char ch[15] = {'*','0','1','2','3','4','5','6','7','8','9',};
int maxd;

//保存每个数
char factor[3][6];
int len[5];


//判断一个式是否成立
int judge()
{
	int a=0, b=0;
	char check_c[10];
	for (int i = 0; i < len[0]; i++)
		a = a * 10 + factor[0][i] - '0';
	for (int i = 0; i < len[1]; i++)
		b = b * 10 + factor[1][i] - '0';
	int c = a*b;

	for (int i = 0; i < len[2]; i++)
	{
		check_c[len[2] - 1 - i] = c % 10 + '0';
		c /= 10;
	}

	if (check_c[0] == '0' || c != 0) return 0;
	
	for (int i = 0; i <  len[2]; i++)
		if (check_c[i] != factor[2][i] && factor[2][i] != '*') return 0;
	return 1;
}

//入口参数 index，当前为枚举第几个数，cnt当前为这个数的第几位
int check(int index,int cnt)
{
	int flag=0;
	if (index == 2) { flag = judge(); return flag; }
	int new_index, new_cnt;
	char temp_fac = factor[index][cnt];
	//如果当前数枚举完成，则枚举下一个数字
	if (cnt == len[index] - 1)
	{
		new_index = index + 1;
		new_cnt = 0;
	}
	else
	{
		new_index = index;
		new_cnt = cnt + 1;
	}

	if (factor[index][cnt] == '*')
	{
		for (int i = 1; i <= 10; i++)
		{
			if (i == 1 && cnt == 0) continue; 
			factor[index][cnt] = ch[i];
			flag += check(new_index, new_cnt);
			if (flag > 1) break;
		}
	}
	else
	{
		flag += check(new_index, new_cnt);
	}
	factor[index][cnt] = temp_fac;	
	return flag;
}

//d为当前深度， index为当前枚举第几个数字，cnt为数字的第几位
bool dfs(int d, int index, int cnt)
{
	int flag;
	if (d == maxd)
	{
		flag = check(0, 0);
		if (flag == 1) return true;
		else return false;

	}
	if (index == 3) return false;
	//下面对每个位置进行枚举
	int new_index, new_cnt;
	char temp_buf = factor[index][cnt];

	if (cnt == len[index] - 1)
	{
		new_index = index + 1;
		new_cnt = 0;
	}
	else
	{
		new_index = index;
		new_cnt = cnt + 1;
	}

	for (int i = 0; i <= 10; i++)
	{
		//去除前导零
		if (i == 1 && cnt == 0) continue;
		//相同则不替换
		if (temp_buf == ch[i])
		{
			//factor[index][cnt] = temp_buf;
			if(dfs(d,new_index,new_cnt)) return true;
		}
		else
		{
			factor[index][cnt] = ch[i];
			if(dfs(d+1, new_index, new_cnt)) return true;
		}

	}
	//复原
	factor[index][cnt] = temp_buf;

	return false;
}



int main()
{
	int kcase = 1;
	memset(factor, 0, sizeof(factor));
	while (scanf("%s %s %s", factor[0], factor[1], factor[2])==3)
	{
		if (factor[0][0] == '0') return 0;
		printf("Case %d: ",kcase++);
		for (int i = 0; i < 3; i++)
			len[i] = strlen(factor[i]);

		for (maxd = 0;; maxd++)
		{
			if (dfs(0, 0, 0)) { printf("%s %s %s\n", factor[0], factor[1], factor[2]); break; }
		}
		memset(factor,0,sizeof(factor));
	}
	
	return 0;
}