#include<cstdio>
#include<queue>
#define re register
#define maxn 1000
#define maxe 20000
#define abs(a) ((a)>=0?(a):(-(a)))

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

int n,a,b,ec;
int des[maxe+1],len[maxe+1],suc[maxe+1],las[maxn+1];
std::queue<int> h;
int ex[maxn+1],cnt[maxn+1],dis[maxn+1];

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<n;++i)
        dis[i]=-2e9;
    cltstream::read(a);
    cltstream::read(b);
    for(re int i=1;i<=a;++i){
        int x,y,l;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(l);
        connect(y,x,-l);
    }
    for(re int i=1;i<=b;++i){
        int x,y,l;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(l);
        connect(x,y,l);
    }
    for(re int i=n;i>=1;--i)
        if(i==n||dis[i]==-2e9){
            h.push(i);
            ex[i]=cnt[i]=1;
            for(;!h.empty();){
                int x=h.front();
                ex[x]=0;
                h.pop();
                for(re int j=las[x];j;j=suc[j])
                    if(dis[des[j]]<dis[x]+len[j]){
                        dis[des[j]]=dis[x]+len[j];
                        cnt[des[j]]=cnt[x]+1;
                        if(cnt[des[j]]>n){
                            putchar(45);
                            putchar(49);
                            return 0;
                        }
                        if(!ex[des[j]]){
                            h.push(des[j]);
                        ex[des[j]]=1;
                        }
                    }
            }
        }
    cltstream::write(dis[1]==-2e9?-2:abs(dis[1]));
    return 0;
}
