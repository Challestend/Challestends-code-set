#include<cstdio>
#include<algorithm>
#define re register
#define maxn 15
#define mod 1000000007

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
int a[maxn+1],b[maxn+1];

void dfs(int cur,int res){
    if(cur==n)
        ans=(ans+res)%mod;
    else
        if(b[cur+1])
            if(b[cur+1]<a[cur+1])
                return;
            else
                dfs(cur+1,res);
        else
            for(int i=cur+1;i<=n;++i)
                if(b[i]+a[cur+1]<=a[i]){
                    b[i]+=a[cur+1];
                    dfs(cur+1,cur+1!=i&&a[cur+1]==a[i]?res<<1:res);
                    b[i]-=a[cur+1];
                }
}

int main(){
    read(n);
    for(re int i=1;i<=n;++i)
        read(a[i]);
    std::sort(a+1,a+n+1);
    dfs(0,1);
    write(ans);
    return 0;
}
