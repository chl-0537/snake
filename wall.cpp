#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <windows.h>
#include <queue>

struct Snake
{
	int x[100];					//��
	int y[100];
	int len = 2;
	std::string dir = "right";	//��ͷ����right,left,up,down
};

class Game
{
public:
	enum
	{
		Heigh = 37,		//����߶�
		Width = 37		//������
	};
	char wallArray[Heigh + 2][Width + 2];
	Snake mysnake;		//��
	int fx;
	int fy;				//��¼ʳ�������
	int mytime = 150;	//��ǰ�����ٶ�
	int count;			//��¼�ߵĲ���
	void init_wall();	//��ʼ��ǽ��
	void draw_surface();	//���ǽ��
	void set_content(int x, int y, char c);//��������
	char get_content(int x, int y);		//��ȡ��ǰλ�õ�����
	void init_snake();  //��ʼ����
	void move_snake();	//�߶�
	void control(char c);//�����ߵ��ƶ�
	void create_food();	//����ʳ��
	int eat_food();		//�ж����ǲ��ǳԵ���ʳ��
	void chang();		//�ߵĳ��ȼ�һ
	int if_failed();		//�ǲ���Ӯ��
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
}//һ��������ΧһȦ�á�*��Χ�������м��ǵĿհ״�

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
			std::cout << "�������˲�����ɣ�����ɲ���ɣ�";
		}
		if (i == 3)
		{
			std::cout << "�����ˣ���Ȱ�㣬����β֭";
		}
		if (i == 4)
		{
			std::cout << "��ʾ��";
		}
		if (i == 5)
		{
			std::cout << "�뿪����д";
		}
		if (i == 6)
		{
			std::cout << "w���ϣ�s���£�a����d����";
		}
		if (i == 7)
		{
			std::cout << "����w��s��a��d��ʼ";
		}
		std::cout << std::endl;
	}
}//����̣���һ����ʾ

void Game::set_content(int x, int y, char c)
{
	wallArray[x][y] = c;
}

char Game::get_content(int x, int y)
{
	return wallArray[x][y];
}

void Game::init_snake()
{//���߳�ʼ��Ϊ���Ͻ�
	mysnake.x[0] = 1;
	mysnake.y[0] = 1;
	int x = mysnake.x[0];
	int y = mysnake.y[0];
	set_content(x, y, '@');
}

void Game::move_snake()
{//�����ߵ��ƶ�
	int t1, t2;
	int x, y;
	if (mysnake.dir == "right")	//��ͷ����
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
	else if (mysnake.dir == "left")	//��ͷ����
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
	else if (mysnake.dir == "up")	//��ͷ����
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
	else if (mysnake.dir == "down")	//��ͷ����
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
	x = (rand() % (Heigh + 1)) + 1;			//�������x
	y = (rand() % (Width + 1)) + 1;			//�������y
	while (get_content(x, y) != ' ')
	{								//�����������߻���ǽ��
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
	std::cout << "��Ϸ����" << std::endl;
	std::cout << "��ķ���Ϊ��" << mysnake.len << std::endl;
}

int main()
 {
	Game w;
	
	int flag = 0;	//1������Ϸ��0������Ϸ
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
			
			system("cls");		//����(�ʹ�ӡ�ĺ�����һ��)
			w.draw_surface();

			w.create_food();	//����ʳ��

			while (1)			//��ʼ��Ϸ
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

				system("cls");		//����(�ʹ�ӡ�ĺ�����һ��)
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