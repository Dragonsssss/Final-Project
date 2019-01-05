#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>     
#include <stdlib.h>    
#include <conio.h>     
#include <windows.h>
using namespace std;

const int MAX_LEVEL = 5;  // �̦h���X���A�i�H��
const int MAX_X = 10; // �a�Ϥ����Z�� (ps. �����j�i�H��) 
const int MAX_Y = 10; // �a�ϫ����Z�� (ps. �����j�i�H��) 
const int MAX_BOXES = 20; //�a�ϳ̦h���X�ӽc�l 


struct Coordinate
{
	int x;
	int y;
};

void gotoxy(int xpos, int ypos) // �ѨM�{�{�����D 
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

class Map
{
private:
	int map[MAX_Y][MAX_X];  // 0��Ů� 1����� 2��ؼ��I
	Coordinate person;  // �H���y��
	bool isBox[MAX_Y][MAX_X];  // �ݸ��I�W���S���c�l
	int targetCnt, finishCnt;
public:
	// �D�n�O�ǤJ�s�a��(�Ů�B����B�ؼ��I)�A�_�l�����I�A�c�l�ƶq�A�c�l���y��
	Map(int newMap[MAX_Y][MAX_X], Coordinate startP, int boxNum, Coordinate boxes[MAX_BOXES]);
	~Map();
	bool isValidMove(Coordinate move);
	bool isPass();
	void draw();
};
Map::Map(int newMap[MAX_Y][MAX_X], Coordinate startP, int boxNum, Coordinate boxes[MAX_BOXES])
{
	targetCnt = 0;
	finishCnt = 0;
	person.x = startP.x;
	person.y = startP.y;
	for (int i = 0; i < MAX_Y; i++) // y�b 
	{
		for (int j = 0; j < MAX_X; j++) // x�b 
		{
			map[i][j] = newMap[i][j];
			if (map[i][j] == 2)
				targetCnt++;
			isBox[i][j] = false;
		}
	}
	for (int i = 0; i < boxNum; i++)
	{
		isBox[boxes[i].y][boxes[i].x] = true;
	}
}
Map::~Map()
{
}
bool Map::isValidMove(Coordinate move)
{
	int newX = person.x + move.x, newY = person.y + move.y;
	if (map[newY][newX] != 1) // �U�@�椣�O����N�i�H�~��ݬ�
	{
		if (isBox[newY][newX] == 1)  // �p�G�O�c�l�N�A�ݬݤU�@��O����
		{
			newX += move.x;
			newY += move.y;
			if (map[newY][newX] != 1 && isBox[newY][newX] == false)  // ���O����]�S�c�l�N��
			{
				person.x += move.x;
				person.y += move.y;
				isBox[newY][newX] = true;
				if (map[newY][newX] == 2) // �p�G�N�c�l���V�ؼ��I 
					finishCnt++;
				isBox[newY - move.y][newX - move.x] = false;
				if (map[newY - move.y][newX - move.x] == 2) // �p�G�N�c�l�����ؼ��I 
					finishCnt--;
				return true;
			}
		}
		else  // �S�c�l�N������
		{
			person.x = newX;
			person.y = newY;
			return true;
		}
	}

	return false;
}
bool Map::isPass()
{
	if (finishCnt == targetCnt)
		return true;
	return false;
}
void Map::draw()
{
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y; i++) // y�b 
	{ 
		for (int j = 0; j < MAX_X; j++) // x�b 
		{
			if(person.x == j and person.y == i)
			{
				cout << "��"; 
				continue;
			}
			
			if(isBox[i][j] == 1)
			{
				cout << "��"; 
				continue;
			}
							
			if(map[i][j] == 0)
				cout << "�@"; // �Ů� 
			else if(map[i][j] == 1)
				cout << "��"; // ��� 
			else
				cout << "��"; // �ؼ��I 
		}
		cout << "\n";
	} 
}


