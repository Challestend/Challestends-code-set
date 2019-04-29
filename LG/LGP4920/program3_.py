maxull=18446744073709551615

inf=open("program3.in","r")
ouf=open("program3.out","w")

n=int(inf.readline().split()[0])
s0=n+1
s1=n*(n+1)//2
s2=n*(n+1)*(2*n+1)//6
s3=s1*s1
s4=n*(n+1)*(2*n+1)*(3*n*n+3*n-1)//30

ouf.write("{}\n{}\n{}\n{}\n{}\n{}\n{}\n{}\n{}\n{}\n".format(
	s0&maxull,
	s0&maxull,
	s1&maxull,
	s1&maxull,
	s2&maxull,
	s2&maxull,
	s3&maxull,
	s3&maxull,
	s4&maxull,
	s4&maxull
))
