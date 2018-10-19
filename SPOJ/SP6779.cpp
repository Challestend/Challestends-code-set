#include<cstdio>
#define re register
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))

namespace cltstream{
    #ifdef ONLINE_JUDGE
        #define size 1048576
        char str[size+1],*head=str,*tail=str;
        inline char gc(){
            if(head==tail){
                tail=(head=str)+fread(str,1,size,stdin);
                if(head==tail)
                    return EOF;
            }
            return *head++;
        }
        #undef size
    #else
        #define gc getchar
    #endif

    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=gc();
        for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
        if(c==45&&c!=EOF)
            sn=-1,c=gc();
        for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=gc());
        x*=sn;
    }

    template <typename _tp>
    inline void write(_tp x,char text=' '){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m,ec,vc;
int w[maxn+1],des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];
struct node{
    int ms,ls,rs,sum,upd,c;

    node(){
        ms=ls=rs=sum=upd=c=0;
    }
};
node a[(maxn<<2)+1];

inline node operator+(node x,node y){
    node z;
    z.ms=max(max(x.ms,y.ms),x.rs+y.ls);
    z.ls=max(x.ls,x.sum+y.ls);
    z.rs=max(y.rs,y.sum+x.rs);
    z.sum=x.sum+y.sum;
    return z;
}

inline void operator+=(node& x,node y){
    x=x+y;
}

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

inline void pushDown(int cur,int ln,int rn){
    if(a[cur].upd){
        a[cur<<1].ms=a[cur<<1].ls=a[cur<<1].rs=max(ln*a[cur].c,a[cur].c);
        a[cur<<1].sum=ln*a[cur].c;
        a[cur<<1].upd=a[cur].upd;
        a[cur<<1].c=a[cur].c;
        a[cur<<1|1].ms=a[cur<<1|1].ls=a[cur<<1|1].rs=max(rn*a[cur].c,a[cur].c);
        a[cur<<1|1].sum=rn*a[cur].c;
        a[cur<<1|1].upd=a[cur].upd;
        a[cur<<1|1].c=a[cur].c;
        a[cur].upd=0;
    }
}

void update(int L,int R,int x,int cur,int l,int r){
    if(l>=L&&r<=R){
        a[cur].ms=a[cur].ls=a[cur].rs=max((r-l+1)*x,x);
        a[cur].sum=(r-l+1)*x;
        a[cur].upd=1;
        a[cur].c=x;
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            update(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update(L,R,x,cur<<1|1,mid+1,r);
        a[cur]=a[cur<<1]+a[cur<<1|1];
    }
}

node getmaxsum(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return a[cur];
    else{
        int mid=(l+r)>>1;
        node res;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            res+=getmaxsum(L,R,cur<<1,l,mid);
        if(R>mid)
            res+=getmaxsum(L,R,cur<<1|1,mid+1,r);
        return res;
    }
}

void dfs1(int cur,int ftr){
    f[cur]=ftr;
    dep[cur]=dep[f[cur]]+1;
    size[cur]=1;
    int maxsize=0;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur]){
            dfs1(des[i],cur);
            size[cur]+=size[des[i]];
            if(maxsize<size[des[i]]){
                maxsize=size[des[i]];
                hes[cur]=des[i];
            }
        }
}

void dfs2(int cur,int curtop){
    id[cur]=++vc;
    update(id[cur],id[cur],w[cur],1,1,n);
    top[cur]=curtop;
    if(!hes[cur])
        return;
    dfs2(hes[cur],curtop);
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

int pthmaxsum(int x,int y){
    node res,res1,res2;
    int dir=1;
    for(;top[x]!=top[y];){
        if(dep[top[x]]>dep[top[y]]){
            swap(x,y);
            dir^=1;
        }
        res=getmaxsum(id[top[y]],id[y],1,1,n);
        if(dir)
            res2=res+res2;
        else{
            swap(res.ls,res.rs);
            res1=res1+res;
        }
        y=f[top[y]];
    }
    if(dep[x]>dep[y]){
        swap(x,y);
        dir^=1;
    }
    res=getmaxsum(id[x],id[y],1,1,n);
    if(dir)
        res2=res+res2;
    else{
        swap(res.ls,res.rs);
        res1=res1+res;
    }
    res1+=res2;
    return max(res1.ms,0);
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i)
        cltstream::read(w[i]);
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    dfs1(1,0);
    dfs2(1,1);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        int opt,x,y,z;
        cltstream::read(opt);
        cltstream::read(x);
        cltstream::read(y);
        if(opt==1)
            cltstream::write(pthmaxsum(x,y),'\n');
        else{
            cltstream::read(z);
            pthupd(x,y,z);
        }
    }
    return 0;
}
