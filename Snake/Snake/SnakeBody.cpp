#include "stdafx.h"
#include "SnakeBody.h"

IMPLEMENT_SERIAL(SnakeBody, CObject, 1);
SnakeBody::SnakeBody()
{
}


SnakeBody::~SnakeBody()
{
}

void SnakeBody::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << row << column;
	}
	else
	{
		ar >> row >> column;
	}
}

SnakeBody::SnakeBody(int _row, int _column)
{
	this->row = _row;
	this->column = _column;
}
