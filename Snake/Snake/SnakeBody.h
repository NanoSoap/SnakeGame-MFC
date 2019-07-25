#pragma once

enum  Direction:int
{
	UP, DOWN, LEFT, RIGHT
};


class SnakeBody:public CObject
{	
public:
	int row, column;

public:
	SnakeBody(int _row, int _column);
	SnakeBody();
	~SnakeBody();
	void Serialize(CArchive& ar);
private:
	
	DECLARE_SERIAL(SnakeBody);
};




