#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <string.h>  
#include <time.h>  
#include <string>
#include <vector>
#include<Windows.h>

using namespace std;

const int H = 20;   //地图的高  
const int W = 40;  //地图的长  
char GameMap[H][W];   //游戏地图  

int  dx[4] = { 0, 0, -1, 1 };  //左、右、上、下的方向  
int  dy[4] = { -1, 1, 0, 0 };  //0   1    2   3

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
int foodx, foody;
bool isExistFood;
int  key;  //按键保存 

// >= x, <= y的随机整数
int randint(int x, int y)
{
	int ans = rand() % (y - x + 1) + x;
	return ans;
}

bool checkCollidWithSnakeHead(int x, int y)
{
	if (GameMap[x][y] == '@')
		return true;
	return false;
}

bool checkCollidWithSnakeBody(int x, int y)
{
	if (GameMap[x][y] == '#')
		return true;
	return false;
}

void Create_food()
{
	int px = randint(1, H - 1);
	int py = randint(1, W - 1);
	while (checkCollidWithSnakeHead(px, py) || checkCollidWithSnakeBody(px, py))
	{
		px = randint(1, H - 1);
		py = randint(1, W - 1);
	}
	foodx = px;
	foody = py;

	GameMap[foodx][foody] = '%';
}

Snake initSnake()
{
	isExistFood = false;
	foodx = 0;
	foody = 0;

	int dir = 0;

	Snake sn;

	int head_randx = randint(H / 3, H / 3 * 2);
	int head_randy = randint(W / 3, W / 3 * 2);
	Head he(head_randx, head_randy, 0);
	sn.sh = he;

	sn.sbLen = 2;
	Body bd1(head_randx, head_randy + 1);
	Body bd2(head_randx, head_randy + 2);

	sn.sb.push_back(bd1);
	sn.sb.push_back(bd2);

	return sn;
}

void setGraph()
{
	memset(GameMap, ' ', sizeof(GameMap));  //初始化地图全部为空'.'  

	if (isExistFood)
	{
		GameMap[foodx][foody] = '%';
	}

	for (int i = 0; i<W; i++)
	{
		GameMap[0][i] = '*';
		GameMap[H - 1][i] = '*';
	}
	for (int i = 1; i<H - 1; i++)
	{
		GameMap[i][0] = '*';
		GameMap[i][W - 1] = '*';
	}

	GameMap[mySnake.sh.x][mySnake.sh.y] = '@';
	for (int i = 0; i<mySnake.sbLen; i++)
	{
		GameMap[mySnake.sb[i].x][mySnake.sb[i].y] = '#';
	}
}

void paint()
{
	for (int i = 0; i < H; i++)   //地图显示  
	{
		for (int j = 0; j < W; j++)
			printf("%c", GameMap[i][j]);
		printf("\n");
	}

	printf("\n小小C语言贪吃蛇\n");
	printf("按任意方向键开始游戏\n");
}

void Button()  //取出按键,并判断方向  
{
	if (_kbhit() != 0) //检查当前是否有键盘输入，若有则返回一个非0值，否则返回0  
	{
		while (_kbhit() != 0)  //可能存在多个按键,要全部取完,以最后一个为主  
			key = _getch(); //将按键从控制台中取出并保存到key中

		switch (key)
		{
			//左  
		case 75:
		{
			mySnake.sh.dir = 0;
			break;
		}
		//右  
		case 77:
		{
			mySnake.sh.dir = 1;
			break;
		}
		//上  
		case 72:
		{
			mySnake.sh.dir = 2;
			break;
		}
		//下  
		case 80:
		{
			mySnake.sh.dir = 3;
			break;
		}
		}
	}
}

void Initial()  //地图的初始化  
{
	int i, j;
	int hx, hy;
	system("title 贪吃蛇");  //控制台的标题  

	memset(GameMap, ' ', sizeof(GameMap));  //初始化地图全部为空'.'  

	for (int i = 0; i<W; i++)
	{
		GameMap[0][i] = '*';
		GameMap[H - 1][i] = '*';
	}
	for (int i = 1; i<H - 1; i++)
	{
		GameMap[i][0] = '*';
		GameMap[i][W - 1] = '*';
	}

	system("cls"); // 清屏函数

	mySnake = initSnake(); //初始一条小蛇

	setGraph();

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
	while (1)
	{
		Sleep(500); //延迟半秒(1000为1s),即每半秒刷新一次地图  

		/***********改变数据*****************/


		Move(); // snake move

		Button();

		if (isExistFood == false) // generate rand food
		{
			Create_food();
			isExistFood = true;
		}

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

	// check if eat food
	// TODO

	// 先处理身体后面的部分，在处理第一个身体
	for (int i = 1; i<mySnake.sbLen; i++)
	{
		mySnake.sb[i].x = mySnake.sb[i - 1].x;
		mySnake.sb[i].y = mySnake.sb[i - 1].y;
	}
	mySnake.sb[0].x = mySnake.sh.x;
	mySnake.sb[0].y = mySnake.sh.y;

	mySnake.sh.x = newHeadx;
	mySnake.sh.y = newHeady;

	setGraph();
}

int main()
{
	srand((unsigned)(time(NULL)));
	Initial();
	Refresh();
	return 0;
}