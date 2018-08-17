#include<cstdio>
#define maxn 100000
#define maxm 100000

int n,m;
long long dis[maxn<<2|1],sum[maxn<<2|1],cost[maxn<<2|1];
int add[maxn<<2|1];
long long d,s,c,cnt,g;

void read(int& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

void write(long long x){
    int digit[20];
    for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
    if(!digit[0])
        putchar(48);
    else
        for(;digit[0];putchar(digit[digit[0]--]^48));
}

void pushdown(int cur,int ln,int rn){
    dis[cur<<1]+=1LL*ln*add[cur];
    sum[cur<<1]+=1LL*ln*(ln+1)*add[cur]/2;
    cost[cur<<1]+=1LL*ln*(ln*ln+3*ln+2)*add[cur]/6;
    add[cur<<1]+=add[cur];
    dis[cur<<1|1]+=1L*rn*add[cur];
    sum[cur<<1|1]+=1LL*rn*(rn+1)*add[cur]/2;
    cost[cur<<1|1]+=1LL*rn*(rn*rn+3*rn+2)*add[cur]/6;
    add[cur<<1|1]+=add[cur];
    add[cur]=0;
}

void update(int L,int R,int x,int cur,int l,int r){
    if(l>=L&&r<=R){
        int curn=r-l+1;
        dis[cur]+=1LL*curn*x;
        sum[cur]+=1LL*curn*(curn+1)*x/2;
        cost[cur]+=1LL*curn*(curn*curn+3*curn+2)*x/6;
    }
    else{
        int mid=l+r>>1,ln=mid-l+1,rn=l-mid;
        pushdown(cur,ln,rn);
        if(L<=mid)
            update(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update(L,R,x,cur<<1|1,mid+1,r);
        cost[cur]=cost[cur<<1]+cost[cur<<1|1]+ln*sum[cur<<1|1]-rn*sum[cur<<1];
        sum[cur]=sum[cur<<1]+sum[cur<<1|1]+rn*dis[cur<<1];
        dis[cur]=dis[cur<<1]+dis[cur<<1|1];
    }
}

void getcost(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R){
        c+=cost[cur]+(r-l+1)*s-(l-L)*sum[cur];
        s+=sum[cur]+(r-l+1)*dis[cur];
        d+=dis[cur];
    }
    else{
        int mid=l+r>>1;
        pushdown(cur,mid-l+1,r-mid);
        if(L<=mid)
            getcost(L,R,cur<<1|1,l,mid);
        if(R>mid)
            getcost(L,R,cur<<1|1,mid+1,r);
    }
}

long long gcd(long long a,long long b){
    return b?gcd(b,a%b):a;
}

int main(){
    read(n),read(m);
    for(int i=1;i<=m;++i){
        char opt=getchar();
        for(;opt<'A'||opt>'Z';opt=getchar());
        int x,y,z;
        read(x),read(y),--y;
        if(opt=='C')
            read(z),
            update(x,y,c,1,1,n);
        else
            d=s=c=0,
            getcost(x,y,1,1,n),
            cnt=1LL*(y-x+1)*(y-x+2)/2,
            g=gcd(c,cnt),
            write(c/g),
            putchar('/'),
            write(cnt/g),
            putchar(10);
    }
    return 0;
}
