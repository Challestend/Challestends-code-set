from flask import Flask,render_template,request,make_response
from json import JSONEncoder
import time,GrandfatherFashion

app=Flask("GrandfatherFashion")

@app.route("/add",methods=["POST","GET"])
def add():
	return GrandfatherFashion.Add(request.form["strs"].split(" "))

@app.route("/remove",methods=["POST","GET"])
def remove():
	return GrandfatherFashion.Remove(request.form["strs"].split(" "))

@app.route("/debug",methods=["POST","GET"])
def debug():
	return GrandfatherFashion.Debug()

@app.route("/speak",methods=["POST","GET"])
def speak():
	return GrandfatherFashion.Speak()

@app.route("/",methods=["GET"])
def home():
	return render_template("main.html")

if __name__=="__main__":
	app.run(port=8080)
