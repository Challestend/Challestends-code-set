#include<cstdio>
#include<iostream>
#include<string>
#include<set>
#define re register
#define maxn 500000
#define maxm 500000
#define _it std::set<node>::iterator

namespace cltstream{
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
}

int n,m;
std::string str;
struct node{
    int l,r;
    mutable int val;

    node(re int _l,re int _r=-1,re int _val=-1){
        l=_l;
        r=_r;
        val=_val;
    }
};
std::set<node> s;

inline bool operator<(re node p,re node q){
    return p.l<q.l;
}

inline _it split(re int pos){
    _it it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    else{
        --it;
        re int l=it->l,r=it->r,val=it->val;
        s.erase(it);
        s.insert(node(l,pos-1,val));
        return s.insert(node(pos,r,val)).first;
    }
}

inline void IntervalAssign(re int l,re int r,re int x){
    re _it itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,x));
}

inline bool IntervalCheck(re int l,re int r){
    re _it itr=split(r+1),itl=split(l);
    --itl;
    if(itl->val==itr->val)
        return false;
    ++itl;
    --itr;
    re int v=itr->val;
    ++itr;
    for(;itl!=itr;++itl)
        if(itl->val!=v)
            return false;
    return true;
}

int main(){
    cltstream::read(n);
    std::cin>>str;
    for(re int i=2,j=1;i<=n;++i){
        if(str[i-1]!=str[i-2]){
            s.insert(node(j,i-1,str[j-1]-'A'+1));
            j=i;
        }
        if(i==n)
            s.insert(node(j,i,str[j-1]-'A'+1));
    }
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        re char opt=getchar();
        for(;opt!='A'&&opt!='B';opt=getchar());
        re int l,r;
        cltstream::read(l);
        cltstream::read(r);
        if(opt=='A'){
            re char x=getchar();
            for(;x!='A'&&x!='B'&&opt!='C';x=getchar());
            IntervalAssign(l,r,x-'A'+1);
        }
        else
            if(IntervalCheck(l,r))
                puts("Yes");
            else
                puts("No");
    }
    return 0;
}
