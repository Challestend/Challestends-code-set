#include<cstdio>
#include<algorithm>
#define re register
#define maxn 4
#define maxm 5

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
int a[maxn+1],b[maxn+1],c[maxm+1][maxn+1],rnk[maxn+1],f[maxn+1][maxn+1];

inline bool cmp(int p,int q){
    return a[p]>a[q]||(a[p]==a[q]&&p<q);
}

void dfs(int cur){
    if(cur>m){
        for(re int i=1;i<=n;++i)
            rnk[i]=i;
        std::sort(rnk+1,rnk+n+1,cmp);
        for(re int i=1;i<=n;++i)
            ++f[rnk[i]][i];
    }
    else{
        for(re int i=1;i<=n;++i)
            c[cur][i]=i;
        for(;;){
            for(re int i=1;i<=n;++i)
                a[i]+=b[c[cur][i]];
            dfs(cur+1);
            for(re int i=1;i<=n;++i)
                a[i]-=b[c[cur][i]];
            if(!std::next_permutation(c[cur]+1,c[cur]+n+1))
                break;
        }
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    for(re int i=1;i<=n;++i)
        cltstream::read(b[i]);
    dfs(1);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=n;++j)
            cltstream::write(f[i][j]," \n"[j<n?0:1]);
    return 0;
}
