import os,time
import pyautogui as pag
from random import randint,choice,sample

partCnt=8
brain=[]
index={}
nxt=[
	[1,2,3,4],
	[2,3,4],
	[3,4],
	[5],
	[5],
	[6,7],
	[7],
	[-1]
]

class part(object):

	def __init__(self,name="",text={}):
		self.name=name
		self.text=text

	def write(self,stream=None):
		if stream is not None:
			stream.write("{0}: {1}\n".format(self.name,self.text))
		else:
			print("{0}: {1}".format(self.name,self.text))

def Init():
	os.system("mode con cols=120 lines=45")
	# data=open("GrandfatherFashion/data","r")
	data=open("data","r")
	for i in range(0,partCnt):
		cmd=data.readline().replace(": {",", ",-1).replace("}\n","",-1).replace("'","",-1).split(", ")
		name=cmd[0]
		text=set()
		for p in cmd[1::1]:
			text.add(p)
		brain.append(part(name,text))
		index.setdefault(name,i)

def Store():
	# data=open("GrandfatherFashion/data","w")
	data=open("data","w")
	for p in brain:
		p.write(data)

def Debug():
	for p in brain:
		p.write()

def Add(cmd):
	tp=index.get(cmd[0])
	s=cmd[1]
	if tp is not None:
		if s not in brain[tp].text:
			brain[tp].text.add(s)
			print("INFO: {0} {1} has been ccessfully added.".format(cmd[0],s))
		else:
			print("ERR!: {0} {1} already exists.".format(cmd[0],s))
	else:
		print("ERR!: Unknown type {0}.".format(cmd[0]))

def Erase(cmd):
	tp=index.get(cmd[0])
	s=cmd[1]
	if tp is not None:
		if s in brain[tp].text:
			brain[tp].text-={s}
			print("INFO: {0} {1} has been removed added.".format(cmd[0],s))
		else:
			print("ERR!: {0} {1} doesn't exit.".format(cmd[0],s))
	else:
		print("ERR!: Unknown type {0}.".format(cmd[0]))

def Print(times=1):
	for i in range(0,times):
		res="GrandfatherFashion: "
		cnt=randint(1,200)
		cur=0
		while cur>=0:
			res+=sample(brain[cur].text,1)[0]
			cur=choice(nxt[cur])
		print(res)

Init()
while True:
	cmd=input().split()
	opt=cmd[0].lower()
	if opt=="":
		continue
	elif opt=="exit":
		Store()
		break
	elif opt=="debug":
		Debug()
	elif opt=="add":
		Add(cmd[1::1])
	elif opt=="erase":
		Erase(cmd[1::1])
	elif opt=="print":
		Print()
	elif opt=="repeat":
		Print(int(cmd[1]))
	else:
		print("ERR!: Unknown command.")
