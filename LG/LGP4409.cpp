#include<cstdio>
#define re register
#define maxn 20000
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,x,y,z,ans;

int main(){
    read(n);
    if(n<=3)
        for(re int i=1;i<=n;++i)
            read(x),ans+=x;
    else{
        read(x),z=x;
        for(re int i=2;i<=n;++i)
            read(y),ans=max(ans,x+y),x=y;
        ans=max(ans,x+z);
    }
    write(ans);
    return 0;
}
