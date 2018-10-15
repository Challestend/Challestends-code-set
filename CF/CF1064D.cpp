#include<cstdio>
#include<iostream>
#include<string>
#include<queue>
#define re register
#define maxn 2000
#define maxm 2000

namespace cltstream{
    #define gc getchar

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

const int dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};

int n,m,r,c,lt,rt,ans=1;
std::string s;
int a[maxn+1][maxm+1];
struct sta{
    int x,y,lc,rc;

    sta(int _x,int _y,int _lc,int _rc){
        x=_x;
        y=_y;
        lc=_lc;
        rc=_rc;
    }
};
std::queue<sta> h;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(r);
    cltstream::read(c);
    cltstream::read(lt);
    cltstream::read(rt);
    for(re int i=1;i<=n;++i){
        std::cin>>s;
        for(re int j=1;j<=m;++j)
            a[i][j]=(s[j-1]=='.');
    }
    h.push(sta(r,c,0,0));
    a[r][c]=0;
    for(;!h.empty();){
        int x=h.front().x,y=h.front().y,lc=h.front().lc,rc=h.front().rc;
        h.pop();
        for(re int i=0;i<4;++i){
            if(lc==lt&&i==1)
                continue;
            if(rc==rt&&i==2)
                continue;
            int x1=x+dx[i],y1=y+dy[i];
            if(x1>=1&&x1<=n&&y1>=1&&y1<=m&&a[x1][y1]){
                a[x1][y1]=0;
                ++ans;
                h.push(sta(x1,y1,lc+(i==1),rc+(i==2)));
            }
        }
    }
    cltstream::write(ans,'\n');
    return 0;
}
