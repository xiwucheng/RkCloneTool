#include "stdafx.h"
#include "StaticEx.h"


CStaticEx::CStaticEx()
{
	m_nPos = 0;
	m_clrText = RGB(255,255,255);
	m_clrFront = RGB(0,200,0);
	m_clrBk = RGB(100,100,100);
	m_nType = 0;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(m_lf), &m_lf);
	m_lf.lfHeight = -14;
	m_hFont = CreateFontIndirect(&m_lf);
}


CStaticEx::~CStaticEx()
{
	DeleteObject(m_hFont);
}


void CStaticEx::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	DWORD dwStyle = GetStyle();
	SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_OWNERDRAW);
	CStatic::PreSubclassWindow();
}


void CStaticEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	CString str;
	int cx;
	CRect rcItem(lpDrawItemStruct->rcItem),rcValid;
	HDC hdc = lpDrawItemStruct->hDC;
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hbmp = CreateCompatibleBitmap(hdc, rcItem.Width(), rcItem.Height());
	SaveDC(hdc);
	SelectObject(hMemDC, hbmp);
	::SetBkColor(hMemDC, m_clrBk);
	SetBkMode(hMemDC, TRANSPARENT);
	::SetTextColor(hMemDC,m_clrText);
	SelectObject(hMemDC, m_hFont);
	ExtTextOut(hMemDC, 0, 0, ETO_OPAQUE, &rcItem, NULL, 0, NULL);
	GetWindowText(str);
	if (m_nType == 0)
	{
		cx = m_nPos*rcItem.Width() / 100;
		if (m_szPrefix.GetLength())
		{
			str.Format(TEXT("%s%d%%"), m_szPrefix,m_nPos);
		}
		else
		{
			str.Format(TEXT("%d%%"), m_nPos);
		}
		::SetBkColor(hMemDC, m_clrFront);
		CopyRect(&rcValid, &rcItem);
		rcValid.right = cx;
		ExtTextOut(hMemDC, 0, 0, ETO_OPAQUE, &rcValid, NULL, 0, NULL);
		if (m_nPos)
		{
			DrawText(hMemDC, str, -1, &rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
	else
	{
		DrawText(hMemDC, str, -1, &rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	BitBlt(hdc, 0, 0, rcItem.Width(), rcItem.Height(), hMemDC, 0, 0, SRCCOPY);
	DeleteObject(hbmp);
	DeleteDC(hMemDC);
	RestoreDC(hdc, -1);
}

int CStaticEx::SetPrefixStr(CString str)
{
	m_szPrefix = str;
	return m_szPrefix.GetLength();
}

int CStaticEx::SetType(int nType)
{
	m_nType = nType ? 1 : 0;
	Invalidate(0);
	return m_nType;
}

int CStaticEx::SetFontSize(int nSize)
{
	DeleteObject(m_hFont);
	m_lf.lfHeight = nSize;
	m_hFont = CreateFontIndirect(&m_lf);
	Invalidate(0);
	return 0;
}

WORD CStaticEx::SetPos(WORD nPos)
{
	WORD pos = LOBYTE(nPos) * 100 + HIBYTE(nPos);
	if (pos > 10000)
		m_nPos = MAKEWORD(100, 0);
	else
		m_nPos = nPos;
	Invalidate(1);
	return m_nPos;
}


int CStaticEx::SetBkColor(COLORREF nColor)
{
	m_clrBk = nColor;
	Invalidate(0);
	return 0;
}


int CStaticEx::SetFrontColor(COLORREF nColor)
{
	m_clrFront = nColor;
	Invalidate(0);
	return 0;
}


int CStaticEx::SetTextColor(COLORREF nColor)
{
	m_clrText = nColor;
	Invalidate(0);
	return 0;
}
BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CStaticEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;// CStatic::OnEraseBkgnd(pDC);
}
