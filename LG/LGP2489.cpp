#include<cstdio>
#include<iostream>
#include<string>
#include<queue>
#define re register
#define maxn 30
#define maxm 30
#define maxk 5
#define maxsize 243
#define maxh 5
#define max(a,b) ((a)>=(b)?(a):(b))

namespace cltstream{
    #define size 1048576
    #define gc getchar

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

const int dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};

int n,m,k,h,size=1,sx,sy;
std::string str;
int poi[maxk+1],val[maxsize+1][maxk+1];
int a[maxn+1][maxm+1],p[(1<<maxk)+1];
double w[maxsize+1],f[maxn+1][maxm+1][maxsize+1][maxh+1],ans[maxn+1][maxm+1];
int v[maxn+1][maxm+1][maxsize+1][maxh+1];
struct status{
    int x,y,info,hp;

    status(int arg1,int arg2,int arg3,int arg4){
        x=arg1;
        y=arg2;
        info=arg3;
        hp=arg4;
    }
};
std::queue<status> q;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    cltstream::read(h);
    for(re int i=1;i<=k;poi[i]=size,size*=3,++i);
    for(re int i=1;i<size;++i){
        val[i][1]=i%3;
        for(re int j=2;j<=k;++j)
            val[i][j]=val[i/3][j-1];
    }
    for(re int i=1;i<=n;++i){
        std::cin>>str;
        for(re int j=1;j<=m;++j)
            switch(str[j-1]){
                case '.':
                    a[i][j]=0;
                    break;
                case '#':
                    a[i][j]=-1;
                    break;
                case '$':
                    sx=i;
                    sy=j;
                    break;
                case '@':
                    a[i][j]=-1;
                    for(re int l=0;l<size;++l)
                        for(re int r=1;r<=h;++r){
                            f[i][j][l][r]=f[i][j][l][r]=1;
                            q.push(status(i,j,l,r));
                        }
                    break;
                default:
                    a[i][j]=str[j-1]-'A'+1;
                    break;
            }
    }
    for(re int i=0;i<(1<<k);++i){
        cltstream::read(p[i]);
        p[1<<k]+=p[i];
    }
    for(re int i=0;i<size;++i)
        for(re int j=0;j<(1<<k);++j){
            int mat=1;
            for(re int l=1;l<=k&&mat;++l)
                if(val[i][l]<2&&val[i][l]!=((j>>(l-1))&1))
                    mat=0;
            if(mat)
                w[i]+=(double)(p[j])/p[1<<k];
        }
    // for(re int i=0;i<size;++i)
    //     printf("P{%d%d%d}=%lf\n",i/9,i%9/3,i%3,w[i]);
    for(;!q.empty();){
        re int x=q.front().x,y=q.front().y,info=q.front().info,hp=q.front().hp;
        q.pop();
        // printf("P{%d,%d,%d%d%d,%d}=%lf\n",x,y,info/9,info%9/3,info%3,hp,f[x][y][info][hp]);
        for(re int i=0;i<4;++i){
            int _x=x+dx[i],_y=y+dy[i];
            if(_x>=1&&_x<=n&&_y>=1&&_y<=m&&a[_x][_y]!=-1){
                if(!a[_x][_y]&&!v[_x][_y][info][hp]){
                    f[_x][_y][info][hp]+=f[x][y][info][hp];
                    v[_x][_y][info][hp]=1;
                    q.push(status(_x,_y,info,hp));
                }
                if(a[_x][_y]){
                    if(val[info][a[_x][_y]]<2){
                        if(!val[info][a[_x][_y]]&&!v[_x][_y][info][hp]){
                            f[_x][_y][info][hp]+=f[x][y][info][hp];
                            v[_x][_y][info][hp]=1;
                            q.push(status(_x,_y,info,hp));
                        }
                        if(val[info][a[_x][_y]]&&!v[_x][_y][info][hp-1]&&hp>1){
                            f[_x][_y][info][hp-1]+=f[x][y][info][hp];
                            v[_x][_y][info][hp-1]=1;
                            q.push(status(_x,_y,info,hp-1));
                        }
                    }
                    else{
                        if(!v[_x][_y][info-(poi[a[_x][_y]]<<1)][hp]){
                            f[_x][_y][info-(poi[a[_x][_y]]<<1)][hp]+=f[x][y][info][hp]/w[info]*w[info-(poi[a[_x][_y]]<<1)];
                            v[_x][_y][info-(poi[a[_x][_y]]<<1)][hp]=1;
                            q.push(status(_x,_y,info-(poi[a[_x][_y]]<<1),hp));
                        }
                        if(!v[_x][_y][info-poi[a[_x][_y]]][hp-1]&&hp>1){
                            f[_x][_y][info-poi[a[_x][_y]]][hp-1]+=f[x][y][info][hp]/w[info]*w[info-poi[a[_x][_y]]];
                            v[_x][_y][info-poi[a[_x][_y]]][hp-1]=1;
                            q.push(status(_x,_y,info-poi[a[_x][_y]],hp-1));
                        }
                    }
                }
            }
        }
    }
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j)
            if(a[i][j]!=-1){
                for(re int l=0;l<size;++l)
                    for(re int r=1;r<=h;++r){
                        ans[i][j]=max(ans[i][j],f[i][j][l][r]);
                        if(f[i][j][l][r])
                        printf("ANS(%d,%d,%d%d%d,%d)=%lf\n",i,j,l/9,l%9/3,l%3,r,f[i][j][l][r]);
                    }
            }
    return 0;
}
