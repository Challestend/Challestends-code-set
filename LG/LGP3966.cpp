#include<cstdio>
#include<iostream>
#include<string>
#include<queue>
#define re register
#define maxn 200
#define maxlen 1000000

namespace ACAutomaton{
	struct node{
		node *ch[27],*fail;
		int end,cnt;
	};

	struct automaton{
		node mempool[maxlen+10],*memtop,*root;

		inline node* newNode(){
			node* p=++memtop;
			for(re int i=0;i<=26;++i)
				p->ch[i]=root;
			p->fail=root;
			p->end=p->cnt=0;
			return p;
		}

		inline node* insStr(std::string& s){
			re int len=s.length();
			re node* cur=root;
			for(re int i=0;i<len;++i){
				if(cur->ch[s[i]-'a']==root)
					cur->ch[s[i]-'a']=newNode();
				cur=cur->ch[s[i]-'a'];
			}
			cur->end=1;
			return cur;
		}

		inline void initFail(){
			std::queue<node*> h;
			for(re int i=0;i<=26;++i)
				if(root->ch[i]!=root)
					h.push(root->ch[i]);
			for(;!h.empty();){
				re node* p=h.front();
				h.pop();
				for(re int i=0;i<=26;++i)
					if(p->ch[i]!=root){
						p->ch[i]->fail=p->fail->ch[i];
						h.push(p->ch[i]);
					}
					else
						p->ch[i]=p->fail->ch[i];
				if(!p->fail->end)
					p->fail=p->fail->fail;
			}
		}

		inline void srhStr(std::string& s){
			re int len=s.length();
			re node* cur=root;
			for(re int i=0;i<len;++i)
				for(node* p=cur=cur->ch[s[i]-'a'];p!=root;p=p->fail)
					p->cnt+=p->end;
		}

		automaton(){
			root=memtop=mempool;
			for(re int i=0;i<=26;++i)
				root->ch[i]=root;
			root->fail=root;
			root->end=root->cnt=0;
		}
	};
}

int n;
ACAutomaton::automaton accepted;
std::string str[maxn+1];
ACAutomaton::node* pos[maxn+1];

int main(){
	scanf("%d",&n);
	for(re int i=1;i<=n;++i){
		std::cin>>str[i];
		str[0]+=str[i]+(char)('z'+1);
		pos[i]=accepted.insStr(str[i]);
	}
	accepted.initFail();
	accepted.srhStr(str[0]);
	for(re int i=1;i<=n;++i)
		printf("%d\n",pos[i]->cnt);
	return 0;
}
