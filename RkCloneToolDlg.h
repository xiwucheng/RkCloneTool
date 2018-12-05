
// RkCloneToolDlg.h : 头文件
//
#include "StaticEx.h"
#pragma once

// CRkCloneToolDlg 对话框
class CRkCloneToolDlg : public CDialogEx
{
// 构造
public:
	CRkCloneToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RKCLONETOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
public:
	static UINT BurnProc(LPVOID lParam);
	static UINT ReadProc(LPVOID lParam);
	UINT BurnImage();
	UINT ReadImage();
	BOOL DownloadImage(TCHAR *szDevPath, TCHAR *szImage, unsigned int uiOffset = 0);
	BOOL UploadImage(TCHAR *szDevPath, TCHAR *szImage, unsigned int uiOffset, unsigned int uiLen);
protected:
	HICON m_hIcon;
	HDEVNOTIFY m_hDevNotify;
	BOOL m_bConnected;
	CString m_szPathName, m_szSavePathName, m_szLinkName;
	DWORD m_dwOffset, m_dwSectorLen;
	CStaticEx m_Prog;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedRead();
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnClose();
};
