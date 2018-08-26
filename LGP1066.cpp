#include<cstdio>
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

int n,m;
struct bignum{
    int s[205];

    void init(){
        s[0]=1;
        for(int i=1;i<=200;++i)
            s[i]=0;
    }

    void print(){
        for(int i=s[0];i>=1;--i)
            putchar(s[i]^48);
    }

    void operator=(const int& a){
        s[0]=1,s[1]=a;
    }

    void operator=(bignum& a){
        s[0]=a.s[0];
        for(int i=1;i<=s[0];++i)
            s[i]=a.s[i];
    }

    void operator+=(bignum& a){
        s[0]=max(s[0],a.s[0]);
        for(int i=1;i<=s[0];++i){
            s[i]+=a.s[i];
            if(s[i]>=10)
                ++s[i+1],s[i]-=10;
        }
        if(s[s[0]+1])
            ++s[0];
    }

    void operator-=(bignum& a){
        for(int i=s[0];i>=1;--i){
            s[i]-=a.s[i];
            if(s[i]<0)
                --s[i+1],s[i]+=10;
        }
        for(;!s[s[0]];--s[0]);
    }

    bignum(){
        init();
    }
};
bignum C[512],ans;

int main(){
    scanf("%d%d",&n,&m);
    int p=m%n,q=m/n,r=(1<<n)-1,s=(1<<p)-1;
    C[0]=1;
    for(int i=1;i<=r;++i){
        C[i]+=C[i-1],C[i]+=C[i-1];
        for(int j=i-1;j>0;--j)
            C[j]+=C[j-1];
        if(i>=r-s&&i>=q&&i<r)
            ans+=C[q],ans-=C[q-1];
    }
    ans+=C[min(r,q)],ans-=C[1];
    ans.print();
    return 0;
}
