#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <string.h>  
#include <time.h>  
#include <string>
#include <vector>

using namespace std;

const int H = 20;   //地图的高  
const int W = 20;  //地图的长  
char GameMap[H][W];   //游戏地图  

int  dx[4] = {0, 0, -1, 1};  //左、右、上、下的方向  
int  dy[4] = {-1, 1, 0, 0};  

void Initial();  //数据初始化，并绘制初始地图  
void Refresh();   //改变数据，刷新显示地图
void Move(); // 移动

typedef struct head{
	int x;
	int y;
	int dir;
	head(int _x = -1, int _y = -1, int _dir = -1)
	{
		x = _x;
		y = _y;
		dir = _dir;
	}
}Head; 

typedef struct body{
	int x;
	int y;
	body(int _x = -1, int _y = -1)
	{
		x = _x;
		y = _y;
	}
}Body; 

typedef struct snake
{
	Head sh;
	vector<Body> sb;
	int sbLen;
}Snake;

Snake mySnake; // 全局变量

Snake initSnake()
{
	int dir = 0;
	
	Snake sn;

	Head he(2,W-4,0);
	sn.sh = he;

	sn.sbLen = 2;
	Body bd1(2, W-3);
	Body bd2(2, W-2);
	
	sn.sb.push_back(bd1);
	sn.sb.push_back(bd2);
	
	return sn;
}

void setGraph()
{
	memset(GameMap, ' ', sizeof(GameMap));  //初始化地图全部为空'.'  

	for(int i=0;i<W;i++)
	{
		GameMap[0][i] = '*';
		GameMap[H-1][i] = '*';
	}
	for(int i=1;i<H-1;i++)
	{
		GameMap[i][0] = '*';
		GameMap[i][W-1] = '*';
	}

	GameMap[mySnake.sh.x][mySnake.sh.y] = '@';
	for(int i=0;i<mySnake.sbLen;i++)
	{
		GameMap[mySnake.sb[i].x][mySnake.sb[i].y] = '#';
	}
}


void paint()
{
	for(int i = 0; i < H; i++)   //地图显示  
	{   
		for(int j = 0; j < W; j++)  
			printf("%c", GameMap[i][j]);  
		printf("\n");  
	}  

	printf("\n小小C语言贪吃蛇\n");  
	printf("按任意方向键开始游戏\n");    
}

void Initial()  //地图的初始化  
{  
	int i, j;  
	int hx, hy;  
	system("title 贪吃蛇");  //控制台的标题  
	
	memset(GameMap, ' ', sizeof(GameMap));  //初始化地图全部为空'.'  

	for(int i=0;i<W;i++)
	{
		GameMap[0][i] = '*';
		GameMap[H-1][i] = '*';
	}
	for(int i=1;i<H-1;i++)
	{
		GameMap[i][0] = '*';
		GameMap[i][W-1] = '*';
	}

	system("cls"); // 清屏函数

	mySnake = initSnake(); //初始一条小蛇
	
	paint();

	//for(i = 0; i < H; i++)   //地图显示  
	//{   
	//	for(j = 0; j < W; j++)  
	//		printf("%c", GameMap[i][j]);  
	//	printf("\n");  
	//}  

	//printf("\n小小C语言贪吃蛇\n");  
	//printf("按任意方向键开始游戏\n");    
}

void Refresh()  //刷新显示地图  
{  
	int i, j;  
	while(1)  
	{    
		_sleep(500); //延迟半秒(1000为1s),即每半秒刷新一次地图  
		
		/***********改变数据*****************/
		
		Move(); // 移动


		/****************************/
		system("cls");   //清空地图再显示刷新的地图  
		paint(); // 重画 

		/*for(i = 0; i < H; i++)   
		{   
			for(j = 0; j < W; j++)  
				printf("%c", GameMap[i][j]);  
			printf("\n");  
		}  

		printf("\n小小C语言贪吃蛇\n");  
		printf("按任意方向键开始游戏\n");  */
	}  
} 

void Move()
{
	int newHeadx = mySnake.sh.x + dx[mySnake.sh.dir];
	int newHeady = mySnake.sh.y + dy[mySnake.sh.dir];

	for(int i=0;i<mySnake.sbLen;i++)
	{
		mySnake.sb[i].x = mySnake.sb[i].x + dx[mySnake.sh.dir];
		mySnake.sb[i].y = mySnake.sb[i].y + dy[mySnake.sh.dir];
	}

	mySnake.sh.x = newHeadx;
	mySnake.sh.y = newHeady;

	setGraph();
}

int main()   
{  
	Initial();  
	Refresh();
	return 0;  
} 