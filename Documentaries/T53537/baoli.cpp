#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define wzx 998244353
#define maxn 100010
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
#define FILE(filename) freopen(filename".in","r",stdin);freopen(filename".ans","w",stdout);
using namespace std;

int n, m, c, r, t, x, y, z, anss, cnt, num;
int a[maxn], b[maxn], rt[maxn];

inline void in(int &x){
    x=0;;char c=getchar();
    while(c<'0'||c>'9'){
        c=getchar();
    }
    while(c<='9'&&c>='0'){
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }
}

void out(int a){
    if(a>=10)out(a/10);
    putchar(a%10+'0');
}

int main() {
    FILE("T53537");
	in(n), in(m);
	FOR(i, 1, n)
	  in(a[i]);
	FOR(i, 1, m) {
		in(t);
		if(t == 1) {
			in(x), in(y), in(z);
			FOR(i, x, y)
			  if(a[i] > z)
			    a[i] -= z;
		}
		if(t == 2) {
			in(x), in(y);
			int minn = 0x7fffffff;
			FOR(i, x, y)
			  if(a[i] < minn)
			    minn = a[i];
			FOR(i, x, y)
			  a[i] = minn;
		}
		if(t == 3) {
			in(x), in(y), in(z);
			int res = 0, id = -1;
			FOR(i, x, y)
			  if(a[i] < z)
			    if(a[i] > res)
			      res = a[i], id = i;
			if(id == -1)
			  puts("GREAT");
			else
			  out(id),
			  puts("");
		}
        // for(re int _i=1;_i<=n;++_i)
        //     printf("%d%c",a[_i]," \n"[_i==n]);
	}
    anss = 0;
	FOR(i, 1, n)
	  anss += a[i], anss %= wzx;
	out(anss);
	puts("");
}
