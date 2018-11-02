#include<cstdio>
#define re register
#define maxn 100

namespace cltstream{
    #define size 1048576
    char cltin[size+1],*ih=cltin,*it=cltin;
    inline char gc(){
        #ifdef ONLINE_JUDGE
            if(ih==it){
                it=(ih=cltin)+fread(cltin,1,size,stdin);
                if(ih==it)
                    return EOF;
            }
            return *ih++;
        #else
            return getchar();
        #endif
    }

    #define pc putchar

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
    inline void write(_tp x,char text=-1){
        if(x<0)
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        if(text>=0)
            pc(text);
    }
}

int n,ans;
int a[maxn+2][maxn+2],b[maxn+1][maxn+1],v[maxn+1];

inline int solve(){
    for(re int i=1;i<=n;++i)
        v[i]=0;
    for(re int i=1;i<=n;++i){
        int cur=1;
        for(;cur<=n&&(!b[cur][i]||v[cur]);++cur);
        if(cur>n)
            return 0;
        v[cur]=i;
        for(re int j=1;j<=n+1;++j)
            if(j!=i){
                if(b[cur][j]%b[cur][i])
                    return 0;
                else
                    b[cur][j]/=b[cur][i];
            }
        b[cur][i]=1;
        for(re int j=1;j<=n;++j)
            if(j!=cur){
                for(re int k=1;k<=n+1;++k)
                    if(k!=i)
                        b[j][k]-=b[j][i]*b[cur][k];
                b[j][i]=0;
            }
    }
    int res=0;
    for(re int i=1;i<=n;++i)
        if(b[i][n+1]<=0)
            return 0;
        else
            if(b[i][n+1]>b[res][n+1])
                res=i;
    for(re int i=1;i<=n;++i)
        if(i!=res&&b[i][n+1]==b[res][n+1])
            return 0;
    return v[res];
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n+1;++i){
        int x,y;
        cltstream::read(x);
        for(re int j=1;j<=x;++j){
            cltstream::read(y);
            a[i][y]=1;
        }
        cltstream::read(a[i][n+1]);
    }
    for(re int i=1;i<=n+1;++i){
        for(re int j=1;j<i;++j)
            for(re int k=1;k<=n+1;++k)
                b[j][k]=a[j][k];
        for(re int j=i+1;j<=n+1;++j)
            for(re int k=1;k<=n+1;++k)
                b[j-1][k]=a[j][k];
        int res=solve();
        if(res){
            if(!ans)
                ans=res;
            else{
                puts("illegal");
                return 0;
            }
        }
    }
    if(ans)
        cltstream::write(ans,10);
    else
        puts("illegal");
    return 0;
}
