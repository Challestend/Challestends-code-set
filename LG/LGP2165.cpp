#include<cstdio>
#define re register
#define maxn 20

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

int n,ans;
int a[maxn+1];

int main(){
    read(n);
    for(re int i=1;i<=n;++i)
        read(a[i]),a[i]+=a[i-1];
    for(re int i=1;i<=n;++i)
        for(re int j=i;j<=n;++j)
            ans+=(a[j]-a[i-1]==a[n]>>1);
    ans>>=1;
    write(ans*(ans-1)>>1);
    return 0;
}
