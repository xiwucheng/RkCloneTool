
// RkCloneToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RkCloneTool.h"
#include "RkCloneToolDlg.h"
#include "afxdialogex.h"
#include <Dbt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRkCloneToolDlg 对话框



CRkCloneToolDlg::CRkCloneToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RKCLONETOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bConnected = FALSE;
}

void CRkCloneToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRkCloneToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(IDC_WRITE, &CRkCloneToolDlg::OnBnClickedWrite)
	ON_BN_CLICKED(IDC_READ, &CRkCloneToolDlg::OnBnClickedRead)
	ON_BN_CLICKED(IDC_BROWSE, &CRkCloneToolDlg::OnBnClickedBrowse)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

GUID UVC = { 0xa5dcbf10, 0x6530, 0x11d2,{ 0x90, 0x1f, 0x0, 0xc0, 0x4f, 0xb9, 0x51, 0xed } };

// CRkCloneToolDlg 消息处理程序

BOOL CRkCloneToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	DEV_BROADCAST_DEVICEINTERFACE   dbi;
	ZeroMemory(&dbi, sizeof(dbi));
	dbi.dbcc_size = sizeof(dbi);
	dbi.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	dbi.dbcc_reserved = 0;
	dbi.dbcc_classguid = UVC;

	m_hDevNotify = RegisterDeviceNotification(m_hWnd, &dbi, DEVICE_NOTIFY_ALL_INTERFACE_CLASSES);

	INIT_DEV_INFO dev_info;
	INIT_LOG_INFO log_info;
	INIT_CALLBACK_INFO callback_info;
	memset(&dev_info, 0, sizeof(INIT_DEV_INFO));
	memset(&callback_info, 0, sizeof(INIT_CALLBACK_INFO));
	dev_info.uiRockMscTimeout = dev_info.uiRockusbTimeout = 30;//30s
															   /*custom device need set vid and pid
															   dev_info.usRockUvcVid = ;
															   dev_info.usRockUvcPid = ;
															   */
	log_info.bLogEnable = FALSE;
	log_info.lpszLogPathName = NULL;// (LPTSTR)(LPCTSTR)m_LogPath;

	BOOL bInitOK = RK_Initialize(dev_info, log_info, callback_info);

	if (!bInitOK)
	{
		PostQuitMessage(1);
		return FALSE;
	}
	PSTRUCT_DEVICE_DESC pDevs = NULL;
	//1.scan device
	int nDev, i;
	nDev = RK_ScanDevice(&pDevs);
	for (i = 0; i < nDev; i++)
	{
		if (pDevs[i].emUsbType == RKUSB_LOADER)
		{
			TRACE(TEXT("Found 1 Loader Device!\n"));
			SetDlgItemText(IDC_STATUS, TEXT("Found 1 Loader Device!"));
			m_bConnected = TRUE;
			m_szLinkName = pDevs[i].szLinkName;
			break;
		}
		else if (pDevs[i].emUsbType == RKUSB_MASKROM)
		{
			TRACE(TEXT("Found 1 MaskRom Device!\n"));
			SetDlgItemText(IDC_STATUS, TEXT("Found 1 MaskRom Device!"));
			m_bConnected = FALSE;
			m_szLinkName = TEXT("");
			break;
		}
	}
	if (i >= nDev)
	{
		m_bConnected = FALSE;
		m_szLinkName = TEXT("");
		SetDlgItemText(IDC_STATUS, TEXT("No devices Found!"));
		TRACE(TEXT("No devices Found!\n"));
	}
	m_Prog.SubclassDlgItem(IDC_PROG, this);
	m_Prog.SetBkColor(RGB(100, 100, 100));
	m_Prog.SetTextColor(RGB(255, 255, 255));
	m_Prog.SetFrontColor(RGB(0, 224, 0));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRkCloneToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRkCloneToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CRkCloneToolDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	switch (nEventType)
	{
	case DBT_DEVICEARRIVAL:
	case DBT_DEVICEREMOVECOMPLETE:
	{
		PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)dwData;
		PDEV_BROADCAST_DEVICEINTERFACE pDevInf;
		if (pHdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
		{
			pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
			if (memcmp(&pDevInf->dbcc_classguid, &UVC, sizeof(GUID)) == 0)
			{
				if (wcsstr(pDevInf->dbcc_name, TEXT("VID_2207")))
				{
					PSTRUCT_DEVICE_DESC pDevs = NULL;
					//1.scan device
					int nDev, i;
					nDev = RK_ScanDevice(&pDevs);
					for (i = 0; i < nDev; i++)
					{
						if (pDevs[i].emUsbType == RKUSB_LOADER)
						{
							TRACE(TEXT("Found 1 Loader Device!\n"));
							SetDlgItemText(IDC_STATUS, TEXT("Found 1 Loader Device!"));
							m_bConnected = TRUE;
							m_Prog.SetFrontColor(RGB(0, 224, 0));
							m_Prog.SetPrefixStr(TEXT(""));
							m_Prog.SetPos(0);
							m_szLinkName = pDevs[i].szLinkName;
							break;
						}
						else if (pDevs[i].emUsbType == RKUSB_MASKROM)
						{
							TRACE(TEXT("Found 1 MaskRom Device!\n"));
							SetDlgItemText(IDC_STATUS, TEXT("Found 1 MaskRom Device!"));
							m_Prog.SetFrontColor(RGB(0, 224, 0));
							m_Prog.SetPrefixStr(TEXT(""));
							m_Prog.SetPos(0);
							m_bConnected = FALSE;
							m_szLinkName = TEXT("");
							break;
						}
					}
					if (i >= nDev)
					{
						m_bConnected = FALSE;
						m_szLinkName = TEXT("");
						//m_Prog.SetFrontColor(RGB(0, 224, 0));
						//m_Prog.SetPrefixStr(TEXT(""));
						//m_Prog.SetPos(0);
						SetDlgItemText(IDC_STATUS, TEXT("No devices Found!"));
						TRACE(TEXT("No devices Found!\n"));
						return 1;
					}
					//AdjDeviceFilter();
				}
			}
		}
		break;
	}
	}
	return TRUE;
}

