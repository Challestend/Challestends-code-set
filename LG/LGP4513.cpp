#include<cstdio>
#define re register
#define maxn 50000
#define max(a,b) ((a)>=(b)?(a):(b))

namespace cltstream{
    #ifdef ONLINE_JUDGE
        #define size 1048576
        char str[size+1],*head=str,*tail=str;
        inline char gc(){
            if(head==tail){
                tail=(head=str)+fread(str,1,size,stdin);
                if(head==tail)
                    return EOF;
            }
            return *head++;
        }
        #undef size
    #else
        #define gc getchar
    #endif

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
    inline void write(_tp x,char text=' '){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m;
long long ms[(maxn<<2)+1],ls[(maxn<<2)+1],rs[(maxn<<2)+1],sum[(maxn<<2)+1];

void update(int L,int x,int cur,int l,int r){
    if(l==r)
        ms[cur]=ls[cur]=rs[cur]=sum[cur]=x;
    else{
        int mid=(l+r)>>1;
        if(L<=mid)
            update(L,x,cur<<1,l,mid);
        else
            update(L,x,cur<<1|1,mid+1,r);
        ms[cur]=max(max(ms[cur<<1],ms[cur<<1|1]),rs[cur<<1]+ls[cur<<1|1]);
        ls[cur]=max(ls[cur<<1],sum[cur<<1]+ls[cur<<1|1]);
        rs[cur]=max(rs[cur<<1|1],sum[cur<<1|1]+rs[cur<<1]);
        sum[cur]=sum[cur<<1]+sum[cur<<1|1];
    }
}

void getmaxsum(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R){
        if(l==L){
            ms[0]=ms[cur];
            ls[0]=ls[cur];
            rs[0]=rs[cur];
            sum[0]=sum[cur];
        }
        else{
            ms[0]=max(max(ms[0],ms[cur]),rs[0]+ls[cur]);
            ls[0]=max(ls[0],sum[0]+ls[cur]);
            rs[0]=max(rs[cur],sum[cur]+rs[0]);
            sum[0]=sum[0]+sum[cur];
        }
    }
    else{
        int mid=(l+r)>>1;
        if(L<=mid)
            getmaxsum(L,R,cur<<1,l,mid);
        if(R>mid)
            getmaxsum(L,R,cur<<1|1,mid+1,r);
    }
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        int x;
        cltstream::read(x);
        update(i,x,1,1,n);
    }
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        int opt,x,y;
        cltstream::read(opt);
        cltstream::read(x);
        cltstream::read(y);
        if(opt==0)
            update(x,y,1,1,n);
        else{
            getmaxsum(x,y,1,1,n);
            cltstream::write(ms[0],'\n');
        }
    }
    return 0;
}
