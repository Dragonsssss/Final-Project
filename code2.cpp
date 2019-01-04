#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>     
#include <stdlib.h>    
#include <conio.h>     
#include <windows.h>
using namespace std;

const int MAX_LEVEL = 2;  // 最多有幾關，可以調
const int MAX_X = 10; // 地圖水平距離 (ps. 不夠大可以調) 
const int MAX_Y = 8; // 地圖垂直距離 (ps. 不夠大可以調) 
const int MAX_BOXES = 20; //地圖最多有幾個箱子 
int step = 0; //　到哪一個階段 
int selection = 0; //　首頁用來判斷到哪一個選項 

struct Coordinate
{
	int x;
	int y;
};

class Map
{
private:
	int map[MAX_Y][MAX_X];  // 0當空格 1當牆壁 2當目標點
	Coordinate person;  // 人的座標
	bool isBox[MAX_Y][MAX_X];  // 看該點上有沒有箱子
	int targetCnt, finishCnt;
public:
	// 主要是傳入新地圖(空格、牆壁、目標點)，起始移動點，箱子數量，箱子的座標
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
	for (int i = 0; i < MAX_Y; i++) // y軸 
	{
		for (int j = 0; j < MAX_X; j++) // x軸 
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
	if (map[newY][newX] != 1) // 下一格不是牆壁就可以繼續看看
	{
		if (isBox[newY][newX] == 1)  // 如果是箱子就再看看下一格是什麼
		{
			newX += move.x;
			newY += move.y;
			if (map[newY][newX] != 1 && isBox[newY][newX] == false)  // 不是牆壁也沒箱子就推
			{
				person.x += move.x;
				person.y += move.y;
				isBox[newY][newX] = true;
				if (map[newY][newX] == 2) // 如果將箱子推向目標點 
					finishCnt++;
				isBox[newY - move.y][newX - move.x] = false;
				if (map[newY - move.y][newX - move.x] == 2) // 如果將箱子推離目標點 
					finishCnt--;
				return true;
			}
		}
		else  // 沒箱子就直接走
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
	system("cls");
	for (int i = 0; i < MAX_Y; i++) // y軸 
	{ 
		for (int j = 0; j < MAX_X; j++) // x軸 
		{
			if(person.x == j and person.y == i)
			{
				cout << 'o'; 
				continue;
			}
			
			if(isBox[i][j] == 1)
			{
				cout << 'X'; 
				continue;
			}
							
			if(map[i][j] == 0)
				cout << ' '; // 空格 
			else if(map[i][j] == 1)
				cout << '#'; // 牆壁 
			else
				cout << 'O'; // 目標點 
		}
		cout << "\n";
	} 
}


int main()
{
	int level = 0;
	Map* stage[MAX_LEVEL]; // 主要放所有關卡的地圖
	for(int i = 0; i < MAX_LEVEL; i++)
	{
		if(i == 0)
		{
			int map1[MAX_Y][MAX_X] = {0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
			                          0, 0, 1, 2, 1, 0, 0, 0, 0, 0,
			                          0, 0, 1, 0, 1, 1, 1, 1, 0, 0,
			                          1, 1, 1, 0, 0, 0, 2, 1, 0, 0,
			                          1, 2, 0, 0, 0, 1, 1, 1, 0, 0,
			                          1, 1, 1, 1, 0, 1, 0, 0, 0, 0,
			                          0, 0, 0, 1, 2, 1, 0, 0, 0, 0,
			                          0, 0, 0, 1, 1, 1, 0, 0, 0, 0};
			Coordinate startP;
			startP.x = 4, startP.y = 3;            
			int boxNum = 4;
			Coordinate boxes[MAX_BOXES] = {0};
			boxes[0].x = 3, boxes[0].y = 3;
			boxes[1].x = 3, boxes[1].y = 4;
			boxes[2].x = 4, boxes[2].y = 5;
			boxes[3].x = 5, boxes[3].y = 3;
			stage[i] = new Map(map1, startP, boxNum, boxes);
			
		}
		else if(i == 1)
		{
			int map2[MAX_Y][MAX_X] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
			                          1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
			                          1, 0, 2, 0, 0, 0, 2, 0, 1, 0,
			                          1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
			                          1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
			                          1, 0, 2, 0, 0, 0, 2, 0, 1, 0,
			                          1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
			                          1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
			Coordinate startP;
			startP.x = 4, startP.y = 5;
			int boxNum = 4;
			Coordinate boxes[MAX_BOXES] = {0};
			boxes[0].x = 3, boxes[0].y = 3;
			boxes[1].x = 5, boxes[1].y = 3;
			boxes[2].x = 3, boxes[2].y = 4;
			boxes[3].x = 5, boxes[3].y = 4;
			stage[i] = new Map(map2, startP, boxNum, boxes);				  			
		}
	}
	
	double timer = 0;
		
	while (true)
	{
		if(step == 0)
		{
			system("cls");
			cout << "Pushing boxs" << endl << endl; // 標題 
			
			if(selection % 2 == 0) // 遊戲開始 
			{
				if(timer < 1) // 原本是想做閃爍特效不過還在研究中 
					cout << "Start! <-" << endl;
				else
					cout << endl;
				cout << "Choosing Level" << endl;
			}else if (selection % 2 == 1) // 選擇關卡 
			{
				cout << "Start!" << endl;
				if(timer < 1)
					cout << "Choosing Level <-" << endl;
				else
					cout << endl;
			}
			
			switch (_getch())
        	{
        	case 's':
            	selection++;
            	break;
        	case 'w':
            	selection--;
            	break;
            case 'k': // 確定鍵 
            	step++;
            	break;
	    	default:
	        	break;            
        	}
        	
        	if(selection < 0)
        		selection = 0;
        	
			timer += 0.01;
			
			if(timer >= 2)
				timer = 0;
			
		} 
		else if(step == 1 && selection == 0)
		{
		
		 
			stage[level]->draw();  // 先畫出最新的遊戲狀態
		
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

			if(stage[level]->isValidMove(move) == 0)  // 指令如果不合理 
			{
				continue; // 回到while迴圈的一開始 
			}	
			if (stage[level]->isPass())  // 如果過關就加一個level
			{
				// 過場畫面
				level += 1;
			}
		}
	}
	return 0;
}
