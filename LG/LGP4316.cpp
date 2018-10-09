#include<cstdio>
#define re register
#define maxn 100000
#define maxm 200000

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

int n,m,ec;
int des[maxm+1],len[maxm+1],suc[maxm+1],las[maxn+1];
int oud[maxn+1],ind[maxn+1],h[maxn+1];
double pro[maxn+1],ans[maxn+1];

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        ++oud[x];
        ++ind[y];
        connect(x,y,z);
    }
    h[1]=pro[1]=1;
    for(re int head=0,tail=1;head<tail;){
        int x=h[++head];
        for(re int i=las[x];i;i=suc[i]){
            pro[des[i]]+=pro[x]/oud[x];
            ans[des[i]]+=(ans[x]+pro[x]*len[i])/oud[x];
            --ind[des[i]];
            if(!ind[des[i]])
                h[++tail]=des[i];
        }
    }
    printf("%0.2lf",ans[n]);
    return 0;
}
