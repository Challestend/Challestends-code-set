#include<cstdio>
#define re register
#define maxn 200000
#define alpha 0.75

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
}

namespace ScapegoatTree{
    struct node{
        public:
            node *ch[2];
            long long val;
            int exist,size,valid;
    };

    struct tree{
        protected:
            node mempool[maxn+10],*rec[maxn+10],*vec[maxn+10];
            node *memtop,*null,*root;
            int rectop,vectop;

            inline node* newNode(long long v){
                node* p=rectop?rec[rectop--]:++memtop;
                p->ch[0]=p->ch[1]=null;
                p->val=v;
                p->exist=p->size=p->valid=1;
                return p;
            }

            void breakDown(node*& p){
                if(p==null)
                    return;
                breakDown(p->ch[0]);
                if(p->exist)
                    vec[++vectop]=p;
                else
                    rec[++rectop]=p;
                breakDown(p->ch[1]);
            }

            node* buildUp(int l,int r){
                if(l>r)
                    return null;
                int mid=(l+r)>>1;
                node* p=vec[mid];
                p->ch[0]=buildUp(l,mid-1);
                p->ch[1]=buildUp(mid+1,r);
                p->size=p->ch[0]->size+p->ch[1]->size+1;
                p->valid=p->ch[0]->valid+p->ch[1]->valid+p->exist;
                return p;
            }

            inline void rebuild(node*& p){
                vectop=0;
                breakDown(p);
                p=buildUp(1,vectop);
            }

            node** insNode(node*& p,long long v){
                if(p==null){
                    p=newNode(v);
                    return &null;
                }
                ++p->size,++p->valid;
                node** res=insNode(p->ch[v>p->val],v);
                if(p->ch[0]->valid>alpha*p->valid||p->ch[1]->valid>alpha*p->valid)
                    res=&p;
                return res;
            }

            inline void delNode(int x){
                for(node* p=root;;){
                    --p->valid;
                    int ln=p->ch[0]->valid+p->exist;
                    if(p->exist&&x==ln){
                        p->exist=0;
                        return;
                    }
                    if(x>ln){
                        x-=ln;
                        p=p->ch[1];
                    }
                    else
                        p=p->ch[0];
                }
            }

            void print(node*& p){
                if(p==null)
                    return;
                print(p->ch[0]);
                if(p->exist){
                    cltstream::write(p->val);
                    putchar(32);
                }
                print(p->ch[1]);
            }
        public:
            inline void init(){
                memtop=mempool;
                null=memtop;
                null->ch[0]=null->ch[1]=null;
                null->val=null->exist=null->size=null->valid=0;
                root=null;
                rectop=vectop=0;
            }

            inline void Insert(long long v){
                node** res=insNode(root,v);
                if(*res!=null)
                    rebuild(*res);
            }

            inline int getRank(long long v){
                int res=1;
                for(node* p=root;p!=null;)
                    if(v>p->val){
                        res+=p->ch[0]->valid+p->exist;
                        p=p->ch[1];
                    }
                    else
                        p=p->ch[0];
                return res;
            }

            inline void Delete(long long v){
                delNode(getRank(v));
                if(root->valid<alpha*root->size)
                    rebuild(root);
            }

            inline void debug(){
                putchar(10);
                print(root);
                putchar(10);
            }

            tree(){
                init();
            }
    };
}

int n;
long long m,a[maxn+1],ans;
ScapegoatTree::tree st;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        a[i]+=a[i-1];
        ans+=(a[i]<m);
        st.Insert(a[i]);
    }
    for(re int i=1;i<n;++i){
        st.Delete(a[i]);
        ans+=st.getRank(a[i]+m)-1;
    }
    cltstream::write(ans);
    return 0;
}
