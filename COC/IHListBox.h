#pragma once


// CIHListBox

class CIHListBox : public CListBox
{
	DECLARE_DYNAMIC(CIHListBox)

public:
	CIHListBox();
	virtual ~CIHListBox();


protected:
	DECLARE_MESSAGE_MAP()
public:
	int AddString(LPCTSTR lpszltem);

	int InsertString(int nIndex, LPCTSTR lpszltem);
	void RefushHorizontalScrollBar(void);
};


