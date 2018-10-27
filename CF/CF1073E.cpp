#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define mod 998244353

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
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

long long l,r;
int k;
int cnt[1024],p[19]={1},num[19],v[19][1024][2];
std::pair<int,int> f[19][1024][2];

std::pair<int,int> dfs(int pos,int S,int touchLimit,int leadingZero){
    if(!touchLimit&&v[pos][S][leadingZero])
        return f[pos][S][leadingZero];
    if(!pos)
        return std::make_pair(1,0);
    std::pair<int,int> res(0,0),tmp;
    if(!touchLimit){
        v[pos][S][leadingZero]=1;
        for(re int i=0;i<=9;++i){
            int T=leadingZero&&!i?S:(S|(1<<i));
            if(cnt[T]<=k){
                tmp=dfs(pos-1,T,0,leadingZero&&!i);
                res.first=(1LL*res.first+tmp.first)%mod;
                res.second=(1LL*res.second+1LL*tmp.first*i%mod*p[pos-1]%mod+tmp.second)%mod;
            }
        }
        f[pos][S][leadingZero]=res;
    }
    else
        for(re int i=0;i<=num[pos];++i){
            int T=leadingZero&&!i?S:(S|(1<<i));
            if(cnt[T]<=k){
                tmp=dfs(pos-1,T,i==num[pos],leadingZero&&!i);
                res.first=(1LL*res.first+tmp.first)%mod;
                res.second=(1LL*res.second+1LL*tmp.first*i%mod*p[pos-1]%mod+tmp.second)%mod;
            }
        }
    return res;
}

int main(){
    for(re int i=1;i<1024;cnt[i]=cnt[i>>1]+(i&1),++i);
    for(re int i=1;i<=18;p[i]=10LL*p[i-1]%mod,++i);
    cltstream::read(l);
    cltstream::read(r);
    cltstream::read(k);
    --l;
    for(num[0]=0;l;num[++num[0]]=l%10,l/=10);
    std::pair<int,int> ansl=dfs(num[0],0,1,1);
    memset(v,0,sizeof(v));
    for(num[0]=0;r;num[++num[0]]=r%10,r/=10);
    std::pair<int,int> ansr=dfs(num[0],0,1,1);
    cltstream::write((ansr.second-ansl.second+mod)%mod,'\n');
    return 0;
}
