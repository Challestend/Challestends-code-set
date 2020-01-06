#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int V = 100000;
const int MAXN = 500050;
const int MAXB = 4050;
void read(int &x) {
    char ch; while(ch = getchar(), ch < '!'); x = ch - 48;
    while(ch = getchar(), ch > '!') x = (x << 3) + (x << 1) + ch - 48;
}
struct Qry {int l, r, id; lint ans;} q[MAXN];
struct T {int l, r, id, op;};
int siz, Vsiz, n, m, a[MAXN], cl[MAXN], cr[MAXN], bl[MAXN];
lint ans[MAXN], t1[MAXN], t2[MAXN], pre1[MAXN], pre2[MAXN], pref1[MAXN], pref2[MAXN], c1[MAXN], s1[MAXB], c2[MAXN], s2[MAXB];
void up1(int x, int val) {for( ; x > 0; t1[x] += val, x -= x&(-x));}
lint qr1(int x) {lint res = 0; for(; x <= V; res += t1[x], x += x&(-x)); return res;}
void up2(int x, int val) {for(; x <= V; t2[x] += val, x += x&(-x));}
lint qr2(int x) {lint res = 0; for( ; x > 0; res += t2[x], x -= x&(-x)); return res;}
int cmp(Qry a, Qry b) {return a.l/siz == b.l/siz ? a.r < b.r : a.l < b.l;}
vector <T> vl[MAXN], vr[MAXN];
int main() {
    freopen("data.in","r",stdin);
    freopen("data.ans","w",stdout);
    read(n); read(m); siz = sqrt(n); Vsiz = 400;
    for(int i = 1; i <= n; ++i) read(a[i]);
    for(int i = 1; i <= m; ++i) {read(q[q[i].id = i].l), read(q[i].r); if(q[i].l>q[i].r||q[i].l<1||q[i].r>n) puts("nmd");}
    sort(q+1, q+m+1, cmp);
    for(int i = 1; i <= n; ++i) {
        pre1[i] = qr1(a[i]+1);
        pre2[i] = qr2(a[i]-1);
        up1(a[i], a[i]); up2(a[i], 1);
        pref1[i] = pref1[i-1] + pre1[i] + 1ll * a[i] * (pre2[i] + 1);
    }
    memset(t1, 0, sizeof t1); memset(t2, 0, sizeof t2);
    for(int i = n; i >= 1; --i) {
        pre1[i] = qr1(a[i]+1);
        pre2[i] = qr2(a[i]-1);
        up1(a[i], a[i]); up2(a[i], 1);
        pref2[i] = pref2[i+1] + pre1[i] + 1ll * a[i] * (pre2[i] + 1);
    }
    for(int L = 1, R = 0, i = 1; i <= m; ++i) {
        int l = q[i].l, r = q[i].r;
        q[i].ans = pref1[r]-pref1[R]+pref2[l]-pref2[L];
        if(L < l) vl[r+1].push_back((T) {L, l-1, i, 1});
        if(L > l) vl[r+1].push_back((T) {l, L-1, i, -1});
        if(R < r) vr[L-1].push_back((T) {R+1, r, i, -1});
        if(R > r) vr[L-1].push_back((T) {r+1, R, i, 1});
        L = l; R = r;
    }
    for(int i = 1; i <= Vsiz; ++i) {
        cl[i] = cr[i-1] + 1; cr[i] = i*Vsiz;
        for(int j = cl[i]; j <= cr[i]; ++j) bl[j] = i;
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j < bl[a[i]]; ++j) s2[j] += a[i];
        for(int j = cl[bl[a[i]]]; j <= a[i]; ++j) c2[j] += a[i];
        for(int j = bl[a[i]]+1; j <= Vsiz; ++j) ++s1[j];
        for(int j = a[i]; j <= cr[bl[a[i]]]; ++j) ++c1[j];
        for(int j = 0; j < vr[i].size(); ++j) {
            int l = vr[i][j].l, r = vr[i][j].r, id = vr[i][j].id;
            lint tmp = 0;
            for(int k = l; k <= r; ++k)
                tmp += 1ll*a[k]*(s1[bl[a[k]-1]]+c1[a[k]-1]) + (s2[bl[a[k]+1]]+c2[a[k]+1]);
            q[id].ans += vr[i][j].op * tmp;
        }
    }
    memset(s1, 0, sizeof s1); memset(c1, 0, sizeof c1); memset(s2, 0, sizeof s2); memset(c2, 0, sizeof c2);
    for(int i = n; i >= 1; --i) {
        for(int j = 1; j < bl[a[i]]; ++j) s2[j] += a[i];
        for(int j = cl[bl[a[i]]]; j <= a[i]; ++j) c2[j] += a[i];
        for(int j = bl[a[i]]+1; j <= Vsiz; ++j) ++s1[j];
        for(int j = a[i]; j <= cr[bl[a[i]]]; ++j) ++c1[j];
        for(int j = 0; j < vl[i].size(); ++j) {
            int l = vl[i][j].l, r = vl[i][j].r, id = vl[i][j].id;
            lint tmp = 0;
            for(int k = l; k <= r; ++k)
                tmp += 1ll*a[k]*(s1[bl[a[k]-1]]+c1[a[k]-1]) + (s2[bl[a[k]+1]]+c2[a[k]+1]);
            q[id].ans += vl[i][j].op * tmp;
        }
    }
    for(int i = 1; i <= m; ++i) q[i].ans += q[i-1].ans, ans[q[i].id] = q[i].ans;
    for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
}
