#include<cstdio>
#include<algorithm>
#define re register
#define maxn 1000
#define maxm 1000

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
int v0,cnt=1;
long long xsum,xsqr,ysum,ysqr,sum,ans1,ans2=1;
long long f[maxn*maxm+1];

bool cmp(cell p,cell q){
    return p.val<q.val;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j){
            a[(i-1)*m+j].x=i;
            a[(i-1)*m+j].y=j;
            cltstream::read(a[i*(n-1)+j].val);
        }
    cltstream::read(r);
    cltstream::read(c);
    v0=a[(r-1)*m+c].val;
    std::sort(a+1,a+n*m+1,cmp);
    a[0].val=-1;
    for(re int i=1;i<=n*m&&a[i-1].val<v0;++i){
        if(a[i].val>a[i-1].val&&i>1){
            f[i]=(i-1)*(a[i].x*a[i].x+a[i].y*a[i].y)-2LL*xsum*a[i].x-2LL*ysum*a[i].y+xsqr+ysqr;
            ans2*=ans1;
            cnt=i;
        }
        else
            f[i]=f[i-1];
        sum+=f[i];
        ans1+=cnt;
        xsum+=a[i].x;
        xsqr+=a[i].x*a[i].x;
        ysum+=a[i].y;
        ysqr+=a[i].y*a[i].y;
        printf("%d %lld %lld %lld\n",i,sum,ans2,ans1);
    }
    printf("%lld/%lld\n",sum,ans2);
    return 0;
}
