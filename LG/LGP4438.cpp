#include<cstdio>
#define re register
#define maxn 20000

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

int n;
int s[maxn+1],t[maxn+1],a[(maxn<<1)+1],b[(maxn<<1)+1];
long long c[(maxn<<1)+1];
int cnt[(maxn<<1)+1][2][2];
long long f[(maxn<<1)+1][2];

void dfs(int cur){
    if(cur<n){
        dfs(s[cur]);
        dfs(t[cur]);
        a[cur]=a[s[cur]]+a[t[cur]];
        b[cur]=b[s[cur]]+b[t[cur]];
        c[cur]=c[s[cur]]+c[t[cur]];
        cnt[cur][0][0]=cnt[cur][1][0]=cnt[s[cur]][0]+cnt[t[cur]][0];
        cnt[cur][0][1]=cnt[cur][1][1]=cnt[s[cur]][1]+cnt[t[cur]][1];
        f[cur][0]=f[cur][1]+=f[s[cur]]+f[t[cur]];
        if(c[t[cur]]*(a[t[cur]]+cnt[t[cur]][0])<=c[s[cur]]*(b[s[cur]]+cnt[s[cur]][1])){
            f[cur]+=c[t[cur]]*(a[t[cur]]+cnt[t[cur]][0]);
            ++cnt[cur][1];
        }
        else{
            f[cur]+=c[s[cur]]*(b[s[cur]]+cnt[s[cur]][1]);
            ++cnt[cur][0];
        }
    }
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<n;++i){
        cltstream::read(s[i]);
        if(s[i]<0)
            s[i]=n-s[i]-1;
        cltstream::read(t[i]);
        if(t[i]<0)
            t[i]=n-t[i]-1;
    }
    for(re int i=1;i<=n;++i){
        cltstream::read(a[n+i-1]);
        cltstream::read(b[n+i-1]);
        cltstream::read(c[n+i-1]);
        f[n+i-1][0]=f[n+i-1][1]=c[n+i-1]*a[n+i-1]*b[n+i-1];
    }
    dfs(1);
    for(re int i=1;i<n;++i)
        printf("f[%d]=%I64d(%d,%d)\n",i,f[i],cnt[i][0],cnt[i][1]);
    return 0;
}
