// IHListBox.cpp : 实现文件
//

#include "stdafx.h"
#include "COC.h"
#include "IHListBox.h"


// CIHListBox

IMPLEMENT_DYNAMIC(CIHListBox, CListBox)

CIHListBox::CIHListBox()
{

}

CIHListBox::~CIHListBox()
{
}


BEGIN_MESSAGE_MAP(CIHListBox, CListBox)
END_MESSAGE_MAP()



// CIHListBox 消息处理程序




int CIHListBox::AddString(LPCTSTR lpszltem)
{
	int nResult = CListBox::AddString( lpszltem );

	RefushHorizontalScrollBar();

	return nResult;
}


int CIHListBox::InsertString(int nIndex, LPCTSTR lpszltem)
{
	int nResult = CListBox::InsertString( nIndex, lpszltem );

	RefushHorizontalScrollBar();

	return nResult;
}


void CIHListBox::RefushHorizontalScrollBar(void)
{
	CDC *pDC = this->GetDC();
	if ( NULL == pDC )
	{
		return;
	}

	int nCount = this->GetCount();
	if ( nCount < 1 )
	{
		this->SetHorizontalExtent( 0 );
		return;
	}

	int nMaxExtent = 0;
	CString szText;
	for ( int i = 0; i < nCount; ++i )
	{
		this->GetText( i, szText );
		CSize &cs = pDC->GetTextExtent( szText );
		if ( cs.cx > nMaxExtent )
		{
			nMaxExtent = cs.cx;
		}
	}

	this->SetHorizontalExtent( nMaxExtent );
}
