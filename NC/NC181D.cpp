#include<cstdio>
#define re register
#define maxn 23333
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,ec,far,ans;
int des[(maxn<<1)+1],len[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1],dis[maxn+1];

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur,int ftr){
    for(int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            dis[des[i]]=dis[cur]+len[i];
            dfs(des[i],cur);
        }
    if(dis[cur]>dis[far])
        far=cur;
    ans=max(ans,dis[far]);
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<n;++i){
        int x,y,z;
        cltstream::read(x),cltstream::read(y),cltstream::read(z);
        connect(x,y,z);
        connect(y,x,z);
    }
    dfs(1,0);
    dis[far]=ans=0;
    dfs(far,0);
    cltstream::write(ans*(ans+1)/2+10*ans);
    return 0;
}
