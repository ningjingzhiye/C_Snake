
# 运行环境

win7 + vs2010、vs2013

# 设计思路与数据结构
```
char GameMap[H][W];   //游戏地图  

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
```

## 画图数据设计

## 蛇数据设计

```
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
```

蛇 = 蛇头（坐标+方向） + 蛇身（坐标）

vector -> list （主要是吃食物需要插入，list效率高于vector）

## 运行逻辑
```
sleep
clear
repaint
```

# 程序运行版本与运行截图

## 1 实现打印小蛇
![](./imgs/01.png)

## 2 实现能跑动的小蛇

根据方向让蛇数据变化，在重画显示的时候可以看到移动效果

```
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
```


## 3 处理蛇移动 改变数据
```
void Move()
{
	int newHeadx = mySnake.sh.x + dx[mySnake.sh.dir];
	int newHeady = mySnake.sh.y + dy[mySnake.sh.dir];

	/*  //error codes
    for(int i=0;i<mySnake.sbLen;i++)
	{
		mySnake.sb[i].x = mySnake.sb[i].x + dx[mySnake.sh.dir];
		mySnake.sb[i].y = mySnake.sb[i].y + dy[mySnake.sh.dir];
	}
    */
    //
	for(int i=1;i<mySnake.sbLen;i++){
		mySnake.sb[i].x=mySnake.sb[i-1].x;
		mySnake.sb[i].y=mySnake.sb[i-1].y;
	}
	mySnake.sb[0].x = mySnake.sh.x;
	mySnake.sb[0].y = mySnake.sh.y;

	mySnake.sh.x = newHeadx;
	mySnake.sh.y = newHeady;

	setGraph();
}
```

## 4 键盘事件添加,控制蛇移动的方向

```
int key; // 全局变量

void Button()
{
	if(kbhit() != 0) //检查当前是否有键盘输入，若有则返回一个非0值，否则返回0  
	{   
		while(kbhit() != 0)  //可能存在多个按键,要全部取完,以最后一个为主  
		key = getch(); //将按键从控制台中取出并保存到key中  
		switch(key)  
		{   //左  
			case 75: 
					mySnake.sh.dir = 0;
				break;  
				//右  
				case 77:  
					mySnake.sh.dir = 1;
				break;  
				//上  
			case 72:  
					mySnake.sh.dir = 2;
				break;  
				//下  
			case 80:  
					mySnake.sh.dir = 3;
				break;  
		}  
	}  
}
```

## 5 随机产生食物
![](./imgs/02.png)

```
srand((unsigned)(time(NULL)));

int randint(int x, int y)
{
	int ans = rand() % (y - x + 1) + x;
	return ans;
}

bool checkCollidWithSnakeHead(int x, int y)
{
	if(GameMap[x][y] == '@')
		return true;
	return false;
}

bool checkCollidWithSnakeBody(int x, int y)
{
	if(GameMap[x][y] == '#')
		return true;
	return false;
}

void Create_food()
{
	int px = randint(1, H-1);
	int py = randint(1, W-1);
	while( checkCollidWithSnakeHead(px, py) || checkCollidWithSnakeBody(px, py))
	{
		px = randint(1, H-1);
		py = randint(1, W-1);
	}
	foodx = px;
	foody = py;

	GameMap[foodx][foody] = '%';
}
```

在void setGraph()中需要重新设置,加入如下的语句
```
if(isExistFood)
{
	GameMap[foodx][foody] = '%';
}
```

## 6 吃食物

## 7 死亡判断

## 8 分数

## 9 面向过程 =》 面向对象

对象： 成员 与 成员方法（属性） =》 面向对象

# 不足与改进

有些函数在不同编译器是不一样的, 比如下面的一些函数，vs6.0, vs2010， vs2013不同的

```
kbhit -> _kbhit
getch -> _getch
sleep -> _sleep -> Sleep（需要包含 window.h）
```


# 作者与参考

* 作者git

 https://github.com/ningjingzhiye

* 主要参考

http://blog.csdn.net/hai8902882/article/details/6976490
