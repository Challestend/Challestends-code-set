#include<cstdio>
#define maxn 100000
#define maxm 200000
using namespace std;

int n,m,s,ec;
int des[maxm+1],len[maxm+1],suc[maxm+1],las[maxn+1];
int h[maxn+1],f[maxn+1],dis[maxn+1];

int read(){
    int sn=1,x=0;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45){
        sn=-1;
        c=getchar();
    }
    for(;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    return sn*x;
}

void write(int x){
    if(x<0){
        putchar(45);
        x=-x;
    }
    if(x>=10)
        write(x/10);
    putchar(x%10^48);
}

void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void swap(int& x,int& y){
    int tmp=x;
    x=y;
    y=tmp;
    tmp=f[x];
    f[x]=f[y];
    f[y]=tmp;
}

void push(int x){
    if(!f[x]){
        h[++h[0]]=x;
        f[x]=h[0];
    }
    for(int p=f[x],q=p>>1;q>=1;)
        if(dis[h[p]]<dis[h[q]]){
            swap(h[p],h[q]);
            p=q;
            q=p>>1;
        }
        else
            break;
}

int pop(){
    int res=h[1];
    f[res]=0;
    f[h[1]=h[h[0]--]]=1;
    for(int p=1,q=p<<1;q<=h[0];){
        if(q<h[0]&&dis[h[q+1]]<dis[h[q]])
            ++q;
        if(dis[h[p]]>dis[h[q]]){
            swap(h[p],h[q]);
            p=q;
            q=p<<1;
        }
        else
            break;
    }
    return res;
}

int main(){
    n=read(),m=read(),s=read();
    for(int i=1;i<=m;++i){
        int x=read(),y=read(),z=read();
        connect(x,y,z);
    }
    for(int i=1;i<=n;++i)
        dis[i]=2e9;
    dis[s]=0;
    push(s);
    for(int i=1;i<=n;++i){
        int x=pop();
        for(int j=las[x];j;j=suc[j])
            if(dis[des[j]]>dis[x]+len[j]){
                dis[des[j]]=dis[x]+len[j];
                push(des[j]);
            }
    }
    for(int i=1;i<=n;++i)
        write(dis[i]),putchar(32);
    return 0;
}
