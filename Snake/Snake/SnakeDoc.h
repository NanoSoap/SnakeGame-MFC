
// SnakeDoc.h : interface of the CSnakeDoc class
//


#pragma once
#include "ElementColor.h"
#include "ElementGame.h"
#include <list>
#include "SnakeBody.h"
#include <memory>
using namespace std;
class CSnakeDoc : public CDocument
{
protected: // create from serialization only
	CSnakeDoc();
	DECLARE_DYNCREATE(CSnakeDoc)

	// Attributes
public:
	Food food;
	COLORREF foodColor = ElementColor::GOLD,
			 snakeColor = ElementColor::GREEN;
	Direction direction = LEFT;
	list<unique_ptr<SnakeBody>> Lsnake;
	int speed = 100;
	int height = 6, width = 8, scale =5;
	ElementGame background[100][100];
public:
	void Update_background();
	void Init_snakebody();
	void CreateFood();
	void AddSnakebody(unique_ptr<SnakeBody>& s);
	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CSnakeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	//	afx_msg void OnUpdateGameStart(CCmdUI *pCmdUI);
	afx_msg void OnSnakecolorYellow();
	afx_msg void OnSnakecolorGreen();
	afx_msg void OnSnakecolorRed();
	afx_msg void OnSnakecolorBlue();
	afx_msg void OnUpdateSnakecolorYellow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSnakecolorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSnakecolorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSnakecolorBlue(CCmdUI *pCmdUI);
	afx_msg void OnOptionsSizeofgrid();
	afx_msg void OnOptionsSnakespeed();
//	afx_msg void OnGameRestart();
	void Restart();
};
