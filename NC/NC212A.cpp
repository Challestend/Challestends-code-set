#include<cstdio>
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

int n;
int x[maxn+1],y[maxn+1];

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(x[i]);
        cltstream::read(y[i]);
    }
    for(re int i=1;i<=n;++i){
        long long r;
        if(i<n)
            r=1LL*(x[i+1]-x[i])*(x[i+1]-x[i])+1LL*(y[i+1]-y[i])*(y[i+1]-y[i]);
        else
            r=1LL*(x[i-1]-x[i])*(x[i-1]-x[i])+1LL*(y[i-1]-y[i])*(y[i-1]-y[i]);
        int f=1;
        for(re int j=1;j<=n&&f;++j)
            if(j!=i&&1LL*(x[j]-x[i])*(x[j]-x[i])+1LL*(y[j]-y[i])*(y[j]-y[i])!=r)
                f=0;
        if(f){
            cltstream::write(i,'\n');
            return 0;
        }
    }
    cltstream::write(-1,'\n');
    return 0;
}
