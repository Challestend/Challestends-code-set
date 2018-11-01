#include<cstdio>
#define re register
#define maxn 100000
#define maxblock 320
#define maxval 100000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,sz;
int a[maxn+1],id[maxn+1],val[maxn+1];
int f[maxn+1],pos[maxblock+1][maxval+1],cnt[maxn+1],maxv[maxblock+1],tag[maxblock+1];

int find(re int x){
    return f[x]==x?x:f[x]=find(f[x]);
}

inline void init(re int x){
    maxv[x]=tag[x]=0;
    for(re int i=(x-1)*sz+1;i<=x*sz&&i<=n;++i)
        if(!pos[x][a[i]]){
            val[i]=a[i];
            f[i]=i;
            pos[x][a[i]]=i;
            cnt[i]=1;
            maxv[x]=max(maxv[x],a[i]);
        }
        else{
            f[i]=pos[x][a[i]];
            ++cnt[pos[x][a[i]]];
        }
}

inline void destory(re int x){
    for(re int i=(x-1)*sz+1;i<=x*sz&&i<=n;++i){
        a[i]=val[find(i)]-tag[x];
        pos[x][val[i]]=0;
    }
}

inline void solve(re int x,re int y){
    if((y<<1)>maxv[x]-tag[x]){
        for(re int i=y+tag[x]+1;i<=maxv[x];++i)
            if(pos[x][i]){
                if(!pos[x][i-y]){
                    pos[x][i-y]=pos[x][i];
                    val[pos[x][i-y]]-=y;
                }
                else{
                    f[pos[x][i]]=pos[x][i-y];
                    cnt[pos[x][i-y]]+=cnt[pos[x][i]];
                }
                pos[x][i]=0;
            }
        maxv[x]=min(maxv[x],y+tag[x]);
    }
    else{
        for(re int i=y+tag[x];i>tag[x];--i)
            if(pos[x][i]){
                if(!pos[x][i+y]){
                    pos[x][i+y]=pos[x][i];
                    val[pos[x][i+y]]+=y;
                }
                else{
                    f[pos[x][i]]=pos[x][i+y];
                    cnt[pos[x][i+y]]+=cnt[pos[x][i]];
                }
                pos[x][i]=0;
            }
        tag[x]+=y;
    }
}

inline void update(re int l,re int r,re int x){
    destory(id[l]);
    for(re int i=l;i<=id[l]*sz&&i<=r;++i)
        if(a[i]>x)
            a[i]-=x;
    init(id[l]);
    for(re int i=id[l]+1;i<=id[r]-1;++i)
        solve(i,x);
    if(id[l]<id[r]){
        destory(id[r]);
        for(re int i=(id[r]-1)*sz+1;i<=r;++i)
            if(a[i]>x)
                a[i]-=x;
        init(id[r]);
    }
}

inline int query(re int l,re int r,re int x){
    re int res=0;
    for(re int i=l;i<=id[l]*sz&&i<=r;++i)
        res+=(val[find(i)]-tag[id[l]]==x);
    for(re int i=id[l]+1;i<=id[r]-1;++i)
        if(x+tag[i]<=maxv[i])
            res+=cnt[pos[i][x+tag[i]]];
    if(id[l]<id[r])
        for(re int i=(id[r]-1)*sz+1;i<=r;++i)
            res+=(val[find(i)]-tag[id[r]]==x);
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(;(sz+1)*(sz+1)<=n;++sz);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        id[i]=(i-1)/sz+1;
    }
    for(re int i=1;i<=id[n];++i)
        init(i);
    for(re int i=1;i<=m;++i){
        re int opt,l,r,x;
        cltstream::read(opt);
        cltstream::read(l);
        cltstream::read(r);
        cltstream::read(x);
        if(opt==1)
            update(l,r,x);
        else
            cltstream::write(query(l,r,x),10);
    }
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
