#include<cstdio>
#define re register
#define maxn 300000
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,ec;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1],f[maxn+1],g[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur,int ftr){
    int p=0,q=0;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            dfs(des[i],cur);
            ++f[cur];
            ++g[cur];
            if(g[des[i]]>=p){
                q=p;
                p=g[des[i]];
            }
            else
                if(g[des[i]]>=q)
                    q=g[des[i]];
        }
    f[cur]+=p+q;
    g[cur]+=p;
}

int main(){
    cltstream::read(n);
    cltstream::read(n);
    ++n;
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    dfs(1,0);
    for(re int i=2;i<=n;++i)
        f[1]=max(f[1],f[i]+1);
    cltstream::write(f[1]+1,'\n');
    cltstream::pc(-1);
    return 0;
}
