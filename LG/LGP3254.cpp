#include<cstdio>
#include<cstring>
#define re register
#define maxn 150
#define maxm 270
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,s,t,sum,ec=-1,maxflow;
int des[2*(maxn+1)*(maxm+1)+1],cap[2*(maxn+1)*(maxm+1)+1];
int suc[2*(maxn+1)*(maxm+1)+1],las[maxn+maxm+5];
int arc[maxn+maxm+5],dep[maxn+maxm+5],cnt[maxn+maxm+5],pre[maxn+maxm+5],h[maxn+maxm+5];

inline void connect(int x,int y,int z){
    des[++ec]=y;
    cap[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

inline void setdepth(){
    for(re int i=1;i<=n+m+2;++i)
        arc[i]=las[i],dep[i]=n+m+2;
    dep[h[1]=t]=0;
    for(re int head=0,tail=1;head<tail;){
        int x=h[++head];
        for(re int i=las[x];i>=0;i=suc[i])
            if(cap[i^1]&&dep[des[i]]==n+m+2)
                dep[h[++tail]=des[i]]=dep[x]+1;
    }
    for(re int i=1;i<=n+m+2;++i)
        ++cnt[dep[i]];
}

inline void addflow(){
    int res=2e9;
    for(re int cur=t;cur!=s;cur=des[pre[cur]^1])
        res=min(res,cap[pre[cur]]);
    maxflow+=res;
    for(re int cur=t;cur!=s;cur=des[pre[cur]^1])
        cap[pre[cur]]-=res,cap[pre[cur]^1]+=res;
}

inline void solve(){
    setdepth();
    for(re int cur=s;dep[s]<n+m+2;){
        if(cur==t)
            addflow(),cur=s;
        int f=0;
        for(re int i=arc[cur];i>=0;i=suc[i])
            if(cap[i]&&dep[des[i]]<dep[cur]){
                f=1;
                arc[cur]=i;
                pre[cur=des[i]]=i;
                break;
            }
        if(!f){
            if(!(--cnt[dep[cur]]))
                break;
            arc[cur]=las[cur];
            int mind=n+m+1;
            for(re int i=las[cur];i>=0;i=suc[i])
                if(cap[i]&&dep[des[i]]<mind)
                    mind=dep[des[i]];
            ++cnt[dep[cur]=mind+1];
            if(cur!=s)
                cur=des[pre[cur]^1];
        }
    }
}

int main(){
    memset(las,-1,sizeof(las));
    read(n),read(m);
    s=n+m+1,t=n+m+2;
    for(re int i=1;i<=n;++i){
        int x;
        read(x);
        sum+=x;
        connect(s,i,x);
        connect(i,s,0);
    }
    for(re int i=1;i<=m;++i){
        int x;
        read(x);
        connect(n+i,t,x);
        connect(t,n+i,0);
    }
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j)
            connect(i,n+j,1),connect(n+j,i,0);
    solve();
    if(maxflow!=sum)
        putchar(48);
    else{
        putchar(49);
        for(re int i=1;i<=n;++i){
            putchar(10);
            for(re int j=las[i];j>=0;j=suc[j])
                if(!cap[j]&&des[j]>n)
                    write(des[j]-n),putchar(32);
        }
    }
    return 0;
}
