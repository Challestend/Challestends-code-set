#include<cstdio>
#define re register
#define maxn 500
#define maxm 500
#define maxsize 5000

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
	#define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout),cltstream::oh=cltstream::cltout
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

int n,m;
struct node{
	node *l,*r,*u,*d;
	int row,col;
};
node mep[maxm+maxsize+1],*met,*head,*ch[maxm+1],*rh[maxn+1];
int size[maxm+1];

inline void insert(re int x,re int y){
	++size[y];
	re node* p=++met;
	if(rh[x]==NULL)
		rh[x]=p->l=p->r=p;
	else{
		p->l=rh[x]->l;
		p->r=rh[x];
		p->l->r=p->r->l=p;
	}
	p->u=ch[y]->u;
	p->d=ch[y];
	p->u->d=p->d->u=p;
	p->row=x;
	p->col=y;
}

inline void removeColumn(re int x){
	ch[x]->l->r=ch[x]->r;
	ch[x]->r->l=ch[x]->l;
	for(re node* i=ch[x]->d;i!=ch[x];i=i->d)
		for(re node* j=i->r;j!=i;j=j->r){
			j->u->d=j->d;
			j->d->u=j->u;
			--size[j->col];
		}
}

inline void resumeColumn(re int x){
	ch[x]->l->r=ch[x]->r->l=ch[x];
	for(re node* i=ch[x]->d;i!=ch[x];i=i->d)
		for(re node* j=i->r;j!=i;j=j->r){
			j->u->d=j->d->u=j;
			++size[j->col];
		}
}

bool dance(){
	if(head->r==head)
		return true;
	else{
		re node* cur=head->r;
		for(re node* i=cur->r;i!=head;i=i->r)
			if(size[i->col]<size[cur->col])
				cur=i;
		removeColumn(cur->col);
		for(re node* i=cur->d;i!=cur;i=i->d){
			for(re node* j=i->r;j!=i;removeColumn(j->col),j=j->r);
			if(dance()){
				cltstream::write(i->row,32);
				return true;
			}
			for(re node* j=i->r;j!=i;resumeColumn(j->col),j=j->r);
		}
		resumeColumn(cur->col);
	}
	return false;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	head=met=mep;
	head->l=head->r=head->u=head->d=head;
	head->row=head->col=0;
	for(re int i=1;i<=m;++i){
		ch[i]=++met;
		ch[i]->l=head->l;
		ch[i]->r=head;
		ch[i]->l->r=ch[i]->r->l=ch[i]->u=ch[i]->d=ch[i];
		ch[i]->row=0;
		ch[i]->col=i;
		size[i]=0;
	}
	for(re int i=1;i<=n;++i)
		rh[i]=NULL;
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j){
			re int x;
			cltstream::read(x);
			if(x)
				insert(i,j);
		}
	if(!dance()){
		cltstream::pc('N');
		cltstream::pc('o');
		cltstream::pc(' ');
		cltstream::pc('s');
		cltstream::pc('o');
		cltstream::pc('l');
		cltstream::pc('u');
		cltstream::pc('t');
		cltstream::pc('i');
		cltstream::pc('o');
		cltstream::pc('n');
		cltstream::pc('!');
	}
	clop();
	return 0;
}
