#include<cstdio>
#include<set>
#define re register
#define maxn 100000
#define maxm 100000
#define maxblock 320
#define maxval 200000
#define mod 998244353
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define FILE(filename) freopen(filename".in","r",stdin);freopen(filename".out","w",stdout);

namespace cltstream{
    #define size 1048576
    char cltin[size+1],*ih=cltin,*it=cltin;
    inline char gc(){
        #ifdef ONLINE_JUDGE
            if(ih==it){
                it=(ih=cltin)+fread(cltin,1,size,stdin);
                if(ih==it)
                    return EOF;
            }
            return *ih++;
        #else
            return getchar();
        #endif
    }

    char cltout[size+1],*oh=cltout;
    int outcnt=0;
    inline void pc(char c){
        if(c==-1)
            fwrite(cltout,1,outcnt,stdout);
        else{
            if(outcnt==size){
                fwrite(cltout,1,size,stdout);
                oh=cltout;
                outcnt=0;
            }
            *oh++=c;
            ++outcnt;
        }
    }
    #undef size

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
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        pc(text);
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
    else{
        cltstream::pc('G');
        cltstream::pc('R');
        cltstream::pc('E');
        cltstream::pc('A');
        cltstream::pc('T');
        cltstream::pc(10);
    }
}

int main(){
    FILE("T53537");
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    for(;(size+1)*(size+1)<=n;++size);
    for(re int i=1;(i-1)*size+1<=n;++i){
        init(i);
        for(re int j=(i-1)*size+1;j<=i*size&&j<=n;++j)
            id[j]=i;
    }
    for(re int i=1;i<=m;++i){
        int opt,l,r,x;
        cltstream::read(opt);
        cltstream::read(l);
        cltstream::read(r);
        switch(opt){
            case 1:
                cltstream::read(x);
                IntervalCut(l,r,x);
                break;
            case 2:
                IntervalAssignToMin(l,r);
                break;
            case 3:
                cltstream::read(x);
                IntervalPre(l,r,x);
                break;
        }
    }
    for(re int i=1;i<=n;++i)
        (a[0]+=sam[id[i]]?sam[id[i]]:val[find(i)]+tag[id[i]])%=mod;
    cltstream::write(a[0],'\n');
    cltstream::pc(-1);
    return 0;
}
