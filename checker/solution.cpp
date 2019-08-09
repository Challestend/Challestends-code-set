#include <iostream>
#include <algorithm>
#include <cstdio>
#include <math.h>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <string.h>
#define REP(i,a,n) for(int i=a;i<=n;++i)
#define PER(i,a,n) for(int i=n;i>=a;--i)
#define hr putchar(10)
#define pb push_back
#define lc (o<<1)
#define rc (lc|1)
#define mid ((l+r)>>1)
#define ls lc,l,mid
#define rs rc,mid+1,r
#define x first
#define y second
#define io std::ios::sync_with_stdio(false)
#define endl '\n'
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int P = 1e9+7, INF = 0x3f3f3f3f;
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}
ll qpow(ll a,ll n) {ll r=1%P;for (a%=P;n;a=a*a%P,n>>=1)if(n&1)r=r*a%P;return r;}
ll inv(ll x){return x<=1?1:inv(P%x)*(P-P/x)%P;}
//head

const int N = 1e6+10;
int n, q;
int a[N], L[N], R[N];
struct _ {int l,r,id;} e[N];
int v1[N<<2], t1[N<<2];
ll v2[N<<2], t2[N<<2], ans[N];

void pd1(int o) {
    if (t1[o]) {
        v1[lc]+=t1[o];
        v1[rc]+=t1[o];
        t1[lc]+=t1[o];
        t1[rc]+=t1[o];
        t1[o]=0;
    }
}
void pd2(int o) {
    if (t2[o]) {
        v2[lc]+=t2[o];
        v2[rc]+=t2[o];
        t2[lc]+=t2[o];
        t2[rc]+=t2[o];
        t2[o]=0;
    }
}
void upd1(int o, int l, int r, int ql, int qr, int v) {
    if (ql<=l&&r<=qr) return v1[o]+=v,t1[o]+=v,void();
    pd1(o);
    if (mid>=ql) upd1(ls,ql,qr,v);
    if (mid<qr) upd1(rs,ql,qr,v);
}
void upd2(int o, int l, int r, int ql, int qr, int v) {
    if (ql<=l&&r<=qr) return v2[o]+=v,t2[o]+=v,void();
    pd2(o);
    if (mid>=ql) upd2(ls,ql,qr,v);
    if (mid<qr) upd2(rs,ql,qr,v);
}
ll qry1(int o, int l, int r, int x) {
    if (l==r) return (ll)l*v1[o];
    pd1(o);
    if (mid>=x) return qry1(ls,x);
    return qry1(rs,x);
}
ll qry2(int o, int l, int r, int x) {
    if (l==r) return (ll)v2[o];
    pd2(o);
    if (mid>=x) return qry2(ls,x);
    return qry2(rs,x);
}

bool A(_ a,_ b){return a.l>b.l;}
bool B(_ a,_ b){return a.r<b.r;}

int main() {
	freopen("data.in","r",stdin);
	freopen("data.ans","w",stdout);
    scanf("%d%d", &n, &q);
    REP(i,1,n) scanf("%d", a+i);
    REP(i,1,n) {
        L[i] = i-1;
        while (L[i]&&a[i]>a[L[i]]) L[i]=L[L[i]];
    }
    PER(i,1,n) {
        R[i] = i+1;
        while (R[i]<=n&&a[i]>a[R[i]]) R[i]=R[R[i]];
    }
    REP(i,1,n) ++L[i],--R[i];
    REP(i,1,q) scanf("%d", &e[i].l);
    REP(i,1,q) scanf("%d", &e[i].r),e[i].id=i;
    sort(e+1,e+1+q,A);
    int now = n;
    REP(i,1,q) {
        while (now>=e[i].l) {
            if (now<=R[now]-1) upd1(1,1,n,now,R[now]-1,1);
            upd2(1,1,n,R[now],n,R[now]);
            --now;
        }
        ans[e[i].id] += qry1(1,1,n,e[i].r)+qry2(1,1,n,e[i].r)+e[i].r-e[i].l+1;
    }
    memset(v1,0,sizeof v1);
    memset(v2,0,sizeof v2);
    memset(t1,0,sizeof t1);
    memset(t2,0,sizeof t2);
    sort(e+1,e+1+q,B);
    now = 1;
    REP(i,1,q) {
        while (now<=e[i].r) {
            if (L[now]+1<=now) upd1(1,1,n,L[now]+1,now,1);
            upd2(1,1,n,1,L[now],L[now]);
            ++now;
        }
        ans[e[i].id] -= qry1(1,1,n,e[i].l)+qry2(1,1,n,e[i].l);
    }
    REP(i,1,q) printf("%lld ", ans[i]);hr;
}
