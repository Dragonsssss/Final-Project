#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int MAX_LEVEL   = 5;   // 最多有幾關，可以調
const int MAX_X       = 10;  // 地圖水平距離 (ps. 不夠大可以調) 
const int MAX_Y       = 10;  // 地圖垂直距離 (ps. 不夠大可以調) 
const int MAX_BOXES   = 20;  // 地圖最多有幾個箱子
const int WIDGET_SIZE = 30;  // 素材的大小(像素)

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
    Coordinate getPerson();
    int (*getMapPtr())[MAX_X];
    bool (*getIsBoxPtr())[MAX_X];
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
Coordinate Map::getPerson()
{
    return person;
}
int (*Map::getMapPtr())[MAX_X] 
{
    return map;
}
bool (*Map::getIsBoxPtr())[MAX_X] 
{
    return isBox;
}
void loadmap(Map* stage[MAX_LEVEL], int i)
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


int dir = 0;

int main()
{
	system( "Title BOXMAN" );
	Map* stage[MAX_LEVEL]; // 主要放所有關卡的地圖
	for(int i = 0; i < MAX_LEVEL; i++)
	{
		loadmap(stage, i);
	}
    int level = 0; // 到第幾關 

    
    srand(time(0));

    RenderWindow window(VideoMode(MAX_X * WIDGET_SIZE, MAX_Y * WIDGET_SIZE), "Box Game!");

    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;
    t1.loadFromFile("images/box.png");
    t2.loadFromFile("images/person.png");
    t3.loadFromFile("images/wall.png");
    t4.loadFromFile("images/hole.png");
    t5.loadFromFile("images/background.png");
    t6.loadFromFile("images/congrats.png");
    t7.loadFromFile("images/choose_stage1.png");
    t8.loadFromFile("images/choose_stage2.png");
    t9.loadFromFile("images/choose_stage3.png");
    t10.loadFromFile("images/choose_stage4.png");
    t11.loadFromFile("images/choose_stage5.png");

    Sprite box(t1), person(t2), wall(t3), hole(t4), background(t5), congrats(t6);
    Sprite choose_stage1(t7), choose_stage2(t8), choose_stage3(t9), choose_stage4(t10), choose_stage5(t11);

    Clock clock;

    float timer = 0, delay = 0.01;
    bool start = false;
    int levelSelect = 0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
		clock.restart();
        timer += time; 
        

        while (start == false)
        {
            Event a;
            while (window.pollEvent(a))
            {
                if (a.type == Event::Closed)      
                    window.close();
                if (Keyboard::isKeyPressed(Keyboard::Up))
                    levelSelect--;
                if (Keyboard::isKeyPressed(Keyboard::Down))
                    levelSelect++;
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    start = true;
                    level = levelSelect % 5;
                    loadmap(stage, level);
                    break;
                }
                    
            }
            if (levelSelect % 5 == 0)
                window.draw(choose_stage1);
            else if (levelSelect % 5 == 1)
                window.draw(choose_stage2);
            else if (levelSelect % 5 == 2)
                window.draw(choose_stage3);
            else if (levelSelect % 5 == 3)
                window.draw(choose_stage4);
            else if (levelSelect % 5 == 4)
                window.draw(choose_stage5);
            
            window.display();
        }


        Event e;
        Coordinate move = {0 , 0};
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)      
                window.close();
    
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				move.x = -1;
				move.y = 0;
			} 
                 
	        if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				move.x = 1;
				move.y = 0;
			}
	        if (Keyboard::isKeyPressed(Keyboard::Up)) 
			{
				move.x = 0;
				move.y = -1;
			}
		    if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				move.x = 0;
				move.y = 1;
			}
            if (Keyboard::isKeyPressed(Keyboard::X))
                loadmap(stage, level);
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                levelSelect = 0;
                start = false;
            }
			if (Keyboard::isKeyPressed(Keyboard::C))
			{
				level++;
			}		
		}
        
		if (level >= MAX_LEVEL)
        {
            while (window.isOpen())
            {
                window.draw(congrats);
                Event e;
                while (window.pollEvent(e))
                {
                    if (e.type == Event::Closed)      
                        window.close();
		        }
                window.display();
            }
        }  
        if (stage[level]->isValidMove(move) == 0)  // 指令如果不合理
        {
            ;
        }
        else if (timer > delay) 
        {
            // draw
            timer = 0;
            window.clear();
            window.draw(background);

            Coordinate personPostion = stage[level]->getPerson();
            int (*map)[MAX_X]        = stage[level]->getMapPtr();
            bool (*isBox)[MAX_X]     = stage[level]->getIsBoxPtr();

            for (int i = 0; i < MAX_Y; i++) // y軸
            {
                for (int j = 0; j < MAX_X; j++) // x軸
                {
                    if (personPostion.x == j and personPostion.y == i)
                    {
                        person.setPosition(j * WIDGET_SIZE, i * WIDGET_SIZE);
                        window.draw(person);
                        continue;
                    }
                    if (isBox[i][j] == 1)
			        {
				        box.setPosition(j * WIDGET_SIZE, i * WIDGET_SIZE); 
                        window.draw(box);
				        continue;
			        }
                    if (map[i][j] == 0)
                        ;
                    else if(map[i][j] == 1)
                    {
                        wall.setPosition(j * WIDGET_SIZE, i * WIDGET_SIZE); 
                        window.draw(wall);
                    }
                    else
                    {
                        hole.setPosition(j * WIDGET_SIZE, i * WIDGET_SIZE); 
                        window.draw(hole);
                    }
                }
            }
            window.display();
        }
        if (stage[level]->isPass())
        {
            level += 1;
        }  
    }

    return 0;
}