#include<cstdio>
#define re register
#define maxn 200
#define maxm 200
#define min(a,b) ((a)<=(b)?(a):(b))

namespace cltstream{
    #define size 1048576
    char cltin[size+1],*ih=cltin,*it=cltin;
    inline char gc(){
        #ifdef ONLINE_JUDGE
            if(ih==it){
                it=(ih=cltin)+fread(cltin,1,size,stdin);
                if(ih==it)
                    return EOF;
            }
            return *ih++;
        #else
            return getchar();
        #endif
    }

    char cltout[size+1],*oh=cltout,*ot=cltout+size;
    inline void pc(char c){
        if(oh==ot){
            fwrite(cltout,1,size,stdout);
            oh=cltout;
        }
        *oh++=c;
    }
    #undef size

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
    inline void write(_tp x,char text=-1){
        if(x<0)
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        if(text>=0)
            pc(text);
    }
}

const int dx[8]={-1,-1,-1,0,0,1,1,1},dy[8]={-1,0,1,-1,1,-1,0,1};

int n,m,maxA,curA,curW,t;
int a[maxn+1][maxm+1],b[maxn+1][maxm+1];

inline void solve(){
    for(re int i=1;i<=t;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        if(b[x][y]!=1){
            cltstream::write(-1,32);
            cltstream::write(-1);
            return;
        }
        if(a[x][y])
            curA=min(curA+a[x][y],maxA);
        else{
            if(curA<10){
                cltstream::write(-1,32);
                cltstream::write(-1);
                return;
            }
            else{
                curA-=10;
                curW+=10;
            }
        }
        b[x][y]=2;
        for(re int j=0;j<8;++j)
            if(x+dx[j]>=1&&x+dx[j]<=n&&y+dy[j]>=1&&y+dy[j]<=m&&b[x+dx[j]][y+dy[j]]==0)
                b[x+dx[j]][y+dy[j]]=1;
    }
    cltstream::write(curA,32);
    cltstream::write(curW);
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(maxA);
    curA=maxA;
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j)
            cltstream::read(a[i][j]);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j)
            cltstream::read(b[i][j]);
    cltstream::read(t);
    solve();
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
