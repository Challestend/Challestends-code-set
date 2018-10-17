#include<cstdio>
#define re register
#define maxn 300
#define maxm 300
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
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m;
int las[maxn+1],suc[maxn+1],val[maxn+1],size[maxn+1],f[maxn+1][maxm+1],g[maxm+2];

void dfs(int cur){
    f[cur][size[cur]=1]=val[cur];
    for(re int i=las[cur];i;i=suc[i]){
        dfs(i);
        for(re int j=1;j<=size[cur];++j)
            for(re int k=1;k<=size[i]&&j+k<=m+1;++k)
                g[j+k]=max(g[j+k],f[cur][j]+f[i][k]);
        size[cur]=min(size[cur]+size[i],m+1);
        for(re int j=2;j<=size[cur];++j){
            f[cur][j]=max(f[cur][j],g[j]);
            g[j]=0;
        }
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        int x;
        cltstream::read(x);
        suc[i]=las[x];
        las[x]=i;
        cltstream::read(val[i]);
    }
    dfs(0);
    cltstream::write(f[0][m+1],'\n');
    return 0;
}
