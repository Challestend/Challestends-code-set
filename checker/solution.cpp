#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int son[50050][2],fa[50050],sz[50050];
long long lsum[50050],val[50050],rsum[50050],EXP[50050],sum[50050],upd_tag[50050];
int rev_tag[50050];

void Push_Up(int rt)
{
    sum[rt] = val[rt] + sum[son[rt][0]] + sum[son[rt][1]];
    sz[rt] = 1 + sz[son[rt][0]] + sz[son[rt][1]];
    lsum[rt] = lsum[son[rt][0]] + val[rt] * (sz[son[rt][0]] + 1) + lsum[son[rt][1]] + sum[son[rt][1]] * (sz[son[rt][0]] + 1);
    rsum[rt] = rsum[son[rt][1]] + val[rt] * (sz[son[rt][1]] + 1) + rsum[son[rt][0]] + sum[son[rt][0]] * (sz[son[rt][1]] + 1);
    EXP[rt] = EXP[son[rt][0]] + EXP[son[rt][1]] + val[rt] * (sz[son[rt][0]] + 1) * (sz[son[rt][1]] + 1) +
              lsum[son[rt][0]] * (sz[son[rt][1]] + 1) + rsum[son[rt][1]] * (sz[son[rt][0]] + 1);
}

void Rev(int rt)
{
    swap(son[rt][0],son[rt][1]);
    swap(lsum[rt],rsum[rt]);
    rev_tag[rt] ^= 1;
}

void Add(int rt,int valx)
{
    long long val1 = (sz[rt] * 1ll * (sz[rt] + 1)) / 2,val2 = (sz[rt] * 1ll * (sz[rt] + 1) * (sz[rt] + 2)) / 6;
    sum[rt] += valx * 1ll * sz[rt];
    val[rt] += valx;
    lsum[rt] += val1 * valx;
    rsum[rt] += val1 * valx;
    EXP[rt] += valx * val2;
    upd_tag[rt] += valx;
}

void Push_Down(int rt)
{
    if(rev_tag[rt])
    {
        Rev(son[rt][0]);
        Rev(son[rt][1]);
        rev_tag[rt] = 0;
    }
    if(upd_tag[rt])
    {
        Add(son[rt][0],upd_tag[rt]);
        Add(son[rt][1],upd_tag[rt]);
        upd_tag[rt] = 0;
    }
}

void Down(int rt)
{
    if(fa[rt]) Down(fa[rt]);
    Push_Down(rt);
}

bool is_root(int rt)
{
    return (son[fa[rt]][0] != rt && son[fa[rt]][1] != rt) || rt == 0;
}

void rotate(int rt)
{
    int f = fa[rt],g = fa[f];
    int way = son[f][1] == rt;
    if(!is_root(f)) son[g][son[g][1] == f] = rt;
    fa[rt] = g; son[f][way] = son[rt][way ^ 1];
    if(son[rt][way ^ 1]) fa[son[rt][way ^ 1]] = f;
    son[rt][way ^ 1] = f; fa[f] = rt;
    Push_Up(f); Push_Up(rt);
}

void splay(int rt)
{
    Down(rt);
    while(!is_root(rt))
    {
        int f = fa[rt],g = fa[f];
        if(!is_root(f)) (son[f][1] == rt) ^ (son[g][1] == rt) ? rotate(rt) : rotate(f);
        rotate(rt);
    }
}

void Access(int u)
{
    for(int v = 0;u;v = u,u = fa[u])
    {
        splay(u);
        son[u][1] = v;
        Push_Up(u);
    }
}

void make_root(int u)
{
    Access(u); splay(u); Rev(u);
}

int find_root(int u)
{
    Access(u); splay(u);
    while(son[u][0]) u = son[u][0];
    return u;
}

long long split(int u,int v)
{
    if(find_root(u) != find_root(v)) return -1;
    make_root(u); Access(v); splay(v);
    return EXP[v];
}

void Update(int u,int v,int val)
{
    if(find_root(u) != find_root(v)) return ;
    make_root(u); Access(v); splay(v);
    Add(v,val);
}

void Link(int u,int v)
{
    if(find_root(u) == find_root(v)) return ;
    make_root(u); fa[u] = v;
}

void Cut(int u,int v)
{
    if(find_root(u) != find_root(v)) return ;
    make_root(u); Access(v); splay(v);
    if(son[u][1] || son[v][0] != u) return;
    son[v][0] = fa[u] = 0;
    Push_Up(v);
}

long long gcd(long long a,long long b)
{
    return b == 0 ? a : gcd(b,a % b);
}

int main()
{
    freopen("data.in","r",stdin);
    freopen("data.ans","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n; ++ i) scanf("%lld",&val[i]),Push_Up(i);
    for(int i = 1;i < n; ++ i)
    {
        int u,v;
        scanf("%d%d",&u,&v); Link(u,v);
    }
    for(int i = 1;i <= m; ++ i)
    {
        int op,u,v;scanf("%d%d%d",&op,&u,&v);
        int w; if(op == 3) scanf("%d",&w);
        if(op == 1) Cut(u,v);
        else if(op == 2) Link(u,v);
        else if(op == 3) Update(u,v,w);
        else
        {
            long long tmp = split(u,v);
            if(tmp == -1) printf("-1\n");
            else
            {
                long long csz = sz[v] * (sz[v] + 1) / 2;
                long long gcdx = gcd(csz,tmp);
                printf("%lld/%lld\n",tmp/gcdx,csz/gcdx);
            }
        }
    }
}
