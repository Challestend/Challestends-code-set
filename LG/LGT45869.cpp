#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 2000
#define max(a,b) ((a)>=(b)?(a):(b))

namespace cltstream{
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

int n,m;
std::string s;
int a[maxn+1][maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        std::cin>>s;
        for(re int j=1;j<=n;++j)
            a[i][j]=s[j-1]-'a';
    }
    for(re int i=1;i<=m;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        int p=0,q=0;
        for(;x-p-1>=1&&x+p+1<=n&&a[x-p-1][y]==a[x+p+1][y];++p);
        for(;y-q-1>=1&&y+q+1<=n&&a[x][y-q-1]==a[x][y+q+1];++q);
        cltstream::write(max(p,q)<<1|1);
        putchar(10);
    }
    return 0;
}
