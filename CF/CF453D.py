F=[]
cnt=[]
a=[]
G=[]

def cltpow(x,y):
	res=1
	while y:
		if y&1:
			res*=x
		x*=x
		y>>=1
	return res

n,m,mod=map(int,input().split())
N=1<<n
for i in input().split():
	F.append(int(i))
cnt.append(0)
for i in range(1,N):
	cnt.append(cnt[i>>1]+(i&1))
for i in input().split():
	a.append(int(i))
for i in range(0,N):
	G.append(a[cnt[i]])
p=1
while p<N:
	i=0
	while i<N:
		for j in range(i,i+p):
			x=F[j]
			y=F[j+p]
			F[j]=x+y
			F[j+p]=x-y
		i+=p<<1
	p<<=1
p=1
while p<N:
	i=0
	while i<N:
		for j in range(i,i+p):
			x=G[j]
			y=G[j+p]
			G[j]=x+y
			G[j+p]=x-y
		i+=p<<1
	p<<=1
for i in range(0,N):
	F[i]=F[i]*cltpow(G[i],m)
p=1
while p<N:
	i=0
	while i<N:
		for j in range(i,i+p):
			x=F[j]
			y=F[j+p]
			F[j]=(x+y)>>1
			F[j+p]=(x-y)>>1
		i+=p<<1
	p<<=1
for i in range(0,N):
	print(F[i]%mod)
