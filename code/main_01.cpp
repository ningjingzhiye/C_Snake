#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <string.h>  
#include <time.h>  
#include <string>
#include <vector>

using namespace std;

const int H = 20;   //��ͼ�ĸ�  
const int W = 20;  //��ͼ�ĳ�  
char GameMap[H][W];   //��Ϸ��ͼ  

int  dx[4] = {0, 0, -1, 1};  //���ҡ��ϡ��µķ���  
int  dy[4] = {-1, 1, 0, 0};  

void Initial();  //���ݳ�ʼ���������Ƴ�ʼ��ͼ  
void Refresh();   //�ı����ݣ�ˢ����ʾ��ͼ
void Move(); // �ƶ�

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

Snake mySnake; // ȫ�ֱ���

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
	memset(GameMap, ' ', sizeof(GameMap));  //��ʼ����ͼȫ��Ϊ��'.'  

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
	for(int i = 0; i < H; i++)   //��ͼ��ʾ  
	{   
		for(int j = 0; j < W; j++)  
			printf("%c", GameMap[i][j]);  
		printf("\n");  
	}  

	printf("\nССC����̰����\n");  
	printf("�����ⷽ�����ʼ��Ϸ\n");    
}

void Initial()  //��ͼ�ĳ�ʼ��  
{  
	int i, j;  
	int hx, hy;  
	system("title ̰����");  //����̨�ı���  
	
	memset(GameMap, ' ', sizeof(GameMap));  //��ʼ����ͼȫ��Ϊ��'.'  

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

	system("cls"); // ��������

	mySnake = initSnake(); //��ʼһ��С��
	
	paint();

	//for(i = 0; i < H; i++)   //��ͼ��ʾ  
	//{   
	//	for(j = 0; j < W; j++)  
	//		printf("%c", GameMap[i][j]);  
	//	printf("\n");  
	//}  

	//printf("\nССC����̰����\n");  
	//printf("�����ⷽ�����ʼ��Ϸ\n");    
}

void Refresh()  //ˢ����ʾ��ͼ  
{  
	int i, j;  
	while(1)  
	{    
		_sleep(500); //�ӳٰ���(1000Ϊ1s),��ÿ����ˢ��һ�ε�ͼ  
		
		/***********�ı�����*****************/
		
		Move(); // �ƶ�


		/****************************/
		system("cls");   //��յ�ͼ����ʾˢ�µĵ�ͼ  
		paint(); // �ػ� 

		/*for(i = 0; i < H; i++)   
		{   
			for(j = 0; j < W; j++)  
				printf("%c", GameMap[i][j]);  
			printf("\n");  
		}  

		printf("\nССC����̰����\n");  
		printf("�����ⷽ�����ʼ��Ϸ\n");  */
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