#pragma warning(disable:4996)
#include <stdio.h>     
#include <stdlib.h>    
#include <conio.h>     

const int MAX_LEVEL = 5;  // 最多有幾關，可以調
struct Coordinate
{
	int x;
	int y;
};
class Map
{
private:
	int map[10][12];  // 0當空格 1當牆壁 2當目標點
	Coordinate person;  // 人的座標
	bool isBox[10][12];  // 看該點上有沒有箱子
	int targetCnt, finishCnt;
public:
	// 主要是傳入新地圖(空格、牆壁、目標點)，起始移動點，箱子數量，箱子的座標
	Map(int* newMap[], Coordinate startP, int boxNum, Coordinate* boxes);  // 把地圖樣式存在其他地方(eg文件、其他陣列)
	~Map();
	bool isValidMove(Coordinate move);
	bool isPass();
	void print();  // !!!!!!!!!!!!!!!!!!!!這個沒寫，但主要是視覺化
};
Map::Map(int* newMap[], Coordinate startP, int boxNum, Coordinate* boxes)
{
	targetCnt = 0;
	finishCnt = 0;
	person.x = startP.x;
	person.y = startP.y;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
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
	if (newX >= 0 && newX + move.x < 12 && newY >= 0 && newY < 10)  // 如果還在地圖邊界裡
	{
		if (map[newY][newX] != 1) // 下一格不是牆壁就可以繼續看看
		{
			if (isBox[newY][newX])  // 如果是箱子就再看看下一格是什麼
			{
				newY += move.y;
				newX += move.x;
				if (map[newY][newX] != 1 && isBox[newY][newX] == false)  // 不是牆壁也沒箱子就推
				{
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
	}
	return false;
}
bool Map::isPass()
{
	if (finishCnt == targetCnt)
		return true;
	return false;
}

int main()
{
	char command;
	int level = 0;
	Map* stage[MAX_LEVEL]; // 主要放所有關卡的地圖
	while (true)
	{
		stage[level]->print();  // 先畫出最新的遊戲狀態

		command = getch();  // 獲取鍵盤輸入的指令
		Coordinate move = { 0 , 0 };
		if (command == 'w')
			move.y = 1;
		else if (command == 's')
			move.y = -1;
		else if (command == 'd')
			move.x = 1;
		else if (command == 'a')
			move.x = -1;

		if(stage[level]->isValidMove(move) == 0)  // 指令如果不合理 
		{
			continue; // 回到while迴圈的一開始 
		}	
		if (stage[level]->isPass())  // 如果過關就加一個level
		{
			// 加個過場畫面？
			level += 1;
		}
		if (command == '0')  // 按0結束遊戲 (再改)
			break;
		//if(level == MAX_LEVEL)
			// 可能給個通關畫面
	}
	


}

