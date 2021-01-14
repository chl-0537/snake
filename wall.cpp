#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <windows.h>
#include <queue>

struct Snake
{
	int x[100];					//蛇
	int y[100];
	int len = 2;
	std::string dir = "right";	//蛇头方向right,left,up,down
};

class Game
{
public:
	enum
	{
		Heigh = 37,		//界面高度
		Width = 37		//界面宽度
	};
	char wallArray[Heigh + 2][Width + 2];
	Snake mysnake;		//蛇
	int fx;
	int fy;				//记录食物的坐标
	int mytime = 150;	//蛇前进的速度
	int count;			//记录蛇的步数
	void init_wall();	//初始化墙壁
	void draw_surface();	//输出墙壁
	void set_content(int x, int y, char c);//设置内容
	char get_content(int x, int y);		//获取当前位置的内容
	void init_snake();  //初始化蛇
	void move_snake();	//蛇动
	void control(char c);//控制蛇的移动
	void create_food();	//设置食物
	int eat_food();		//判断蛇是不是吃到了食物
	void chang();		//蛇的长度加一
	int if_failed();		//是不是赢了
	void printlose();
};

void Game::init_wall()
{
	int i, j;
	for (i = 0;i <= Heigh + 1;i++)
	{
		for (j = 0;j <= Width + 1;j++)
		{
			if (i == 0 || j == 0 || i == Heigh + 1 || j == Width + 1)
			{
				wallArray[i][j] = '*';
			}
			else
			{
				wallArray[i][j] = ' ';
			}
		}
	}
}//一个矩阵，周围一圈用“*”围起来，中间是的空白处

void Game::draw_surface()
{
	int i, j;
	for (i = 0;i <= Heigh + 1;i++)
	{
		for (j = 0;j <= Width + 1;j++)
		{
			std::cout << wallArray[i][j] << ' ';
		}
		if (i == 2)
		{
			std::cout << "不会有人不会玩吧？不会吧不会吧？";
		}
		if (i == 3)
		{
			std::cout << "年轻人，我劝你，耗子尾汁";
		}
		if (i == 4)
		{
			std::cout << "提示：";
		}
		if (i == 5)
		{
			std::cout << "请开启大写";
		}
		if (i == 6)
		{
			std::cout << "w向上，s向下，a向左，d向右";
		}
		if (i == 7)
		{
			std::cout << "按下w、s、a、d开始";
		}
		std::cout << std::endl;
	}
}//打个盘，加一点提示

void Game::set_content(int x, int y, char c)
{
	wallArray[x][y] = c;
}

char Game::get_content(int x, int y)
{
	return wallArray[x][y];
}

void Game::init_snake()
{//将蛇初始化为左上角
	mysnake.x[0] = 1;
	mysnake.y[0] = 1;
	int x = mysnake.x[0];
	int y = mysnake.y[0];
	set_content(x, y, '@');
}

void Game::move_snake()
{//控制蛇的移动
	int t1, t2;
	int x, y;
	if (mysnake.dir == "right")	//蛇头先行
	{
		t1 = mysnake.x[0];
		t2 = mysnake.y[0];
		mysnake.y[0]++;
		x = mysnake.x[0];
		y = mysnake.y[0];
		set_content(x, y, '@');
		for (int i = 1;i < mysnake.len;i++)
		{
			x = mysnake.x[i];
			y = mysnake.y[i];
			mysnake.x[i] = t1;
			mysnake.y[i] = t2;
			t1 = x;
			t2 = y;
			set_content(mysnake.x[i], mysnake.y[i], '#');
		}
		set_content(x, y, ' ');
	}
	else if (mysnake.dir == "left")	//蛇头先行
	{
		t1 = mysnake.x[0];
		t2 = mysnake.y[0];
		mysnake.y[0]--;
		x = mysnake.x[0];
		y = mysnake.y[0];
		set_content(x, y, '@');
		for (int i = 1;i < mysnake.len;i++)
		{
			x = mysnake.x[i];
			y = mysnake.y[i];
			mysnake.x[i] = t1;
			mysnake.y[i] = t2;
			t1 = x;
			t2 = y;
			set_content(mysnake.x[i], mysnake.y[i], '#');
		}
		set_content(x, y, ' ');
	}
	else if (mysnake.dir == "up")	//蛇头先行
	{
		t1 = mysnake.x[0];
		t2 = mysnake.y[0];
		mysnake.x[0]--;
		x = mysnake.x[0];
		y = mysnake.y[0];
		set_content(x, y, '@');
		for (int i = 1;i < mysnake.len;i++)
		{
			x = mysnake.x[i];
			y = mysnake.y[i];
			mysnake.x[i] = t1;
			mysnake.y[i] = t2;
			t1 = x;
			t2 = y;
			set_content(mysnake.x[i], mysnake.y[i], '#');
		}
		set_content(x, y, ' ');
	}
	else if (mysnake.dir == "down")	//蛇头先行
	{
		t1 = mysnake.x[0];
		t2 = mysnake.y[0];
		mysnake.x[0]++;
		x = mysnake.x[0];
		y = mysnake.y[0];
		set_content(x, y, '@');
		for (int i = 1;i < mysnake.len;i++)
		{
			x = mysnake.x[i];
			y = mysnake.y[i];
			mysnake.x[i] = t1;
			mysnake.y[i] = t2;
			t1 = x;
			t2 = y;
			set_content(mysnake.x[i], mysnake.y[i], '#');
		}
		set_content(x, y, ' ');
	}
}

