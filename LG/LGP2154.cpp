#include<cstdio>
#include<algorithm>
#define re register
#define maxw 100000
#define maxk 10
#define mod 2147483648LL

namespace cltstream{
    // #define ONLINE_JUDGE
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

int n,m,w,k;
long long ans=0;
std::pair<int,int> pos[maxw+1];
int x[maxw+1],y[maxw+1];
int sumx[maxw+1],sumy[maxw+1],cntx[maxw+1],cnty[maxw+1];
long long C[maxw+1][maxk+1],fwt[maxw+1];

inline void update(int L,long long x){
    for(re int i=L;i<=y[0];i+=i&(-i))
        fwt[i]=((fwt[i]+x)%mod+mod)%mod;
}

inline long long getsum(int L){
    long long res=0;
    for(re int i=L;i>=1;i-=i&(-i))
        res=((res+fwt[i])%mod+mod)%mod;
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(w);
    for(re int i=1;i<=w;++i){
        cltstream::read(pos[i].first);
        cltstream::read(pos[i].second);
        x[i]=pos[i].first;
        y[i]=pos[i].second;
    }
    cltstream::read(k);
    std::sort(x+1,x+w+1);
    x[0]=std::unique(x+1,x+w+1)-x-1;
    std::sort(y+1,y+w+1);
    y[0]=std::unique(y+1,y+w+1)-y-1;
    for(re int i=1;i<=w;++i){
        pos[i].first=std::lower_bound(x+1,x+x[0]+1,pos[i].first)-x;
        ++sumx[pos[i].first];
        pos[i].second=std::lower_bound(y+1,y+y[0]+1,pos[i].second)-y;
        ++sumy[pos[i].second];
    }
    std::sort(pos+1,pos+w+1);
    for(re int i=0;i<=w;++i)
        C[i][0]=1;
    for(re int i=1;i<=w;++i)
        for(re int j=1;j<=i&&j<=k;++j)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    for(re int i=1;i<=w;++i){
        int curx=pos[i].first,cury=pos[i].second;
        if(pos[i-1].first==curx&&cntx[curx]>=k&&sumx[curx]-cntx[curx]>=k){
            long long res1=C[cntx[curx]][k]*C[sumx[curx]-cntx[curx]][k]%mod;
            long long res2=((getsum(cury-1)-getsum(pos[i-1].second))%mod+mod)%mod;
            ans=(ans+res1*res2%mod)%mod;
        }
        ++cntx[curx];
        update(cury,((-C[cnty[cury]][k]*C[sumy[cury]-cnty[cury]][k])%mod+mod)%mod);
        ++cnty[cury];
        update(cury,C[cnty[cury]][k]*C[sumy[cury]-cnty[cury]][k]%mod);
    }
    cltstream::write(ans,'\n');
    return 0;
}
