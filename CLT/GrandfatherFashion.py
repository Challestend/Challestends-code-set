from random import randint,choice,sample
from json import JSONEncoder

def Init():
	brain=set()
	lst=open("data","r").readline().replace("{","",-1).replace("}","",-1).replace("\'","",-1).split(", ")
	for string in lst:
		if string not in brain:
			brain^={string}
	return brain

def Store(brain):
	open("data","w").write(str(brain))

def Add(strs):
	brain=Init()
	res=set()
	for string in strs:
		if string not in brain:
			brain^={string}
		else:
			res^={string}
	if res==set():
		Store(brain)
		return JSONEncoder().encode({
			"code":0,
			"data":"All strings successfully added."
		})
	else:
		return JSONEncoder().encode({
			"code":-1,
			"data":"{} already exist.".format(str(res))
		})

def Remove(strs):
	brain=Init()
	res=set()
	for string in strs:
		if string in brain:
			brain^={string}
		else:
			res^={string}
	if res==set():
		Store(brain)
		return JSONEncoder().encode({
			"code":0,
			"data":"All strings successfully removed."
		})
	else:
		return JSONEncoder().encode({
			"code":-1,
			"data":"{} don't exit.".format(str(res))
		})

def Debug():
	brain=Init()
	return JSONEncoder().encode({
		"code":0,
		"data":str(brain)+"(Current Size={})".format(len(brain))
	})

def Speak():
	brain=Init()
	return JSONEncoder().encode({
		"code":0,
		"data":"".join(sample(brain,randint(0,len(brain))))
	})
