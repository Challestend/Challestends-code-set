#include<cstdio>
#include<cstdlib>

int main() {
	for(int cnt=1;cnt<=100;++cnt){
		system("cls");
		printf("Running on test %d...\n",cnt);
		system("random.exe");
		system("T53537_chtholly_tree.exe");
		system("T53537_divided_blocks.exe");
		if (system("fc T53537.out T53537.ans > nul")) {
			system("cls");
			printf("Wrong answer on test %d.\n",cnt);
			system("fc T53537.out T53537.ans");
			return 0;
		}
	}
	system("cls");
	puts("Accepted.");
	return 0;
}
