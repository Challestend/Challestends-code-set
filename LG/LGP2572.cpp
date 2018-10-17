#include<cstdio>
#include<set>
#define re register
#define _it std::set<node>::iterator
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
int a[100001];
struct node{
    int l,r;
    mutable int val;

    node(int _l,int _r=-1,int _val=-1){
        l=_l;
        r=_r;
        val=_val;
    }
};
std::set<node> s;

inline bool operator<(node p,node q){
    return p.l<q.l;
}

inline _it split(int pos){
    _it p=s.lower_bound(node(pos));
    if(p!=s.end()&&p->l==pos)
        return p;
    else{
        --p;
        int l=p->l,r=p->r,val=p->val;
        s.erase(p);
        s.insert(node(l,pos-1,val));
        return s.insert(node(pos,r,val)).first;
    }
}

inline void IntervalAssign(int l,int r,int x){
    _it itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,x));
}

inline void IntervalXor(int l,int r){
    _it itr=split(r+1),itl=split(l);
    for(;itl!=itr;itl->val^=1,++itl);
}

inline int IntervalSum(int l,int r){
    int res=0;
    _it itr=split(r+1),itl=split(l);
    for(;itl!=itr;res+=(itl->r-itl->l+1)*itl->val,++itl);
    return res;
}

inline int IntervalMaxSum(int l,int r){
    int res=0,con=0;
    _it itr=split(r+1),itl=split(l);
    for(;itl!=itr;++itl)
        if(itl->val)
            con+=itl->r-itl->l+1;
        else{
            res=max(res,con);
            con=0;
        }
    return max(res,con);
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(a[1]);
    for(re int i=2,las=1;i<=n;++i){
        cltstream::read(a[i]);
        if(a[i]!=a[i-1]){
            s.insert(node(las,i-1,a[i-1]));
            las=i;
        }
        if(i==n)
            s.insert(node(las,i,a[i]));
    }
    for(re int i=1;i<=m;++i){
        int opt,l,r;
        cltstream::read(opt);
        cltstream::read(l);
        ++l;
        cltstream::read(r);
        ++r;
        switch(opt){
            case 0:
            case 1:
                IntervalAssign(l,r,opt);
                break;
            case 2:
                IntervalXor(l,r);
                break;
            case 3:
                cltstream::write(IntervalSum(l,r),'\n');
                break;
            case 4:
                cltstream::write(IntervalMaxSum(l,r),'\n');
                break;
        }
    }
    return 0;
}
