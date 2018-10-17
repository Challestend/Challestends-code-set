#include<cstdio>
#define re register
#define maxn 200000

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

int n,ec;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
long long evesum[maxn+1],oddsum[maxn+1];
int evecnt[maxn+1],oddcnt[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs1(int cur,int ftr){
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            dfs1(des[i],cur);
            evesum[cur]+=oddsum[des[i]]+oddcnt[des[i]];
            evecnt[cur]+=oddcnt[des[i]];
            oddsum[cur]+=evesum[des[i]]+evecnt[des[i]]+1;
            oddcnt[cur]+=evecnt[des[i]]+1;
        }
}

void dfs2(int cur,int ftr){
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            evesum[des[i]]=oddsum[cur]+oddcnt[cur]-(evecnt[des[i]]<<1)-2;
            evecnt[des[i]]=oddcnt[cur]-1;
            oddsum[des[i]]=evesum[cur]+evecnt[cur]-(oddcnt[des[i]]<<1)+1;
            oddcnt[des[i]]=evecnt[cur]+1;
            dfs2(des[i],cur);
        }
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    dfs1(1,0);
    dfs2(1,0);
    long long ans=0;
    for(re int i=1;i<=n;++i)
        ans+=(evesum[i]+oddsum[i]+oddcnt[i])>>1;
    cltstream::write(ans>>1,'\n');
    return 0;
}
