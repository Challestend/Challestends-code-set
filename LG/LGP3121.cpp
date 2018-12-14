#include<cstdio>
#include<iostream>
#include<string>
#include<queue>
#define re register
#define maxlen 100000

namespace ACAutomaton{
	struct node{
		node *ch[26],*fail;
		int l;
	};

	struct automaton{
		node mempool[maxlen+10],*memtop,*root;
		node *pos[maxlen+10];

		inline node* newNode(){
			node* p=++memtop;
			for(re int i=0;i<26;++i)
				p->ch[i]=root;
			p->fail=root;
			p->l=0;
			return p;
		}

		inline void insStr(std::string& s){
			re int len=s.length();
			re node* p=root;
			for(re int i=1;i<=len;++i){
				if(p->ch[s[i-1]-'a']==root)
					p->ch[s[i-1]-'a']=newNode();
				p=p->ch[s[i-1]-'a'];
			}
			p->l=len;
		}

		inline void initFail(){
			std::queue<node*> h;
			for(re int i=0;i<26;++i)
				if(root->ch[i]!=root)
					h.push(root->ch[i]);
			for(;!h.empty();){
				re node* p=h.front();
				h.pop();
				for(re int i=0;i<26;++i)
					if(p->ch[i]!=root){
						p->ch[i]->fail=p->fail->ch[i];
						h.push(p->ch[i]);
					}
					else
						p->ch[i]=p->fail->ch[i];
				if(!p->fail->l)
					p->fail=p->fail->fail;
			}
		}

		inline void optStr(std::string& s){
			re int len=s.length();
			pos[0]=root;
			for(re int i=1;i<=len;++i){
				re node* p=pos[i]=pos[i-1]->ch[s[i-1]-'a'];
				for(;!p->l&&p!=root;p=p->fail);
				if(p->l){
					s=s.substr(0,i-p->l)+s.substr(i);
					len-=p->l;
					i-=p->l;
				}
			}
		}

		automaton(){
			root=memtop=mempool;
			for(re int i=0;i<26;++i)
				root->ch[i]=root;
			root->fail=root;
			root->l=0;
		}
	};
}

int n;
ACAutomaton::automaton clt;
std::string A,B;

int main(){
	std::cin>>A;
	scanf("%d",&n);
	for(re int i=1;i<=n;++i){
		std::cin>>B;
		clt.insStr(B);
	}
	clt.initFail();
	clt.optStr(A);
	std::cout<<A<<std::endl;
	return 0;
}