UINT CRkCloneToolDlg::BurnProc(LPVOID lParam)
{
	CRkCloneToolDlg* p = (CRkCloneToolDlg*)lParam;
	PSTRUCT_DEVICE_DESC pDevs = NULL;
	EnableMenuItem(::GetSystemMenu(p->m_hWnd, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED);
	p->GetDlgItem(IDC_STARTADDR)->EnableWindow(0);
	p->GetDlgItem(IDC_DATALEN)->EnableWindow(0);
	p->GetDlgItem(IDC_BROWSE)->EnableWindow(0);
	p->GetDlgItem(IDC_WRITE)->EnableWindow(0);
	p->GetDlgItem(IDC_READ)->EnableWindow(0);
	p->BurnImage();
	p->GetDlgItem(IDC_STARTADDR)->EnableWindow();
	p->GetDlgItem(IDC_DATALEN)->EnableWindow();
	p->GetDlgItem(IDC_BROWSE)->EnableWindow();
	p->GetDlgItem(IDC_WRITE)->EnableWindow();
	p->GetDlgItem(IDC_READ)->EnableWindow();
	EnableMenuItem(::GetSystemMenu(p->m_hWnd, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
	return 0L;
}

UINT CRkCloneToolDlg::ReadProc(LPVOID lParam)
{
	CRkCloneToolDlg* p = (CRkCloneToolDlg*)lParam;
	EnableMenuItem(::GetSystemMenu(p->m_hWnd, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED);
	p->GetDlgItem(IDC_STARTADDR)->EnableWindow(0);
	p->GetDlgItem(IDC_DATALEN)->EnableWindow(0);
	p->GetDlgItem(IDC_BROWSE)->EnableWindow(0);
	p->GetDlgItem(IDC_WRITE)->EnableWindow(0);
	p->GetDlgItem(IDC_READ)->EnableWindow(0);
	p->ReadImage();
	p->GetDlgItem(IDC_STARTADDR)->EnableWindow();
	p->GetDlgItem(IDC_DATALEN)->EnableWindow();
	p->GetDlgItem(IDC_BROWSE)->EnableWindow();
	p->GetDlgItem(IDC_WRITE)->EnableWindow();
	p->GetDlgItem(IDC_READ)->EnableWindow();
	EnableMenuItem(::GetSystemMenu(p->m_hWnd, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
	return 0L;
}

UINT CRkCloneToolDlg::BurnImage()
{
	if (!DownloadImage((LPTSTR)(LPCTSTR)m_szLinkName, (LPTSTR)(LPCTSTR)m_szPathName))
	{
		return 1;
	}
	return 0L;
}

UINT CRkCloneToolDlg::ReadImage()
{
	if (!UploadImage((LPTSTR)(LPCTSTR)m_szLinkName, (LPTSTR)(LPCTSTR)m_szSavePathName, m_dwOffset, m_dwSectorLen))
	{
		return 1;
	}
	return 0L;
}

#define SECTOR_SIZE 512
#define MAX_READWRITE_SECTORS 32
BOOL CRkCloneToolDlg::DownloadImage(TCHAR *szDevPath, TCHAR *szImage, unsigned int uiOffset)
{
	int iRet;
	BOOL bSuccess = FALSE, bRet;
	CFile file;
	DWORD dwMaxReadWriteBytes;
	PBYTE pBuf = NULL;
	PBYTE pRead = NULL;
	UINT  uiBegin, uiRead, uiTransferSec;
	ULONGLONG dwTotalWritten, dwTotalRead;
	DWORD dwTransferBytes, dwProgress, dwLastProgress;
	ULONGLONG dwFWSize;
	CString strFile, strPromptText, strFormatText;
	ULONGLONG dwLen;
	WCHAR szOffset[MAX_PATH], szLen[MAX_PATH];
	GetDlgItemText(IDC_STARTADDR, szOffset,MAX_PATH);
	GetDlgItemText(IDC_DATALEN, szLen,MAX_PATH);
	uiOffset = wcstoul(szOffset, 0, 16);
	dwLen = wcstoul(szLen, 0, 16);
	dwLen = dwLen ? dwLen : (ULONGLONG)-1;
	CString szReadSector;
	ULONGLONG dwSecSize;


	file.m_hFile = INVALID_HANDLE_VALUE;

	dwMaxReadWriteBytes = MAX_READWRITE_SECTORS * SECTOR_SIZE;
	pBuf = new BYTE[dwMaxReadWriteBytes];
	pRead = new BYTE[dwMaxReadWriteBytes];

	bRet = file.Open(szImage, CFile::typeBinary | CFile::modeRead);
	if (!bRet)
	{
		goto Exit_DownloadImage;
	}

	dwFWSize = min(file.GetLength(), dwLen*SECTOR_SIZE);
	dwSecSize = ((dwFWSize%SECTOR_SIZE == 0) ? (dwFWSize / SECTOR_SIZE) : (dwFWSize / SECTOR_SIZE + 1));
	file.SeekToBegin();
	dwTotalWritten = 0;
	dwLastProgress = dwProgress = 0;
	uiBegin = uiOffset;
	m_Prog.SetFrontColor(RGB(0, 224, 0));
	szReadSector.Format(TEXT("Write [00000000/%08llX]..."), dwSecSize);
	m_Prog.SetPrefixStr(szReadSector);
	m_Prog.SetPos(0);
	while (dwTotalWritten<dwFWSize)
	{
		memset(pBuf, 0, dwMaxReadWriteBytes);
		if ((dwFWSize - dwTotalWritten) >= dwMaxReadWriteBytes)
		{
			dwTransferBytes = dwMaxReadWriteBytes;
			uiTransferSec = MAX_READWRITE_SECTORS;
		}
		else
		{
			dwTransferBytes = (DWORD)(dwFWSize - dwTotalWritten);
			uiTransferSec = ((dwTransferBytes%SECTOR_SIZE == 0) ? (dwTransferBytes / SECTOR_SIZE) : (dwTransferBytes / SECTOR_SIZE + 1));
		}
		uiRead = file.Read(pBuf, dwTransferBytes);
		if (uiRead != dwTransferBytes)
		{
			goto Exit_DownloadImage;
		}
		iRet = RKD_WriteLBA(szDevPath, uiBegin, uiTransferSec, pBuf);
		if (0 == iRet)
		{
			dwTotalWritten += dwTransferBytes;
			uiBegin += uiTransferSec;
			dwProgress = (DWORD)((dwTotalWritten / 1024) * 100 / (dwFWSize / 1024));
			szReadSector.Format(TEXT("Write [%08llX/%08llX]..."), dwTotalWritten/SECTOR_SIZE, dwSecSize);
			m_Prog.SetPrefixStr(szReadSector);
			m_Prog.SetPos((WORD)dwProgress);
			if (dwProgress != dwLastProgress)
			{
				dwLastProgress = dwProgress;
				//strPromptText.Format(strFormatText, dwProgress);
				//SetDlgItemText(IDC_STATUS, strPromptText);
			}
		}
		else
		{
			goto Exit_DownloadImage;
		}
	}
	Sleep(200);
	dwLastProgress = dwProgress = 0;
	szReadSector.Format(TEXT("Verify [00000000/%08llX]..."), dwSecSize);
	m_Prog.SetPrefixStr(szReadSector);
	m_Prog.SetPos(0);
	//skip 0x40 protection sectors
#if 0
	uiBegin = uiOffset + 0x40;
	file.Seek(0x40 * SECTOR_SIZE, CFile::begin);
	dwTotalRead = 0x40 * SECTOR_SIZE;
#else
	uiBegin = uiOffset;
	file.Seek(0, CFile::begin);
	dwTotalRead = 0;
#endif

	while (dwTotalRead<dwFWSize)
	{
		memset(pBuf, 0, dwMaxReadWriteBytes);
		memset(pRead, 0, dwMaxReadWriteBytes);
		if ((dwFWSize - dwTotalRead) >= dwMaxReadWriteBytes)
		{
			dwTransferBytes = dwMaxReadWriteBytes;
			uiTransferSec = MAX_READWRITE_SECTORS;
		}
		else
		{
			dwTransferBytes = (DWORD)(dwFWSize - dwTotalRead);
			uiTransferSec = ((dwTransferBytes%SECTOR_SIZE == 0) ? (dwTransferBytes / SECTOR_SIZE) : (dwTransferBytes / SECTOR_SIZE + 1));
		}
		uiRead = file.Read(pBuf, dwTransferBytes);
		if (uiRead != dwTransferBytes)
		{
			goto Exit_DownloadImage;
		}
		iRet = RKD_ReadLBA(szDevPath, uiBegin, uiTransferSec, pRead);
		if (0 == iRet)
		{
			dwTotalRead += dwTransferBytes;
			uiBegin += uiTransferSec;
		}
		else
		{
			goto Exit_DownloadImage;
		}

		if (0 != memcmp(pBuf, pRead, dwTransferBytes))
		{
			goto Exit_DownloadImage;
		}

		dwProgress = (DWORD)((dwTotalRead / 1024) * 100 / (dwFWSize / 1024));
		szReadSector.Format(TEXT("Verify [%08llX/%08llX]..."), dwTotalRead / SECTOR_SIZE, dwSecSize);
		m_Prog.SetPrefixStr(szReadSector);
		m_Prog.SetPos((WORD)dwProgress);
		if (dwProgress != dwLastProgress)
		{
			dwLastProgress = dwProgress;
			//strPromptText.Format(strFormatText, dwProgress);
			//SetDlgItemText(IDC_STATUS, strPromptText);
		}
	}

	bSuccess = TRUE;

Exit_DownloadImage:

	if (file.m_hFile != INVALID_HANDLE_VALUE)
		file.Close();
	if (pBuf)
		delete[]pBuf;
	if (pRead)
		delete[]pRead;
	if (bSuccess)
	{
		//RK_ResetRockusb();
	}
	else
	{
		m_Prog.SetFrontColor(RGB(224, 0, 0));
	}
	return bSuccess;
}

BOOL CRkCloneToolDlg::UploadImage(TCHAR *szDevPath, TCHAR *szImage, unsigned int uiOffset, unsigned int uiLen)
{
	CFile fp;
	int iRet;
	BOOL bSuccess = FALSE, bRet;
	DWORD dwMaxReadWriteBytes;
	PBYTE pRead = NULL;
	UINT  uiBegin, uiTransferSec;
	ULONGLONG dwTotalRead;
	DWORD dwTransferBytes, dwProgress, dwLastProgress;
	ULONGLONG dwFWSize;
	CString szReadSector;

	//------------------------------------------------------------------------------------
	dwMaxReadWriteBytes = MAX_READWRITE_SECTORS * SECTOR_SIZE;
	pRead = new BYTE[dwMaxReadWriteBytes];

	fp.m_hFile = INVALID_HANDLE_VALUE;
	bRet = fp.Open(m_szSavePathName, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary);
	if (!bRet)
	{
		goto Exit_ReadImage;
	}

	dwFWSize = uiLen * SECTOR_SIZE;
	dwLastProgress = dwProgress = 0;
	szReadSector.Format(TEXT("Read [00000000/%08llX]..."),uiLen);
	m_Prog.SetPrefixStr(szReadSector);
	m_Prog.SetPos(0);

	uiBegin = uiOffset;
	dwTotalRead = 0;

	while (dwTotalRead<dwFWSize)
	{
		memset(pRead, 0, dwMaxReadWriteBytes);
		if ((dwFWSize - dwTotalRead) >= dwMaxReadWriteBytes)
		{
			dwTransferBytes = dwMaxReadWriteBytes;
			uiTransferSec = MAX_READWRITE_SECTORS;
		}
		else
		{
			dwTransferBytes = (DWORD)(dwFWSize - dwTotalRead);
			uiTransferSec = ((dwTransferBytes%SECTOR_SIZE == 0) ? (dwTransferBytes / SECTOR_SIZE) : (dwTransferBytes / SECTOR_SIZE + 1));
		}
		iRet = RKD_ReadLBA((LPTSTR)(LPCTSTR)m_szLinkName, uiBegin, uiTransferSec, pRead);
		if (0 == iRet)
		{
			fp.Write(pRead, dwTransferBytes);
			dwTotalRead += dwTransferBytes;
			uiBegin += uiTransferSec;
		}
		else
		{
			goto Exit_ReadImage;
		}
		dwProgress = (DWORD)((dwTotalRead / 1024) * 100 / (dwFWSize / 1024));
		szReadSector.Format(TEXT("Read [%08llX/%08llX]..."), dwTotalRead / SECTOR_SIZE, uiLen);
		m_Prog.SetPrefixStr(szReadSector);
		m_Prog.SetPos((WORD)dwProgress);
		if (dwProgress != dwLastProgress)
		{
			dwLastProgress = dwProgress;
		}
	}

	bSuccess = TRUE;

Exit_ReadImage:

	if (fp.m_hFile != INVALID_HANDLE_VALUE)
		fp.Close();
	if (pRead)
		delete[]pRead;
	if (bSuccess)
	{
		//RK_ResetRockusb();
	}
	else
	{
		m_Prog.SetFrontColor(RGB(224, 0, 0));
	}
	return bSuccess;
}

void CRkCloneToolDlg::OnBnClickedWrite()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bConnected == FALSE)
	{
		MessageBox(TEXT("未发现Rockchip设备"), TEXT("错误"), MB_ICONERROR);
		return;
	}
	AfxBeginThread(BurnProc, this);
}


void CRkCloneToolDlg::OnBnClickedRead()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bConnected == FALSE)
	{
		MessageBox(TEXT("未发现Rockchip设备"), TEXT("错误"), MB_ICONERROR);
		return;
	}

	WCHAR szOffset[MAX_PATH], szLen[MAX_PATH];
	GetDlgItemText(IDC_STARTADDR, szOffset, MAX_PATH);
	GetDlgItemText(IDC_DATALEN, szLen, MAX_PATH);
	m_dwOffset = wcstoul(szOffset, 0, 16);
	m_dwSectorLen = wcstoul(szLen, 0, 16);

	if (wcslen(szOffset) == 0)
	{
		MessageBox(TEXT("请指定读扇区的开始地址"), TEXT("错误"), MB_ICONERROR);
		return;
	}

	if (wcslen(szLen) == 0)
	{
		MessageBox(TEXT("请指定读扇区总数"), TEXT("错误"), MB_ICONERROR);
		return;
	}

	if (m_dwSectorLen == 0)
	{
		MessageBox(TEXT("请输入有效的读扇区总数"), TEXT("错误"), MB_ICONERROR);
		return;
	}

	CFileDialog dlg(FALSE, 0, 0, 6, TEXT("Image File|*.img;*.bin||"), this);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	m_szSavePathName = dlg.GetPathName();
	CString szExt = PathFindExtension(m_szSavePathName);
	if (szExt.CompareNoCase(TEXT(".bin")) && szExt.CompareNoCase(TEXT(".img")))
	{
		m_szSavePathName += TEXT(".img");
	}
	AfxBeginThread(ReadProc, this);
}


void CRkCloneToolDlg::OnBnClickedBrowse()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, 0, 0, 6, TEXT("Image File|*.img;*.bin||"), this);
	if (dlg.DoModal() == IDOK)
	{
		m_szPathName = dlg.GetPathName();
		SetDlgItemText(IDC_PATHNAME, dlg.GetPathName());
	}
}


void CRkCloneToolDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RK_Uninitialize();
	UnregisterDeviceNotification(m_hDevNotify);
	CDialogEx::OnClose();
}