int main()
{
	int level = 0;
	Map* stage[MAX_LEVEL]; // �D�n��Ҧ����d���a��
	for(int i = 0; i < MAX_LEVEL; i++)
	{
		if(i == 0)
		{
			int map1[MAX_Y][MAX_X] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
									  0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
			                          0, 0, 1, 2, 1, 0, 0, 0, 0, 0,
			                          0, 0, 1, 0, 1, 1, 1, 1, 0, 0,
			                          1, 1, 1, 0, 0, 0, 2, 1, 0, 0,
			                          1, 2, 0, 0, 0, 1, 1, 1, 0, 0,
			                          1, 1, 1, 1, 0, 1, 0, 0, 0, 0,
			                          0, 0, 0, 1, 2, 1, 0, 0, 0, 0,
			                          0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
									  0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			Coordinate startP;
			startP.x = 4, startP.y = 4;            
			int boxNum = 4;
			Coordinate boxes[MAX_BOXES] = {0};
			boxes[0].x = 3, boxes[0].y = 4;
			boxes[1].x = 3, boxes[1].y = 5;
			boxes[2].x = 4, boxes[2].y = 6;
			boxes[3].x = 5, boxes[3].y = 4;
			stage[i] = new Map(map1, startP, boxNum, boxes);
			
		}
		else if(i == 1)
		{
			int map2[MAX_Y][MAX_X] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
									  1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
			                          1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
			                          1, 0, 2, 0, 0, 0, 2, 0, 1, 0,
			                          1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
			                          1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
			                          1, 0, 2, 0, 0, 0, 2, 0, 1, 0,
			                          1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
			                          1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
									  0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			Coordinate startP;
			startP.x = 4, startP.y = 6;
			int boxNum = 4;
			Coordinate boxes[MAX_BOXES] = {0};
			boxes[0].x = 3, boxes[0].y = 4;
			boxes[1].x = 5, boxes[1].y = 4;
			boxes[2].x = 3, boxes[2].y = 5;
			boxes[3].x = 5, boxes[3].y = 5;
			stage[i] = new Map(map2, startP, boxNum, boxes);				  			
		}
		
		else if(i == 2)
		{
			int map3[MAX_Y][MAX_X] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
									  0, 0, 1, 0, 0, 0, 0, 1, 1, 1,
									  0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
									  1, 1, 1, 0, 0, 0, 1, 1, 0, 1,
									  1, 2, 2, 2, 0, 0, 0, 0, 0, 0,
									  1, 2, 2, 2, 0, 1, 0, 0, 1, 1,
									  1, 1, 1, 1, 0, 1, 0, 0, 0, 1,
									  0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
									  0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
									  0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			Coordinate startP;
			startP.x = 7, startP.y = 7;
			int boxNum = 6;
			Coordinate boxes[MAX_BOXES] = {0};
			boxes[0].x = 4, boxes[0].y = 2;
			boxes[1].x = 4, boxes[1].y = 3;
			boxes[2].x = 5, boxes[2].y = 4;
			boxes[3].x = 4, boxes[3].y = 5;
			boxes[4].x = 6, boxes[4].y = 5;
			boxes[5].x = 7, boxes[5].y = 6;
			stage[i] = new Map(map3, startP, boxNum, boxes);				  			
		}

		else if(i == 3)
		{
			int map4[MAX_Y][MAX_X] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
									  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
									  0, 0, 1, 2, 0, 2, 2, 1, 0, 0,
									  0, 0, 1, 2, 0, 0, 2, 1, 0, 0,
									  0, 1, 1, 1, 0, 0, 0, 1, 1, 0,
									  0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
									  0, 1, 0, 1, 0, 1, 1, 0, 1, 0,
									  0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
									  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
									  0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			Coordinate startP;
			startP.x = 5, startP.y = 7;
			int boxNum = 5;
			Coordinate boxes[MAX_BOXES] = {0};
			boxes[0].x = 5, boxes[0].y = 3;
			boxes[1].x = 6, boxes[1].y = 4;
			boxes[2].x = 3, boxes[2].y = 5;
			boxes[3].x = 6, boxes[3].y = 5;
			boxes[4].x = 4, boxes[4].y = 6;
			stage[i] = new Map(map4, startP, boxNum, boxes);
		}
		
		else if(i == 4)
		{
			int map5[MAX_Y][MAX_X] = {0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
									  0, 1, 0, 0, 1, 1, 1, 1, 1, 0,
									  1, 1, 0, 0, 1, 1, 0, 0, 1, 0,
									  1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
									  1, 0, 0, 0, 1, 1, 0, 0, 1, 0,
									  1, 1, 1, 2, 1, 1, 0, 1, 1, 1,
									  0, 1, 2, 2, 2, 0, 0, 0, 0, 1,
									  0, 1, 1, 2, 2, 0, 0, 0, 0, 1,
									  0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
									  0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			Coordinate startP;
			startP.x = 4, startP.y = 3;
			int boxNum = 6;
			Coordinate boxes[MAX_BOXES] = {0};
			boxes[0].x = 2, boxes[0].y = 2;
			boxes[1].x = 3, boxes[1].y = 3;
			boxes[2].x = 5, boxes[2].y = 3;
			boxes[3].x = 6, boxes[3].y = 4;
			boxes[4].x = 5, boxes[4].y = 6;
			boxes[5].x = 7, boxes[5].y = 6;
			stage[i] = new Map(map5, startP, boxNum, boxes);
		}
	}
	
	double timer = 0;
	int step = 0; //�@����@�Ӷ��q 
	int selection = 0; //�@�����ΨӧP�_����@�ӿﶵ 
	int levelSelection = 0; // ���d��ܧP�_ 
		
	while (true)
	{
		if(step == 0)
		{
			gotoxy(0, 0);
			cout << "Pushing boxs" << endl << endl; // ���D 
			
			if(selection % 2 == 0) // �C���}�l 
			{	
				cout << "Start! <-" << endl;
				cout << "Choosing Level" << endl;
			}else if (selection % 2 == 1) // ������d 
			{
				cout << "Start!" << endl;
				cout << "Choosing Level <-" << endl;
			}
			
			switch (_getch())
        	{
        	case 's':
            	selection++;
            	break;
        	case 'w':
            	selection--;
            	break;
            case 'k': // �T�w�� 
            	if(selection == 0)
            		step++;
            	if(selection == 1)
            		step += 2;
            	break;
	    	default:
	        	break;            
        	}
        	
        	if(selection < 0)
        		selection = 0;
        	if(selection > 1)
        		selection = 1;
			
		} 
		else if(step == 2)
		{
			gotoxy(0, 0);
			cout << "Choose level" << endl << endl; // ���D
			if(levelSelection % 5 == 0)  
			{
				cout << "Level 1 <-" << endl;
				cout << "Level 2" << endl;
				cout << "Level 3" << endl;
				cout << "Level 4" << endl;
				cout << "Level 5" << endl;
			}
			else if (levelSelection % 5 == 1)  
			{
				cout << "Level 1" << endl;
				cout << "Level 2 <-" << endl;
				cout << "Level 3" << endl;
				cout << "Level 4" << endl;
				cout << "Level 5" << endl;
			}
			else if (levelSelection % 5 == 2)  
			{
				cout << "Level 1" << endl;
				cout << "Level 2" << endl;
				cout << "Level 3 <-" << endl;
				cout << "Level 4" << endl;
				cout << "Level 5" << endl;
			}
			else if (levelSelection % 5 == 3)  
			{
				cout << "Level 1" << endl;
				cout << "Level 2" << endl;
				cout << "Level 3" << endl;
				cout << "Level 4 <-" << endl;
				cout << "Level 5" << endl;
			}
			else if (levelSelection % 5 == 4) 
			{
				cout << "Level 1" << endl;
				cout << "Level 2" << endl;
				cout << "Level 3" << endl;
				cout << "Level 4" << endl; 
				cout << "Level 5 <-" << endl;
			}
			
			switch (_getch())
        	{
        	case 's':
            	levelSelection++;
            	break;
        	case 'w':
            	levelSelection--;
            	break;
            case 'k': // �T�w�� 
            	step--;
            	level = levelSelection; // ��ܪ����d 
            	break;
	    	default:
	        	break;            
        	}
        	
        	if(levelSelection < 0)
        		levelSelection = 0;
        	if(levelSelection > 4)
        		levelSelection = 4;
			
		}
		else if(step == 1)
		{
		
			stage[level]->draw();  // ���e�X�̷s���C�����A
		
			if(level == MAX_LEVEL)
			{
				break;
			}	
			
			Coordinate move = {0 , 0};
        	switch (_getch())
        	{
        	case 'a':
        	    move.x = -1;
        	    break;
       		case 'd':
         		move.x = 1;
        	    break;
        	case 'w':
            	move.y = -1;
            	break;
        	case 's':
            	move.y = +1;
            	break;
	    	default:
	        	break;            
        	}

			if(stage[level]->isValidMove(move) == 0)  // ���O�p�G���X�z 
			{
				continue; // �^��while�j�骺�@�}�l 
			}	
			if (stage[level]->isPass())  // �p�G�L���N�[�@��level
			{
				// �L���e��
				level += 1;
			}
		}
		
	}
	return 0;
}
