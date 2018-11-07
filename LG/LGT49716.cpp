#include<cstdio>
#define re register
#define maxn 10000
#define mod 1000000007

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
    #define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout)
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

int n,root,m,ec;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1],f[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs1(int cur,int ftr){
    f[cur]=1;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            dfs1(des[i],cur);
            f[cur]+=f[des[i]];
        }
}

void dfs2(int cur,int ftr){
    f[cur]=1LL*f[cur]*f[cur]%mod;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            f[cur]=((f[cur]-1LL*f[des[i]]*f[des[i]]%mod)%mod+mod)%mod;
            dfs2(des[i],cur);
        }
}

int main(){
    cltstream::read(n);
    cltstream::read(root);
    cltstream::read(m);
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    dfs1(root,0);
    dfs2(root,0);
    for(re int i=1;i<=m;++i){
        int x;
        cltstream::read(x);
        cltstream::write(f[x],10);
    }
    clop();
    return 0;
}
