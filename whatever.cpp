#include<bits/stdc++.h>
using namespace std;

queue<int>q;
char ans[17]=" DDDBBAAAABABBBB";

int main()
{
	srand(time(NULL));
	int score=0;
	for (int i=1; i<=15; ++i)
	{
		char c=rand()%4+'A';
		if (c==ans[i]) score+=2,q.push(i);
		printf("%c",c);
		if (i%5==0) printf(" ");
	}
	puts("");
	printf("Right:");
	while (!q.empty()) printf("%d ",q.front()),q.pop();
	printf("\nScore:%d\n",score);
}
