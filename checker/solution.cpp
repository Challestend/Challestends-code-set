#include<bits/stdc++.h>
#define ll long long
#define rg register
using namespace std;
const int MAXN=5e5+10;
struct gao{   int u,v,w,Next;   }Edge[MAXN<<1],E[MAXN];
int n,m,Maxj,Ls,Qs,Ds,Es,First[MAXN],High[MAXN],Hard[MAXN],Lsh[MAXN];
int Tot[MAXN],Dfn[MAXN],Jump[MAXN][21];
inline int Read()
{   rg int a=0,c=1;   rg char b=getchar();
	while(b!='-'&&(b<'0'||b>'9'))b=getchar();
	if(b=='-')c=-1,b=getchar();
	while(b>='0'&&b<='9')a=a*10+b-48,b=getchar();
	return a*c;
}
inline void Link(rg int u,rg int v)
{   Edge[++Es]=(gao){u,v,0,First[u]},First[u]=Es;   }
inline bool cmp(rg gao A,rg gao B){   return A.w<B.w;   }
namespace Union
{   int Bel[MAXN<<1];
	inline int Find(rg int S){   return Bel[S]==S?S:Bel[S]=Find(Bel[S]);   }
	inline void Merge(rg int A,rg int B){   A=Find(A),B=Find(B),Bel[A]=B;   }
}using Union::Bel;using Union::Find;using Union::Merge;
namespace Tree
{   int Ts,Root[MAXN];
	struct jin{   int Sum,Lson,Rson;   }Tr[MAXN*10];
	inline void Modify(rg int &S,rg int Le,rg int Ri,rg int Aim)
	{   Tr[++Ts]=Tr[S],S=Ts,Tr[S].Sum++;   rg int Mid=(Le+Ri)>>1;
		if(Le!=Ri) Aim<=Mid?Modify(Tr[S].Lson,Le,Mid,Aim):Modify(Tr[S].Rson,Mid+1,Ri,Aim);
	}
	inline int Query(rg int R1,rg int R2,rg int Le,rg int Ri,rg int K)
	{   if(Le==Ri) return Le;   rg int Mid=(Le+Ri)>>1,Rs=Tr[Tr[R2].Rson].Sum-Tr[Tr[R1].Rson].Sum;
		return Rs>=K?Query(Tr[R1].Rson,Tr[R2].Rson,Mid+1,Ri,K):Query(Tr[R1].Lson,Tr[R2].Lson,Le,Mid,K-Rs);
	}
}using Tree::Root;using Tree::Modify;using Tree::Query;
inline void Kruskal()
{   sort(E+1,E+m+1,cmp),Ds=n;
	for(rg int i=1;i<=n+n;i++) Bel[i]=i;
	for(rg int i=1,u,v,w;i<=m;i++)
	{   u=Find(E[i].u),v=Find(E[i].v),w=E[i].w;
		if(u!=v) Hard[++Ds]=w,Merge(u,Ds),Merge(v,Ds),Link(u,Ds),Link(Ds,u),Link(v,Ds),Link(Ds,v);
	}
	for(rg int i=n+1;i<=Ds;i++) High[i]=1;
}
inline void Dfs(rg int Now,rg int Ba)
{   Dfn[Now]=++Ds,Jump[Now][0]=Ba,Tot[Now]=1;
	Root[Ds]=Root[Ds-1],Modify(Root[Ds],1,Ls,High[Now]);
	for(rg int i=First[Now];i!=-1;i=Edge[i].Next)
		if(Edge[i].v!=Ba) Dfs(Edge[i].v,Now),Tot[Now]+=Tot[Edge[i].v];
}
inline int Query(rg int Now,rg int Lim)
{   for(rg int i=Maxj;i>=0;i--)
		if(Hard[Jump[Now][i]]<=Lim) Now=Jump[Now][i];
	return Now;
}
int main()
{   freopen("data.in","r",stdin);
	freopen("data.ans","w",stdout);n=Read(),m=Read(),Qs=Read();
	memset(First,-1,sizeof(First));
	for(rg int i=1;i<=n;i++) High[i]=Lsh[++Ls]=Read();
	Lsh[++Ls]=0,sort(Lsh+1,Lsh+Ls+1),Ls=unique(Lsh+1,Lsh+Ls+1)-Lsh-1;
	for(rg int i=1;i<=n;i++) High[i]=lower_bound(Lsh+1,Lsh+Ls+1,High[i])-Lsh;
	for(rg int i=1;i<=m;i++) E[i].u=Read(),E[i].v=Read(),E[i].w=Read();
	Kruskal(),n=Ds,Ds=0,Dfs(Find(1),Find(1)),Maxj=log2(n);
	for(rg int j=1;j<=Maxj;j++)
		for(rg int i=1;i<=n;i++) Jump[i][j]=Jump[Jump[i][j-1]][j-1];
	for(rg int i=1,V,X,K;i<=Qs;i++)
		V=Read(),X=Read(),K=Read(),V=Query(V,X),K=Query(Root[Dfn[V]-1],Root[Dfn[V]+Tot[V]-1],1,Ls,K),printf("%d\n",K==1?-1:Lsh[K]);
}
