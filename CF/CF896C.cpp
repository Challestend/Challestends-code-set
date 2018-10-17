#include<cstdio>
#include<algorithm>
#include<set>
#define re register
#define maxn 100000
#define _it std::set<node>::iterator

namespace cltstream{
    #define size 1048576
    char input[size+1],*input_head=input,*input_tail=input;
    inline char gc(){
        #ifdef ONLINE_JUDGE
            if(input_head==input_tail){
                input_tail=(input_head=input)+fread(input,1,size,stdin);
                if(input_head==input_tail)
                    return EOF;
            }
            return *input_head++;
        #else
            return getchar();
        #endif
    }

    char output[size+1],*output_head=output,*output_tail=output+size;
    inline void pc(char x){
        if(x==-1)
            fwrite(output,1,output_head-output,stdout);
        else{
            if(output_head==output_tail)
                fwrite(output_head=output,1,size,stdout);
            *output_head++=x;
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
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        pc(text);
    }
}

int n,m,seed,maxval;
struct node{
    int l,r;
    mutable long long val;

    node(re int _l,re int _r=-1,re long long _val=-1){
        l=_l,
        r=_r,
        val=_val;
    }
};
std::set<node> s;
std::pair<long long,int> vec[maxn+1];

inline int rnd(){
    re int res=seed;
    seed=(7LL*seed+13)%1000000007;
    return res;
}

inline void swap(re int& l,re int& r){
    re int tmp=l;
    l=r,
    r=tmp;
}

int cltpow(re int x,re int y,re int mod){
    if(y==1)
        return x;
    re int res=cltpow(x,y>>1,mod);
    res=1LL*res*res%mod;
    if(y&1)
        res=1LL*res*x%mod;
    return res;
}

inline bool operator<(re node p,re node q){
    return p.l<q.l;
}

inline _it split(re int pos){
    re _it it=std::lower_bound(s.begin(),s.end(),node(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    --it;
    re int l=it->l,r=it->r;
    re long long val=it->val;
    s.erase(it),
    s.insert(node(l,pos-1,val));
    return s.insert(node(pos,r,val)).first;
}

inline void IntervalAdd(re int l,re int r,re int x){
    re _it itr=split(r+1),itl=split(l);
    for(;itl!=itr;++itl)
        itl->val+=x;
}

inline void IntervalAssign(re int l,re int r,re int x){
    re _it itr=split(r+1),itl=split(l);
    s.erase(itl,itr),
    s.insert(node(l,r,x));
}

inline long long IntervalXth(re int l,re int r,re int x){
    re _it itr=split(r+1),itl=split(l);
    re int cnt=0;
    for(;itl!=itr;++itl)
        vec[++cnt]=std::make_pair(itl->val,itl->r-itl->l+1);
    std::sort(vec+1,vec+cnt+1);
    for(re int i=1;i<=cnt;++i){
        x-=vec[i].second;
        if(x<=0)
            return vec[i].first;
    }
    return 0;
}

inline int IntervalXpow(re int l,re int r,re int x,re int y){
    re _it itr=split(r+1),itl=split(l);
    re int res=0;
    for(;itl!=itr;++itl)
        res=(1LL*res+1LL*(itl->r-itl->l+1)*cltpow(itl->val%y,x,y)%y)%y;
    return res;
}

int main(){
    cltstream::read(n),
    cltstream::read(m),
    cltstream::read(seed),
    cltstream::read(maxval);
    for(re int i=1;i<=n;++i)
        s.insert(node(i,i,rnd()%maxval+1));
    for(re int i=1;i<=m;++i){
        re int opt=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1,x,y;
        if(l>r)
            swap(l,r);
        if(opt==1){
            x=rnd()%maxval+1,
            IntervalAdd(l,r,x);
            continue;
        }
        if(opt==2){
            x=rnd()%maxval+1,
            IntervalAssign(l,r,x);
            continue;
        }
        if(opt==3){
            x=rnd()%(r-l+1)+1,
            cltstream::write(IntervalXth(l,r,x),'\n');
            continue;
        }
        if(opt==4){
            x=rnd()%maxval+1,
            y=rnd()%maxval+1,
            cltstream::write(IntervalXpow(l,r,x,y),'\n');
            continue;
        }
    }
    cltstream::pc(-1);
    return 0;
}
