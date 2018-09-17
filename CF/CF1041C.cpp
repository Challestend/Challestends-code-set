#include<cstdio>
#include<algorithm>
#include<vector>
#define re register
#define maxn 200010
#define alpha 0.75
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,d;
int a[maxn],b[maxn],f[maxn];

namespace ScapegoatTree{
    struct node{
        node* ch[2];
        int val,size,valid,exist;
    };

    struct tree{
        protected:
            node mempool[maxn],*memtop;
            node *root,*null;
            node *rec[maxn];
            int rectop;
            std::vector<node*> vec;

            inline node* newNode(int v){
                node* p=rectop>0?rec[rectop--]:++memtop;
                p->ch[0]=p->ch[1]=null;
                p->val=v;
                p->size=p->valid=p->exist=1;
                return p;
            }

            void breakDown(node*& p){
                if(p==null)
                    return;
                breakDown(p->ch[0]);
                if(p->exist)
                    vec.push_back(p);
                else
                    rec[++rectop]=p;
                breakDown(p->ch[1]);
            }

            node* buildUp(int l,int r){
                if(l>r)
                    return null;
                int mid=l+r>>1;
                node* p=vec[mid-1];
                p->ch[0]=buildUp(l,mid-1);
                p->ch[1]=buildUp(mid+1,r);
                p->size=p->ch[0]->size+p->ch[1]->size+1;
                p->valid=p->ch[0]->valid+p->ch[1]->valid+p->exist;
                return p;
            }

            inline void rebuild(node*& p){
                vec.clear();
                breakDown(p);
                p=buildUp(1,vec.size());
            }

            node** insNode(node*& p,int v){
                if(p==null){
                    p=newNode(v);
                    return &null;
                }
                else{
                    p->size++,p->valid++;
                    node** res=insNode(p->ch[a[v]>a[p->val]],v);
                    if(p->ch[0]->size>alpha*p->size||p->ch[1]->size>alpha*p->size)
                        res=&p;
                    return res;
                }
            }

            inline void delNode(int k){
                node* cur=root;
                for(;cur!=null;){
                    cur->valid--;
                    int ln=cur->ch[0]->valid+cur->exist;
                    if(k==ln&&cur->exist){
                        cur->exist=0;
                        return;
                    }
                    if(k>ln){
                        k-=ln;
                        cur=cur->ch[1];
                    }
                    else
                        cur=cur->ch[0];
                }
            }
        public:
            inline void init(){
                memtop=mempool;
                null=memtop;
                null->ch[0]=null->ch[1]=null;
                null->val=null->size=null->valid=null->exist=0;
                root=null;
                rectop=-1;
            }

            inline void insert(int v){
                node** res=insNode(root,v);
                if(*res!=null)
                    rebuild(*res);
            }

            inline int getRank(int v){
                node* cur=root;
                int res=1;
                for(;cur!=null;)
                    if(v>a[cur->val]){
                        res+=cur->ch[0]->valid+cur->exist;
                        cur=cur->ch[1];
                    }
                    else
                        cur=cur->ch[0];
                return res;
            }

            inline int findRank(int x){
                node* cur=root;
                for(;cur!=null;){
                    int ln=cur->ch[0]->valid+cur->exist;
                    if(x==ln&&cur->exist)
                        return cur->val;
                    if(x>ln){
                        x-=ln;
                        cur=cur->ch[1];
                    }
                    else
                        cur=cur->ch[0];
                }
                return -1;
            }

            inline void delVal(int v){
                delNode(getRank(v));
                if(root->valid<alpha*root->size)
                    rebuild(root);
            }

            tree(){
                init();
            }
    };
}

bool cmp(int x,int y){
    return a[x]<a[y];
}

ScapegoatTree::tree st;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(d);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        b[i]=i;
    }
    std::sort(b+1,b+n+1,cmp);
    f[0]=f[b[1]]=1;
    st.insert(b[1]);
    for(re int i=2;i<=n;++i){
        if(a[b[i]]>d+1){
            int x=st.findRank(st.getRank(a[b[i]]-d-1));
            if(x!=-1){
                f[b[i]]=f[x];
                st.delVal(a[x]);
            }
            else
                f[b[i]]=++f[0];
        }
        else
            f[b[i]]=++f[0];
        st.insert(b[i]);
    }
    cltstream::write(f[0]);
    putchar(10);
    for(re int i=1;i<=n;++i){
        cltstream::write(f[i]);
        putchar(32);
    }
    return 0;
}
