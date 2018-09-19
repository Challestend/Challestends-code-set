#include<cstdio>
#define re register
#define maxn 1000

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

int n,ec;
int a[maxn+1],h[maxn+1];
int src[maxn+1],des[maxn+1];

inline void swap(int& x,int& y){
    int tmp=x;
    x=y;
    y=tmp;
}

inline void connect(int x,int y){
    src[++ec]=x;
    des[ec]=y;
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        if(x==y){
            printf("NO");
            return 0;
        }
        if(x>y)
            swap(x,y);
        if(y!=n){
            printf("NO");
            return 0;
        }
        ++a[x];
    }
    for(re int i=1;i<n;++i)
        if(a[i]){
            if(h[0]<a[i]-1){
                printf("NO");
                return 0;
            }
            else{
                if(a[i]>1){
                    connect(h[h[0]],i);
                    for(re int j=1;j<a[i]-1;++j){
                        connect(h[h[0]-1],h[h[0]]);
                        --h[0];
                    }
                    connect(n,h[h[0]--]);
                }
                else
                    connect(n,i);
            }
        }
        else
            h[++h[0]]=i;
    printf("YES\n");
    for(re int i=1;i<n;++i){
        cltstream::write(src[i]);
        putchar(32);
        cltstream::write(des[i]);
        putchar(10);
    }
    return 0;
}
