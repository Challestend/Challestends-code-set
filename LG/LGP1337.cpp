#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#define re register
#define maxn 1000

namespace cltstream{
    #ifdef ONLINE_JUDGE
        #define size 1048576
        char str[size+1],*head=str,*tail=str;
        inline char gc(){
            if(head==tail){
                tail=(head=str)+fread(str,1,size,stdin);
                if(head==tail)
                    return EOF;
            }
            return *head++;
        }
        #undef size
    #else
        #define gc getchar
    #endif

    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=gc();
        for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
        if(c==45&&c!=EOF)
            sn=-1,c=gc();
        for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=gc());
        x*=sn;
    }

    template <typename _tp>
    inline void write(_tp x,char text=' '){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

const double eps=1e-8,t0=2000,delta=0.995,tk=1e-14,MAX_TIME=0.985;

int n;
int x[maxn+1],y[maxn+1],w[maxn+1];
double t,ansx,ansy,ans;

inline double cal(double _x,double _y){
    double res=0;
    for(re int i=1;i<=n;++i)
        res+=sqrt((_x-x[i])*(_x-x[i])+(_y-y[i])*(_y-y[i]))*w[i];
    return res;
}

inline void SA(){
    t=t0;
    for(;t-tk>eps;){
        double curx=((rand()<<1)-RAND_MAX+1)*t,cury=((rand()<<1)-RAND_MAX+1)*t;
        double cur=cal(curx,cury);
        if(cur-ans<eps||(cur-ans>eps&&exp(-(cur-ans)/t)*RAND_MAX>rand())){
            ansx=curx;
            ansy=cury;
            ans=cur;
        }
        t*=delta;
    }
}

int main(){
    srand(19260817);
    for(re int i=1;i<=2048;++i)
        srand(rand());
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(x[i]);
        cltstream::read(y[i]);
        cltstream::read(w[i]);
        ansx+=x[i];
        ansy+=y[i];
    }
    ans=cal(ansx/=n,ansy/=n);
    for(;double(clock())/CLOCKS_PER_SEC<MAX_TIME;SA());
    printf("%0.3lf %0.3lf",ansx,ansy);
    return 0;
}
