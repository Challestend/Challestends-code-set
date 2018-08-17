#include<cstdio>
#define re register
#define maxn 1000000
#define maxm 1000000
using namespace std;

int n,m,vc;
struct node{
    int val,lc,rc;
};
node a[4*maxn+20*maxm+1];
int root[maxm+1];

int read(){
    int sn=1,x=0;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45){
        sn=-1;
        c=getchar();
    }
    for(;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    return sn*x;
}

void write(int x){
    if(x<0){
        putchar(45);
        x=-x;
    }
    if(x>=10)
        write(x/10);
    putchar(x%10^48);
}

void build(int L,int x,int cur,int l,int r){
    if(l==r)
        a[cur].val=x;
    else{
        int mid=l+r>>1;
        if(L<=mid){
            if(!a[cur].lc)
                a[cur].lc=++vc;
            build(L,x,a[cur].lc,l,mid);
        }
        else{
            if(!a[cur].rc)
                a[cur].rc=++vc;
            build(L,x,a[cur].rc,mid+1,r);
        }
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
    }
}

int getval(int L,int cur,int l,int r){
    if(l==r)
        return a[cur].val;
    else{
        int mid=l+r>>1;
        if(L<=mid)
            return getval(L,a[cur].lc,l,mid);
        else
            return getval(L,a[cur].rc,mid+1,r);
    }
}

int main(){
    n=read(),m=read();
    root[0]=++vc;
    for(re int i=1;i<=n;++i){
        int x=read();
        build(i,x,root[0],1,n);
    }
    for(re int i=1;i<=m;++i){
        int v=read(),opt=read(),x=read(),y;
        if(opt==1){
            y=read();
            update(x,y,root[v],1,n);
            root[i]=vc;
        }
        else{
            write(getval(x,root[v],1,n));
            putchar(10);
            root[i]=root[v];
        }
    }
    return 0;
}
