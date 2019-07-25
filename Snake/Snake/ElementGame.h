#pragma once
//#define height*scale 30
//#define width*scale  40
#define SCALE  20
#define SCALE_B 19
#define SPEED  150
enum ElementGame:int{
	BACKGROUND, WALL,HEAD,BODY,FOOD
};
struct Food
{
	int x, y;
	bool valid;
};
