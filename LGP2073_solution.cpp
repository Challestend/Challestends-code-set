// luogu-judger-enable-o2
#include<iostream>
#include<cstring>
#include<cstdio>
#include<set>
#include<map>
#define re register
#define mp make_pair
using namespace std;
typedef pair<long long,long long> pii;
set<pii> s;
set<pii>::iterator i;
map<long,long> f;
long long p,w,k,ans,tot;
inline long long read()
{
    char c=getchar();
    long long x=0,r=1;
    while(c<'0'||c>'9')
    {
        if(c=='-') r=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
      x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*r;
}
int main()
{
    freopen("LGP2073.in","r",stdin);
    freopen("LGP2073.ans","w",stdout);
    while(1)
    {
        p=read();
        if(p==-1) break;
        if(p==1)
        {
            k=read();
            w=read();
            if(!f[w])
            {
                f[w]++;
                s.insert(mp(w,k));
            }
        }
        if(p==3&&s.size())
        {
            //if(!s.size()) continue;
            i=s.begin();
            pii ha=*i;
            w=ha.first;
            f[w]--;
            s.erase(ha);
        }
        if(p==2&&s.size())
        {
            //if(!s.size()) continue;
            i=s.end();
            i--;
            pii ha=*i;
            w=ha.first;
            f[w]--;
            s.erase(ha);
        }
    }
    for(i=s.begin();i!=s.end();i++)
    {
        pii ha=*i;
        tot+=ha.first;
        ans+=ha.second;
    }
    printf("%lld %lld",ans,tot);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
