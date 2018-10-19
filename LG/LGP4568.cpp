#include<cstdio>
#include<queue>
#define re register
#define maxn 10000
#define maxm 50000
#define maxk 20
#define htp std::pair<int,std::pair<int,int> >
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,k,s,t,ec,cnt;
int des[(maxm<<1)+1],len[(maxm<<1)+1],suc[(maxm<<1)+1],las[maxn+1];
int dis[maxn+1][maxk+1],v[maxn+1][maxk+1];
std::priority_queue<htp,std::vector<htp >,std::greater<htp > > h;

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    s=1;
    t=n;
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        connect(x,y,z);
        connect(y,x,z);
    }
    for(re int i=1;i<=n;++i)
        for(re int j=0;j<=k;++j)
            dis[i][j]=2e9;
    h.push(std::make_pair(dis[s][0]=0,std::make_pair(s,0)));
    for(re int i=1;i<=n*(k+1)&&cnt<k+1;++i){
        for(;v[h.top().second.first][h.top().second.second];h.pop());
        int x=h.top().second.first,y=h.top().second.second;
        v[x][y]=1;
        cnt+=(x==t);
        h.pop();
        for(re int i=las[x];i;i=suc[i]){
            if(dis[des[i]][y]>dis[x][y]+len[i])
                h.push(std::make_pair(dis[des[i]][y]=dis[x][y]+len[i],std::make_pair(des[i],y)));
            if(dis[des[i]][y+1]>dis[x][y]&&y<k)
                h.push(std::make_pair(dis[des[i]][y+1]=dis[x][y],std::make_pair(des[i],y+1)));
        }
    }
    for(re int i=1;i<=k;++i)
        dis[t][0]=min(dis[t][0],dis[t][i]);
    cltstream::write(dis[t][0],'\n');
    return 0;
}
