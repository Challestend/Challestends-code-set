#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#define re register
#define maxn 1000

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
int date[maxn+1];
std::string name[maxn+1];
std::vector<std::pair<int,int> > a[maxn+1];
int faq[maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        std::cin>>name[i];
        cltstream::read(date[i]);
        faq[i]=date[i]%10000;
    }
    std::sort(faq+1,faq+n+1);
    faq[0]=std::unique(faq+1,faq+n+1)-faq-1;
    for(re int i=1;i<=n;++i){
        int x=std::lower_bound(faq+1,faq+faq[0]+1,date[i]%10000)-faq;
        a[x].push_back(std::make_pair(date[i]/10000,i));
    }
    for(re int i=1;i<=n;++i)
        std::sort(a[i].begin(),a[i].end());
    for(re int i=1;i<=m;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        y=std::lower_bound(faq+1,faq+faq[0]+1,y)-faq;
        std::cout<<name[a[y][x-1].second]<<std::endl;
    }
    return 0;
}
