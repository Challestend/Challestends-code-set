#include<cstdio>
#include<set>
#define re register
#define _it std::set<node>::iterator

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

int n;
struct node{
    long long l,r;
    mutable int val;

    node(re long long _l,re long long _r=-1,re int _val=-1){
        l=_l;
        r=_r;
        val=_val;
    }
};
std::set<node> s;

inline bool operator<(re node p,re node q){
    return p.l<q.l;
}

inline _it split(re long long pos){
    re _it it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    else{
        --it;
        re long long l=it->l,r=it->r;
        re int val=it->val;
        s.erase(it);
        s.insert(node(l,pos-1,val));
        return s.insert(node(pos,r,val)).first;
    }
}

inline void IntervalAssign(re long long l,re long long r,re int x){
    re _it itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,x));
}

inline void IntervalXor(re long long l,re long long r){
    re _it itr=split(r+1),itl=split(l);
    for(;itl!=itr;itl->val^=1,++itl);
}

int main(){
    s.insert(node(1,1e18+1,0));
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        re int opt;
        re long long l,r;
        cltstream::read(opt);
        cltstream::read(l);
        cltstream::read(r);
        switch(opt){
            case 1:
                IntervalAssign(l,r,1);
                break;
            case 2:
                IntervalAssign(l,r,0);
                break;
            case 3:
                IntervalXor(l,r);
                break;
        }
        re _it p=s.begin();
        for(;p->val;++p);
        cltstream::write(p->l,10);
    }
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
