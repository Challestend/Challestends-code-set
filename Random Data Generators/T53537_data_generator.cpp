#include<cstdio>
#include<ctime>
#include<cstring>
#include<set>
#include"cltrnd.h"
#define re register
#define maxn 100000
#define maxm 100000
#define maxblock 320
#define maxval 200000
#define mod 998244353
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define FILE(filename) freopen(filename".in","w",stdout);

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
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m,size;
int a[maxn+1],id[maxn+1];
int val[maxn+1],f[maxn+1];
int pos[maxblock+1][maxval+1];
int maxv[maxblock+1],minv[maxblock+1],tag[maxblock+1],sam[maxblock+1];
std::set<int> s[maxblock+1];

int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}

inline void init(int x){
    maxv[x]=-2e9;
    minv[x]=2e9;
    tag[x]=sam[x]=0;
    s[x].clear();
    for(re int i=(x-1)*size+1;i<=x*size&&i<=n;++i)
        if(!pos[x][a[i]]){
            val[i]=a[i];
            f[i]=i;
            pos[x][a[i]]=i;
            maxv[x]=max(maxv[x],a[i]);
            minv[x]=min(minv[x],a[i]);
            s[x].insert(a[i]);
        }
        else
            f[i]=pos[x][a[i]];
}

inline void destory(int x){
    for(re int i=(x-1)*size+1;i<=x*size&&i<=n;++i){
        a[i]=sam[x]?sam[x]:val[find(i)]+tag[x];
        pos[x][val[i]]=0;
    }
    tag[x]=sam[x]=0;
    s[x].clear();
}

inline void solve(int x,int y){
    if(sam[x]){
        if(sam[x]>y)
            sam[x]-=y;
        return;
    }
    if(maxv[x]-(y-tag[x])<=(y-tag[x])-minv[x]+1){
        for(re int i=(y-tag[x])+1;i<=maxv[x];++i)
            if(pos[x][i]){
                s[x].erase(i);
                if(!pos[x][i-y]){
                    val[pos[x][i]]-=y;
                    pos[x][i-y]=pos[x][i];
                    s[x].insert(i-y);
                }
                else
                    if(pos[x][i]>pos[x][i-y])
                        f[pos[x][i]]=pos[x][i-y];
                    else{
                        f[pos[x][i-y]]=pos[x][i];
                        pos[x][i-y]=pos[x][i];
                        val[pos[x][i-y]]-=y;
                    }
                pos[x][i]=0;
            }
    }
    else{
        for(re int i=(y-tag[x]);i>=minv[x];--i)
            if(pos[x][i]){
                s[x].erase(i);
                if(!pos[x][i+y]){
                    val[pos[x][i]]+=y;
                    pos[x][i+y]=pos[x][i];
                    s[x].insert(i+y);
                }
                else
                    if(pos[x][i]>pos[x][i+y])
                        f[pos[x][i]]=pos[x][i+y];
                    else{
                        f[pos[x][i+y]]=pos[x][i];
                        pos[x][i+y]=pos[x][i];
                        val[pos[x][i+y]]+=y;
                    }
                pos[x][i]=0;
            }
        tag[x]-=y;
    }
    minv[x]=*s[x].begin();
    std::set<int>::iterator it=s[x].end();
    --it;
    maxv[x]=*it;
}

inline void IntervalCut(int l,int r,int x){
    int L=id[l],R=id[r];
    destory(L);
    for(re int i=l;i<=L*size&&i<=r;++i)
        if(a[i]>x)
            a[i]-=x;
    init(L);
    for(re int i=L+1;i<=R-1;++i)
        solve(i,x);
    if(L<R){
        destory(R);
        for(re int i=(R-1)*size+1;i<=r;++i)
            if(a[i]>x)
                a[i]-=x;
        init(R);
    }
}

