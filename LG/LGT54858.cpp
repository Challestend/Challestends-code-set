#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define re register
#define maxn 600

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

const int dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};

int n;
int a[maxn*maxn+1],h[maxn*maxn+1],v[maxn*maxn+1],f[maxn*maxn+1],g[maxn*maxn+1];

inline void bfs(int st){
    int head=0,tail=1;
    h[1]=st;
    v[st]=1;
    f[st]=st;
    for(;head<tail;){
        ++head;
        int x=(h[head]-1)/n+1,y=(h[head]-1)%n+1;
        for(re int i=0;i<4;++i){
            int _x=x+dx[i],_y=y+dy[i],_z=(_x-1)*n+_y;
            if(_x>=1&&_x<=n&&_y>=1&&_y<=n){
                if(a[_z]==a[st]&&!v[_z]){
                    h[++tail]=_z;
                    v[_z]=1;
                    f[_z]=st;
                }
                else
                    g[st]+=(!a[_z]);
            }
        }
    }
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n*n;++i){
        char c=cltstream::gc();
        for(;c!='.'&&c!='X'&&c!='O';c=cltstream::gc());
        if(c=='X')
            a[i]=1;
        if(c=='O')
            a[i]=2;
    }
    for(re int i=1;i<=n*n;++i)
        if(a[i]&&!v[i])
            bfs(i);
    for(re int i=1;i<=n*n;++i)
        if(!a[i]){
            f[i]=i;
            h[++h[0]]=i;
        }
    srand(clock()*time(0)+998244353);
    std::random_shuffle(h+1,h+h[0]+1);
    for(re int i=1;i<=h[0];++i){
        int x=(h[i]-1)/n+1,y=(h[i]-1)%n+1,valid=1;
        a[h[i]]=((i-1)&1)+1;
        for(re int j=0;j<4;++j){
            int _x=x+dx[j],_y=y+dy[j],_z=(_x-1)*n+_y;
            if(_x>=1&&_x<=n&&_y>=1&&_y<=n&&a[f[_z]]&&a[f[_z]]!=a[f[h[i]]]){
                --g[f[_z]];
                if(g[f[_z]]<=0)
                    valid=0;
            }
        }
        for(re int j=0;j<4;++j){
            int _x=x+dx[j],_y=y+dy[j],_z=(_x-1)*n+_y;
            if(_x>=1&&_x<=n&&_y>=1&&_y<=n){
                if(valid){
                    if(!a[_z])
                        ++g[f[h[i]]];
                    else
                        if(a[f[_z]]==a[f[h[i]]]&&f[_z]!=f[h[i]]){
                            g[f[_z]]+=g[f[h[i]]];
                            f[h[i]]=f[_z];
                        }
                }
                else
                    if(a[f[_z]]!=a[f[h[i]]])
                        ++g[f[_z]];
            }
        }
        if(valid){
            cltstream::write(x,32);
            cltstream::write(y,10);
        }
        else
            a[h[i]]=0;
    }
    cltstream::write(-1,32);
    cltstream::write(-1,10);
    clop();
    return 0;
}
