#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 200
#define maxm 200
#define maxc 20

namespace cltstream{
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
}

const int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};

int n,m,c,k,x,y;
std::string s[maxn+1],opt[maxc+1];
std::pair<int,int> a[maxn+1][maxm+1];
int alive[maxc+1],hx[maxc+1],hy[maxc+1],len[maxc+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=1;i<=n;++i){
        std::cin>>s[i];
        for(re int j=1;j<=m;++j)
            switch(s[i][j-1]){
                case '.':
                    a[i][j]=std::make_pair(0,0);
                    break;
                case '&':
                    a[i][j]=std::make_pair(0,1);
                    break;
                case '@':
                    a[i][j]=std::make_pair(++c,0);
                    hx[c]=i;
                    hy[c]=j;
                    len[c]=1;
                    break;
                case '#':
                    a[i][j]=std::make_pair(-1,0);
                    break;
            }
    }
    for(re int i=1,j;i<=c;++i){
        x=hx[i],y=hy[i];
        for(j=0;j<4;)
            for(;j<4;++j){
                int x0=x+dx[j],y0=y+dy[j];
                if(x0>=1&&x0<=n&&y0>=1&&y0<=m&&a[x0][y0].first==-1){
                    ++len[i];
                    x=x0;
                    y=y0;
                    a[x][y]=std::make_pair(i,1-len[i]);
                    break;
                }
            }
    }
    for(re int i=1;i<=n;++i){
        for(re int j=1;j<=m;++j)
            printf("%d ",a[i][j].first);
        printf("\n");
    }
    printf("\n");
    for(re int i=1;i<=n;++i){
        for(re int j=1;j<=m;++j)
            printf("%d ",a[i][j].second);
        printf("\n");
    }
    printf("\n");
    for(re int j=1;j<=n;++j){
        for(re int k=1;k<=m;++k)
            if(a[j][k].first){
                if(a[j][k].second==0)
                    putchar('@');
                else
                    putchar('#');
            }
            else
                putchar(a[j][k].second?'&':'.');
        putchar(10);
    }
    putchar(10);
    for(re int i=1;i<=c;++i){
        std::cin>>opt[i];
        alive[i]=1;
    }
    for(re int i=1;i<=k;++i){
        for(re int j=1;j<=c;++j)
            if(alive[j]){
                switch(opt[j][i-1]){
                    case 'W':
                        x=hx[j]+dx[0];
                        y=hy[j]+dy[0];
                        break;
                    case 'A':
                        x=hx[j]+dx[1];
                        y=hy[j]+dy[1];
                        break;
                    case 'S':
                        x=hx[j]+dx[2];
                        y=hy[j]+dy[2];
                        break;
                    case 'D':
                        x=hx[j]+dx[3];
                        y=hy[j]+dx[3];
                        break;
                }
                printf("%d(%d,%d)->(%d,%d)\n",j,hx[j],hy[j],x,y);
                int z=a[x][y].first,w=a[x][y].second;
                if(z){
                    if(alive[z]){
                        if(i-w-(j<z)<len[z])
                            alive[j]=0;
                        else
                            a[hx[j]=x][hy[j]=y]=std::make_pair(j,i);
                    }
                    else{
                        a[hx[j]=x][hy[j]=y]=std::make_pair(j,i);
                        ++len[j];
                    }
                }
                else{
                    a[hx[j]=x][hy[j]=y]=std::make_pair(j,i);
                    if(w){
                        ++len[j];
                        a[x][y]=std::make_pair(0,0);
                    }
                }
            }
        for(re int j=1;j<=n;++j){
            for(re int k=1;k<=m;++k)
                if(a[j][k].first){
                    if(alive[a[j][k].first]){
                        if(a[j][k].second==i)
                            putchar('@');
                        else
                            if(i-a[j][k].second<len[a[j][k].first])
                                putchar('#');
                            else
                                putchar('.');
                    }
                    else
                        putchar('&');
                }
                else
                    putchar(a[j][k].second?'&':'.');
            putchar(10);
        }
        putchar(10);
    }
    for(re int i=1;i<=c;++i){
        cltstream::write(i);
        putchar(32);
        cltstream::write(alive[i]*len[i]);
        putchar(10);
    }
    return 0;
}
