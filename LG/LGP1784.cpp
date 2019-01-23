#include<cstdio>
#define re register
#define maxn 729
#define maxm 324
#define maxsize 2916

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

const int scr[10][10]={
	{0,0,0,0,0,0,0,0,0,0},
	{0,6,6,6,6,6,6,6,6,6},
	{0,6,7,7,7,7,7,7,7,6},
	{0,6,7,8,8,8,8,8,7,6},
	{0,6,7,8,9,9,9,8,7,6},
	{0,6,7,8,9,10,9,8,7,6},
	{0,6,7,8,9,9,9,8,7,6},
	{0,6,7,8,8,8,8,8,7,6},
	{0,6,7,7,7,7,7,7,7,6},
	{0,6,6,6,6,6,6,6,6,6},
};

struct node{
	node *l,*r,*u,*d;
	int row,col;
};
node mep[maxsize+maxm+1],*met,*head,*ch[maxm+1],*rh[maxn+1];
int size[maxm+1],ans;

inline void insert(re int x,re int y){
	++size[y];
	re node* p=++met;
	if(rh[x]==NULL)
		rh[x]=p->l=p->r=p;
	else
		p->l=rh[x]->l,
		p->r=rh[x],
		p->l->r=p->r->l=p;
	p->u=ch[y]->u,
	p->d=ch[y],
	p->u->d=p->d->u=p,
	p->row=x,
	p->col=y;
}

inline void remove(re int x){
	ch[x]->l->r=ch[x]->r,
	ch[x]->r->l=ch[x]->l;
	for(re node* i=ch[x]->d;i!=ch[x];i=i->d)
		for(re node* j=i->r;j!=i;j=j->r)
			j->u->d=j->d,
			j->d->u=j->u,
			--size[j->col];
}

inline void resume(re int x){
	ch[x]->l->r=ch[x]->r->l=ch[x];
	for(re node* i=ch[x]->d;i!=ch[x];i=i->d)
		for(re node* j=i->r;j!=i;j=j->r)
			j->u->d=j->d->u=j,
			++size[j->col];
}

bool dance(re int res){
	if(head->r==head){
		if(ans<res)
			ans=res;
		return true;
	}
	else{
		re bool f=false;
		re node* cur=head->r;
		for(re node* i=cur->r;i!=head;i=i->r)
			if(size[i->col]<size[cur->col])
				cur=i;
		remove(cur->col);
		for(re node* i=cur->d;i!=cur;i=i->d){
			for(re node* j=i->r;j!=i;remove(j->col),j=j->r);
			f|=dance(res+((i->row-1)%9+1)*scr[(i->row-1)/81+1][(i->row-1)/9%9+1]);
			for(re node* j=i->r;j!=i;resume(j->col),j=j->r);
		}
		resume(cur->col);
		return f;
	}
}

int main(){
	head=met=mep,
	head->l=head->r=head->u=head->d=head,
	head->row=head->col=0;
	for(re int i=1;i<=maxm;++i)
		ch[i]=++met,
		ch[i]->l=head->l,
		ch[i]->r=head,
		ch[i]->l->r=ch[i]->r->l=ch[i]->u=ch[i]->d=ch[i],
		ch[i]->row=0,
		ch[i]->col=i,
		size[i]=0;
	for(re int i=1;i<=maxn;++i)
		rh[i]=NULL;
	for(re int i=1;i<=9;++i)
		for(re int j=1;j<=9;++j){
			re int x;
			cltstream::read(x);
			if(x)
				insert((i-1)*81+(j-1)*9+x,(i-1)*9+j),
				insert((i-1)*81+(j-1)*9+x,(i-1)*9+x+81),
				insert((i-1)*81+(j-1)*9+x,(j-1)*9+x+162),
				insert((i-1)*81+(j-1)*9+x,((i-1)/3*3+(j-1)/3)*9+x+243);
			else
				for(re int k=1;k<=9;++k)
					insert((i-1)*81+(j-1)*9+k,(i-1)*9+j),
					insert((i-1)*81+(j-1)*9+k,(i-1)*9+k+81),
					insert((i-1)*81+(j-1)*9+k,(j-1)*9+k+162),
					insert((i-1)*81+(j-1)*9+k,((i-1)/3*3+(j-1)/3)*9+k+243);
		}
	if(dance(0))
		cltstream::write(ans);
	else
		cltstream::write(-1);
	clop();
	return 0;
}
