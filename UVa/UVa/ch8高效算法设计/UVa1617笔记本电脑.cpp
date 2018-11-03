#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1000000+100;

struct Task
{
    int r;
    int d;
    bool operator < (const Task &rhs) const{
        return rhs.d==d?r<rhs.r:d<rhs.d;
    } 
};
int T;
int n;

Task tasks[maxn];

int solve()
{
    int ans=0;
	sort(tasks, tasks + n);
    int right = tasks[0].d;
    for(int i=1;i<n;i++)
    {
        if(tasks[i].d!=right)
        {
            if(right<tasks[i].r)
            {
                ans++;
                right=tasks[i].d;
            }
            else{
                right++;  //贪心策略，紧靠着上一个放置的任务进行放置
            }
        }
    }

    return ans;
}

int main()
{
	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
	scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
         scanf("%d%d",&tasks[i].r,&tasks[i].d);
       int ans= solve();
       printf("%d\n",ans);
    }
}