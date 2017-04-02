#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <string.h>  
#include <time.h>  
#include <string>
#include <vector>
#include<Windows.h>

using namespace std;

const int H = 20;   //��ͼ�ĸ�  
const int W = 40;  //��ͼ�ĳ�  
char GameMap[H][W];   //��Ϸ��ͼ  

int  dx[4] = { 0, 0, -1, 1 };  //���ҡ��ϡ��µķ���  
int  dy[4] = { -1, 1, 0, 0 };  //0   1    2   3

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
int foodx, foody;
bool isExistFood;
int  key;  //�������� 

// >= x, <= y���������
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
	memset(GameMap, ' ', sizeof(GameMap));  //��ʼ����ͼȫ��Ϊ��'.'  

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
	for (int i = 0; i < H; i++)   //��ͼ��ʾ  
	{
		for (int j = 0; j < W; j++)
			printf("%c", GameMap[i][j]);
		printf("\n");
	}

	printf("\nССC����̰����\n");
	printf("�����ⷽ�����ʼ��Ϸ\n");
}

void Button()  //ȡ������,���жϷ���  
{
	if (_kbhit() != 0) //��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0  
	{
		while (_kbhit() != 0)  //���ܴ��ڶ������,Ҫȫ��ȡ��,�����һ��Ϊ��  
			key = _getch(); //�������ӿ���̨��ȡ�������浽key��

		switch (key)
		{
			//��  
		case 75:
		{
			mySnake.sh.dir = 0;
			break;
		}
		//��  
		case 77:
		{
			mySnake.sh.dir = 1;
			break;
		}
		//��  
		case 72:
		{
			mySnake.sh.dir = 2;
			break;
		}
		//��  
		case 80:
		{
			mySnake.sh.dir = 3;
			break;
		}
		}
	}
}

void Initial()  //��ͼ�ĳ�ʼ��  
{
	int i, j;
	int hx, hy;
	system("title ̰����");  //����̨�ı���  

	memset(GameMap, ' ', sizeof(GameMap));  //��ʼ����ͼȫ��Ϊ��'.'  

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

	system("cls"); // ��������

	mySnake = initSnake(); //��ʼһ��С��

	setGraph();

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
	while (1)
	{
		Sleep(500); //�ӳٰ���(1000Ϊ1s),��ÿ����ˢ��һ�ε�ͼ  

		/***********�ı�����*****************/


		Move(); // snake move

		Button();

		if (isExistFood == false) // generate rand food
		{
			Create_food();
			isExistFood = true;
		}

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

	// check if eat food
	// TODO

	// �ȴ����������Ĳ��֣��ڴ����һ������
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