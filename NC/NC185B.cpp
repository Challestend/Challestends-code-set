#include<cstdio>
#include<queue>
#define re register
#define maxn 30
#define maxm 10

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
int a[maxn+1][maxn+1],ex[maxn+1],dis[maxn+1],cnt[maxn+1][maxm+1];
std::queue<int> h;

int main(){
    cltstream::read(n),cltstream::read(m);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=n;++j){
            int x;
            cltstream::read(x);
            if(x)
                a[i][++a[i][0]]=j;
        }
    dis[1]=0;
    cnt[1][0]=1;
    h.push(1);
    ex[1]=1;
    for(;!h.empty();){
        int x=h.front();
        h.pop();
        ex[x]=0;
        for(re int i=1;i<=a[x][0];++i){
            dis[a[x][i]]=dis[x]+1;
            for(re int j=0;j<m;++j)
                cnt[a[x][i]][j+1]+=cnt[x][j];
            if(!ex[a[x][i]]&&dis[a[x][i]]<m){
                h.push(a[x][i]);
                ex[a[x][i]]=1;
            }
        }
    }
    cltstream::write(cnt[n][m]);
    return 0;
}
