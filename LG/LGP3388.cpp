#include<cstdio>
#define re register
#define maxn 200000
#define maxm 1000000
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
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m,ec,vc,cnt;
int des[(maxm<<1)+1],suc[(maxm<<1)+1],las[maxn+1];
int dfn[maxn+1],low[maxn+1],cut[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur,int ftr){
    dfn[cur]=low[cur]=++dfn[0];
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            if(!dfn[des[i]]){
                cnt+=(!ftr);
                dfs(des[i],cur);
                low[cur]=min(low[cur],low[des[i]]);
                if(low[des[i]]>=dfn[cur]&&ftr&&!cut[cur]){
                    ++cut[0];
                    ++cut[cur];
                }
            }
            else
                low[cur]=min(low[cur],dfn[des[i]]);
        }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        re int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    for(re int i=1;i<=n;++i)
        if(!dfn[i]){
            cnt=0;
            dfs(i,0);
            cut[0]+=(cnt>1);
            cut[i]+=(cnt>1);
        }
    cltstream::write(cut[0],'\n');
    for(re int i=1;i<=n;++i)
        if(cut[i])
            cltstream::write(i);
    return 0;
}
