#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,ans=2e9;
std::string s;
int cnt[26];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    std::cin>>s;
    for(re int i=0;i<n;++i)
        ++cnt[s[i]-'A'];
    for(re int i=0;i<m;++i)
        ans=min(ans,cnt[i]);
    cltstream::write(ans*m);
    return 0;
}
