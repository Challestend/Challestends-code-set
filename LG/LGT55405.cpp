#include<cstdio>
#include<algorithm>
#define re register
#define maxn 1000
#define maxm 1000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define mp(a,b) std::make_pair(a,b)

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
    #define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout)
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

const int dx[2]={0,1},dy[2]={1,0};

int n,m;
int a[maxn+1][maxm+1],maxt[maxn+1][maxm+1][2],mint[maxn+1][maxm+1][2];
std::pair<std::pair<int,int>,int> h[5*maxn*maxm+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j){
            char c=cltstream::gc();
            for(;c!='o'&&c!='#';c=cltstream::gc());
            a[i][j]=(c=='#');
            maxt[i][j][0]=maxt[i][j][1]=-2e9;
            mint[i][j][0]=mint[i][j][1]=2e9;
        }
    maxt[1][2][0]=mint[1][2][0]=maxt[2][1][1]=mint[2][1][1]=0;
    if(!a[1][1]&&!a[1][2])
        h[1]=mp(mp(1,2),0);
    if(!a[1][1]&&!a[2][1])
        h[2]=mp(mp(2,1),1);
    for(re int head=0,tail=2;head!=tail;){
        head=head%(n*m)+1;
        re int x=h[head].first.first,y=h[head].first.second,dir=h[head].second;
        re int _x=x+dx[dir],_y=y+dy[dir];
        if(_x<=n&&_y<=m&&!a[_x][_y]&&
            (maxt[_x][_y][dir]<maxt[x][y][dir]||mint[_x][_y][dir]>mint[x][y][dir])){
            maxt[_x][_y][dir]=max(maxt[_x][_y][dir],maxt[x][y][dir]);
            mint[_x][_y][dir]=min(maxt[_x][_y][dir],mint[x][y][dir]);
            h[tail=tail%(n*m)+1]=mp(mp(_x,_y),dir);
        }
        _x=x+dx[dir^1];
        _y=y+dy[dir^1];
        if(_x<=n&&_y<=m&&!a[_x][_y]&&
            (maxt[_x][_y][dir^1]<maxt[x][y][dir]+1||mint[_x][_y][dir^1]>mint[x][y][dir]+1)){
            maxt[_x][_y][dir^1]=max(maxt[_x][_y][dir^1],maxt[x][y][dir]+1);
            mint[_x][_y][dir^1]=min(mint[_x][_y][dir^1],mint[x][y][dir]+1);
            h[tail=tail%(n*m)+1]=mp(mp(_x,_y),dir^1);
        }
    }
    if(max(maxt[n][m][0],maxt[n][m][1])==-2e9)
        cltstream::write(-1);
    else{
        cltstream::write(max(maxt[n][m][0],maxt[n][m][1]),32);
        cltstream::write(min(mint[n][m][0],mint[n][m][1]));
    }
    clop();
    return 0;
}
