#include<cstdio>
#include<set>
#define re register
#define _it std::set<node>::iterator
#define max(a,b) ((a)>=(b)?(a):(b))

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
	mutable int l,r,v;

	node(re int _l=0,re int _r=0,re int _v=0){
		l=_l;
		r=_r;
		v=_v;
	}
};
std::set<node> s;
node a[500010];

inline bool operator<(re node p1,re node p2){
	return p1.l<p2.l;
}

inline _it split(re int pos){
	_it it=s.lower_bound(node(pos));
	if(it!=s.end()&&it->r==pos)
		return it;
	else{
		--it;
		re int l=it->l,r=it->r,v=it->v;
		s.erase(it);
		s.insert(node(l,pos-1,v));
		return s.insert(node(pos,r,v)).first;
	}
}

inline void InsArr(re int pos,re int len){
	re _it it=split(pos+1);
	for(;it!=s.end();it->l+=len,it->r+=len,++it);
	for(re int i=1;i<=len;++i){
		re int v;
		cltstream::read(v);
		s.insert(node(pos+i,pos+i,v));
	}
}

inline void DelArr(re int pos,re int len){
	re _it itr=split(pos+len),itl=split(pos);
	s.erase(itl,itr);
	for(;itr!=s.end();itr->l-=len,itr->r-=len,++itr);
}

inline void ModArr(re int pos,re int len,re int val){
	re _it itr=split(pos+len),itl=split(pos);
	s.erase(itl,itr);
	s.insert(node(pos,pos+len-1,val));
}

inline void RevArr(re int pos,re int len){
	re _it itr=split(pos+len),itl=split(pos);
	re int cnt=0;
	for(re _it it=itl;it!=itr;a[++cnt]=node(it->l,it->r,it->v),++it);
	s.erase(itl,itr);
	for(re int i=cnt;i>=1;pos+=a[i].r-a[i].l+1,--i)
		s.insert(node(pos,pos+a[i].r-a[i].l,a[i].v));
}

inline int GetSum(re int pos,re int len){
	re int res=0;
	re _it itr=split(pos+len),itl=split(pos);
	for(;itl!=itr;res+=(itl->r-itl->l+1)*itl->v,++itl);
	return res;
}

inline int GetMaxSum(){
	re int res=-2e9,tmp=0;
	for(re _it it=s.begin();it!=s.end();tmp=max(tmp+(it->r-it->l+1)*it->v,(it->r-it->l+1)*it->v),res=max(res,tmp),++it);
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		re int v;
		cltstream::read(v);
		s.insert(node(i,i,v));
	}
	for(re int i=1;i<=m;++i){
		for(re char c=cltstream::gc();c<'A'||c>'Z';c=cltstream::gc());
		re char opt=cltstream::gc();
		opt=cltstream::gc();
		for(re char c=cltstream::gc();c!=32&&c!=45;c=cltstream::gc());
		re int pos,len,val;
		switch(opt){
			case 'S':
				cltstream::read(pos);
				cltstream::read(len);
				InsArr(pos,len);
				break;
			case 'L':
				cltstream::read(pos);
				cltstream::read(len);
				DelArr(pos,len);
				break;
			case 'K':
				cltstream::read(pos);
				cltstream::read(len);
				cltstream::read(val);
				ModArr(pos,len,val);
				break;
			case 'V':
				cltstream::read(pos);
				cltstream::read(len);
				RevArr(pos,len);
				break;
			case 'T':
				cltstream::read(pos);
				cltstream::read(len);
				cltstream::write(GetSum(pos,len),10);
				break;
			case 'X':
				cltstream::write(GetMaxSum(),10);
				for(re char c=cltstream::gc();c!='\r'&&c!='\n';c=cltstream::gc());
				break;
		}
	}
	clop();
	return 0;
}
