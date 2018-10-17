#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 100
#define maxm 10
#define maxsize 1024
#define max(a,b) ((a)>=(b)?(a):(b))

namespace cltstream{
    #define gc getchar
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

int n,m,size;
std::string s;
int a[maxn+1],valid[maxsize+1]={1},cnt[maxsize+1],f[maxn+1][maxsize+1][maxsize+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    size=1<<m;
    for(re int i=1;i<=n;++i){
        std::cin>>s;
        for(re int j=1;j<=m;++j)
            a[i]=(a[i]<<1)|(s[j-1]=='H');
    }
    for(re int i=1;i<size;++i){
        valid[i]=(i&1)?valid[i>>3]&((~i)>>2)&((~i)>>1):valid[i>>1];
        cnt[i]=cnt[i>>1]+(i&1);
    }
    for(re int i=0;i<size;++i)
        if((i&a[1])==a[1]&&valid[i^a[1]])
            for(re int j=0;j<size;++j)
                if((j&a[2])==a[2]&&valid[j^a[2]]&&((i^a[1])&(j^a[2]))==0)
                    f[2][i][j]=cnt[i^a[1]]+cnt[j^a[2]];
    for(re int i=3;i<=n;++i)
        for(re int j=0;j<size;++j)
            if((j&a[i-2])==a[i-2]&&valid[j^a[i-2]])
                for(re int k=0;k<size;++k)
                    if((k&a[i-1])==a[i-1]&&valid[k^a[i-1]]&&((j^a[i-2])&(k^a[i-1]))==0)
                        for(re int l=0;l<size;++l)
                            if((l&a[i])==a[i]&&valid[l^a[i]]&&((l^a[i])&(j^a[i-2]))==0&&((l^a[i])&(k^a[i-1]))==0)
                                f[i][k][l]=max(f[i][k][l],f[i-1][j][k]+cnt[l^a[i]]);
    for(re int i=0;i<size;++i)
        for(re int j=0;j<size;++j)
            f[n][0][0]=max(f[n][0][0],f[n][i][j]);
    cltstream::write(f[n][0][0],'\n');
    return 0;
}
