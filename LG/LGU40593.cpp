#include<cstdio>
#include<algorithm>
#define re register
#define maxn 50000
#define maxm 500
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m;
int tp[maxn+1],val[maxn+1],col[maxn+1],x[(maxn<<1)+1];
long long sum[(maxn<<1)+1],maxv,f[maxn+1][maxm+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(tp[i]);
        cltstream::read(val[i]);
        x[++x[0]]=tp[i];
    }
    for(re int i=1;i<=n;++i){
        cltstream::read(col[i]);
        x[++x[0]]=col[i];
    }
    std::sort(x+1,x+x[0]+1);
    x[0]=std::unique(x+1,x+x[0]+1)-x-1;
    for(re int i=1;i<=n;++i){
        tp[i]=std::lower_bound(x+1,x+x[0]+1,tp[i])-x;
        col[i]=std::lower_bound(x+1,x+x[0]+1,col[i])-x;
    }
    sum[tp[1]]=maxv=val[1];
    f[1][0]=val[1];
    for(re int i=2;i<=n;++i){
        sum[tp[i]]+=val[i];
        maxv=max(maxv,val[i]);
        f[i][0]=f[i-1][0]+max(sum[col[i]],maxv);
        for(re int j=1;j<=(i>>1)&&j<=m;++j)
            f[i][j]=max(f[i-1][j]+max(sum[col[i]],maxv),f[i-2][j-1]+2*max(sum[col[i]],maxv));
    }
    cltstream::write(f[n][m],'\n');
    return 0;
}
