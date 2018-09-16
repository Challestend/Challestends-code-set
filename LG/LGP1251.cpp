#include<cstdio>
#define re register
#define maxn 2000

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

int n,p0,t1,p1,t2,p2,x,y;
int a[maxn+1];
long long ans;

int main(){
    // freopen("LGP1251.in","r",stdin);
    // freopen("LGP1251.out","w",stdout);
    cltstream::read(n);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    cltstream::read(p0),cltstream::read(t1),cltstream::read(p1);
    cltstream::read(t2),cltstream::read(p2);
    for(re int i=1;i<=n;++i){
        if(i>t1)
            x+=a[i-t1];
        if(i>t2)
            y+=a[i-t2];
        printf("Day #%d:x=%d,y=%d,r=%d\n",i,x,y,a[i]);
        a[0]=a[i];
        if(p0>p2&&y>0){
            if(y>=a[0]){
                printf("Slow wash %d.\n",a[0]);
                ans+=1LL*p2*a[0];
                x-=a[0];
                y-=a[0];
                continue;
            }
            else{
                printf("Slow wash %d.\n",y);
                ans+=1LL*p2*y;
                a[0]-=y;
                x-=y;
                y-=y;
            }
        }
        if(p0>p1&&x>0){
            if(x>=a[0]){
                printf("Fast wash %d.\n",a[0]);
                ans+=1LL*p1*a[0];
                y-=a[0];
                x-=a[0];
                continue;
            }
            else{
                printf("Fast wash %d.\n",x);
                ans+=1LL*p1*x;
                a[0]-=x;
                y-=x;
                x-=x;
            }
        }
        printf("Buy %d.\n",a[0]);
        ans+=1LL*p0*a[0];
    }
    cltstream::write(ans);
    // fclose(stdin);
    // fclose(stdout);
    return 0;
}
