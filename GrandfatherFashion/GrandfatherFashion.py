from random import randint

partCnt=8
Name=["主语","转义","状语","谓语（无宾补）","谓语（有宾补）","宾语","宾语补足语","句尾"]
Text=[]
Order=[
	[0,3,5,7],
	[0,1,3,5,7],
	[0,2,3,5,7],
	[0,1,2,3,5,7],
	# [0,4,5,6,7],
	# [0,1,4,5,6,7],
	# [0,2,4,5,6,7],
	# [0,1,2,4,5,6,7],
	[0,5,6,7],
	[0,1,5,6,7],
	[0,2,5,6,7],
	[0,1,2,5,6,7]
]

def randomElement(lst):
	return lst[randint(0,len(lst)-1)]

def Append(tp,s):
	s=s.replace("\n","",-1)
	Text[tp].append(s)
	Text[tp].sort()
	print("潮爷：{0} \"{1}\" 已被成功追加。".format(Name[tp],s))

def Erase(tp,x):
	s=Text[tp][x]
	for i in range(x,len(Text[tp])-1):
		Text[tp][i]=Text[tp][i+1]
	Text[tp].pop()
	Text[tp].sort()
	print("潮爷：{0} \"{1}\" 已被成功移除。".format(Name[tp],s))

def Print():
	res="潮爷："
	x=randomElement(Order)
	for i in range(0,len(x)):
		if len(Text[x[i]])==0:
			print("潮爷：找不到合法的 {0}。".format(Name[x[i]]))
			return
		else:
			res=res+randomElement(Text[x[i]])
	print(res)

def Init():
	# data=open("GrandfatherFashion/data.txt","r")
	data=open("data","r")
	for i in range(0,partCnt):
		Text.append(data.readline().replace("[","",-1).replace("]","",-1).replace("\'","",-1).replace(",","",-1).split())

def Store():
	# data=open("GrandfatherFashion/data.txt","w")
	data=open("data","w")
	for i in range(0,partCnt):
		data.write("{0}\n".format(Text[i]))

def Debug():
	for i in range(0,partCnt):
		print("{0}:\n{1}".format(Name[i],Text[i]))

Init()
while True:
	opt=input()
	if opt=="append":
		tp=int(input())
		if tp>=0 and tp<partCnt:
			s=input()
			Append(tp,s)
		else:
			print("潮爷：无法识别的类型。")
	if opt=="erase":
		tp=int(input())
		if tp>=0 and tp<partCnt:
			x=int(input())
			if x>=0 and x<len(Text[tp]):
				Erase(tp,x)
			else:
				print("潮爷：下标越界。")
		else:
			print("潮爷：无法识别的类型。")
	elif opt=="print":
		Print()
	elif opt=="repeat":
		cnt=int(input())
		for i in range(0,cnt):
			Print()
	elif opt=="exit":
		Store()
		break
	elif opt=="debug":
		Debug()
	else:
		print("潮爷：无法识别的指令。")
