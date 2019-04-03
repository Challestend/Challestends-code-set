#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 16
#define maxh 21
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define valid(a,lwr,upr) ((a)>=(lwr)&&(a)<(upr))

const int dx[8]={-1,-1,0,1,1,1,0,-1},dy[8]={0,-1,-1,-1,0,1,1,1};
const int fx[6]={-1,1,0,0,0,0},fy[6]={0,0,-1,1,0,0},fz[6]={0,0,0,0,-1,1};

struct pos{
	int x,y,z;

	pos(int _x=0,int _y=0,int _z=0){
		x=_x;
		y=_y;
		z=_z;
	}
};

int n,mh,x0,y0,r,c,m;
int blockCnt,finalHeight,innerCnt,outerCnt,doorCnt,doorMid,halfCnt,holeCnt,cornerCnt;
std::string opt;
int val[maxn][maxn],ex[maxn][maxn][maxh];
int vis[maxn][maxn][maxh];
pos h[maxn*maxn*maxh];

inline int check(int x,int y,int z){
	for(re int i=0;i<n;++i)
		for(re int j=0;j<n;++j)
			for(re int k=0;k<mh;++k)
				vis[i][j][k]=0;
	int head=-1,tail=0,gnd=0;
	h[0]=pos(x,y,z);
	vis[x][y][z]=1;
	gnd|=!z;
	for(;head<tail&&!gnd;){
		pos p=h[++head];
		for(re int i=0;i<6;++i){
			int _x=p.x+fx[i],_y=p.y+fy[i],_z=p.z+fz[i];
			if(valid(_x,0,n)&&valid(_y,0,n)&&valid(_z,0,mh)&&ex[_x][_y][_z]&&!vis[_z][_y][_z]){
				h[++tail]=pos(_x,_y,_z);
				vis[_x][_y][_z]=1;
				gnd|=!_z;
			}
		}
	}
	if(!gnd){
		for(re int i=0;i<=tail;++i){
			pos p=h[i];
			ex[p.x][p.y][p.z]=0;
		}
		return tail+1;
	}
	else
		return 0;
}

