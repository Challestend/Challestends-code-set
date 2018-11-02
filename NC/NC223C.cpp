#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000

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

int t,n;
int a[maxn+1],rnk[maxn+1],f[maxn+2],g[maxn+2];

inline bool cmp1(int x,int y){
    return a[x]<a[y];
}

inline bool cmp2(int x,int y){
    return a[x]>a[y];
}

int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}

int main(){
    cltstream::read(t);
    for(;t;--t){
        cltstream::read(n);
        for(re int i=1;i<=n;++i){
            cltstream::read(a[i]);
            rnk[i]=i;
        }
        long long ans=0;
        std::sort(rnk+1,rnk+n+1,cmp1);
        for(re int i=1;i<=n;++i){
            f[i]=i;
            g[i]=0;
        }
        for(re int i=1;i<=n;++i){
            g[rnk[i]]=1;
            ans+=1LL*(g[find(rnk[i]-1)]+1)*(g[find(rnk[i]+1)]+1)*a[rnk[i]];
            if(g[rnk[i]-1]){
                g[rnk[i]]+=g[f[rnk[i]-1]];
                f[f[rnk[i]-1]]=find(rnk[i]);
            }
            if(g[rnk[i]+1]){
                g[rnk[i]]+=g[f[rnk[i]+1]];
                f[f[rnk[i]+1]]=find(rnk[i]);
            }
        }
        std::sort(rnk+1,rnk+n+1,cmp2);
        for(re int i=1;i<=n;++i){
            f[i]=i;
            g[i]=0;
        }
        for(re int i=1;i<=n;++i){
            g[rnk[i]]=1;
            ans-=1LL*(g[find(rnk[i]-1)]+1)*(g[find(rnk[i]+1)]+1)*a[rnk[i]];
            if(g[rnk[i]-1]){
                g[rnk[i]]+=g[f[rnk[i]-1]];
                f[f[rnk[i]-1]]=find(rnk[i]);
            }
            if(g[rnk[i]+1]){
                g[rnk[i]]+=g[f[rnk[i]+1]];
                f[f[rnk[i]+1]]=find(rnk[i]);
            }
        }
        cltstream::write(ans,10);
    }
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
