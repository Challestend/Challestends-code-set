#include<cstdio>
#include<iostream>
#include<string>
#include<set>
#define maxn 233333

int n;
std::set<std::string> teacher,student,playing,caught;
std::string s,cur;
bool watch;

void teacherEvent(){
    if(s=="came!"){
        watch=true;
        for(std::set<std::string>::iterator p=playing.begin();p!=playing.end();++p)
            caught.insert(*p);
        playing.clear();
    }
    else
        if(s=="left!")
            watch=false;
}

void studentEvent(){
    if(s=="started playing games!")
        if(watch)
            caught.insert(cur);
        else
            playing.insert(cur);
    else
        if(s=="stopped playing games!")
            playing.erase(cur);
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<3;++i)
        std::cin>>s,teacher.insert(s);
    for(int i=0;i<5;++i)
        std::cin>>s,student.insert(s);
    for(int i=0;i<=n;++i){
        getline(std::cin,s);
        int pos=s.find(32);
        if(pos==-1)
            continue;
        cur=s.substr(0,pos),s=s.substr(pos+1);
        if(teacher.count(cur))
            teacherEvent();
        else
            if(student.count(cur))
                studentEvent();
            else
                continue;
    }
    if(caught.size()){
        for(std::set<std::string>::iterator p=caught.begin();p!=caught.end();++p)
            std::cout<<*p,putchar(32);
        putchar(10);
    }
    if(caught.size()==0)
        puts("How Good Oiers Are!");
    if(caught.size()==5)
        puts("How Bad Oiers Are!");
    return 0;
}
