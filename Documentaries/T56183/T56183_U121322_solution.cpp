#include<iostream>
#include<cstdio>
#include<string>
#include<cmath>
#include<cstring>
#include<queue>
#define p pair<int,int>
#define pp make_pair
using namespace std;
priority_queue<p,vector< p >,greater< p > >q;
struct edge
{
	int next;
	int to;
	int dis;
}g[50000500];
int last[100050];
int c[100050];
int d[100050];
int num,ans=1000000000;
int aa,bb,cc;
int n,m,k;
int t,dd;
void add(int from,int to,int dis)
{
	g[++num].next=last[from];
	g[num].to=to;
	g[num].dis=dis;
	last[from]=num;
}
int main()
{
	freopen("10.in","r",stdin);
	freopen("10.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&aa,&bb,&cc);
		add(aa,bb,cc);
		add(bb,aa,cc);
		for(int j=1;j<=k;j++)
		{
			add(j*n+aa,j*n+bb,cc);
			add(j*n+bb,j*n+aa,cc);
			add((j-1)*n+aa,j*n+bb,0);
			add((j-1)*n+bb,j*n+aa,0);
		}
	}
	memset(c,0x3f,sizeof(c));
	c[1]=0;
	q.push(pp(0,1));
	while(q.size())
	{
		t=q.top().second;
		dd=q.top().first;
		q.pop();
		if(d[t]) continue;
		d[t]=1;
		for(int i=last[t];i;i=g[i].next)
		{
			int v=g[i].to;
			int mm=max(dd,g[i].dis);
			if(c[v]>mm)
			{
				c[v]=mm;
				q.push(pp(c[v],v));
			}
		}
	}
	for(int i=1;i<=k+1;i++)
	{
		ans=min(ans,c[i*n]);
	}
	printf("%d\n",ans);
}
