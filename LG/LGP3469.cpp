#include<cstdio>
#define re register
#define maxn 100000
#define maxm 500000
#define min(a,b) ((a)<=(b)?(a):(b))

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

    char cltout[size+1],*oh=cltout,*ot=cltout+size;
    inline void pc(char c){
        if(oh==ot){
            fwrite(cltout,1,size,stdout);
            oh=cltout;
        }
        *oh++=c;
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
    inline void write(_tp x,char text=-1){
        if(x<0)
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        if(text>=0)
            pc(text);
    }
}

int n,m,ec,vc,cc;
int des[(maxm<<1)+1],suc[(maxm<<1)+1],las[maxn+1];
int dfn[maxn+1],low[maxn+1],size[maxn+1];
long long ans[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur,int ftr){
    re int tmp=0;
    dfn[cur]=low[cur]=++vc;
    size[cur]=1;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            if(!dfn[des[i]]){
                cc+=(!ftr);
                dfs(des[i],cur);
                low[cur]=min(low[cur],low[des[i]]);
                if(low[des[i]]>=dfn[cur]){
                    size[cur]+=size[des[i]];
                    ans[cur]+=1LL*size[des[i]]*(n-size[des[i]]-1);
                }
                else
                    tmp+=size[des[i]];
            }
            else
                low[cur]=min(low[cur],dfn[des[i]]);
        }
    if(ans[cur])
        ans[cur]+=1LL*(size[cur]-1)*(n-size[cur]);
    size[cur]+=tmp;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        re int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    dfs(1,0);
    for(re int i=1;i<=n;++i)
        cltstream::write(ans[i]+((n-1)<<1),10);
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
