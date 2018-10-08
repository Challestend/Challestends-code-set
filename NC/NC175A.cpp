#include<cstdio>
#define re register

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
long long l,r,x,y;

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(l);
        cltstream::read(r);
        cltstream::read(x);
        if(x<=1){
            if(l<=1&&r>=1)
                puts("1");
            else
                puts("None.");
        }
        else{
            for(y=1;y>0&&y<l;y*=x);
            if(y<=0||y>r)
                puts("None.");
            else{
                for(;y<=r;){
                    cltstream::write(y);
                    putchar(32);
                    long long z=y*x;
                    if(z<=y)
                        break;
                    else
                        y=z;
                }
                putchar(10);
            }
        }
    }
    return 0;
}
