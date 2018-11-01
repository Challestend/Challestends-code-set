#include<cstdio>
#define re register
#define maxn 250000

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

int m;
long long sum[(maxn<<2)+1],inc[(maxn<<2)+1],ind[(maxn<<2)+1];
long long dec[(maxn<<2)+1],ded[(maxn<<2)+1],upd[(maxn<<2)+1],c[(maxn<<2)+1];

inline void pushDown(int cur,int ln,int rn){
    if(upd[cur]){
        sum[cur<<1]=1LL*ln*c[cur];
        inc[cur<<1]=ind[cur<<1]=dec[cur<<1]=ded[cur<<1]=0;
        upd[cur<<1]=1;
        c[cur<<1]=c[cur];
        sum[cur<<1|1]=1LL*rn*c[cur];
        inc[cur<<1|1]=ind[cur<<1|1]=dec[cur<<1|1]=ded[cur<<1|1]=0;
        upd[cur<<1|1]=1;
        c[cur<<1|1]=c[cur];
        upd[cur]=0;
    }
    sum[cur<<1]+=1LL*ln*inc[cur]+(1LL*ln*(ln-1)*ind[cur]>>1);
    sum[cur<<1]+=1LL*ln*dec[cur]-(1LL*ln*(ln-1)*ded[cur]>>1);
    inc[cur<<1]+=inc[cur];
    ind[cur<<1]+=ind[cur];
    dec[cur<<1]+=dec[cur];
    ded[cur<<1]+=ded[cur];
    inc[cur]+=1LL*ln*ind[cur];
    dec[cur]-=1LL*ln*ded[cur];
    sum[cur<<1|1]+=1LL*rn*inc[cur]+(1LL*rn*(rn-1)*ind[cur]>>1);
    sum[cur<<1|1]+=1LL*rn*dec[cur]-(1LL*rn*(rn-1)*ded[cur]>>1);
    inc[cur<<1|1]+=inc[cur];
    ind[cur<<1|1]+=ind[cur];
    dec[cur<<1|1]+=dec[cur];
    ded[cur<<1|1]+=ded[cur];
    inc[cur]=ind[cur]=dec[cur]=ded[cur]=0;
}

void optA(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R){
        sum[cur]+=(1LL*(r-L+1)*(r-L+2)>>1)-(1LL*(l-L+1)*(l-L)>>1);
        inc[cur]+=l-L+1;
        ++ind[cur];
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            optA(L,R,cur<<1,l,mid);
        if(R>mid)
            optA(L,R,cur<<1|1,mid+1,r);
        sum[cur]=sum[cur<<1]+sum[cur<<1|1];
    }
}

void optB(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R){
        sum[cur]+=(1LL*(R-l+1)*(R-l+2)>>1)-(1LL*(R-r+1)*(R-r)>>1);
        dec[cur]+=R-l+1;
        ++ded[cur];
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            optB(L,R,cur<<1,l,mid);
        if(R>mid)
            optB(L,R,cur<<1|1,mid+1,r);
        sum[cur]=sum[cur<<1]+sum[cur<<1|1];
    }
}

void optC(int L,int R,int x,int cur,int l,int r){
    if(l>=L&&r<=R){
        sum[cur]=1LL*(r-l+1)*x;
        inc[cur]=ind[cur]=dec[cur]=ded[cur]=0;
        upd[cur]=1;
        c[cur]=x;
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            optC(L,R,x,cur<<1,l,mid);
        if(R>mid)
            optC(L,R,x,cur<<1|1,mid+1,r);
        sum[cur]=sum[cur<<1]+sum[cur<<1|1];
    }
}

long long optS(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return sum[cur];
    else{
        int mid=(l+r)>>1;
        long long res=0;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            res+=optS(L,R,cur<<1,l,mid);
        if(R>mid)
            res+=optS(L,R,cur<<1|1,mid+1,r);
        return res;
    }
}

int main(){
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        char opt=cltstream::gc();
        for(;opt<'A'||opt>'Z';opt=cltstream::gc());
        int l,r,x;
        cltstream::read(l);
        cltstream::read(r);
        switch(opt){
            case 'A':
                optA(l,r,1,1,maxn);
                break;
            case 'B':
                optB(l,r,1,1,maxn);
                break;
            case 'C':
                cltstream::read(x);
                optC(l,r,x,1,1,maxn);
                break;
            case 'S':
                cltstream::write(optS(l,r,1,1,maxn),10);
                break;
        }
    }
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
