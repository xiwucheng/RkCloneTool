
// RkCloneTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "RKUpgradeDll.h"
#ifdef _DEBUG
#pragma comment(lib,"RKUpgrade_Debug.lib")
#else
#pragma comment(lib,"RKUpgrade.lib")
#endif


// CRkCloneToolApp: 
// �йش����ʵ�֣������ RkCloneTool.cpp
//

class CRkCloneToolApp : public CWinApp
{
public:
	CRkCloneToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRkCloneToolApp theApp;