int main(){
	freopen("C:\\Users\\Challestend\\Downloads\\testdata(1).in","r",stdin);
	freopen("C:\\Users\\Challestend\\Downloads\\testdata(1).ans","w",stdout);
	std::cin>>n>>mh>>x0>>y0>>r>>c>>m;
	++mh;
	for(;m;--m){
		std::cin>>opt;
		if(opt=="ICE_BARRAGE"){
			int x,y,d,s,cnt=0;
			std::cin>>x>>y>>d>>s;
			for(re int i=0;i<=s&&valid(x,0,n)&&valid(y,0,n)&&!ex[x][y][0];++i,x+=dx[d],y+=dy[d])
				if(val[x][y]<4){
					++val[x][y];
					++cnt;
				}
			std::cout<<"CIRNO FREEZED "<<cnt<<" BLOCK(S)"<<std::endl;
		}
		if(opt=="MAKE_ICE_BLOCK"){
			int cnt=0;
			for(re int i=0;i<n;++i)
				for(re int j=0;j<n;++j)
					if(!ex[i][j][0]&&val[i][j]==4){
						val[i][j]=0;
						++blockCnt;
						++cnt;
					}
			std::cout<<"CIRNO MADE "<<cnt<<" ICE BLOCK(S),NOW SHE HAS "<<blockCnt<<" ICE BLOCK(S)"<<std::endl;
		}
		if(opt=="PUT_ICE_BLOCK"){
			int x,y,z;
			std::cin>>x>>y>>z;
			if(!blockCnt){
				std::cout<<"CIRNO HAS NO ICE_BLOCK"<<std::endl;
				continue;
			}
			int able=!z;
			for(re int i=0;i<6&&!able;++i){
				int _x=x+fx[i],_y=y+fy[i],_z=z+fz[i];
				valid(_x,0,n)&&valid(_y,0,n)&&valid(_z,0,mh)&&ex[_x][_y][_z]&&(able=1);
			}
			if(ex[x][y][z]||!able){
				std::cout<<"BAKA CIRNO,CAN\'T PUT HERE"<<std::endl;
				continue;
			}
			ex[x][y][z]=1;
			--blockCnt;
			if(!valid(x,x0,x0+r)||!valid(y,y0,y0+c))
				std::cout<<"CIRNO MISSED THE PLACE"<<std::endl;
			else
				if(valid(x,x0+1,x0+r-1)&&valid(y,y0+1,y0+c-1))
					std::cout<<"CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE"<<std::endl;
				else
					std::cout<<"CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS "<<blockCnt<<" ICE_BLOCK(S)"<<std::endl;
		}
		if(opt=="REMOVE_ICE_BLOCK"){
			int x,y,z;
			std::cin>>x>>y>>z;
			if(!ex[x][y][z]){
				std::cout<<"BAKA CIRNO,THERE IS NO ICE_BLOCK"<<std::endl;
				continue;
			}
			ex[x][y][z]=0;
			++blockCnt;
			int cnt=0;
			for(re int i=0;i<6;++i){
				int _x=x+fx[i],_y=y+fy[i],_z=z+fz[i];
				valid(_x,0,n)&&valid(_y,0,n)&&valid(_z,0,mh)&&ex[_x][_y][_z]&&(cnt+=check(_x,_y,_z));
			}
			if(cnt)
				std::cout<<"CIRNO REMOVED AN ICE_BLOCK,AND "<<cnt<<" BLOCK(S) ARE BROKEN"<<std::endl;
			else
				std::cout<<"CIRNO REMOVED AN ICE_BLOCK"<<std::endl;
		}
		if(opt=="MAKE_ROOF"){
			for(re int k=0;k<mh;++k){
				for(re int i=0;i<r;++i){
					ex[x0+i][y0][k]&&(finalHeight=max(finalHeight,k));
					ex[x0+i][y0+c-1][k]&&(finalHeight=max(finalHeight,k));
				}
				for(re int j=0;j<c;++j){
					ex[x0][y0+j][k]&&(finalHeight=max(finalHeight,k));
					ex[x0+r-1][y0+j][k]&&(finalHeight=max(finalHeight,k));
				}
			}
			++finalHeight;
			for(re int i=0;i<r;++i)
				for(re int j=0;j<c;++j)
					ex[x0+i][y0+j][finalHeight]?++blockCnt:ex[x0+i][y0+j][finalHeight]=1;
			if(blockCnt<r*c){
				std::cout<<"SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO MAKE ROOF"<<std::endl;
				continue;
			}
			if(mh<2||(r-2)*(c-2)<2){
				std::cout<<"SORRY CIRNO,HOUSE IS TOO SMALL"<<std::endl;
				continue;
			}
			blockCnt-=r*c;
			for(re int i=0;i<n;++i)
				for(re int j=0;j<n;++j)
					for(re int k=0;k<mh;++k){
						valid(i,x0+1,x0+r-1)&&valid(j,y0+1,y0+c-1)&&valid(k,0,finalHeight)&&ex[i][j][k]&&
						(ex[i][j][k]=0,++innerCnt);
						(!valid(i,x0,x0+r)||!valid(j,y0,y0+c)||!valid(k,0,finalHeight+1))&&ex[i][j][k]&&
						(ex[i][j][k]=0,++outerCnt);
					}
			std::cout<<innerCnt<<" ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED"<<std::endl;
			std::cout<<outerCnt<<" ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED"<<std::endl;
			blockCnt+=innerCnt+outerCnt;
			if(check(x0,y0,finalHeight)){
				std::cout<<"SORRY CIRNO,HOUSE IS BROKEN WHEN REMOVING BLOCKS"<<std::endl;
				continue;
			}
			for(re int k=0;k<2;++k){
				for(re int i=1;i<r-1;++i){
					!ex[x0+i][y0][k]&&(!ex[x0+i][y0][k^1]?++doorCnt,doorMid|=i==(r-1)/2||i==r/2:++halfCnt);
					!ex[x0+i][y0+c-1][k]&&(!ex[x0+i][y0+c-1][k^1]?++doorCnt,doorMid|=i==(r-1)/2||i==r/2:++halfCnt);
				}
				for(re int j=1;j<c-1;++j){
					!ex[x0][y0+j][k]&&(!ex[x0][y0+j][k^1]?++doorCnt,doorMid|=j==(c-1)/2||j==c/2:++halfCnt);
					!ex[x0+r-1][y0+j][k]&&(!ex[x0+r-1][y0+j][k^1]?++doorCnt,doorMid|=j==(c-1)/2||j==c/2:++halfCnt);
				}
			}
			for(re int k=2;k<finalHeight;++k){
				for(re int i=1;i<r-1;++i){
					holeCnt+=!ex[x0+i][y0][k];
					holeCnt+=!ex[x0+i][y0+c-1][k];
				}
				for(re int j=1;j<c-1;++j){
					holeCnt+=!ex[x0][y0+j][k];
					holeCnt+=!ex[x0+r-1][y0+j][k];
				}
			}
			for(re int k=0;k<finalHeight;++k){
				cornerCnt+=!ex[x0][y0][k]/* &&printf("(%d,%d,%d)\n",x0,y0,k) */;
				cornerCnt+=!ex[x0][y0+c-1][k]/* &&printf("(%d,%d,%d)\n",x0,y0+c-1,k) */;
				cornerCnt+=!ex[x0+r-1][y0][k]/* &&printf("(%d,%d,%d)\n",x0+r-1,y0,k) */;
				cornerCnt+=!ex[x0+r-1][y0+c-1][k]/* &&printf("(%d,%d,%d)\n",x0+r-1,y0+c-1,k) */;
			}
			// printf("%d %d %d %d\n",doorCnt,halfCnt,holeCnt,cornerCnt);
			holeCnt+=max(doorCnt-2,0)+halfCnt;
			// printf("%d %d %d %d\n",doorCnt,halfCnt,holeCnt,cornerCnt);
			if(blockCnt<holeCnt){
				std::cout<<"SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO FIX THE WALL"<<std::endl;
				continue;
			}
			blockCnt-=holeCnt;
			// printf("BLOCKCNT=%d\n",blockCnt);
			std::cout<<"GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE"<<std::endl;
			doorCnt/=2;
			std::cout<<(doorCnt?"DOOR IS OK":"HOUSE HAS NO DOOR")<<std::endl;
			!doorCnt&&(blockCnt+=2);
			std::cout<<(!holeCnt?"WALL IS OK":"WALL NEED TO BE FIXED")<<std::endl;
			std::cout<<(!cornerCnt?"CORNER IS OK":"CORNER NEED TO BE FIXED")<<std::endl;
			blockCnt=max(blockCnt-cornerCnt,0);
			std::cout<<"CIRNO FINALLY HAS "<<blockCnt<<" ICE_BLOCK(S)"<<std::endl;
			!innerCnt&&!outerCnt&&doorCnt&&doorMid&&!holeCnt&&!cornerCnt&&std::cout<<"CIRNO IS PERFECT!"<<std::endl;
		}
	}
	return 0;
}
