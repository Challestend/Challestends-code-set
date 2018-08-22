#include<cstdio>
#include<set>
#define re register
#define maxn 200000
#define maxlogn 20
#define maxm 200000

int n,m,n0,vc;
int f[maxn+1];
std::set<int> s;
int g[maxn+1],h[maxn+1];
struct node{
    int sum,lc,rc;
};
node a[maxn*maxlogn+1];
int root[maxm+1];
int digit[20];

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
    if(x<0)
        putchar(45),x=-x;
    for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
    if(!digit[0])
        putchar(48);
    else
        for(;digit[0];putchar(digit[digit[0]--]^48));
}

int build(int l,int r){
    int cur=++vc;
    if(l<r){
        int mid=l+r>>1;
        a[cur].lc=build(l,mid),a[cur].rc=build(mid+1,r);
    }
    return cur;
}

int update(int L,int pre,int l,int r){
    int cur=++vc;
    a[cur].lc=a[pre].lc,a[cur].rc=a[pre].rc,a[cur].sum=a[pre].sum+1;
    if(l<r){
        int mid=l+r>>1;
        if(L<=mid)
            a[cur].lc=update(L,a[pre].lc,l,mid);
        else
            a[cur].rc=update(L,a[pre].rc,mid+1,r);
    }
    return cur;
}

int getkth(int L,int R,int k,int l,int r){
    if(l==r)
        return g[l];
    else{
        int mid=l+r>>1;
        if(k<=a[a[R].lc].sum-a[a[L].lc].sum)
            return getkth(a[L].lc,a[R].lc,k,l,mid);
        else
            return getkth(a[L].rc,a[R].rc,k-a[a[R].lc].sum+a[a[L].lc].sum,mid+1,r);
    }
}

int main(){
    read(n),read(m);
    for(re int i=1;i<=n;++i)
        read(f[i]),s.insert(f[i]);
    for(std::set<int>::iterator p=s.begin();p!=s.end();++p)
        g[++n0]=*p;
    root[0]=build(1,n0);
    for(re int i=1;i<=n;++i){
        int l=1,r=n0,mid;
        for(;l<r;)
            if(g[mid=l+r>>1]>=f[i])
                r=mid;
            else
                l=mid+1;
        root[i]=update(h[i]=l,root[i-1],1,n0);
    }
    for(re int i=1;i<=m;++i){
        int x,y,z;
        read(x),read(y),read(z);
        write(getkth(root[x-1],root[y],z,1,n0));
        putchar(10);
    }
    return 0;
}
