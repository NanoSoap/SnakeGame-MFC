
// SnakeView.cpp : implementation of the CSnakeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Snake.h"
#endif

#include "SnakeDoc.h"
#include "SnakeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "ElementColor.h"



// CSnakeView

IMPLEMENT_DYNCREATE(CSnakeView, CView)

BEGIN_MESSAGE_MAP(CSnakeView, CView)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_GAME_START, &CSnakeView::OnGameStart)
	ON_COMMAND(ID_GAME_PAUSE, &CSnakeView::OnGamePause)
//	ON_COMMAND(ID_GAME_CONTINUE, &CSnakeView::OnGameContinue)
	ON_COMMAND(ID_GAME_RESTART, &CSnakeView::OnGameRestart)
END_MESSAGE_MAP()

// CSnakeView construction/destruction

CSnakeView::CSnakeView()
{
	
	// TODO: add construction code here

}

CSnakeView::~CSnakeView()
{
}

BOOL CSnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSnakeView drawing

void CSnakeView::OnDraw(CDC* pDC)
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->Update_background();
		CBrush brushPaleBlue(ElementColor::PALEBLUE);
		CBrush brushBlack(ElementColor::BLACK);
		CBrush brushRed(ElementColor::RED);
		CBrush brushGreen(ElementColor::GREEN);
		CBrush brushGold(ElementColor::GOLD);
		CBrush brushViolet(ElementColor::VIOLET);

		CBrush brushBody(pDoc->snakeColor);
		CBrush brushFood(pDoc->foodColor);


		//draw background
		int height = pDoc->height;
		int width = pDoc->width;
		int scale = pDoc->scale;
		//CPaintDC dc(this); // 用于绘制的设备上下文

		CRect rc;//用来获取窗口矩形区域的大小
		CDC dcMem;//用来在位图上画图的DC
		GetClientRect(&rc);//获取窗口大小
		CBitmap bmp;//我们画图的位图

		dcMem.CreateCompatibleDC(pDC);//创建一个兼容DC
		bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());//创建一个兼容的DC，以后画图就直接画在我们的位图上
		CBitmap *pOldBit = dcMem.SelectObject(&bmp);//把我们的位图选到兼容DC里面去

		for (int i = 0; i < height*scale; i++)
		{
			for (int j = 0; j < width*scale; j++)
			{
				CRect rt;
				rt.left = j * SCALE;
				rt.top = i * SCALE;
				rt.right = rt.left + SCALE;
				rt.bottom = rt.top + SCALE;
				CRect _rt;
				_rt.left = rt.left + 2;
				_rt.top = rt.top + 2;
				_rt.right = rt.right - 2;
				_rt.bottom = rt.bottom - 2;
				switch (pDoc->background[i][j])
				{
				case WALL: dcMem.FillRect(rt, &brushPaleBlue); break;
				case BACKGROUND: dcMem.FillRect(rt, &brushBlack); break;
				case HEAD:dcMem.SelectObject(brushViolet);
					dcMem.Ellipse(rt); break;
				case BODY:
					dcMem.FillRect(rt, &brushBlack);

					dcMem.FillRect(_rt, &brushBody); break;
				case FOOD:dcMem.FillRect(rt, &brushFood); break;
				default:
					break;
				}
			}
			// TODO: add draw code for native data here
		}

		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, SRCCOPY);//把在位图上画的图贴到我们的真正的DC上面去

																		//释放资源的代码
		dcMem.SelectObject(pOldBit);
		dcMem.DeleteDC();
		bmp.DeleteObject();

}


// CSnakeView diagnostics

#ifdef _DEBUG
void CSnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CSnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSnakeDoc* CSnakeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeDoc)));
	return (CSnakeDoc*)m_pDocument;
}
#endif //_DEBUG


// CSnakeView message handlers


void CSnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	switch (nChar)
	{
	case 'W':
		if (pDoc->direction != DOWN)
		{
			pDoc->direction = UP;
		}
		break;
	case 'S':
		if (pDoc->direction != UP)
		{
			pDoc->direction = DOWN;
		}
		break;
	case 'A':
		if (pDoc->direction != RIGHT)
		{
			pDoc->direction = LEFT;
		}
		break;
	case 'D':
		if (pDoc->direction != LEFT)
		{
			pDoc->direction = RIGHT;
		}
		break;
	default:
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSnakeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (nIDEvent == 1)
	{	
		//iterate snake body to suplant each element to update their position
		list<std::unique_ptr<SnakeBody>>::iterator it_front = pDoc->snake.end();
		list<std::unique_ptr<SnakeBody>>::iterator it_tail = pDoc->snake.end();
		it_front--;
		it_tail--;

		while (it_front != pDoc->snake.begin())
		{
			it_front--;
			it_tail->get()->column = it_front->get()->column;
			it_tail->get()->row= it_front->get()->row;
			it_tail--;
		}
		it_front = pDoc->snake.begin();



		//moving logic

		switch (pDoc->direction)
		{
		case LEFT:
			it_front->get()->column -= 1;
			break;
		case RIGHT:
			it_front->get()->column+= 1;
			break;
		case UP:
			it_front->get()->row -= 1;
			break;
		case DOWN:
			it_front->get()->row += 1;
			break;
		}
		//eating logic

		if (pDoc->background[it_front->get()->row][it_front->get()->column]==FOOD)
		{
			pDoc->CreateFood();
			unique_ptr<SnakeBody> psnakebody(new SnakeBody(it_tail->get()->row, it_tail->get()->column));
			pDoc->snake.push_back(psnakebody);
			
		}

		//death logic
		if (pDoc->background[it_front->get()->row][it_front->get()->column] == WALL)
		{
			KillTimer(1);
			AfxMessageBox(101, MB_OK);
			return;
		}
		if (pDoc->background[it_front->get()->row][it_front->get()->column] == BODY)
		{
			KillTimer(1);
			AfxMessageBox(101, MB_OK);
			return;
		}

		Invalidate();
	}

	CView::OnTimer(nIDEvent);
}


void CSnakeView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnRButtonDown(nFlags, point);
}


void CSnakeView::OnInitialUpdate()
{	
	
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
}


void CSnakeView::OnGameStart()
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	SetTimer(1, pDoc->speed, NULL);
	// TODO: Add your command handler code here
}


void CSnakeView::OnGamePause()
{
	KillTimer(1);
	// TODO: Add your command handler code here
}


//void CSnakeView::OnGameContinue()
//{
//	SetTimer(1, SPEED, NULL);
//	// TODO: Add your command handler code here
//}


void CSnakeView::OnGameRestart()
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->Restart();
	Invalidate();
	// TODO: Add your command handler code here
}
