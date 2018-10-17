#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#define re register
#define maxn 100
#define maxm 1000
#define maxe ((maxn*(maxn+2))<<1)
#define min(a,b) ((a)<=(b)?(a):(b))

namespace cltstream{
    #define gc getchar

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

const int table[5][5]={{0,1,1,0,0},
                       {0,0,1,0,1},
                       {0,0,0,1,1},
                       {1,1,0,0,0},
                       {1,0,0,1,0}};

int n,m,s,t,vc,ec=-1,mf;
std::string str;
int tp[maxn+1][2],mogic[2];
int des[maxe+1],cap[maxe+1],suc[maxe+1],las[(maxn<<1)+3];
int h[(maxn<<1)+3],arc[(maxn<<1)+3],dep[(maxn<<1)+3],cnt[(maxn<<1)+3],pre[(maxn<<1)+3];

inline void connect(int x,int y,int p){
    des[++ec]=y;
    cap[ec]=p;
    suc[ec]=las[x];
    las[x]=ec;
}

inline void initdepth(){
    for(re int i=1;i<=vc;++i){
        arc[i]=las[i];
        dep[i]=vc;
    }
    dep[t]=0;
    h[1]=t;
    for(int head=0,tail=1;head<tail;){
        int x=h[++head];
        for(re int i=las[x];i>=0;i=suc[i])
            if(cap[i^1]&&dep[des[i]]==vc)
                dep[h[++tail]=des[i]]=dep[x]+1;
    }
    for(re int i=1;i<=vc;++i)
        ++cnt[dep[i]];
}

inline void addflow(){
    int res=2e9;
    for(re int cur=t;cur!=s;cur=des[pre[cur]^1])
        res=min(res,cap[pre[cur]]);
    mf+=res;
    for(re int cur=t;cur!=s;cur=des[pre[cur]^1]){
        cap[pre[cur]]-=res;
        cap[pre[cur]^1]+=res;
    }
}

inline void isap(){
    initdepth();
    for(re int cur=s;dep[s]<vc;){
        if(cur==t){
            addflow();
            cur=s;
        }
        int f=0;
        for(re int i=arc[cur];i>=0;i=suc[i])
            if(cap[i]&&dep[des[i]]<dep[cur]){
                f=1;
                arc[cur]=i;
                pre[cur=des[i]]=i;
                break;
            }
        if(!f){
            if(!(--cnt[dep[cur]]))
                return;
            arc[cur]=las[cur];
            int mind=vc-1;
            for(re int i=las[cur];i>=0;i=suc[i])
                if(cap[i]&&dep[des[i]]<mind)
                    mind=dep[des[i]];
            ++cnt[dep[cur]=mind+1];
            if(cur!=s)
                cur=des[pre[cur]^1];
        }
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    s=(n<<1)+1;
    t=(n<<1)+2;
    vc=t;
    for(re int i=1;i<=n;++i){
        std::cin>>str;
        switch(str[0]){
            case 'J':
                tp[i][0]=0;
                break;
            case 'H':
                tp[i][0]=1;
                break;
            case 'W':
                tp[i][0]=2;
                break;
            case 'Y':
                ++mogic[0];
                tp[i][0]=3;
                break;
            case 'E':
                tp[i][0]=4;
                break;
        }
    }
    for(re int i=1;i<=n;++i){
        std::cin>>str;
        switch(str[0]){
            case 'J':
                tp[i][1]=0;
                break;
            case 'H':
                tp[i][1]=1;
                break;
            case 'W':
                tp[i][1]=2;
                break;
            case 'Y':
                ++mogic[1];
                tp[i][1]=3;
                break;
            case 'E':
                tp[i][1]=4;
                break;
        }
    }
    memset(las,-1,sizeof(las));
    for(re int i=1;i<=n;++i){
        int x;
        cltstream::read(x);
        if(!tp[i][0])
            x+=mogic[0];
        connect(s,i,x);
        connect(i,s,0);
    }
    for(re int i=1;i<=n;++i){
        int x;
        cltstream::read(x);
        if(!tp[i][1])
            x+=mogic[1];
        connect(n+i,t,x);
        connect(t,n+i,0);
    }
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=n;++j)
            if(table[tp[i][0]][tp[j][1]]){
                connect(i,n+j,1);
                connect(n+j,i,0);
            }
    isap();
    cltstream::write(min(mf,m),'\n');
    return 0;
}
