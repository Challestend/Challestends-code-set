#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000

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

int n,m,tp,ec,ans;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int dep[maxn+1],f[maxn+1],v[maxn+1],h[maxn+1],l[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs1(int cur,int ftr){
    dep[cur]=dep[ftr]+1;
    f[cur]=ftr;
    h[cur]=cur;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur])
            dfs1(des[i],cur);
}

inline bool cmp(int x,int y){
    return dep[x]>dep[y];
}

void dfs2(int cur,int dis){
    if(dis>m||m-dis<l[cur])
        return;
    else{
        v[cur]=1;
        l[cur]=m-dis;
        for(re int i=las[cur];i;i=suc[i])
            dfs2(des[i],dis+1);
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(tp);
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    dfs1(1,0);
    std::sort(h+1,h+n+1,cmp);
    for(re int i=1;i<=n;++i)
        if(v[h[i]]==0){
            ++ans;
            int j=h[i];
            for(re int k=1;k<=m;++k,j=f[j]);
            dfs2(j,0);
        }
    cltstream::write(ans,'\n');
    return 0;
}
