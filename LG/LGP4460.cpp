#include<cstdio>
#include<cmath>
#define re register
#define maxn 20
#define eps 1e-6
#define mod 100000007
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) max(a,-(a))

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

    char cltout[size+1],*oh=cltout,*ot=cltout+size;
    inline void pc(char c){
        if(oh==ot){
            fwrite(cltout,1,size,stdout);
            oh=cltout;
        }
        *oh++=c;
    }
    #undef size

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
int x[maxn+1],y[maxn+1],s[maxn+1][maxn+1],cnt[(1<<maxn)+1],f[(1<<maxn)+1][maxn+1];

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(x[i]);
        cltstream::read(y[i]);
    }
    for(re int i=1;i<=n;++i)
        for(re int j=i+1;j<=n;++j){
            for(re int k=1;k<=n;++k)
                if(k!=i&&k!=j){
                    if(x[k]<min(x[i],x[j])||x[k]>max(x[i],x[j]))
                        continue;
                    if(y[k]<min(y[i],y[j])||y[k]>max(y[i],y[j]))
                        continue;
                    if(x[i]==x[j]&&x[k]!=x[j])
                        continue;
                    if(y[i]==y[j]&&y[k]!=y[j])
                        continue;
                    if(x[i]!=x[j]&&y[i]!=y[j]&&
abs(atan(double(abs(x[k]-x[i]))/abs(y[k]-y[i]))-atan(double(abs(x[k]-x[j]))/abs(y[k]-y[j])))>eps)
                        continue;
                    s[i][j]|=1<<(k-1);
                    s[j][i]|=1<<(k-1);
                }
        }
    for(re int i=1;i<(1<<n);++i)
        cnt[i]=cnt[i>>1]+(i&1);
    for(re int i=1;i<=n;++i)
        f[1<<(i-1)][i]=1;
    for(re int i=1;i<(1<<n);++i){
        if(cnt[i]>=4)
            for(re int j=1;j<=n;++j)
                if((i>>(j-1))&1)
                    (ans+=f[i][j])%=mod;
        for(re int j=1;j<=n;++j)
            if((i>>(j-1))&1)
                for(re int k=1;k<=n;++k)
                    if((((i>>(k-1))&1)^1)&&(i|s[j][k])==i)
                        (f[i|(1<<(k-1))][k]+=f[i][j])%=mod;
    }
    cltstream::write(ans);
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
