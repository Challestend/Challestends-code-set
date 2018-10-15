#include<cstdio>
#define re register
#define maxn 100000
#define maxm 100000
#define maxlog 16

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
int lg[maxn+1],ch[maxn+1][2],dep[maxn+1],f[maxn+1][maxlog+1];

void dfs(int cur){
    if(!cur)
        return;
    dep[cur]=dep[f[cur][0]]+1;
    for(re int i=1;f[cur][i-1]&&f[f[cur][i-1]][i-1];++i)
        f[cur][i]=f[f[cur][i-1]][i-1];
    dfs(ch[cur][0]);
    dfs(ch[cur][1]);
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=2;i<=n;++i)
        lg[i]=lg[i>>1]+1;
    for(re int i=1;i<=n;++i){
        int x;
        cltstream::read(x);
        if(x){
            cltstream::read(ch[i][0]);
            cltstream::read(ch[i][1]);
            f[ch[i][0]][0]=f[ch[i][1]][0]=i;
        }
    }
    dfs(1);
    for(re int i=1;i<=m;++i){
        int x,y,_x,_y;
        cltstream::read(x);
        cltstream::read(y);
        if(dep[x]<=dep[y]){
            _x=x;
            _y=y;
        }
        else{
            _x=y;
            _y=x;
        }
        int h=dep[_y]-dep[_x];
        for(;h;){
            int _h=h&(-h);
            _y=f[_y][lg[_h]];
            h-=_h;
        }
        if(_x!=_y){
            for(re int j=maxlog;j>=0&&f[_x][0]!=f[_y][0];--j)
                if(f[_x][j]!=f[_y][j]){
                    _x=f[_x][j];
                    _y=f[_y][j];
                }
            _x=f[_x][0];
        }
        if(_x==x)
            puts("1.000");
        else
            if(_x==y)
                puts("0.000");
            else
                puts("0.500");
    }
    return 0;
}