inline void IntervalAssignToMin(int l,int r){
    int L=id[l],R=id[r],res=2e9;
    destory(L);
    for(re int i=l;i<=L*size&&i<=r;++i)
        res=min(res,a[i]);
    for(re int i=L+1;i<=R-1;++i)
        res=min(res,sam[i]?sam[i]:minv[i]+tag[i]);
    if(L<R){
        destory(R);
        for(re int i=(R-1)*size+1;i<=r;++i)
            res=min(res,a[i]);
    }
    for(re int i=l;i<=L*size&&i<=r;++i)
        a[i]=res;
    init(L);
    for(re int i=L+1;i<=R-1;++i)
        sam[i]=res;
    if(L<R){
        for(re int i=(R-1)*size+1;i<=r;++i)
            a[i]=res;
        init(R);
    }
}

inline void IntervalPre(int l,int r,int x){
    int L=id[l],R=id[r],p=0,res=-2e9;
    if(sam[L]){
        if(sam[L]<x&&sam[L]>res){
            p=l;
            res=sam[L];
        }
    }
    else
        for(re int i=l;i<=L*size&&i<=r;++i)
            if(val[find(i)]+tag[L]<x&&val[find(i)]+tag[L]>res){
                p=i;
                res=val[f[i]]+tag[L];
            }
    for(re int i=L+1;i<=R-1;++i)
        if(sam[i]){
            if(sam[i]<x&&sam[i]>res){
                p=(i-1)*size+1;
                res=sam[i];
            }
        }
        else{
            std::set<int>::iterator it=s[i].lower_bound(x-tag[i]);
            if(it!=s[i].begin()){
                --it;
                if(*it+tag[i]<x&&*it+tag[i]>res){
                    p=pos[i][*it];
                    res=*it+tag[i];
                }
            }
        }
    if(L<R){
        if(sam[R]){
            if(sam[R]<x&&sam[R]>res){
                p=(R-1)*size+1;
                res=sam[R];
            }
        }
        else
            for(re int i=(R-1)*size+1;i<=r;++i)
                if(val[find(i)]+tag[R]<x&&val[find(i)]+tag[R]>res){
                    p=i;
                    res=val[f[i]]+tag[R];
                }
    }
    if(p)
        cltstream::write(p,'\n');
    else
        puts("GREAT");
}

inline void swap(int& x,int& y){
    int tmp=x;
    x=y;
    y=tmp;
}

inline int IntervalMax(int l,int r){
    int L=id[l],R=id[r],res=-2e9;
    for(re int i=l;i<=L*size&&i<=r;++i)
        res=max(res,sam[L]?sam[L]:val[find(i)]+tag[L]);
    for(re int i=L+1;i<=R-1;++i)
        res=max(res,sam[i]?sam[i]:maxv[i]+tag[i]);
    if(L<R)
        for(re int i=(R-1)*size+1;i<=r;++i)
            res=max(res,sam[R]?sam[R]:val[find(i)]+tag[R]);
    return res;
}

int main(){
    cltrnd::srnd(time(0));
    FILE("low13");
    n=m=100000;
    cltstream::write(n);
    cltstream::write(m,'\n');
    for(re int i=1;i<=n;++i)
        cltstream::write(a[i]=cltrnd::rnd()%(maxval>>1)+1," \n"[i==n]);
    for(;(size+1)*(size+1)<=n;++size);
    for(re int i=1;(i-1)*size+1<=n;++i){
        init(i);
        for(re int j=(i-1)*size+1;j<=i*size&&j<=n;++j)
            id[j]=i;
    }
    for(re int i=1;i<=m;++i){
        int opt=cltrnd::rnd()%20+1;
        if(opt<=9){
            cltstream::write(1);
            int len=cltrnd::rnd()%n+1,l=cltrnd::rnd()%(n-len+1)+1,r=l+len;
            cltstream::write(l);
            cltstream::write(r);
            cltstream::write(IntervalMax(l,r)>>1,'\n');
        }
        else
            if(opt<=11){
                cltstream::write(2);
                int len=cltrnd::rnd()%10000+1,l=cltrnd::rnd()%(n-len+1)+1,r=l+len;
                cltstream::write(l);
                cltstream::write(r,'\n');
            }
            else{
                cltstream::write(3);
                int len=cltrnd::rnd()%n+1,l=cltrnd::rnd()%(n-len+1)+1,r=l+len;
                cltstream::write(l);
                cltstream::write(r);
                cltstream::write(cltrnd::rnd()%(maxval>>1)+1,'\n');
            }
    }
    return 0;
}
