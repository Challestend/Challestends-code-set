#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
#define maxm 100000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) max(a,-(a))

namespace cltstream{
    #define size 1048576
    char cltin[size+1],*ih=cltin,*it=cltin;
    inline char gc(){
        #ifdef ONLINE_JUDGE
            if(ih==it){
                it=(ih=cltin)+fread(cltin,1,size,stdin);
                if(ih==it)
                    return EOF;
            }
            return *ih++;
        #else
            return getchar();
        #endif
    }

    char cltout[size+1],*oh=cltout,*ot=cltout+size;
    inline void pc(char c){
        if(c==-1)
            fwrite(cltout,1,oh-cltout,stdout);
        else{
            if(oh==ot){
                fwrite(cltout,1,size,stdout);
                oh=cltout;
            }
            *oh++=c;
        }
    }
    #undef size

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
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        pc(text);
    }
}

int n,m,ans=2e9;
std::pair<int,int> a[maxn+2];
int b[maxm+1];

inline bool cmp(std::pair<int,int> p,std::pair<int,int> q){
    return (double)(p.first/p.second)>(double)(q.first/q.second);
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i].first);
        cltstream::read(a[i].second);
    }
    std::sort(a+1,a+n+1,cmp);
    a[n+1].first=-1;
    a[n+1].second=1;
    for(re int i=1;i<=m;++i){
        cltstream::read(b[i]);
        b[0]+=b[i];
    }
    for(re int i=1;i<=n;++i){
        a[0].first+=a[i].first;
        a[0].second+=a[i].second;
        int x0=a[0].first/(a[0].second+b[0]);
        if(x0>=a[i+1].first/a[i+1].second)
            ans=min(ans,abs(1LL*(a[0].second+b[0])*x0-a[0].first));
        if(x0+1>=a[i+1].first/a[i+1].second)
            ans=min(ans,abs(1LL*(a[0].second+b[0])*(x0+1)-a[0].first));
    }
    cltstream::write(ans,'\n');
    cltstream::pc(-1);
    return 0;
}
