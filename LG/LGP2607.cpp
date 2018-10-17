#include<cstdio>
#define re register
#define maxn 1000000
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,head,tail;
int nxt[maxn+1],pre[maxn+1],ind[maxn+1],crc[maxn+1],h[maxn+1];
long long f[maxn+1][2][2],ans;

inline void dp(int root,int cur,int dir){
    for(crc[cur]=0;cur!=root;crc[cur]=0){
        int x=dir?pre[cur]:nxt[cur];
        f[x][0][dir]+=max(f[cur][0][dir],f[cur][1][dir]);
        f[x][1][dir]+=f[cur][0][dir];
        cur=x;
    }
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(f[i][1][0]);
        cltstream::read(nxt[i]);
        ++ind[nxt[i]];
        crc[i]=1;
    }
    for(re int i=1;i<=n;++i)
        if(!ind[i]){
            crc[i]=0;
            h[++tail]=i;
        }
    for(;head<tail;){
        int x=h[++head];
        f[nxt[x]][0][0]+=max(f[x][0][0],f[x][1][0]);
        f[nxt[x]][1][0]+=f[x][0][0];
        if(!(--ind[nxt[x]]))
            crc[h[++tail]=nxt[x]]=0;
    }
    for(re int i=1;i<=n;++i)
        if(crc[i]){
            pre[nxt[i]]=i;
            f[i][0][1]=f[i][0][0];
            f[i][1][1]=f[i][1][0];
        }
    for(re int i=1;i<=n;++i)
        if(crc[i]){
            dp(pre[i],i,0);
            dp(i,pre[i],1);
            ans+=max(f[pre[i]][0][0],f[i][0][1]);
        }
    cltstream::write(ans,'\n');
    return 0;
}
