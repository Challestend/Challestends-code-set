#include<cstdio>
#include<cstring>
#define re register
#define maxn 10
#define maxlen 1000000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

int n,len,mx,ans;
char s[maxlen+5];
int fst[maxlen+1],snd[2*maxlen+1],tak[maxlen+1];
int sa[maxlen+1],rnk[maxlen+1],het[maxlen+1];
int col[maxlen+1],cnt[maxn+1],p[maxlen+1];

int main(){
	for(;scanf("%s",s+len+1)==1;){
		++n;
		re int tmp=strlen(s+len+1);
		for(re int j=len+1;j<=len+tmp;++j)
			col[j]=n;
		s[len=len+tmp+1]='#';
	}
	mx=122;
	for(re int i=1;i<=len;++i)
		++tak[fst[i]=s[i]];
	for(re int i=1;i<=mx;++i)
		tak[i]+=tak[i-1];
	for(re int i=len;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1;;k<<=1){
		re int cnt=0;
		for(re int i=len-k+1;i<=len;++i)
			snd[++cnt]=i;
		for(re int i=1;i<=len;++i)
			if(sa[i]>k)
				snd[++cnt]=sa[i]-k;
		for(re int i=0;i<=mx;++i)
			tak[i]=0;
		for(re int i=1;i<=len;++i)
			++tak[fst[i]];
		for(re int i=1;i<=mx;++i)
			tak[i]+=tak[i-1];
		for(re int i=len;i>=1;--i)
			sa[tak[fst[snd[i]]]--]=snd[i];
		for(re int i=1;i<=len;++i)
			snd[i]=fst[i];
		cnt=1;
		fst[sa[1]]=1;
		for(re int i=2;i<=len;++i)
			fst[sa[i]]=snd[sa[i]]==snd[sa[i-1]]&&snd[sa[i]+k]==snd[sa[i-1]+k]?cnt:++cnt;
		if(cnt==len)
			break;
		else
			mx=cnt;
	}
	for(re int i=1;i<=len;++i)
		rnk[sa[i]]=i;
	for(re int i=1,j=0;i<=len;++i)
		if(rnk[i]>1){
			if(j)
				--j;
			re int pos=sa[rnk[i]-1];
			for(;i+j<=len&&pos+j<=len&&s[i+j]==s[pos+j];++j);
			het[rnk[i]]=j;
		}
	re int l=1,r=0;
	if(col[sa[1]]){
		cnt[0]+=cnt[col[sa[1]]];
		++cnt[col[sa[1]]];
	}
	for(re int head=0,tail=0;;){
		for(;r<len&&cnt[0]<n;){
			++r;
			if(col[sa[r]]){
				cnt[0]+=(cnt[col[sa[r]]]==0);
				++cnt[col[sa[r]]];
			}
			for(;head<tail&&het[r]<=het[p[tail]];--tail);
			p[++tail]=r;
		}
		if(r==len&&cnt[0]<n)
			break;
		for(;cnt[0]==n;){
			if(cnt[col[sa[l]]]==1)
				ans=max(ans,het[p[head+1]]);
			if(col[sa[l]]){
				cnt[0]-=(cnt[col[sa[l]]]==1);
				--cnt[col[sa[l]]];
			}
			++l;
			if(p[head+1]==l)
				++head;
		}
	}
	printf("%d",ans);
	return 0;
}
