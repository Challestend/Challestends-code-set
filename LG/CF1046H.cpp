#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<set>
#define re register
#define maxn 100000

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

int n;
int cnt[26];
std::multiset<std::pair<int,int> > a;

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        std::string s;
        std::cin>>s;
        memset(cnt,0,sizeof(cnt));
        for(re int j=1;j<=s.length();++j)
            cnt[s[j-1]-'a']^=1;
        int x=0;
        for(re int j=0;j<26;++j)
            x|=cnt[j]<<j;
        a.insert(std::make_pair(0,x));
        for(re int j=0;j<26;++j)
            if(s.find('a'+j)!=-1&&(x>>j&1)){
                int y=x^(1<<j);
                printf("%d->%d\n",x,y);
                a.insert(std::make_pair(1,y));
            }
    }
    for(std::multiset<std::pair<int,int> >::iterator p=a.begin();p!=a.end();++p)
        if(a.count(*p)>1)
            printf("%d %d\n",(*p).first,(*p).second);
}