void Game::control(char c)
{
	if ((c == 'w' || c == 'W') && mysnake.dir != "down" && mysnake.dir != "up")
	{
		mysnake.dir = "up";
	}
	else if ((c == 's' || c == 'S') && mysnake.dir != "down" && mysnake.dir != "up")
	{
		mysnake.dir = "down";
	}
	else if ((c == 'd' || c == 'D') && mysnake.dir != "right" && mysnake.dir != "left")
	{
		mysnake.dir = "right";
	}
	else if ((c == 'a' || c == 'A') && mysnake.dir != "right" && mysnake.dir != "left")
	{
		mysnake.dir = "left";
	}
}

void Game::create_food()
{
	int x, y;
	srand((int)time(0));
	x = (rand() % (Heigh + 1)) + 1;			//随机生成x
	y = (rand() % (Width + 1)) + 1;			//随机生成y
	while (get_content(x, y) != ' ')
	{								//不能生成在蛇或者墙上
		x = (rand() % (Heigh + 1)) + 1;
		y = (rand() % (Width + 1)) + 1;
	}
	set_content(x, y, '$');
	fx = x;
	fy = y;
}

int Game::eat_food()
{
	if (mysnake.x[0] == fx && mysnake.y[0] == fy)
		return 1;
	return 0;
}

void Game::chang()
{
	int tag = 0;
	if (eat_food() == 1)
	{
		mysnake.len++;
	}
	for (int i = 0;i <= Heigh + 1;i++)
	{
		for (int j = 0;j <= Width + 1;j++)
		{
			if (wallArray[i][j] == '$')
			{
				tag = 1;
				break;
			}
		}
	}
	if (tag == 0)
	{
		create_food();
	}
}

int Game::if_failed()
{
	if (mysnake.x[0] == 0 || mysnake.y[0] == 0 || mysnake.x[0] == Heigh + 1 || mysnake.y[0] == Width + 1)
	{
		return 1;
	}
	int flag = 0;
	for (int i = 1;i < mysnake.len;i++)
	{
		if (mysnake.x[0] == mysnake.x[i] && mysnake.y[0] == mysnake.y[i])
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
		return 1;
	return 0;
}

void Game::printlose()
{
	std::cout << "游戏结束" << std::endl;
	std::cout << "你的分数为：" << mysnake.len << std::endl;
}

int main()
 {
	Game w;
	
	int flag = 0;	//1继续游戏，0结束游戏
	w.init_wall();
	w.draw_surface();
	while (1)
	{
		if ((::GetAsyncKeyState('A') & 0x8000) || (::GetAsyncKeyState('S') & 0x8000)
			|| (::GetAsyncKeyState('D') & 0x8000) || (::GetAsyncKeyState('W') & 0x8000)
			|| (::GetAsyncKeyState('a') & 0x8000) || (::GetAsyncKeyState('s') & 0x8000)
			|| (::GetAsyncKeyState('d') & 0x8000) || (::GetAsyncKeyState('w') & 0x8000))
		{
			w.init_snake();
			
			system("cls");		//清屏(和打印的函数在一块)
			w.draw_surface();

			w.create_food();	//生成食物

			while (1)			//开始游戏
			{
				if ((::GetAsyncKeyState('A') & 0x8000) || (::GetAsyncKeyState('a') & 0x8000))
				{
					w.control('A');
				}
				else if ((::GetAsyncKeyState('S') & 0x8000) || (::GetAsyncKeyState('s') & 0x8000))
				{
					w.control('S');
				}
				else if ((::GetAsyncKeyState('D') & 0x8000) || (::GetAsyncKeyState('d') & 0x8000))
				{
					w.control('D');
				}
				else if ((::GetAsyncKeyState('W') & 0x8000) || (::GetAsyncKeyState('w') & 0x8000))
				{
					w.control('W');
				}
				
				w.move_snake();
				w.chang();

				system("cls");		//清屏(和打印的函数在一块)
				w.draw_surface();
				
				if (w.if_failed() == 1)
				{
					flag = 1;
					break;
				}

				::Sleep(w.mytime);
			}
		}
		::Sleep(100);

		if (flag == 1)
		{
			break;
		}
	}
	w.printlose();

	getchar();
	return 0;
}