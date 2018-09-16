#include<cstdio>

namespace CLT{
    inline void read(int& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
        x*=sn;
    }

    inline void write(int x){
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
    const int maxn=100000+10;
    const double alpha=0.75;

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
            node *vec[maxn];
            int vectop;

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
                    vec[++vectop]=p;
                else
                    rec[++rectop]=p;
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
                p->valid=p->ch[0]->valid+p->ch[1]->valid+p->exist;
                return p;
            }

            inline void rebuild(node*& p){
                vectop=0;
                breakDown(p);
                p=buildUp(1,vectop);
            }

            node** insNode(node*& p,int v){
                if(p==null){
                    p=newNode(v);
                    return &null;
                }
                else{
                    p->size++,p->valid++;
                    node** res=insNode(p->ch[v>p->val],v);
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

            void print(node*& p,int x){
                if(p==null)
                    return;
                print(p->ch[0],0);
                if(p->exist){
                    CLT::write(p->val);
                    if(x==0||(x==1&&p->ch[1]!=null))
                        putchar(',');
                }
                print(p->ch[1],x&1);
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
                    if(v>cur->val){
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

            inline void check(){
            	CLT::write(root->valid);
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

int n;
ScapegoatTree::tree st;

int main(){
    CLT::read(n);
    for(;n;--n){
        int opt,x;
        CLT::read(opt),CLT::read(x);
        switch(opt){
            case 1:
                st.insert(x);
                break;
            case 2:
                st.delVal(x);
                break;
            case 3:
                CLT::write(st.getRank(x));
                putchar(10);
                break;
            case 4:
                CLT::write(st.findRank(x));
                putchar(10);
                break;
            case 5:
                CLT::write(st.findRank(st.getRank(x)-1));
                putchar(10);
                break;
            case 6:
                CLT::write(st.findRank(st.getRank(x+1)));
                putchar(10);
                break;
        }
    }
    return 0;
}
