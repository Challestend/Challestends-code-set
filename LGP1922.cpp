#include<cstdio>
#define re register
#define maxn 100000

template <typename _tp>
inline void read(_tp& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

template <typename _tp>
inline void write(_tp x){
    if(x<0)
        putchar(45),x=-x;
    if(!x)
        putchar(48);
    else{
        int digit[20];
        for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
        for(;digit[0];putchar(digit[digit[0]--]^48));
    }
}

int n,ec;
int des[maxn*2+1],suc[maxn*2+1],las[maxn+1],f[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur,int ftr){
    int cnt=1;
    for(int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr)
            if(suc[las[des[i]]])
                dfs(des[i],cur),f[cur]+=f[des[i]];
            else
                ++cnt;
    f[cur]+=cnt>>1;
}

int main(){
    read(n);
    for(int i=1;i<n;++i){
        int x,y;
        read(x),read(y);
        connect(x,y);
        connect(y,x);
    }
    dfs(1,0);
    write(f[1]);
    return 0;
}
