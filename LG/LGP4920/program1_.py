inf=open("program1.in","r")
ouf=open("program1.out","w")

for i in range(0,10):
	a,b,c=map(int,inf.readline().split())
	ouf.write("{}\n".format(a*b%c))
