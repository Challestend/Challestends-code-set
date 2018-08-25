#include<cstdio>
#define re register
#define min(a,b) ((a)<=(b)?(a):(b))

template <typename T>
inline void read(T& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

template <typename T>
inline void write(T x){
    if(!x)
        putchar(48);
    else{
        int digit[20];
        for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
        for(;digit[0];putchar(digit[digit[0]--]^48));
    }
}

namespace ScapegoatTree{
    const int maxn=32767+10;
    const double alpha=0.75;

    struct node{
        node *ch[2];
        int val,size;
    };

    struct tree{
        protected:
            node mempool[maxn],*memtop;
            node *null,*root;
            node *vec[maxn];
            int vectop;

            inline node* newNode(int x){
                node* p=++memtop;
                p->ch[0]=p->ch[1]=null;
                p->val=x;
                p->size=1;
                return p;
            }

            node** insNode(node*& p,int x){
                if(p==null){
                    p=newNode(x);
                    return &null;
                }
                else{
                    p->size++;
                    node** res=insNode(p->ch[x>p->val],x);
                    if(p->ch[0]->size>alpha*p->size||p->ch[1]->size>alpha*p->size)
                        res=&p;
                    return res;
                }
            }

            void breakDown(node*& p){
                if(p==null)
                    return;
                breakDown(p->ch[0]);
                vec[++vectop]=p;
                breakDown(p->ch[1]);
            }

            node* buildUp(int l,int r){
                if(l>r)
                    return null;
                int mid=l+r>>1;
                node* p=vec[mid];
                p->ch[0]=buildUp(l,mid-1);
                p->ch[1]=buildUp(mid+1,r);
                p->size=p->ch[0]->size+p->ch[1]->size+1;
                return p;
            }

            inline void rebuild(node*& p){
                vectop=0;
                breakDown(p);
                p=buildUp(1,vectop);
            }

            void print(node*& p,int x){
                if(p==null)
                    return;
                print(p->ch[0],0);
                write(p->val);
                if(x==0||(x==1&&p->ch[1]!=null))
                    putchar(',');
                print(p->ch[1],x&1);
            }
        public:
            inline void init(){
                memtop=mempool;
                null=memtop;
                null->ch[0]=null->ch[1]=null;
                null->val=null->size=0;
                root=null;
            }

            inline void insert(int x){
                node** res=insNode(root,x);
                if(*res!=null)
                    rebuild(*res);
            }

            inline int getRank(int x){
                int res=1;
                for(node* cur=root;cur!=null;)
                    if(x>cur->val){
                        res+=cur->ch[0]->size+1;
                        cur=cur->ch[1];
                    }
                    else
                        cur=cur->ch[0];
                return res;
            }

            inline int findRank(int x){
                for(node* cur=root;cur!=null;){
                    int ln=cur->ch[0]->size+1;
                    if(x==ln)
                        return cur->val;
                    else
                        if(x>ln){
                            x-=ln;
                            cur=cur->ch[1];
                        }
                        else
                            cur=cur->ch[0];
                }
            }

            inline void check(){
                write(root->size);
                puts(" number(s) in total.");
                putchar('<');
                print(root,1);
                putchar('>');
                putchar(10);
            }

            tree(){
                init();
            }
    };
}

int n,ans;
ScapegoatTree::tree st;

int main(){
    read(n);
    read(ans);
    st.insert(ans);
    for(re int i=2;i<=n;++i){
        int x,l,r;
        read(x);
        int rank=st.getRank(x);
        if(st.findRank(x+1)==rank+1)
            l=r=x;
        else
            l=rank>1?st.findRank(rank-1):-2e9,r=rank<i?st.findRank(rank):2e9;
        ans+=min(x-l,r-x);
        st.insert(x);
    }
    write(ans);
    return 0;
}
