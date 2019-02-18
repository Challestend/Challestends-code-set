#include<cstdio>
#define re register
#define maxm 20

int n,m,mod;
char s[maxm+5];
int nxt[maxm+1],v[11];
struct matrix{
	int mat[maxm+1][maxm+1];

	matrix(){
		for(re int i=0;i<=maxm;++i)
			for(re int j=0;j<=maxm;++j)
				mat[i][j]=0;
	}
};
matrix A,B;

inline matrix operator*(const matrix& A,const matrix& B){
	matrix res;
	for(re int k=0;k<m;++k)
		for(re int i=0;i<m;++i)
			for(re int j=0;j<m;++j)
				res.mat[i][j]=(res.mat[i][j]+A.mat[i][k]*B.mat[k][j])%mod;
	return res;
}

int main(){
	scanf("%d%d%d",&n,&m,&mod);
	scanf("%s",s+1);
	for(int i=2,j=0;i<=m;i++){
		for(;j&&s[j+1]!=s[i];j=nxt[j]);
		if(s[j+1]==s[i])
			j++;
		nxt[i]=j;
	}
	for(re int i=0;i<m;++i){
		for(re int j=0;j<=10;++j)
			v[j]=0;
		++A.mat[i+1][i];
		++v[s[i+1]^48];
		for(re int j=nxt[i];j;j=nxt[j])
			if(!v[s[j+1]^48]){
				++A.mat[j+1][i];
				++v[s[j+1]^48];
				++v[10];
			}
		if(!v[s[1]^48]){
			++A.mat[1][i];
			++v[s[1]^48];
			++v[10];
		}
		A.mat[0][i]=9-v[10];
		B.mat[i][i]=1;
	}
	for(;n;){
		if(n&1)
			B=A*B;
		A=A*A;
		n>>=1;
	}
	re int ans=0;
	for(re int i=0;i<m;++i)
		ans=(ans+B.mat[i][0])%mod;
	printf("%d",ans);
	return 0;
}
