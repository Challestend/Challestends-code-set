#include<cstdio>
#define re register
#define maxn 200000

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

int n;
int a[maxn+1],las[4],cnt,opt;

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        if(a[i]<0)
            ++cnt;
    }
    int cnt0=cnt;
    for(re int i=1;i<=n;++i){
        if(a[i]==0){
            if(las[0]){
                ++opt;
                putchar(49);
                putchar(32);
                cltstream::write(las[0]);
                putchar(32);
                cltstream::write(i);
                putchar(10);
            }
            las[0]=i;
            continue;
        }
        if(a[i]>0){
            if(las[1]){
                ++opt;
                putchar(49);
                putchar(32);
                cltstream::write(las[1]);
                putchar(32);
                cltstream::write(i);
                putchar(10);
            }
            las[1]=i;
            continue;
        }
        if(a[i]<0){
            --cnt0;
            if((cnt&1)&&!cnt0){
                las[3]=i;
                continue;
            }
            if(las[2]){
                ++opt;
                putchar(49);
                putchar(32);
                cltstream::write(las[2]);
                putchar(32);
                cltstream::write(i);
                putchar(10);
            }
            las[2]=i;
            continue;
        }
    }
    if(las[1]&&las[2]){
        ++opt;
        putchar(49);
        putchar(32);
        cltstream::write(las[1]);
        putchar(32);
        cltstream::write(las[2]);
        putchar(10);
    }
    if((cnt&1)&&las[3]){
        if(las[0]){
            ++opt;
            putchar(49);
            putchar(32);
            cltstream::write(las[0]);
            putchar(32);
            cltstream::write(las[3]);
            putchar(10);
        }
        ++opt;
        putchar(50);
        putchar(32);
        cltstream::write(las[3]);
        putchar(10);
    }
    else
        if(opt<n-1&&las[0]){
            ++opt;
            putchar(50);
            putchar(32);
            cltstream::write(las[0]);
            putchar(10);
        }
    return 0;
}
