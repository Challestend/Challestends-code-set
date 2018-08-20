#include<cstdio>
#include<algorithm>
#define re register
#define maxn 200000
#define maxm 200000

int n,m,n0,vc;
int f[maxn+1],g[maxn+1],h[maxn+1],cnt[maxn+1];
struct node{
    int val,lc,rc;
};
node a[20*maxn+1];
int root[maxm+1];

inline void read(int& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

inline void write(int x){
    int digit[20];
    if(x<0)
        putchar(45),x=-x;
    for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
    if(!digit[0])
        putchar(48);
    else
        for(;digit[0];putchar(digit[digit[0]]^48),--digit[0]);
}

bool cmp(int x,int y){
    return f[x]<f[y]||(f[x]==f[y]&&x<y);
}

void build(int L,int cur,int l,int r){
    if(l<r){
        int mid=l+r>>1;
        if(!a[cur].lc)
            a[cur].lc=++vc;
        build(L,a[cur].lc,l,mid);
        if(!a[cur].rc)
            a[cur].rc=++vc;
        build(L,a[cur].rc,mid+1,r);
    }
}

void update(int L,int x,int cur,int l,int r){
    if(l==r)
        a[++vc].val=x;
    else{
        int mid=l+r>>1;
        if(L<=mid){
            update(L,x,a[cur].lc,l,mid);
            ++vc;
            a[vc].lc=vc-1;
            a[vc].rc=a[cur].rc;
        }
        else{
            update(L,x,a[cur].rc,mid+1,r);
            ++vc;
            a[vc].lc=a[cur].lc;
            a[vc].rc=vc-1;
        }
        a[vc].val=a[a[vc].lc].val+a[a[vc].rc].val;
    }
}

int getkth(int L,int R,int k,int l,int r){
    if(l==r)
        return f[g[l]];
    else{
        int mid=l+r>>1;
        if(k<=a[a[R].lc].val-a[a[L].lc].val)
            return getkth(a[L].lc,a[R].lc,k,l,mid);
        else
            return getkth(a[L].rc,a[R].rc,k-a[a[R].lc].val+a[a[L].lc].val,mid+1,r);
    }
}

int main(){
    read(n),read(m);
    for(re int i=1;i<=n;++i){
        scanf("%d",&f[i]);
        g[i]=i;
    }
    std::sort(g+1,g+n+1,cmp);
    for(re int i=1;i<=n;++i)
        if(f[g[i]]>f[g[i-1]])
            g[++n0]=g[i],cnt[n0]=1;
        else
            ++cnt[n0];
    root[0]=++vc;
    for(int i=1;i<=n0;++i){
        build(i,root[0],1,n);
        h[g[i]]=i;
    }
    for(re int i=1,ver=0;i<=n0;++i)
        for(int j=1;j<=cnt[h[i]];++j){
            update(h[i],j,root[i-1],1,n);
            root[++ver]=vc;
        }
    for(re int i=1;i<=m;++i){
        int x,y,z;
        read(x),read(y),read(z);
        write(getkth(root[x-1],root[y],z,1,n));
        putchar(10);
    }
    return 0;
}
