#include<cstdio>
#define re register
#define maxn 500000

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

int n,ec;
int des[(maxn<<1)+1];
double len[(maxn<<1)+1];
int suc[(maxn<<1)+1],las[maxn+1];
double f[maxn+1],ans[maxn+1];

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=1.0*z/100;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs1(int cur,int ftr){
    ans[cur]=1-ans[cur];
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            dfs1(des[i],cur);
            ans[cur]*=1-len[i]*(1-ans[des[i]]);
        }
}

void dfs2(int cur,int ftr){
    ans[0]+=1-ans[cur];
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            double x=1-len[i]*(1-ans[des[i]])>0?ans[cur]/(1-len[i]*(1-ans[des[i]])):ans[cur];
            ans[des[i]]*=1-len[i]*(1-x);
            dfs2(des[i],cur);
        }
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<n;++i){
        int x,y,z;
        cltstream::read(x),cltstream::read(y),cltstream::read(z);
        connect(x,y,z);
        connect(y,x,z);
    }
    for(re int i=1;i<=n;++i){
        int x;
        cltstream::read(x);
        ans[i]=1.0*x/100;
    }
    dfs1(1,0);
    dfs2(1,0);
    printf("%lf",ans[0]);
    return 0;
}
