#include<cstdio>
#define re register
#define maxa 10000

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=10*x+(c^48),c=getchar());
        x*=sn;
    }

    template <typename _tp>
    inline void write(_tp x){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
    }
}

int n,a,b,c;
int f[maxa+1],g[maxa+1],las[maxa+1],d[maxa+1];

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

int main(){
    for(re int i=2;i<=maxa;++i){
        if(!f[i]){
            g[++g[0]]=i;
            las[i]=d[i]=2;
        }
        for(re int j=1;j<=g[0]&&i*g[j]<=maxa;++j){
            f[i*g[j]]=1;
            if(i%g[j]){
                d[i*g[j]]=d[i]*las[g[j]];
                las[i*g[j]]=las[g[j]];
            }
            else{
                d[i*g[j]]=d[i]*(las[i]+1)/las[i];
                las[i*g[j]]=las[i]+1;
            }
        }
    }
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(a),cltstream::read(b);
        c=gcd(a,b);
        cltstream::write(d[a]*d[b]-d[c]*(d[c]-1)/2);
        putchar(10);
    }
    return 0;
}
