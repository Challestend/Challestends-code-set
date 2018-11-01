#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn=100000,maxm=300000,maxq=100000;

int n,m,q,v;
struct edge{
    int src,des,len,suc;
};
edge e[maxm+1<<1];
int las[maxn+1];
int w[maxn+1],root[maxn+1],f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],ord[maxn+1],top[maxn+1];
int a[maxn+1<<2];

int read(){
    int sn=1,d=0;
    char c=getchar();
    for(;c<48||c>57;c=getchar());
    if(c==45){
        sn=-1;
        c=getchar();
    }
    for(;c>=48&&c<=57;d=(d<<3)+(d<<1)+(c^48),c=getchar());
    return sn*d;
}

bool cmp(edge p,edge q){
    return p.len<q.len;
}

int find(int p){
    if(f[p]!=p)
        f[p]=find(f[p]);
    return f[p];
}

void update(int L,int x,int cur,int l,int r){
    if(l==r)
        a[cur]=x;
    else{
        int mid=l+r>>1;
        if(L<=mid)
            update(L,x,cur<<1,l,mid);
        else
            update(L,x,cur<<1|1,mid+1,r);
        a[cur]=max(a[cur<<1],a[cur<<1|1]);
    }
}

int getmax(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return a[cur];
    else{
        int mid=l+r>>1,res=-2e9;
        if(L<=mid)
            res=max(res,getmax(L,R,cur<<1,l,mid));
        if(R>mid)
            res=max(res,getmax(L,R,cur<<1|1,mid+1,r));
        return res;
    }
}

void setdepth(int cur,int curroot,int curf,int curdep){
    root[cur]=curroot;
    f[cur]=curf;
    dep[cur]=curdep;
    size[cur]=1;
    int maxsize=0;
    for(int i=las[cur];i;i=e[i].suc){
        int x=e[i].des;
        if(x!=f[cur]){
            w[x]=e[i].len;
            f[x]=cur;
            setdepth(x,curroot,cur,curdep+1);
            size[cur]+=size[x];
            if(maxsize<size[x]){
                maxsize=size[x];
                hes[cur]=x;
            }
        }
    }
}

void setorder(int cur,int curtop){
    ord[cur]=++v;
    update(v,w[cur],1,1,n);
    top[cur]=curtop;
    if(!hes[cur])
        return;
    setorder(hes[cur],curtop);
    for(int i=las[cur];i;i=e[i].suc){
        int x=e[i].des;
        if(x!=f[cur]&&x!=hes[cur])
            setorder(x,x);
    }
}

void swap(int& p,int& q){
    int tmp=p;
    p=q;
    q=tmp;
}

int pthmax(int x,int y){
    int res=-2e9;
    for(;top[x]!=top[y];){
        if(dep[top[x]]>dep[top[y]])
            swap(x,y);
        res=max(res,getmax(ord[top[y]],ord[y],1,1,n));
        y=f[top[y]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    return max(res,getmax(ord[x]+1,ord[y],1,1,n));
}

int main(){
    n=read();
    m=read();
    for(int i=1;i<=m;++i){
        e[i].src=read();
        e[i].des=read();
        e[i].len=read();
    }
    sort(e+1,e+m+1,cmp);
    for(int i=1;i<=n;++i)
        f[i]=i;
    for(int i=1,j=0;i<=m&&j<n-1;++i){
        int x=e[i].src,y=e[i].des,z=e[i].len;
        if(find(x)!=find(y)){
            f[f[x]]=f[y];
            e[i].suc=las[x];
            las[x]=i;
            ++j;
            e[m+j].src=y;
            e[m+j].des=x;
            e[m+j].len=z;
            e[m+j].suc=las[y];
            las[y]=m+j;
        }
    }
    for(int i=1;i<=n;++i)
        if(!root[i]){
            setdepth(i,i,0,0);
            setorder(i,i);
        }
    q=read();
    for(int i=1;i<=q;++i){
        int x=read(),y=read();
        if(root[x]==root[y])
            printf("%d\n",pthmax(x,y));
        else
            puts("impossible");
    }
    return 0;
}
