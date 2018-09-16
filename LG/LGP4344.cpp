#include<cstdio>
#define re register
#define maxn 800010
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m;
int sum[maxn],ls[maxn],rs[maxn],ms[maxn],upd[maxn];
int LS,RS,MS;

inline void pushDown(int cur,int ln,int rn){
    if(upd[cur]){
        sum[cur<<1]=ln*(upd[cur]-1);
        ls[cur<<1]=rs[cur<<1]=ms[cur<<1]=((upd[cur]-1)^1)*ln;
        upd[cur<<1]=upd[cur];
        sum[cur<<1|1]=rn*(upd[cur]-1);
        ls[cur<<1|1]=rs[cur<<1|1]=ms[cur<<1|1]=((upd[cur]-1)^1)*rn;
        upd[cur<<1|1]=upd[cur];
        upd[cur]=0;
    }
}

inline void pushUp(int cur,int ln,int rn){
    sum[cur]=sum[cur<<1]+sum[cur<<1|1];
    ls[cur]=ls[cur<<1]+(ls[cur<<1]==ln)*ls[cur<<1|1];
    rs[cur]=rs[cur<<1|1]+(rs[cur<<1|1]==rn)*rs[cur<<1];
    ms[cur]=max(max(ms[cur<<1],ms[cur<<1|1]),rs[cur<<1]+ls[cur<<1|1]);
    ms[cur]=max(max(ls[cur],rs[cur]),ms[cur]);
}

void update(int L,int R,int x,int cur,int l,int r){
    if(l>=L&&r<=R){
        sum[cur]=(r-l+1)*x;
        ls[cur]=rs[cur]=ms[cur]=(x^1)*(r-l+1);
        upd[cur]=x+1;
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            update(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update(L,R,x,cur<<1|1,mid+1,r);
        pushUp(cur,mid-l+1,r-mid);
    }
}

int getsum(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return sum[cur];
    else{
        int mid=(l+r)>>1,res=0;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            res+=getsum(L,R,cur<<1,l,mid);
        if(R>mid)
            res+=getsum(L,R,cur<<1|1,mid+1,r);
        return res;
    }
}

void cover(int L,int R,int& x,int cur,int l,int r){
    if(!x)
        return;
    else
        if(l>=L&&r<=R&&r-l-sum[cur]+1<=x){
            x-=r-l-sum[cur]+1;
            sum[cur]=r-l+1;
            ls[cur]=rs[cur]=ms[cur]=0;
            upd[cur]=2;
        }
        else{
            int mid=(l+r)>>1;
            pushDown(cur,mid-l+1,r-mid);
            if(L<=mid)
                cover(L,R,x,cur<<1,l,mid);
            if(R>mid)
                cover(L,R,x,cur<<1|1,mid+1,r);
            pushUp(cur,mid-l+1,r-mid);
        }
}

void getmaxcon(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        if(l==L)
            LS=ls[cur],RS=rs[cur],MS=ms[cur];
        else{
            MS=max(max(MS,ms[cur]),RS+ls[cur]);
            LS=LS+(LS==l-L)*ls[cur];
            RS=rs[cur]+(rs[cur]==r-l+1)*RS;
            MS=max(max(LS,RS),MS);
        }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            getmaxcon(L,R,cur<<1,l,mid);
        if(R>mid)
            getmaxcon(L,R,cur<<1|1,mid+1,r);
    }
}

int main(){
    read(n),read(m);
    update(1,n,1,1,1,n);
    for(re int i=1;i<=m;++i){
        int opt,a,b,c,d,e;
        read(opt);
        switch(opt){
            case 0:
                read(a),read(b);
                update(a,b,0,1,1,n);
                break;
            case 1:
                read(a),read(b),read(c),read(d);
                e=getsum(a,b,1,1,n);
                update(a,b,0,1,1,n);
                cover(c,d,e,1,1,n);
                break;
            case 2:
                read(a),read(b);
                getmaxcon(a,b,1,1,n);
                write(MS);
                putchar(10);
                break;
        }
    }
    return 0;
}
