#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 100
#define maxm 10
#define maxsize 1024

namespace cltstream{
    #define LOCAL
    #ifdef LOCAL
        #define gc getchar
    #else
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

int n,m,size;
std::string s;
int a[maxn+1],valid[maxsize+1]={1},cnt[maxsize+1],f[maxn+1][maxsize+1];

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
        valid[i]=(i&1)?valid[i>>3]&((~i)>>2)&((~i)>>1)):valid[i>>1];
        cnt[i]=cnt[i>>1]+(i&1);
    }
}
