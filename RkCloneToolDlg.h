
// RkCloneToolDlg.h : ͷ�ļ�
//
#include "StaticEx.h"
#pragma once

// CRkCloneToolDlg �Ի���
class CRkCloneToolDlg : public CDialogEx
{
// ����
public:
	CRkCloneToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RKCLONETOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
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

	// ���ɵ���Ϣӳ�亯��
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
