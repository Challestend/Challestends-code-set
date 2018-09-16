#include<cstdio>
#include<cmath>
#define re register

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

long long a,b;
int n,c,d;

int main(){
    read(n);
    for(re int i=1;i<=n;++i){
        read(a),read(b);
        c=sqrt(a),d=sqrt(b);
        if(1LL*c*c<a)
            ++c;
        if((((d-c+1)>>1)+((d-c+1)&c))&1)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
