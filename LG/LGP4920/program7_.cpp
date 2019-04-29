#include<cstdio>
#define re register
#define id(a) (1<<((a)-'A'))

char a[16][16];
int r[16],c[16],p[16];

int dfs(re int x,re int y){
	if(x==16)
		return 1;
	else
		if(a[x][y]=='?'){
			for(re char i='A';i<='P';++i)
				if(!(r[x]&id(i))&&!(c[y]&id(i))&&!(p[x/4*4+y/4]&id(i))){
					a[x][y]=i;
					r[x]^=id(i);
					c[y]^=id(i);
					p[x/4*4+y/4]^=id(i);
					if(dfs(x+(y+1)/16,(y+1)%16))
						return 1;
					a[x][y]='?';
					r[x]^=id(i);
					c[y]^=id(i);
					p[x/4*4+y/4]^=id(i);
				}
			return 0;
		}
		else
			return dfs(x+(y+1)/16,(y+1)%16);
}

int main(){
	freopen("program7.in","r",stdin);
	freopen("program7.out","w",stdout);
	for(re int T=4;T;--T){
		for(re int i=0;i<16;++i)
			r[i]=c[i]=p[i]=0;
		re int FAQ=0;
		for(re int i=0;i<16;++i){
			scanf("%s",a[i]);
			for(re int j=0;j<16;++j)
				if(a[i][j]!='?'){
					(r[i]&id(a[i][j]))&&(FAQ=1);
					r[i]^=id(a[i][j]);
					(c[j]&id(a[i][j]))&&(FAQ=1);
					c[j]^=id(a[i][j]);
					(p[i/4*4+j/4]&id(a[i][j]))&&(FAQ=1);
					p[i/4*4+j/4]^=id(a[i][j]);
				}
		}
		if(FAQ)
			for(re int i=0;i<5-T;++i)
				puts("NO SOLUTION.");
		else
			if(dfs(0,0))
				for(re int i=0;i<5-T;++i,puts(""))
					for(re int j=0;j<16;++j)
						printf("%s",a[j]);
			else
				for(re int i=0;i<5-T;++i)
					puts("NO SOLUTION.");
	}
	return 0;
}
