try:
	while True:
		S=[input()]
		n=len(S[0])
		D={S[0]:0}
		lwr=0
		upr=0

		for i in range(0,2281701377):
			S.append("")
			for j in range(0,n):
				if S[i][(j+1)%n]!=S[i][(j+n-1)%n]:
					S[i+1]+="1"
				else:
					S[i+1]+="0"
			lwr=D.setdefault(S[i+1],i+1)
			upr=i+1
			if lwr<upr:
				break
		print("----------------")
		for i in range(0,upr+1):
			print(" !"[i>=lwr],S[i])
except KeyboardInterrupt:
	print("FAQ")
