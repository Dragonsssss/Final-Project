#pragma warning(disable:4996)
#include <stdio.h>     
#include <stdlib.h>    
#include <conio.h>     

const int MAX_LEVEL = 5;  // �̦h���X���A�i�H��
struct Coordinate
{
	int x;
	int y;
};
class Map
{
private:
	int map[10][12];  // 0��Ů� 1����� 2��ؼ��I
	Coordinate person;  // �H���y��
	bool isBox[10][12];  // �ݸ��I�W���S���c�l
	int targetCnt, finishCnt;
public:
	// �D�n�O�ǤJ�s�a��(�Ů�B����B�ؼ��I)�A�_�l�����I�A�c�l�ƶq�A�c�l���y��
	Map(int* newMap[], Coordinate startP, int boxNum, Coordinate* boxes);  // ��a�ϼ˦��s�b��L�a��(eg���B��L�}�C)
	~Map();
	bool isValidMove(Coordinate move);
	bool isPass();
	void print();  // !!!!!!!!!!!!!!!!!!!!�o�ӨS�g�A���D�n�O��ı��
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
	if (newX >= 0 && newX + move.x < 12 && newY >= 0 && newY < 10)  // �p�G�٦b�a����ɸ�
	{
		if (map[newY][newX] != 1) // �U�@�椣�O����N�i�H�~��ݬ�
		{
			if (isBox[newY][newX])  // �p�G�O�c�l�N�A�ݬݤU�@��O����
			{
				newY += move.y;
				newX += move.x;
				if (map[newY][newX] != 1 && isBox[newY][newX] == false)  // ���O����]�S�c�l�N��
				{
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
	Map* stage[MAX_LEVEL]; // �D�n��Ҧ����d���a��
	while (true)
	{
		stage[level]->print();  // ���e�X�̷s���C�����A

		command = getch();  // �����L��J�����O
		Coordinate move = { 0 , 0 };
		if (command == 'w')
			move.y = 1;
		else if (command == 's')
			move.y = -1;
		else if (command == 'd')
			move.x = 1;
		else if (command == 'a')
			move.x = -1;

		if(stage[level]->isValidMove(move) == 0)  // ���O�p�G���X�z 
		{
			continue; // �^��while�j�骺�@�}�l 
		}	
		if (stage[level]->isPass())  // �p�G�L���N�[�@��level
		{
			// �[�ӹL���e���H
			level += 1;
		}
		if (command == '0')  // ��0�����C�� (�A��)
			break;
		//if(level == MAX_LEVEL)
			// �i�൹�ӳq���e��
	}
	


}

