#include<cstdio>
#define re register
#define maxn 100000
#define maxm 100000
#define maxlog 16
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

int n,m,ec,vc,root,soot;
int lg[(maxn<<1)+1],st[(maxn<<1)+1][maxlog+2],ex[maxn+1];
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1],w[maxn+1];
int minw[(maxn<<2)+1],upd[(maxn<<2)+1],c[(maxn<<2)+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

inline void pushDown(int cur){
    if(!upd[cur])
        return;
    minw[cur<<1]=minw[cur];
    upd[cur<<1]=upd[cur];
    c[cur<<1]=c[cur];
    minw[cur<<1|1]=minw[cur];
    upd[cur<<1|1]=upd[cur];
    c[cur<<1|1]=c[cur];
    upd[cur]=0;
}

void update(int L,int R,int x,int cur,int l,int r){
    if(l>=L&&r<=R){
        minw[cur]=c[cur]=x;
        upd[cur]=1;
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur);
        if(L<=mid)
            update(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update(L,R,x,cur<<1|1,mid+1,r);
        minw[cur]=min(minw[cur<<1],minw[cur<<1|1]);
    }
}

int getmin(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return minw[cur];
    else{
        int mid=(l+r)>>1,res=2e9;
        pushDown(cur);
        if(L<=mid)
            res=min(res,getmin(L,R,cur<<1,l,mid));
        if(R>mid)
            res=min(res,getmin(L,R,cur<<1|1,mid+1,r));
        return res;
    }
}

void dfs1(int cur,int ftr){
    st[++st[0][0]][0]=cur;
    ex[cur]=st[0][0];
    f[cur]=ftr;
    dep[cur]=dep[ftr]+1;
    size[cur]=1;
    int maxsize=0;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur]){
            dfs1(des[i],cur);
            size[cur]+=size[des[i]];
            if(maxsize<size[des[i]]){
                hes[cur]=des[i];
                maxsize=size[des[i]];
            }
        }
    st[++st[0][0]][0]=cur;
}

void dfs2(int cur,int ctp){
    id[cur]=++vc;
    update(id[cur],id[cur],w[cur],1,1,n);
    top[cur]=ctp;
    if(!hes[cur])
        return;
    dfs2(hes[cur],ctp);
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur]&&des[i]!=hes[cur])
            dfs2(des[i],des[i]);
}

inline void swap(int& x,int& y){
    int tmp=x;
    x=y;
    y=tmp;
}

void pthupd(int x,int y,int z){
    for(;top[x]!=top[y];){
        if(dep[top[x]]>dep[top[y]])
            swap(x,y);
        update(id[top[y]],id[y],z,1,1,n);
        y=f[top[y]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    update(id[x],id[y],z,1,1,n);
}

inline int stmin(int x,int y){
    if(x>y)
        swap(x,y);
    int z=lg[y-x+1];
    int p=st[x][z],q=st[y-(1<<z)+1][z];
    return dep[p]<=dep[q]?p:q;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=(n<<1);++i)
        lg[i]=lg[i>>1]+1;
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    for(re int i=1;i<=n;++i)
        cltstream::read(w[i]);
    dfs1(1,0);
    dfs2(1,1);
    for(re int i=1;i<=st[0][0];++i)
        printf("%d ",st[i][0]);
    printf("\n");
    for(re int i=1;i<=maxlog+1;++i)
        for(re int j=1;j+(1<<i)-1<=(n<<1);++j)
            st[j][i]=dep[st[j][i-1]]<=dep[st[j+(1<<(i-1))][j-1]]?st[j][i-1]:st[j+(1<<(i-1))][j-1];
    cltstream::read(root);
    for(re int i=1;i<=m;++i){
        int opt,x,y,z;
        cltstream::read(opt);
        cltstream::read(x);
        switch(opt){
            case 1:
                root=x;
                break;
            case 2:
                cltstream::read(y);
                cltstream::read(z);
                pthupd(x,y,z);
                break;
            case 3:
                if(x==root){
                    cltstream::write(minw[1]);
                    putchar(10);
                    break;
                }
                int lca=stmin(ex[root],ex[x]);
                printf("LCA(%d,%d)=%d\n",root,x,lca);
        }
    }
    return 0;
}
