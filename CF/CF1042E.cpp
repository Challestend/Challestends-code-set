#include<cstdio>
#include<algorithm>
#define re register
#define maxn 1000
#define maxm 1000
#define mod 998244353
#define sqr(a) ((a)*(a))

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

int n,m,r,c;
struct cell{
    int x,y,val;
};
cell a[maxn*maxm+1];
int f[maxn*maxm+1];
int cnt,fs,xs,ys,ss,fa,xa,ya,sa,res;

bool cmp(cell p,cell q){
    return p.val<q.val||(p.val==q.val&&p.x+p.y-r-c<q.x+q.y-r-c);
}

int cltpow(long long x,int y){
    if(y==1)
        return x;
    int res=cltpow(x,y>>1);
    res=1LL*res*res%mod;
    if(y&1)
        res=1LL*res*x%mod;
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j){
            a[(i-1)*m+j].x=i;
            a[(i-1)*m+j].y=j;
            cltstream::read(a[(i-1)*m+j].val);
        }
    cltstream::read(r);
    cltstream::read(c);
    std::sort(a+1,a+n*m+1,cmp);
    for(re int i=1;i<=n*m;++i){
        if(a[i].val>a[i-1].val){
            cnt=i-1;
            fs=(1LL*fs+fa)%mod;
            xs=(1LL*xs+xa)%mod;
            ys=(1LL*ys+ya)%mod;
            ss=(1LL*ss+sa)%mod;
            fa=xa=ya=sa=0;
        }
        res=(1LL*fs+1LL*cnt*(sqr(a[i].x)+sqr(a[i].y))%mod)%mod;
        res=(1LL*res-2LL*xs*a[i].x%mod-2LL*ys*a[i].y%mod+ss+mod)%mod;
        f[i]=1LL*res*cltpow(cnt,mod-2)%mod;
        if(a[i].x==r&&a[i].y==c){
            cltstream::write(f[i]);
            break;
        }
        fa=(1LL*fa+f[i])%mod;
        xa=(1LL*xa+a[i].x)%mod;
        ya=(1LL*ya+a[i].y)%mod;
        sa=(1LL*sa+sqr(a[i].x)+sqr(a[i].y))%mod;
    }
    return 0;
}
