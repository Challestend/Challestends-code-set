#include<cstdio>
#define re register
#define maxn 10000
#define maxm 1000
#define INF 2e9
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

namespace cltstream{
    #ifdef ONLINE_JUDGE
        #define size 1048576
        char str[size+1],*head=str,*tail=str;
        inline char gc(){
            if(head==tail){
                tail=(head=str)+fread(str,1,size,stdin);
                if(head==tail)
                    return EOF;
            }
            return *head++;
        }
        #undef size
    #else
        #define gc getchar
    #endif

    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=gc();
        for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
        if(c==45&&c!=EOF)
            sn=-1,c=gc();
        for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=gc());
        x*=sn;
    }

    template <typename _tp>
    inline void write(_tp x,char text=' '){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m,k;
int x[maxn+1],y[maxn+1],l[maxn+1],h[maxn+1],cnt[maxn+1];
int f[maxn+1][maxm+1],ans[maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=0;i<n;++i){
        cltstream::read(x[i]);
        cltstream::read(y[i]);
        h[i]=m+1;
    }
    h[n]=m+1;
    for(re int i=1;i<=k;++i){
        int x;
        cltstream::read(x);
        cltstream::read(l[x]);
        cltstream::read(h[x]);
        ++cnt[x];
    }
    for(re int i=1;i<=n;++i)
        for(re int j=0;j<=m;++j)
            f[i][j]=INF;
    for(re int i=1;i<=n;++i){
        cnt[i]+=cnt[i-1];
        ans[i]=INF;
    }
    for(re int i=1;i<=n;++i){
        for(re int j=1;j<=m-x[i-1];++j)
            f[i][j+x[i-1]]=min(f[i][j+x[i-1]],min(f[i][j],f[i-1][j])+1);
        for(re int j=m-x[i-1]+1;j<m;++j)
            f[i][m]=min(f[i][m],min(f[i][j],f[i-1][j])+1);
        for(re int j=1;j<=m-y[i-1];++j)
            f[i][j]=min(f[i][j],f[i-1][j+y[i-1]]);
        for(re int j=1;j<=m;++j)
            if(j>l[i]&&j<h[i])
                ans[i]=min(ans[i],f[i][j]);
            else
                f[i][j]=2e9;
        if(ans[i]==INF){
            putchar(48);
            putchar(10);
            cltstream::write(cnt[i-1],'\n');
            return 0;
        }
    }
    putchar(49);
    putchar(10);
    cltstream::write(ans[n],'\n');
    return 0;
}
