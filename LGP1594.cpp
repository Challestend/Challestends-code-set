#include<cstdio>
#include<cmath>
#define re register
#define maxn 1000
#define maxlog 10
#define Min(a,b) ((a)<=(b)?(a):(b))

template <typename _tp>
inline void read(_tp& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

int n,cap,len;
long long w[maxn+1],s[maxn+1][maxlog+1];
double f[maxn+1];

inline long long getmin(int l,int r){
    int x=log2(r-l+1);
    return Min(s[l][x],s[r-(1<<x)+1][x]);
}

int main(){
    read(cap),read(len),read(n);
    for(re int i=1;i<=n;++i)
        read(w[i]),w[i]+=w[i-1],read(s[i][0]),f[i]=9223372036854775800LL;
    for(re int i=1;i<=maxlog;++i)
        for(re int j=1;j+(1<<i)-1<=n;++j)
            s[j][i]=Min(s[j][i-1],s[j+(1<<i-1)][i-1]);
    for(re int i=1;i<=n;++i)
        for(re int j=i-1;j>=0&&w[i]-w[j]<=cap;--j)
            f[i]=Min(f[i],f[j]+1.0*len/getmin(j+1,i));
    printf("%0.1lf",60LL*f[n]);
    return 0;
}
