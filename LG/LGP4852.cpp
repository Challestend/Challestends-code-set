#include<cstdio>
#define re register
#define maxn 40
#define maxm 80000
#define maxc 3000
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,c,d;
int a[maxn*maxc+maxm+1],h[maxn*maxc+maxm+1];
long long f[maxn*maxc+maxm+1][maxn+1];
int pre[maxn*maxc+maxm+1][maxn+1],ans[maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(c);
    cltstream::read(d);
    for(re int i=1;i<=n*c+m;++i){
        cltstream::read(a[i]);
        a[i]+=a[i-1];
    }
    for(re int i=c;i<=c+d;++i)
        f[i][1]=a[i]-a[i-c+1];
    for(re int i=c+d+1;i<=n*c+m;++i)
        f[i][1]=2e9;
    for(re int j=2;j<=n;++j){
        re int head=0,tail=0;
        for(re int i=j*c;i<=n*c+m;++i){
            for(;head<tail&&h[head+1]+c+d<i;++head);
            for(;head<tail&&f[h[tail]][j-1]>=f[i-c][j-1];--tail);
            h[++tail]=i-c;
            f[i][j]=f[h[head+1]][j-1]+a[i]-a[i-c+1];
            pre[i][j]=h[head+1];
        }
    }
    re int las=n*c+m-d;
    for(re int i=n*c+m-d;i<=n*c+m;++i)
        if(f[las][n]>=f[i][n])
            las=i;
    cltstream::write(a[n*c+m]-f[las][n],10);
    ans[1]=las;
    for(re int i=1;i<n;++i)
        ans[i+1]=pre[ans[i]][n-i+1];
    for(re int i=n;i>=1;--i)
        cltstream::write(ans[i]-c+1,32);
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
