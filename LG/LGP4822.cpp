#include<cstdio>
#include<queue>
#define re register
#define maxn 50
#define maxm 1000
#define maxk 50
#define htp std::pair<int,std::pair<int,int> >
#define mp(a,b) std::make_pair(a,b)

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
        if(oh==ot){
            fwrite(cltout,1,size,stdout);
            oh=cltout;
        }
        *oh++=c;
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
    inline void write(_tp x,char text=-1){
        if(x<0)
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        if(text>=0)
            pc(text);
    }
}

int n,m,k,ec;
int des[(maxm<<1)+1],len[(maxm<<1)+1],suc[(maxm<<1)+1],las[maxn+1];
std::priority_queue<htp,std::vector<htp >,std::greater<htp > > h;
int dis[maxn+1][maxk+1];

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
    h.push(mp(dis[1][0]=0,mp(1,0)));
    for(;;){
        for(;h.top().first>dis[h.top().second.first][h.top().second.second];h.pop());
        int x=h.top().second.first,y=h.top().second.second;
        if(x==n){
            cltstream::write(dis[x][y]);
            fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
            break;
        }
        h.pop();
        for(re int i=las[x];i;i=suc[i]){
            if(dis[des[i]][y]>dis[x][y]+len[i])
                h.push(mp(dis[des[i]][y]=dis[x][y]+len[i],mp(des[i],y)));
            if(y<k&&dis[des[i]][y+1]>dis[x][y]+(len[i]>>1))
                h.push(mp(dis[des[i]][y+1]=dis[x][y]+(len[i]>>1),mp(des[i],y+1)));
        }
    }
    return 0;
}
