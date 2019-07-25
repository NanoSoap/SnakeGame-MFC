
// SnakeDoc.cpp : implementation of the CSnakeDoc class
//

#include "stdafx.h"
#include "GridDialog.h"
#include "SpeedDialog.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Snake.h"
#endif

#include "SnakeDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSnakeDoc
 
IMPLEMENT_DYNCREATE(CSnakeDoc, CDocument)

BEGIN_MESSAGE_MAP(CSnakeDoc, CDocument)
//	ON_UPDATE_COMMAND_UI(ID_GAME_START, &CSnakeDoc::OnUpdateGameStart)
ON_COMMAND(ID_SNAKECOLOR_YELLOW, &CSnakeDoc::OnSnakecolorYellow)
ON_COMMAND(ID_SNAKECOLOR_GREEN, &CSnakeDoc::OnSnakecolorGreen)
ON_COMMAND(ID_SNAKECOLOR_RED, &CSnakeDoc::OnSnakecolorRed)
ON_COMMAND(ID_SNAKECOLOR_BLUE, &CSnakeDoc::OnSnakecolorBlue)
ON_UPDATE_COMMAND_UI(ID_SNAKECOLOR_YELLOW, &CSnakeDoc::OnUpdateSnakecolorYellow)
ON_UPDATE_COMMAND_UI(ID_SNAKECOLOR_GREEN, &CSnakeDoc::OnUpdateSnakecolorGreen)
ON_UPDATE_COMMAND_UI(ID_SNAKECOLOR_RED, &CSnakeDoc::OnUpdateSnakecolorRed)
ON_UPDATE_COMMAND_UI(ID_SNAKECOLOR_BLUE, &CSnakeDoc::OnUpdateSnakecolorBlue)
ON_COMMAND(ID_OPTIONS_SIZEOFGRID, &CSnakeDoc::OnOptionsSizeofgrid)
ON_COMMAND(ID_OPTIONS_SNAKESPEED, &CSnakeDoc::OnOptionsSnakespeed)
//ON_COMMAND(ID_GAME_RESTART, &CSnakeDoc::OnGameRestart)
END_MESSAGE_MAP()


// CSnakeDoc construction/destruction

CSnakeDoc::CSnakeDoc()
{
	// TODO: add one-time construction code here

}

CSnakeDoc::~CSnakeDoc()
{
}

void CSnakeDoc::Update_background()
{	
	//map background and wall data

	for (int i = 0; i < height*scale; i++)
	{
		for (int j = 0; j < width*scale; j++)
		{
			if (i==0||j==0||i==height*scale-1||j==width*scale-1)
			{
				background[i][j] = ElementGame::WALL;
			}
			else {
				background[i][j] = ElementGame::BACKGROUND;
			}
		}
	}
	//map snake data 

	list<std::unique_ptr<SnakeBody>>::iterator it = snake.begin();
	background[it->get()->row][it->get()->column] = ElementGame::HEAD;
	it++;
	while (it!=snake.end())
	{
		background[it->get()->row][it->get()->column] = ElementGame::BODY;
		it++;
	}
	background[food.x][food.y] = ElementGame::FOOD;
}


void CSnakeDoc::Init_snakebody()
{	

	for (int i = 0; i < 5; i++)
	{	
		unique_ptr<SnakeBody> psnakebody(new SnakeBody(8,15+i));
		AddSnakebody(psnakebody);
	}
}

void CSnakeDoc::CreateFood()
{
	srand(time(NULL));
	int y = 1 + rand() % (width*scale - 2);
	int x = 1 + rand() % (height*scale - 2);
	while (background[x][y]==BODY)
	{
		int y = 1 + rand() % (width*scale - 2);
		int x = 1 + rand() % (height*scale - 2);
	}
	food.x = x; food.y = y;
}

void CSnakeDoc::AddSnakebody(unique_ptr<SnakeBody>& s)
{
	snake.push_back(s);
}



BOOL CSnakeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	Init_snakebody();
	CreateFood();
	return TRUE;
}




// CSnakeDoc serialization

void CSnakeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << static_cast<int> (direction) << food.x << food.y << scale << foodColor <<snakeColor<< speed;
		ar << snake.size();
		for (const auto & var : snake)
		{
			ar << var.get();
		}
		// TODO: add storing code here
	}
	else
	{
		int d;
		ar >> d >> food.x >> food.y >> scale >> foodColor >> snakeColor>>speed;
		direction = static_cast<Direction> (d);
		size_t snakebody_c;
		ar >> snakebody_c;
		SnakeBody* snaketemp;
		snake.clear();
		for (size_t i = 0; i < snakebody_c; i++)
		{
			ar >> snaketemp;
			snake.push_back(unique_ptr<SnakeBody>(snaketemp));
		}

			// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSnakeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSnakeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSnakeDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSnakeDoc diagnostics

#ifdef _DEBUG
void CSnakeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSnakeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSnakeDoc commands


//void CSnakeDoc::OnUpdateGameStart(CCmdUI *pCmdUI)
//{
//	pCmdUI->Enable(false);
//	// TODO: Add your command update UI handler code here
//}


void CSnakeDoc::OnSnakecolorYellow()
{
	snakeColor = ElementColor::GOLD;
	// TODO: Add your command handler code here
}


void CSnakeDoc::OnSnakecolorGreen()
{
	snakeColor = ElementColor::GREEN;

	// TODO: Add your command handler code here
}


void CSnakeDoc::OnSnakecolorRed()
{
	snakeColor = ElementColor::RED;

	// TODO: Add your command handler code here
}


void CSnakeDoc::OnSnakecolorBlue()
{
	snakeColor = ElementColor::BLUE;
	// TODO: Add your command handler code here
}


void CSnakeDoc::OnUpdateSnakecolorYellow(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(snakeColor == ElementColor::GOLD);
	// TODO: Add your command update UI handler code here
}


void CSnakeDoc::OnUpdateSnakecolorGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(snakeColor == ElementColor::GREEN);
	// TODO: Add your command update UI handler code here
}


void CSnakeDoc::OnUpdateSnakecolorRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(snakeColor == ElementColor::RED);
	// TODO: Add your command update UI handler code here
}


void CSnakeDoc::OnUpdateSnakecolorBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(snakeColor ==ElementColor::BLUE);

	// TODO: Add your command update UI handler code here
}


void CSnakeDoc::OnOptionsSizeofgrid()
{
	GridDialog dlg;
	dlg.scale = scale;
	if (dlg.DoModal()==IDOK)
	{
		scale = dlg.scale;
		CreateFood();
	}

	// TODO: Add your command handler code here
}


void CSnakeDoc::OnOptionsSnakespeed()
{
	SpeedDialog dlg;
	dlg.speed = speed;
	if (dlg.DoModal()==IDOK)
	{
		speed = dlg.speed;
	}
	// TODO: Add your command handler code here
}

void CSnakeDoc::Restart()
{
	snake.clear();
	Init_snakebody();
	CreateFood();
	direction = LEFT;
}
