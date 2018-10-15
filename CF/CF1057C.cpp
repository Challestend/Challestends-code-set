#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#define re register
#define maxn 50
#define maxval 2500
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) ((a)>=0?(a):(-(a)))

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

int n,s,m,ans=2e9;
std::string str;
struct candy{
    int pos,cnt,col;
};
candy a[maxn+1];
int f[maxn+1][maxval+1];

inline bool cmp(candy p,candy q){
    return p.cnt<q.cnt||(p.cnt==q.cnt&&p.pos<q.pos);
}

int main(){
    cltstream::read(n);
    cltstream::read(s);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        a[i].pos=i;
        cltstream::read(a[i].cnt);
        a[0].cnt+=a[i].cnt;
    }
    if(a[0].cnt<m){
        putchar(45);
        putchar(49);
        putchar(10);
        return 0;
    }
    std::cin>>str;
    for(re int i=1;i<=n;++i)
        switch(str[i-1]){
            case 'R':
                a[i].col=0;
                break;
            case 'G':
                a[i].col=1;
                break;
            case 'B':
                a[i].col=2;
                break;
        }
    std::sort(a+1,a+n+1,cmp);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=a[0].cnt;++j)
            f[i][j]=2e9;
    for(re int i=1;i<=n;++i)
        f[i][0]=f[i][a[i].cnt]=abs(s-a[i].pos);
    for(re int i=1;i<=n;++i)
        for(re int j=1;a[j].cnt<a[i].cnt;++j)
            if(a[i].col!=a[j].col)
                for(re int k=a[i].cnt;k<=a[0].cnt;++k)
                    f[i][k]=min(f[i][k],f[j][k-a[i].cnt]+abs(a[i].pos-a[j].pos));
    for(re int i=1;i<=n;++i)
        for(re int j=m;j<=a[0].cnt;++j)
            ans=min(ans,f[i][j]);
    cltstream::write(ans<2e9?ans:-1,'\n');
    return 0;
}
