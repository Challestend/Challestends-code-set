#include<cstdio>
#define re register
#define maxn 100
#define maxm 6
#define mod 1000000007

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57)&&c!=EOF;c=getchar());
        if(c==45&&c!=EOF)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=getchar());
        x*=sn;
    }

    template <typename _tp>
    inline void write(_tp x,char text=-1){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            short digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        if(text>=0)
            putchar(text);
    }
}

int n,m,ans;
short v[1<<maxm];
int f[2][1<<maxm][1<<maxm];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    if(n==1){
        cltstream::write(1<<m);
        return 0;
    }
    for(re int i=1;i<(1<<m);++i)
        v[i]=(v[i>>1]<<1)|(((i&1)&&!(i&2))<<2)|((i&4)&&!(i&2));
    for(re int i=0;i<(1<<m);++i)
        for(re int j=0;j<(1<<m);++j)
            if(!(j&v[i])&&!(i&v[j]))
                f[1][i][j]=1;
    for(re int i=3;i<=n;++i){
        for(re int j=0;j<(1<<m);++j)
            for(re int k=0;k<(1<<m);++k)
                f[(i-1)&1][j][k]=0;
        for(re int j=0;j<(1<<m);++j)
            for(re int k=0;k<(1<<m);++k)
                if(!(k&v[j])&&!(j&v[k]))
                    for(re int l=0;l<(1<<m);++l)
                        if(!(l&v[k])&&!(k&v[l])){
                            re int tmp=~k,valid=1;
                            for(;tmp&&valid;){
                                re int x=tmp&(-tmp);
                                if((j&x)&&((l&(x<<1))|(l&(x>>1))))
                                    valid=0;
                                if((l&x)&&((j&(x<<1))|(j&(x>>1))))
                                    valid=0;
                                tmp^=x;
                            }
                            if(valid)
                                (f[(i-1)&1][k][l]+=f[(i-2)&1][j][k])%=mod;
                        }
    }
    for(re int i=0;i<(1<<m);++i)
        for(re int j=0;j<(1<<m);++j)
            (ans+=f[(n-1)&1][i][j])%=mod;
    cltstream::write(ans);
    return 0;
}
