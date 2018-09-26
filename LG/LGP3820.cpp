#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxsize 1000000
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m,q;
std::string s;
int a[maxsize+1],h[maxsize+1],f[maxsize+1],g[maxsize+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        std::cin>>s;
        for(re int j=1;j<=m;++j)
            a[(i-1)*m+j]=(s[j-1]=='.');
    }
    for(re int i=1;i<=n*m;++i)
        if(!f[i]){
            f[i]=i;
            if(a[i]){
                g[i]=1;
                h[1]=i;
                for(re int head=0,tail=1;head<tail;){
                    int x=h[++head];
                    for(re int j=0;j<4;++j){
                        if(j==0&&(x-1)/m+1==1)
                            continue;
                        if(j==1&&(x-1)%m+1==1)
                            continue;
                        if(j==2&&(x-1)/m+1==n)
                            continue;
                        if(j==3&&(x-1)%m+1==n)
                            continue;
                        int y=x+dx[j]*m+dy[j];
                        if(a[y]&&!f[y]){
                            ++g[i];
                            f[y]=i;
                            h[++tail]=y;
                        }
                    }
                }
            }
        }
    cltstream::read(q);
    for(re int i=1;i<=q;++i){
        int opt,w,x,y,maxa=-1,ans=0;
        cltstream::read(opt);
        cltstream::read(w);
        for(re int j=1;j<=w;++j){
            cltstream::read(x);
            cltstream::read(y);
            x=(x-1)*m+y;
            if(opt==1){
                if(maxa<g[f[x]]){
                    ans=j;
                    maxa=g[f[x]];
                }
            }
            else
                if(a[x]){
                    if(f[x]!=x){
                        --g[f[x]];
                        a[x]=0;
                        f[x]=x;
                    }
                    else{
                        for(re int k=0;k<4;++k){
                            y=x+dx[k]*m+dy[k];
                            if(y>=1&&y<=n*m&&a[y]){
                                a[x]=1;
                                f[x]=f[y];
                                ++g[f[x]];
                                break;
                            }
                        }
                    }
                }
                else{
                    a[x]=1;
                    f[x]=x;
                    g[x]=1;
                    for(re int k=0;k<4;++k){
                        y=x+dx[k]*m+dy[k];
                        if(y>=1&&y<=n*m&&a[y]){
                            f[x]=f[y];
                            ++g[f[x]];
                            break;
                        }
                    }
                }
        }
        if(opt==1){
            cltstream::write(ans);
            putchar(10);
        }
    }
    return 0;
}
