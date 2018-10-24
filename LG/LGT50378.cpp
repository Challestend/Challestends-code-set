#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register

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

int tec,l,r,sc,s,tc,t;
long long p[10]={1};
int num[10],v[10][1023];
std::pair<int,long long> f[10][1023];

std::pair<int,long long> dfs(int pos,int cur,int touchLimit){
    if(!touchLimit&&v[pos][cur&s])
        return f[pos][cur&s];
    if(!pos)
        return std::make_pair((cur&s)==s,0);
    std::pair<int,long long> res(0,0);
    if(touchLimit){
        for(re int i=0;i<=num[pos];++i)
            if(!(t&(1<<i))){
                std::pair<int,long long> ret=dfs(pos-1,cur|(1<<i),i==num[pos]);
                res.first+=ret.first;
                res.second+=p[pos-1]*ret.first*i+ret.second;
            }
        return res;
    }
    else{
        v[pos][cur&s]=1;
        for(re int i=0;i<=9;++i)
            if(!(t&(1<<i))){
                std::pair<int,long long> ret=dfs(pos-1,cur|(1<<i),0);
                res.first+=ret.first;
                res.second+=p[pos-1]*ret.first*i+ret.second;
            }
        return f[pos][cur&s]=res;
    }
}

int main(){
    for(re int i=1;i<10;++i)
        p[i]=(p[i-1]<<3)+(p[i-1]<<1);
    cltstream::read(tec);
    for(;tec;--tec){
        cltstream::read(l);
        --l;
        cltstream::read(r);
        cltstream::read(sc);
        s=0;
        for(re int i=1;i<=sc;++i){
            int x;
            cltstream::read(x);
            s|=1<<x;
        }
        cltstream::read(tc);
        t=0;
        for(re int i=1;i<=tc;++i){
            int x;
            cltstream::read(x);
            t|=1<<x;
        }
        memset(v,0,sizeof(v));
        memset(f,0,sizeof(f));
        for(num[0]=0;l;num[++num[0]]=l%10,l/=10);
        long long ansl=dfs(num[0],0,1).second;
        memset(v,0,sizeof(v));
        memset(f,0,sizeof(f));
        for(num[0]=0;r;num[++num[0]]=r%10,r/=10);
        long long ansr=dfs(num[0],0,1).second;
        cltstream::write(ansr-ansl,'\n');
    }
    return 0;
}

/*
3
11 40
1 3
2 4 7
2018 20170901
1 4
1 7
19260817 998244353
3 2 5 6
4 0 7 8 9
*/

/*
1
1 40
1 3
2 4 7
*/
