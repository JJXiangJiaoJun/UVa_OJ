#include<cstdio>
#include<map>
#include<queue>
#include<cstring>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stdlib.h>
#include <math.h>
#include <stack>
using namespace std;
const int maxn = 505;

int a[maxn];

int main()
{
    int CaseNum;
    scanf("%d",&CaseNum);
    while(CaseNum--){
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;i++) scanf("%d",&a[i]);

        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(a[i]>a[j]) ans++;
            }
        }

        if(ans&1 && n&1) printf("impossible\n");
        else printf("possible\n");
    }

}