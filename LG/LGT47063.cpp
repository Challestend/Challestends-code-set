#include<cstdio>
#include<algorithm>
#include<set>
#define re register
#define maxn 50000
#define maxm 50000
#define maxblock 230
#define maxval 100000
#define id(a) (((a)-1)/size+1)
#define max(a,b) ((a)>=(b)?(a):(b))
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

int n,m,size;
int a[maxn+1],val[maxn+1],f[maxn+1];
int pos[maxblock+1][maxval+1],tag[maxblock+1],maxv[maxblock+1],minv[maxblock+1];
std::set<int> s[maxblock+1];

int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}

inline void init(int x){
    maxv[x]=-1e9;
    minv[x]=1e9;
    for(re int i=(x-1)*size+1;i<=x*size&&i<=n;++i)
        if(pos[x][a[i]])
            f[i]=pos[x][a[i]];
        else{
            val[i]=a[i];
            f[i]=i;
            pos[x][a[i]]=i;
            maxv[x]=max(maxv[x],a[i]);
            minv[x]=min(minv[x],a[i]);
            s[x].insert(a[i]);
        }
}

inline void clearData(int x){
    for(re int i=(x-1)*size;i<=x*size&&i<=n;++i){
        a[i]=val[find(i)]+tag[x];
        pos[x][a[i]-tag[x]]=0;
    }
    tag[x]=0;
    s[x].clear();
}

inline void solve(int x,int z){
    if(z-tag[x]-minv[x]<=maxv[x]-z+tag[x]+1){
        for(re int i=minv[x];i<z-tag[x];++i)
            if(pos[x][i]){
                s[x].erase(i);
                if(pos[x][i+z]){
                    f[pos[x][i]]=pos[x][i+z];
                    pos[x][i]=0;
                }
                else{
                    pos[x][i+z]=pos[x][i];
                    pos[x][i]=0;
                    val[pos[x][i+z]]+=z;
                    s[x].insert(i+z);
                }
            }
    }
    else{
        for(re int i=z-tag[x];i<=maxv[x];++i)
            if(pos[x][i]){
                s[x].erase(i);
                if(pos[x][i-z]){
                    f[pos[x][i]]=pos[x][i-z];
                    pos[x][i]=0;
                }
                else{
                    pos[x][i-z]=pos[x][i];
                    pos[x][i]=0;
                    val[pos[x][i-z]]-=z;
                    s[x].insert(i-z);
                }
            }
        tag[x]+=z;
    }
    std::set<int>::iterator p=s[x].end();
    --p;
    maxv[x]=*p;
    minv[x]=*s[x].begin();
}

inline void update(int x,int y,int z){
    int L=id(x),R=id(y);
    if(L==R){
        clearData(L);
        for(re int i=x;i<=y;++i)
            if(a[i]<z)
                a[i]+=z;
        init(L);
        return;
    }
    if((x-1)%size){
        clearData(L);
        for(re int i=x;i<=L*size&&i<=y;++i)
            if(a[i]<z)
                a[i]+=z;
        init(L);
    }
    if(y%size){
        clearData(R);
        for(re int i=y;i>(R-1)*size;--i)
            if(a[i]<z)
                a[i]+=z;
        init(R);
    }
    L+=((x-1)%size>0);
    R-=(y%size>0);
    for(re int i=L;i<=R;++i)
        solve(i,z);
}

inline int getPre(int x,int y,int z){
    int L=id(x),R=id(y),res=-1;
    if(L==R){
        for(re int i=x;i<=y;++i)
            if(val[find(i)]+tag[L]<z)
                res=max(res,val[f[i]]+tag[L]);
        return res;
    }
    if((x-1)%size){
        for(re int i=x;i<=L*size&&i<=y;++i)
            if(val[find(i)]+tag[L]<z)
                res=max(res,val[f[i]]+tag[L]);
    }
    if(y%size){
        for(re int i=y;i>(R-1)*size;--i)
            if(val[find(i)]+tag[R]<z)
                res=max(res,val[f[i]]+tag[R]);
    }
    L+=((x-1)%size>0);
    R-=(y%size>0);
    for(re int i=L;i<=R;++i)
        if(z>maxv[i]+tag[i])
            res=max(res,maxv[i]+tag[i]);
        else{
            std::set<int>::iterator k=std::lower_bound(s[i].begin(),s[i].end(),z-tag[i]);
            if(k==s[i].begin())
                continue;
            --k;
            res=max(res,*k+tag[i]);
        }
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]),d[i]=a[i];
    for(;size*size+2*size+1<=n;++size);
    for(re int i=1;(i-1)*size<n;++i)
        init(i);
    for(re int i=1;i<=m;++i){
        int opt,x,y,z;
        cltstream::read(opt);
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        if(opt==1)
            update(x,y,z);
        else{
            cltstream::write(getPre(x,y,z));
            putchar(10);
        }
    }
    return 0;
}
