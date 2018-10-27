#include<cstdio>
#include<queue>
#define re register
#define maxn 10
#define maxm 10
#define maxsize 1024
#define htp std::pair<int,std::pair<int,int> >

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

int n,m;
int des[maxm+1],c[maxm+1],p[maxm+1],r[maxm+1],suc[maxm+1],las[maxn+1];
int dis[maxn+1][maxsize+1];
std::priority_queue<htp,std::vector<htp >,std::greater<htp > > h;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        int x;
        cltstream::read(x);
        cltstream::read(des[i]);
        cltstream::read(c[i]);
        cltstream::read(p[i]);
        cltstream::read(r[i]);
        suc[i]=las[x];
        las[x]=i;
    }
    for(re int i=1;i<=n;++i)
        for(re int j=0;j<(1<<n);++j)
            dis[i][j]=2e9;
    h.push(std::make_pair(dis[1][1]=0,std::make_pair(1,1)));
    for(;!h.empty();){
        for(;h.top().first>dis[h.top().second.first][h.top().second.second];h.pop());
        int x=h.top().second.first,S=h.top().second.second;
        h.pop();
        if(x==n){
            cltstream::write(dis[x][S],'\n');
            return 0;
        }
        for(re int i=las[x];i;i=suc[i]){
            int cost=((S>>(c[i]-1))&1)?p[i]:r[i];
            if(dis[des[i]][S|(1<<(des[i]-1))]>dis[x][S]+cost){
                h.push(std::make_pair(dis[des[i]][S|(1<<(des[i]-1))]=dis[x][S]+cost,std::make_pair(des[i],S|(1<<(des[i]-1)))));
            }
        }
    }
    puts("impossible");
    return 0;
}
