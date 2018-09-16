#include<cstdio>
#include<iostream>
#include<string>
#define re register

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

int n,m,t;
std::string s;
int len,dx,dy,q,x,y;

int main(){
    cltstream::read(n),cltstream::read(m),cltstream::read(t);
    std::cin>>s;
    len=s.length();
    for(re int i=0;i<len;++i)
        switch(s[i]){
            case 'U':--dx;break;
            case 'D':++dx;break;
            case 'L':--dy;break;
            case 'R':++dy;break;
        }
    dx=(1LL*t*dx%n+n)%n,dy=(1LL*t*dy%m+m)%m;
    cltstream::read(q);
    for(re int i=1;i<=q;++i){
        cltstream::read(x),cltstream::read(y);
        cltstream::write((x+dx-1)%n+1),putchar(32),cltstream::write((y+dy-1)%m+1),putchar(10);
    }
    return 0;
}
