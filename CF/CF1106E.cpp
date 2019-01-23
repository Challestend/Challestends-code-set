#include<cstdio>
#include<iostream>
#include<string>
#include<map>
#define re register
#define maxr 40
#define maxc 100000
#define maxsize 100000
#define max(a,b) ((a)>=(b)?(a):(b))

int n,m,r,c,ans;
std::string name;
std::map<std::string,int> M;
int a[maxr+1][maxc+1];
struct node{
	node *l,*r,*u,*d;
	int row,col;
};
node mempool[maxsize+maxc+1],*memtop,*head,*ch[maxc+1],*rh[maxr+1];
int size[maxc+1];

inline void build(){
	head=memtop=mempool;
	head->l=head->r=head->u=head->d=head;
	head->row=head->col=0;
	for(re int i=1;i<=c;++i){
		ch[i]=++memtop;
		ch[i]->l=head->l;
		ch[i]->r=head;
		ch[i]->l->r=ch[i]->r->l=ch[i]->u=ch[i]->d=ch[i];
		ch[i]->row=0;
		ch[i]->col=i;
		size[i]=0;
	}
	for(re int i=1;i<=r;++i)
		rh[i]=NULL;
}

inline void insNode(re int x,re int y){
	++size[y];
	re node* p=++memtop;
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

inline void remove(re int x){
	ch[x]->l->r=ch[x]->r;
	ch[x]->r->l=ch[x]->l;
	for(re node* i=ch[x]->d;i!=ch[x];i=i->d)
		for(re node* j=i->r;j!=i;j=j->r){
			j->u->d=j->d;
			j->d->u=j->u;
			--size[j->col];
		}
}

inline void resume(re int x){
	ch[x]->l->r=ch[x]->r->l=ch[x];
	for(re node* i=ch[x]->d;i!=ch[x];i=i->d)
		for(re node* j=i->r;j!=i;j=j->r){
			j->u->d=j->d->u=j;
			++size[j->col];
		}
}

inline void dance(re int cnt){
	if(head->r==head)
		ans=max(ans,cnt);
	else{
		re node* cur=head->r;
		for(re node* i=cur->r;i!=head;i=i->r)
			if(size[i->col]<size[cur->col])
				cur=i;
		remove(cur->col);
		for(re node* i=cur->d;i!=cur;i=i->d){
			for(re node* j=i->r;j!=i;remove(j->col),j=j->r);
			dance(cnt+1);
			for(re node* j=i->r;j!=i;resume(j->col),j=j->r);
		}
		resume(cur->col);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(re int i=1,j=1;i<=n;++i){
		int opt;
		scanf("%d",&opt);
		if(opt==1){
			if(j){
				++c;
				j=0;
			}
		}
		else{
			++j;
			std::cin>>name;
			if(!M[name])
				M[name]=++r;
			a[M[name]][c]=1;
		}
	}
	build();
	for(re int i=1;i<=r;++i)
		for(re int j=1;j<=c;++j)
			if(a[i][j])
				insNode(i,j);
	dance(0);
	printf("%d",ans);
	return 0;
}
