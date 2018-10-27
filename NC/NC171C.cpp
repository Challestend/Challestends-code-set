#include<cstdio>
#include<cstring>
#include<cmath>
#define re register
#define maxval 10000

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
        if(c==-1)
            fwrite(cltout,1,oh-cltout,stdout);
        else{
            if(oh==ot){
                fwrite(cltout,1,size,stdout);
                oh=cltout;
            }
            *oh++=c;
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

int t,n;
int f[maxval+1],g[maxval+1],p[maxval+1],r[maxval+1];

int main(){
    for(re int i=2;i<=maxval;++i){
        if(!f[i])
            g[++g[0]]=i;
        for(re int j=1;j<=g[0]&&i*g[j]<=maxval;++j){
            f[i*g[j]]=1;
            if(i%g[j]==0)
                break;
        }
    }
    cltstream::read(t);
    for(;t;--t){
        memset(p,0,sizeof(p));
        memset(r,-1,sizeof(r));
        cltstream::read(n);
        for(re int i=1;i<=n;++i){
            int opt,x;
            cltstream::read(opt);
            cltstream::read(x);
            switch(opt){
                case 1:
                    if(x)
                        memset(p,0,sizeof(p));
                    for(re int j=1;j<=g[0];++j)
                        if(r[g[j]]>=0)
                            (r[g[j]]+=x)%=g[j];
                    break;
                case 2:
                    for(re int j=1,_x=x;j<=g[0];++j)
                        if(x%g[j]==0){
                            re int cnt=0;
                            for(;_x%g[j]==0;_x/=g[j],++cnt);
                            p[g[j]]+=cnt;
                            r[g[j]]=0;
                        }
                    break;
                case 3:
                    re int f=1;
                    for(re int j=1,_x=x;j<=g[0];++j)
                        if(x%g[j]==0){
                            re int cnt=0;
                            for(;_x%g[j]==0;_x/=g[j],++cnt);
                            f&=(p[g[j]]>=cnt);
                        }
                    break;
            }
        }
    }
    return 0;
}
