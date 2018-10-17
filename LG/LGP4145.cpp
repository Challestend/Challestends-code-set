#include<cstdio>
#include<cmath>
#define re register
#define maxn 100000
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
long long sumw[(maxn<<2)+1],maxw[(maxn<<2)+1];

inline void swap(int& x,int& y){
    int tmp=x;
    x=y;
    y=tmp;
}

void build(int cur,int l,int r){
    if(l==r){
        cltstream::read(sumw[cur]);
        maxw[cur]=sumw[cur];
    }
    else{
        int mid=(l+r)>>1;
        build(cur<<1,l,mid);
        build(cur<<1|1,mid+1,r);
        sumw[cur]=sumw[cur<<1]+sumw[cur<<1|1];
        maxw[cur]=max(maxw[cur<<1],maxw[cur<<1|1]);
    }
}

void update(int L,int R,int cur,int l,int r){
    if(l==r)
        sumw[cur]=maxw[cur]=sqrt(sumw[cur]);
    else{
        int mid=(l+r)>>1;
        if(L<=mid&&maxw[cur<<1]>1)
            update(L,R,cur<<1,l,mid);
        if(R>mid&&maxw[cur<<1|1]>1)
            update(L,R,cur<<1|1,mid+1,r);
        sumw[cur]=sumw[cur<<1]+sumw[cur<<1|1];
        maxw[cur]=max(maxw[cur<<1],maxw[cur<<1|1]);
    }
}

long long getsum(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return sumw[cur];
    else{
        int mid=(l+r)>>1;
        long long res=0;
        if(L<=mid)
            res+=getsum(L,R,cur<<1,l,mid);
        if(R>mid)
            res+=getsum(L,R,cur<<1|1,mid+1,r);
        return res;
    }
}

int main(){
    for(re int cnt=1;;++cnt){
        cltstream::read(n);
        if(!n)
            break;
        printf("Case #%d:\n",cnt);
        build(1,1,n);
        cltstream::read(m);
        for(re int i=1;i<=m;++i){
            int opt,l,r;
            cltstream::read(opt);
            cltstream::read(l);
            cltstream::read(r);
            if(l>r)
                swap(l,r);
            if(opt==0)
                update(l,r,1,1,n);
            else
                cltstream::write(getsum(l,r,1,1,n),'\n');
        }
        putchar(10);
    }
    return 0;
}
