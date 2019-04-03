#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<windows.h>
#include<iostream>
#include<string>
#include<vector>
#define height 9
#define Width 120
#define rowPerPage 3
#define pageCnt ((rowCnt-1)/rowPerPage+1)
#define curPageSize (index<pageCnt?rowPerPage:(rowCnt-1)%rowPerPage+1)
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define FAQ(c1,c2,a) {\
	int curWidth=0;\
	for(int j=row[i-1].first;j<=row[i-1].second;++j){\
		std::string str=data[j-1].first;\
		int len=str.size();\
		std::cout<<" "<<c1<<c2;\
		a\
		std::cout<<c2<<c1<<" ";\
		curWidth+=len+6;\
	}\
	for(;curWidth<Width;putchar(' '),++curWidth);\
}
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME)&0x8000)?1:0)
#define SET_COLOR(COLOR_NAME) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),COLOR_NAME)

char lines[][120]={
	"",
	" #############  ################  #############  ##########  #######  ######## ",
	" |           |  |              |  |           |  |        |  |     |  |      | ",
	" | Prev Page |  | Page    /    |  | Next Page |  | Append |  | Pop |  | Quit | ",
	" |           |  |              |  |           |  |        |  |     |  |      | ",
	" #############  ################  #############  ##########  #######  ######## "
};

int strCnt,rowCnt,lastWidth=Width,index=1;
std::vector<std::pair<std::string,int> > data;
std::vector<std::pair<int,int> > row;

inline POINT GetCursorPos(){
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(GetForegroundWindow(),&p);
	return p;
}

inline void Insert(std::string str,int cnt){
	int len=str.size();
	for(;len<10;str=str+' ',++len);
	++strCnt;
	data.push_back(std::make_pair(str,cnt));
	if(lastWidth+len+6>Width){
		lastWidth=len+6;
		++rowCnt;
		row.push_back(std::make_pair(strCnt,strCnt));
	}
	else{
		lastWidth+=len+6;
		++row[rowCnt-1].second;
	}
}

inline void Print(std::string info="",int col=7){
	system("cls");
	int lwr=(index-1)*rowPerPage+1,upr=min(index*rowPerPage,rowCnt);
	for(int i=lwr;i<=upr;++i){
		printf("%-120s",lines[0]);
		FAQ('#','#',for(int k=1;k<=len;++k)putchar('#');)
		FAQ('|',' ',for(int k=1;k<=len;++k)putchar(' ');)
		FAQ('|',' ',std::cout<<str;)
		FAQ('|',' ',for(int k=1;k<=len;++k)putchar(' ');)
		FAQ('|',' ',printf("%-10d",data[j-1].second);for(int k=11;k<=len;++k)putchar(' ');)
		FAQ('|',' ',for(int k=1;k<=len;++k)putchar(' ');)
		FAQ('#','#',for(int k=1;k<=len;++k)putchar('#');)
		printf("%-120s",lines[0]);
	}
	lines[3][25]=index%10+48;
	lines[3][24]=index/10%10?index/10%10+48:32;
	lines[3][23]=index/100%10?index/100%10+48:32;
	lines[3][29]=pageCnt%10+48;
	lines[3][28]=pageCnt/10%10?pageCnt/10%10+48:32;
	lines[3][27]=pageCnt/100%10?pageCnt/100%10+48:32;
	printf("%-120s",lines[0]);
	printf("%-120s",lines[1]);
	printf("%-120s",lines[2]);
	printf("%-120s",lines[3]);
	printf("%-120s",lines[4]);
	printf("%-120s",lines[5]);
	printf("%-120s",lines[0]);
	printf("%-120s",lines[0]);
	SET_COLOR(col);
	std::cout<<info;
	SET_COLOR(7);
	lines[3][23]=lines[3][24]=lines[3][25]=lines[3][27]=lines[3][28]=lines[3][29]=32;
}

inline void Init(){
	system("mode con cols=120 lines=45");
	MoveWindow(GetForegroundWindow(),288,60,1508,1014,TRUE);
	std::fstream in;
	in.open("data");
	std::string str;
	int cnt;
	for(;in>>str>>cnt;Insert(str,cnt));
	in.close();
}

inline void Store(){
	std::fstream out;
	out.open("data");
	for(int i=1;i<=strCnt;++i)
		out<<data[i-1].first<<" "<<data[i-1].second<<std::endl;
	out.close();
}

int main(){
	Init();
	Print();
	for(;;Sleep(20)){
		if(KEY_DOWN(MOUSE_WHEELED)){
			POINT p=GetCursorPos();
			if(p.y>(curPageSize*height+1)*16&&p.y<=(curPageSize*height+6)*16){
				if(p.x>1*8&&p.x<=14*8){
					if(index>1){
						--index;
						Print();
					}
					else
						Print("No Prev Page.",4);
					continue;
				}
				if(p.x>34*8&&p.x<=47*8){
					if(index<pageCnt){
						++index;
						Print();
					}
					else
						Print("No Next Page.",4);
					continue;
				}
				if(p.x>49*8&&p.x<=59*8){
					Print("A string without spaces is wanted:\n");
					std::string str;
					std::cin>>str;
					if(str.size()+6<=Width){
						Insert(str,0);
						index=pageCnt;
						Print();
					}
					else
						Print("Too long.",4);
					continue;
				}
				if(p.x>61*8&&p.x<=68*8){
					if(!strCnt)
						Print("Failed.",4);
					else{
						if(row[rowCnt-1].first<row[rowCnt-1].second){
							lastWidth-=data[strCnt-1].first.size()+6;
							--row[rowCnt-1].second;
						}
						else{
							--rowCnt;
							row.pop_back();
							lastWidth=rowCnt?0:Width;
							if(rowCnt)
								for(int j=row[rowCnt-1].first;j<=row[rowCnt-1].second;++j)
									lastWidth+=data[j-1].first.size()+6;
						}
						--strCnt;
						data.pop_back();
						index=pageCnt;
						Print();
					}
					continue;
				}
				if(p.x>70*8&&p.x<=78*8)
					break;
			}
			int lwr=(index-1)*rowPerPage+1,upr=min(index*rowPerPage,rowCnt);
			for(int i=lwr;i<=upr;++i)
				for(int curWidth=0,j=row[i-1].first;j<=row[i-1].second;++j){
					std::string str=data[j-1].first;
					int len=str.size();
					if(p.x>(curWidth+1)*8&&p.x<=(curWidth+len+5)*8){
						if(p.y>((i-lwr)*height+1)*16&&p.y<=((i-lwr)*height+3)*16){
							++data[j-1].second;
							Print();
							break;
						}
						if(p.y>((i-lwr)*height+6)*16&&p.y<=((i-lwr)*height+8)*16){
							--data[j-1].second;
							Print();
							break;
						}
					}
					curWidth+=len+6;
				}
		}
	}
	Store();
	return 0;
}
