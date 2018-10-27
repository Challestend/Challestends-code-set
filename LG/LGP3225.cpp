#include<cstdio>
#include<cstring>
#define re register
#define maxn 500
#define maxm 500
#define max(a,b) ((a)>=(b)?(a):(b))
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

int m,n,ec,vc,cnt;
int ex[maxn+1],des[(maxm<<1)+1],suc[(maxm<<1)+1],las[maxn+1];
int dfn[maxn+1],low[maxn+1],cut[maxn+1],h[maxn+1];

inline void connect(int x,int y){
    n=max(n,x);
    ex[x]=1;
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur,int ftr){
    dfn[cur]=low[cur]=++vc;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            if(!dfn[des[i]]){
                dfs(des[i],cur);
                cnt+=(!ftr);
                low[cur]=min(low[cur],low[des[i]]);
                cut[cur]|=(low[des[i]]>=dfn[cur]&&ftr);
            }
            else
                low[cur]=min(low[cur],dfn[des[i]]);
        }
}

long long cntNode(int x){
    h[1]=x;
    re int head=0,tail=1;
    for(;head<tail;){
        int x=h[++head];
        for(re int i=las[x];i;i=suc[i])
            if(!cut[des[i]])
                cut[h[++tail]=des[i]]=1;
    }
    return tail;
}

int main(){
    for(re int tc=1;;++tc){
        cltstream::read(m);
        if(!m)
            break;
        n=0;
        ec=vc=0;
        memset(las,0,sizeof(las));
        memset(ex,0,sizeof(ex));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(cut,0,sizeof(cut));
        for(re int i=1;i<=m;++i){
            int x,y;
            cltstream::read(x);
            cltstream::read(y);
            connect(x,y);
            connect(y,x);
        }
        cnt=0;
        dfs(n,0);
        cut[n]=(cnt>1);
        cnt=0;
        long long ans=1;
        for(re int i=1;i<=n;++i)
            if(ex[i]&&!cut[i]){
                cut[i]=1;
                ++cnt;
                ans*=cntNode(i);
            }
        printf("Case %d: ",tc);
        if(cnt==1){
            cltstream::write(cnt+1);
            cltstream::write(ans*(ans-1)>>1,'\n');
        }
        else{
            cltstream::write(cnt);
            cltstream::write(ans,'\n');
        }
    }
    return 0;
}
