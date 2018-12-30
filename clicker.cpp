#include<cstdio>
#include<windows.h>
#define KEY_DOWN(KEY_NAME) ((GetAsyncKeyState(KEY_NAME)&0x8000)?1:0)
#define SET_COLOR(COLOR_NAME) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),COLOR_NAME)

int main(){
	system("cls");
	SET_COLOR(4);
	puts("Inactive");
	for(int s=0;;){
		if(KEY_DOWN('1')&&s!=2){
			for(;KEY_DOWN('1'););
			system("cls");
			SET_COLOR(2);
			puts("Active");
			s=1;
			continue;
		}
		if(KEY_DOWN('2')&&s!=2){
			for(;KEY_DOWN('2'););
			system("cls");
			SET_COLOR(4);
			puts("Inactive");
			s=0;
			continue;
		}
		if(KEY_DOWN('L')){
			for(;KEY_DOWN('L'););
			if(s!=2){
				system("cls");
				SET_COLOR(8);
				puts("Locked");
				s=2;
			}
			else{
				system("cls");
				SET_COLOR(4);
				puts("Inactive");
				s=0;
			}
			continue;
		}
		if(s==1){
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
			Sleep(1);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			Sleep(1);
			continue;
		}
	}
	return 0;
}
