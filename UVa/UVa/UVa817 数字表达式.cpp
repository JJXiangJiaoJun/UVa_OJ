#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
#define N 10+5
#define mem(a,b) memset(a,b,sizeof(a))
bool have_solution = false;
const int maxn = 9 + 5;
//利用二进制枚举，先枚举插入的位置，之后枚举插入的三种情况 +，-，*
string expression;
int len;
//保存插入位置的数组
int insert_place[maxn];
char insert_operate[maxn];
//保存每次要插入的个数
int insert_cnt;
const char op[] = { '+','-','*' };


//bool compute_express(char* t) {
//	int len = strlen(t);
//	int num[N], cNum = 0, cOp = 0;
//	char op[N];
//
//
//	int sum = 0;
//	bool bo = false, ok = false;
//	for (int i = 0; i <= len; i++) {
//		if (t[i] >= '0' && t[i] <= '9') {
//			sum = sum * 10 + t[i] - '0';
//
//			if (bo) return false;
//			if (sum == 0) bo = true;
//
//		}
//		else if (ok) {
//			int u = num[--cNum];
//			num[cNum++] = sum * u; sum = 0; bo = false;
//
//			if (t[i] != '*' && t[i] != '\0') {
//				op[cOp++] = t[i]; ok = false;
//			}
//
//		}
//		else if (t[i] == '*') {
//
//			num[cNum++] = sum; sum = 0; ok = true; bo = false;
//		}
//		else {
//
//			num[cNum++] = sum; sum = 0;
//			if (t[i] != '\0') op[cOp++] = t[i];
//			bo = false;
//		}
//	}
//
//	sum = num[0];
//	for (int i = 1; i < cNum; i++) {
//		if (op[i - 1] == '-') sum -= num[i];
//		else sum += num[i];
//	}
//
//	if (sum == 2000) return true;
//	return false;
//}


bool compute_express(char* exp) {

	int tnew_num[maxn];
	int num[maxn];
	int cnt = 0;
	int cnt_op = 0;
	char oper[maxn];
	int sum = 0;
	int len = strlen(exp);
	//第一遍遍历统计数字以及操作运算符个数
	for (int i = 0; i<len; i++)
	{
		if (exp[i] >= '0'&&exp[i] <= '9')
		{
			sum = sum * 10 + exp[i] - '0';
		}
		else
		{
			num[cnt++] = sum;
			sum = 0;
			oper[cnt_op++] = exp[i];
		}

	}
	num[cnt++] = sum;

	//cout << "num数组为:" << endl;
	//for (int i = 0; i < cnt; i++)
	//	cout << num[i] << " ";
	//cout << endl;
	//cout << "oper数组为:" << endl;
	//for (int i = 0; i < cnt_op; i++)
	//	cout << oper[i] << " ";
	//cout << endl;

	tnew_num[0] = num[0];

	int position = 0;
	//遍历一遍表达式，先计算乘积
	for (int i = 0; i < cnt_op; i++)
	{
		if (oper[i] == '+')
		{
			tnew_num[++position] = num[i + 1];
		}
		else if (oper[i] == '-')
		{
			tnew_num[++position] = -num[i + 1];
		}
		else if (oper[i] == '*')
		{
			tnew_num[position] = tnew_num[position] * num[i + 1];
		}
	}
	//已经计算完成乘积，下面进行加法运算

	int fin = 0;
	for (int i = 0; i <= position; i++)
		fin += tnew_num[i];
	return fin == 2000;
}


bool have_zero()
{
	for (int i = 0; i < insert_cnt-1; i++)
	{
		//去除有前导0的情况
		//对表达式切片
		//string str1 = expression.substr(0, insert_place[i] + 1);
		//string str2 = expression.substr(insert_place[i] + 1);
		//string str = expression.substr(insert_place[i]+1,insert_place[i+1]-insert_pa)
		if (insert_place[i] + 1 != insert_place[i + 1])
		{
			if (expression[insert_place[i] + 1] == '0') return true;
		}
	}
	if (insert_place[insert_cnt - 1]+1  != expression.length()-1)
	{
		if (expression[insert_place[insert_cnt - 1] + 1] == '0') return true;
	}

	return false;
}

int count_num = 0;

//枚举插入的每一种情况 cur 为当前枚举到第几个插入位置, count为一共有多少个插入位置
void dfs(int cur)
{
	//每个位置都枚举完成，那么进行表达式判断
	if (cur == insert_cnt)
	{
		string expr_buf = expression;
		//进行插入操作
		for (int i = 0; i < insert_cnt; i++)
		{
			string str1 = expr_buf.substr(0, insert_place[i] + 1 + i);
			string str2 = expr_buf.substr(insert_place[i] + 1 + i);
			expr_buf = str1 + insert_operate[i] + str2;
		}
		//cout << "insert_cnt=" << insert_cnt << endl;
		//如果满足条件则输出
		if (compute_express((char*)expr_buf.c_str())) { have_solution = true; cout << "  " << expr_buf << '=' << endl; }
		return;
	}
	//对需要穷举的位置进行穷举,穷举三种运算符
	for (int i = 0; i < 3; i++)
	{
		//如果合法,枚举每个插入位置的算式
		insert_operate[cur] =op[i];
		dfs(cur + 1);
	}

}


void solve()
{
	//去除输入中最后的等于号
	expression.pop_back();
	//获得插入位置个数 = 字符个数-1
	len = expression.length()-1;
	//if (expression[0] == '0') {
	//	cout << "  IMPOSSIBLE" << endl; return;
	//}
	have_solution = false;
	//cout << "len=" << len << endl;
	//cout << "expression=" << expression << endl;
	//二进制枚举位置，若该位为1那么表示插入符号，否则不进行插入
	//0不枚举，0表示什么都不插入，不符合条件
	for (int pos = 1; pos < 1 << len; pos++)
	{		//寻找插入位置
		//cout << "pos=" << pos << endl;
		mem(insert_place, 0);
		insert_cnt = 0;
		for (int i = 0; i < len; i++)
		{	

			//cout << "i<<" << i << "=" << (1 << i) << endl;
			//cout << "pos&(1<<" << i << ")" << "=" << (pos&(1 << i));

			if (pos&(1 << i)) { insert_place[insert_cnt] = i; insert_cnt++; }

			//cout << "insert_cnt=" << insert_cnt << endl;
			//先判断插入位置是否合法，必须无前导零
			//if(!have_zero()) dfs(0);
		}
		//cout << "insert_cnt=" << insert_cnt << endl;
		if (!have_zero()) dfs(0);
	}
	if (!have_solution)
		cout<<"  IMPOSSIBLE"<<endl;
}

int main()
{
	ifstream fin("C:\\Users\\lenovo\\Desktop\\test\\in.txt");
	ofstream fout("C:\\Users\\lenovo\\Desktop\\test\\out.txt");
	//freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);

	cout.rdbuf(fout.rdbuf());
	cin.rdbuf(fin.rdbuf());

	int kcase = 1;
	while (cin >> expression)
	{
		//读到等于号那么结束输入
		if (expression.length() == 1 && expression[0] == '=') return 0;
		cout << "Problem " << kcase++ << endl;
		solve();
		expression.clear();
		//cout << "gongyou:" << count_num << endl;
		
		//if (compute_express((char*)expression.c_str()))
		//{
		//	cout << "True"<<endl;
		//}
		//else
		//{
		//	cout << "Flase"<<endl;
		//}
		//expression.clear();
	}
		
	return 0; 
}

