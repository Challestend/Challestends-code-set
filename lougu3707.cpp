#include<cstdio>
#define re register
#define maxn 100000
#define maxm 100000

int n,m;
long long sum[maxn<<2|1][2],sqrsum[maxn<<2|1],prodsum[maxn<<2|1];
long long add[maxn<<2|1][2],c[maxn<<2|1],upd[maxn<<2|1][2];
double sx,sy,ss,ps,a,b;

inline void read(int& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

inline void pushdown(int cur,int ln,int rn){
    if(c[cur]){
        sqrsum[cur<<1]=1LL*ln*upd[cur][0]*upd[cur][0]+1LL*ln*(ln-1)*upd[cur][0]+1LL*ln*(ln-1)*(2*ln-1)/6;
        sqrsum[cur<<1|1]=1LL*rn*(upd[cur][0]+ln)*(upd[cur][0]+ln)+1LL*rn*(rn-1)*(upd[cur][0]+ln)+1LL*rn*(rn-1)*(2*rn-1)/6;
        prodsum[cur<<1]=1LL*ln*upd[cur][0]*upd[cur][1]+1LL*ln*(ln-1)*(upd[cur][0]+upd[cur][1])/2+1LL*ln*(ln-1)*(2*ln-1)/6;
        prodsum[cur<<1|1]=1LL*rn*(upd[cur][0]+ln)*(upd[cur][1]+ln)+1LL*rn*(rn-1)*(upd[cur][0]+upd[cur][1]+2*ln)/2+1LL*rn*(rn-1)*(2*rn-1)/6;
        for(int i=0;i<2;++i){
            sum[cur<<1][i]=1LL*ln*upd[cur][i]+1LL*ln*(ln-1)/2;
            add[cur<<1][i]=0;
            upd[cur<<1][i]=upd[cur][i];
            sum[cur<<1|1][i]=1LL*rn*(upd[cur][0]+ln)+1LL*rn*(rn-1)/2;
            add[cur<<1|1][i]=0;
            upd[cur<<1|1][i]=upd[cur][0]+ln;
        }
        c[cur<<1]=c[cur<<1|1]=1;
        c[cur]=0;
    }
    if(add[cur][0]||add[cur][1]){
        sqrsum[cur<<1]+=2LL*upd[cur][0]*sum[cur<<1][0]+1LL*ln*upd[cur][0]*upd[cur][0];
        sqrsum[cur<<1|1]+=2LL*upd[cur][0]*sum[cur<<1|1][0]+1LL*rn*upd[cur][0]*upd[cur][0];
        prodsum[cur<<1]+=1LL*upd[cur][0]*sum[cur<<1][1]+1LL*upd[cur][1]*sum[cur<<1][0]+1LL*ln*upd[cur][0]*upd[cur][1];
        prodsum[cur<<1|1]+=1LL*upd[cur][0]*sum[cur<<1|1][1]+1LL*upd[cur][1]*sum[cur<<1|1][0]+1LL*rn*upd[cur][0]*upd[cur][1];
        for(int i=0;i<2;++i){
            sum[cur<<1][i]+=1LL*ln*add[cur][i];
            add[cur<<1][i]+=add[cur][i];
            sum[cur<<1|1][i]+=1LL*rn*add[cur][i];
            add[cur<<1|1][i]+=add[cur][i];
            add[cur][i]=0;
        }
    }
}

inline void pushup(int cur){
    sum[cur][0]=sum[cur<<1][0]+sum[cur<<1|1][0];
    sum[cur][1]=sum[cur<<1][1]+sum[cur<<1|1][1];
    sqrsum[cur]=sqrsum[cur<<1]+sqrsum[cur<<1|1];
    prodsum[cur]=prodsum[cur<<1]+prodsum[cur<<1|1];
}

void build(int L,int x,int tp,int cur,int l,int r){
    if(l==r)
        sum[cur][tp]=x,sqrsum[cur]=1LL*sum[cur][0]*sum[cur][0],prodsum[cur]=1LL*sum[cur][0]*sum[cur][1];
    else{
        int mid=l+r>>1;
        if(L<=mid)
            build(L,x,tp,cur<<1,l,mid);
        else
            build(L,x,tp,cur<<1|1,mid+1,r);
        pushup(cur);
    }
}

void update_add(int L,int R,int x,int y,int cur,int l,int r){
    if(l>=L&&r<=R){
        int curn=r-l+1;
        sqrsum[cur]+=2LL*x*sum[cur][0]+1LL*curn*x*x;
        prodsum[cur]+=1LL*x*sum[cur][1]+1LL*y*sum[cur][0]+1LL*curn*x*y;
        sum[cur][0]+=1LL*curn*x;
        sum[cur][1]+=1LL*curn*y;
        add[cur][0]+=x;
        add[cur][1]+=y;
    }
    else{
        int mid=l+r>>1;
        pushdown(cur,mid-l+1,r-mid);
        if(L<=mid)
            update_add(L,R,x,y,cur<<1,l,mid);
        if(R>mid)
            update_add(L,R,x,y,cur<<1|1,mid+1,r);
        pushup(cur);
    }
}

void update_upd(int L,int R,int x,int y,int cur,int l,int r){
    if(l>=L&&r<=R){
        int curn=r-l+1;
        prodsum[cur]=1LL*curn*x*y+1LL*curn*(curn-1)*(x+y)/2+1LL*(curn)*(curn-1)*(2*curn-1)/6;
        sqrsum[cur]=1LL*curn*x*x+1LL*curn*(curn-1)*x+1LL*curn*(curn-1)*(2*curn-1)/6;
        sum[cur][0]=1LL*curn*x+curn*(curn-1)/2;
        sum[cur][1]=1LL*curn*y+curn*(curn-1)/2;
        add[cur][0]=0;
        add[cur][1]=0;
        c[cur]=1;
        upd[cur][0]=x;
        upd[cur][1]=y;
    }
    else{
        int mid=l+r>>1;
        pushdown(cur,mid-l+1,r-mid);
        if(L<=mid)
            update_upd(L,R,x,y,cur<<1,l,mid);
        if(R>mid)
            update_upd(L,R,x+mid-l+1,y+mid-l+1,cur<<1|1,mid+1,r);
        pushup(cur);
    }
}

void getres(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        sx+=sum[cur][0],sy+=sum[cur][1],ss+=sqrsum[cur],ps+=prodsum[cur];
    else{
        int mid=l+r>>1;
        pushdown(cur,mid-l+1,r-mid);
        if(L<=mid)
            getres(L,R,cur<<1,l,mid);
        if(R>mid)
            getres(L,R,cur<<1|1,mid+1,r);
    }
}

int main(){
    read(n),read(m);
    for(re int i=1;i<=n;++i){
        int x;
        read(x);
        build(i,x,0,1,1,n);
    }
    for(re int i=1;i<=n;++i){
        int x;
        read(x);
        build(i,x,1,1,1,n);
    }
    for(re int i=1;i<=m;++i){
        int opt,l,r,x,y;
        read(opt),read(l),read(r);
        switch(opt){
            case 1:
                sx=sy=ss=ps=0;
                getres(l,r,1,1,n);
                a=ps-sx*sy/(r-l+1),b=ss-sx*sx/(r-l+1);
                printf("%0.10lf\n",a/b);
                break;
            case 2:
                read(x),read(y);
                update_add(l,r,x,y,1,1,n);
                break;
            case 3:
                read(x),read(y);
                update_upd(l,r,x+l,y+l,1,1,n);
                break;
        }
    }
    return 0;
}
