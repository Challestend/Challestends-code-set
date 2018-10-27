#include<cstdio>
#define re register

long long n,m,p;

long long mul(long long a,long long b,long long mod){
    long long tmp=a;
    for(a=0;b;){
        a+=(b&1)*tmp;
        tmp=(tmp<<1)%mod;
        b>>=1;
    }
    return a;
}

int main(){
    scanf("%lld%lld%lld",&n,&m,&p);
    m=(m-n+p)%p;
    for(re long long cnt=1,tmp=(n<<1)-2;cnt<=(p<<1);++cnt,tmp=mul(tmp,(n<<1)-2,p))
        if(tmp==m){
            printf("%lld",cnt);
            return 0;
        }
    puts("INF");
    return 0;
}
