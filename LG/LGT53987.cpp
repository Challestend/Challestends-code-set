#include<cstdio>
#include<queue>
#define re register
#define maxn 100000
#define maxm 200000
#define mod 19260817
#define htp std::pair<std::pair<long long,long long>,int>
#define mp(a,b) std::make_pair(a,b)
#define F first
#define S second

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
        if(c==-1)
            fwrite(cltout,1,oh-cltout,stdout);
        else{
            if(oh==ot){
                fwrite(cltout,1,size,stdout);
                oh=cltout;
            }
            *oh++=c;
        }
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
    inline void write(_tp x,char text=' '){
        if(x<0)
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        pc(text);
    }
}

int n,m,c1,c2,ec;
int des[(maxm<<1)+1],len[(maxm<<1)+1],suc[(maxm<<1)+1],las[maxn+1];
long long dis1[maxn+1],dis2[maxn+1];
std::priority_queue<htp,std::vector<htp >,std::greater<htp > > h;
int ind[maxn+1],f[maxn+1],cnt[maxn+1];

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(c1);
    cltstream::read(c2);
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        connect(x,y,z);
        connect(y,x,z);
    }
    for(re int i=1;i<=n;++i)
        dis1[i]=dis2[i]=4e18;
    h.push(mp(mp(dis1[1]=0,dis2[1]),1));
    for(;;){
        for(;!h.empty()&&(h.top().F.F>dis1[h.top().S]||h.top().F.S>dis2[h.top().S]);h.pop());
        if(h.empty())
            break;
        int x=h.top().S;
        h.pop();
        for(re int i=las[x];i;i=suc[i]){
            long long d1=dis1[des[i]],d2=dis2[des[i]];
            if(dis1[des[i]]>dis1[x]+len[i]){
                dis2[des[i]]=dis1[des[i]];
                dis1[des[i]]=dis1[x]+len[i];
            }
            if(dis1[des[i]]<dis1[x]+len[i]&&dis2[des[i]]>dis1[x]+len[i])
                dis2[des[i]]=dis1[x]+len[i];
            if(dis1[des[i]]<dis2[x]+len[i]&&dis2[des[i]]>dis2[x]+len[i])
                dis2[des[i]]=dis2[x]+len[i];
            if(dis1[des[i]]<d1||dis2[des[i]]<d2)
                h.push(mp(mp(dis1[des[i]],dis2[des[i]]),des[i]));
        }
    }
    for(re int i=1;i<=n;++i)
        for(re int j=las[i];j;j=suc[j])
            if(dis1[i]+len[j]==dis1[des[j]])
                ++ind[des[j]];
    cnt[f[1]=1]=1;
    for(re int head=0,tail=1;head<tail;){
        int x=f[++head];
        for(re int i=las[x];i;i=suc[i])
            if(dis1[x]+len[i]==dis1[des[i]]){
                --ind[des[i]];
                (cnt[des[i]]+=cnt[x])%=mod;
                if(!ind[des[i]])
                    f[++tail]=des[i];
            }
    }
    cltstream::write((1LL*c1*cnt[n]%mod+1LL*c2*dis2[n]%mod)%mod,'\n');
    cltstream::pc(-1);
    return 0;
}
