#include<cstdio>
#include<algorithm>
#include<queue>
#define re register
#define maxn 1000
#define maxm 1000
#define tp std::pair<int,std::pair<int,int> >

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

int n,m,k;
int a[maxn+1][maxm+1];
std::priority_queue<tp,std::vector<tp >,std::greater<tp > > h;
long long ans;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=1;i<=n;++i){
        for(re int j=1;j<=m;++j)
            cltstream::read(a[i][j]);
        std::sort(a[i]+1,a[i]+m+1);
        h.push(std::make_pair(a[i][m],std::make_pair(i,m)));
    }
    for(re int i=1;i<=k;++i){
        int res=h.top().first,r=h.top().second.first,c=h.top().second.second;
        h.pop();
        ans+=res;
        if(c>1)
            h.push(std::make_pair(a[r][c-1],std::make_pair(r,c-1)));
    }
    cltstream::write(ans,'\n');
    return 0;
}
