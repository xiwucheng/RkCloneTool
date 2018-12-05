/******************************************************************/
/*	Copyright (C)  ROCK-CHIPS FUZHOU . All Rights Reserved. 	  */
/*******************************************************************
File    :   RKUpgradeDll.h
Desc    :   Rockchip upgrade tool DLL
Author  :   Steven Chen
Date    :   2009-12-30
Notes   :   

Revision 1.00  2009-12-30 10:18:54	Steven Chen
********************************************************************/

#ifndef __RKUPGRADEDLL_H__
#define __RKUPGRADEDLL_H__

#ifdef RKUPGRADEDLL_EXPORTS
#define RKUPGRADE_API __declspec(dllexport)
#else
#define RKUPGRADE_API __declspec(dllimport)
#endif

/***************************************Const Declaration****************************************/
#define MAX_DEVICE				16
/****************************************Type Declaration****************************************/
typedef enum
{
	RKUSB_NONE = 0x0,
	RKUSB_MASKROM = 0x01,
	RKUSB_LOADER = 0x02,
	RKUSB_MSC = 0x04,
	RKUSB_ADB = 0x08,
	RKUSB_MTP = 0x10,
	RKUSB_UVC = 0x20
}ENUM_RKUSB_TYPE;

#pragma pack(1)
// Struct of initialize parameter
typedef struct _INIT_DEV_INFO
{	
    BOOL	bScan4FsUsb;				// Scan for full speed usb device
    USHORT	usRockusbVid;
    USHORT	usRockusbPid;
    USHORT	usRockMscVid;
    USHORT	usRockMscPid;
	USHORT  usRockAdbVid;
	USHORT  usRockAdbPid;
	USHORT  usRockUvcVid;
	USHORT  usRockUvcPid;
	USHORT  usRockMtpVid;
	USHORT  usRockMtpPid;
    UINT	uiRockusbTimeout;
    UINT	uiRockMscTimeout;
    UINT	emSupportDevice;
}INIT_DEV_INFO,PINIT_DEV_INFO;

typedef struct _INIT_LOG_INFO_W
{
    BOOL bLogEnable;
    LPWSTR lpszLogPathName;
}INIT_LOG_INFO_W,PINIT_LOG_INFO_W;
typedef struct _INIT_LOG_INFO_A
{
    BOOL bLogEnable;
    LPSTR lpszLogPathName;
}INIT_LOG_INFO_A,PINIT_LOG_INFO_A;
#ifdef _UNICODE
	#define INIT_LOG_INFO INIT_LOG_INFO_W
	#define PINIT_LOG_INFO PINIT_LOG_INFO_W
#else
	#define INIT_LOG_INFO INIT_LOG_INFO_A
	#define PINIT_LOG_INFO PINIT_LOG_INFO_A
#endif

typedef struct _INIT_CALLBACK_INFO
{
    LPVOID pUpgradeStepPromptProc;	// Prompt certain step status is started, passed or failed.
    LPVOID pProgressPromptProc;		// Prompt progress of certain operation which may take long time.
}INIT_CALLBACK_INFO,PINIT_CALLBACK_INFO;

// Struct of device information
typedef struct _STRUCT_DEVICE_DESC_W
{
    USHORT	usVid;
    USHORT	usPid;
    DWORD	dwDeviceInstance;
    WCHAR   szLinkName[MAX_PATH];
	DWORD	dwLayer;   
    UINT	emUsbType;
    UINT	emDeviceType;
	BOOL	bUsb20;
}STRUCT_DEVICE_DESC_W,*PSTRUCT_DEVICE_DESC_W;
typedef struct _STRUCT_DEVICE_DESC_A
{
    USHORT	usVid;
    USHORT	usPid;
    DWORD	dwDeviceInstance;
    CHAR    szLinkName[MAX_PATH];
    DWORD	dwLayer;
    UINT	emUsbType;
    UINT	emDeviceType;
	BOOL	bUsb20;
}STRUCT_DEVICE_DESC_A,*PSTRUCT_DEVICE_DESC_A;
#ifdef _UNICODE
	#define STRUCT_DEVICE_DESC STRUCT_DEVICE_DESC_W
	#define PSTRUCT_DEVICE_DESC PSTRUCT_DEVICE_DESC_W
#else
	#define STRUCT_DEVICE_DESC STRUCT_DEVICE_DESC_A
	#define PSTRUCT_DEVICE_DESC PSTRUCT_DEVICE_DESC_A
#endif

typedef struct _STRUCT_UPGRADE_PARAM_A 
{
	BOOL bEnableFormat; //format user disk  
	BOOL bEnableCopyData;//copy file or dir to user disk 
	BOOL bEnableFormatDataDisk;//format data disk  <android not support>
	BOOL bEnableCopyDataDiskData;//copy file or dir to data disk <android not support>
	LPSTR lpszDiskVolume;//user disk volume,can be NULL									  
	LPSTR lpszDataPath;//path of file|dir copying to user disk,can be NULL
	LPSTR lpszDataDiskVolume;//data disk volume,can be NULL
	LPSTR lpszDataDiskPath;//path of file|dir copying to data disk,can be NULL
	UINT  uiMiscModifyFlag;//0:not change misc.img,1:wipe_all 2:wipe_data(only support android)
	BOOL	bMscReset;//true:after copying data,device reset automatically,default is false
	BOOL	bResetAfterUpgrade;//true:after finishing upgrade,device reset(default),false:not to reset device
	USHORT usIgnoreIDBUpgradeFlag;//0x5AA5:upgrade firmware without upgrading idblock only in upgrade function
}STRUCT_UPGRADE_PARAM_A,*PSTRUCT_UPGRADE_PARAM_A;

typedef struct _STRUCT_UPGRADE_PARAM_W 
{
	BOOL bEnableFormat; 
	BOOL bEnableCopyData;
	BOOL bEnableFormatDataDisk;
	BOOL bEnableCopyDataDiskData;
	LPWSTR lpszDiskVolume;									  
	LPWSTR lpszDataPath;
	LPWSTR lpszDataDiskVolume;
	LPWSTR lpszDataDiskPath;
	UINT  uiMiscModifyFlag;
	BOOL	bMscReset;
	BOOL	bResetAfterUpgrade;
	USHORT usIgnoreIDBUpgradeFlag;
}STRUCT_UPGRADE_PARAM_W,*PSTRUCT_UPGRADE_PARAM_W;

typedef struct _STRUCT_SEC3_DATA
{
	PBYTE pSn;
	USHORT usSnSize;
	PBYTE pUid;
	BYTE  btUidSize;
	PBYTE pImei;
	BYTE  btImeiSize;
	PBYTE pBt;
	BYTE  btBlueToothSize;
	PBYTE pMac;
	BYTE  btMacSize;
	PBYTE pWifi;
	BYTE  btWifiSize;
	PBYTE pReserved;
	BYTE  btReservedSize;
}STRUCT_SEC3_DATA,*PSTRUCT_SEC3_DATA;

#ifdef _UNICODE
#define STRUCT_UPGRADE_PARAM STRUCT_UPGRADE_PARAM_W
#define PSTRUCT_UPGRADE_PARAM PSTRUCT_UPGRADE_PARAM_W
#else
#define STRUCT_UPGRADE_PARAM STRUCT_UPGRADE_PARAM_A
#define PSTRUCT_UPGRADE_PARAM PSTRUCT_UPGRADE_PARAM_A
#endif

//struct of provisioning data
typedef struct _PROVISIONING_DATA 
{
	USHORT id;
	USHORT flag;
	USHORT size;
	USHORT reserved;
	BYTE   data[1];
}PROVISIONING_DATA,*PPROVISIONING_DATA;
#pragma pack()
/****************************************Function Declaration************************************/
/*----------------------------------------------------------------------
Name    :   RK_Initialize
Desc    :   Initialize global variables
Params  :   (IN)InitDevInfo:			Device info to be initialized
            (IN)InitLogInfo:			Log info to be initialized
            (IN)InitCallbackInfo		Callback function info to be initialized
Return  :   TRUE:						SUCCESSED
            FALSE:						FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_InitializeW(INIT_DEV_INFO InitDevInfo, 
										   INIT_LOG_INFO_W InitLogInfo,
										   INIT_CALLBACK_INFO InitCallbackInfo);
RKUPGRADE_API BOOL _stdcall RK_InitializeA(INIT_DEV_INFO InitDevInfo, 
										   INIT_LOG_INFO_A InitLogInfo,
										   INIT_CALLBACK_INFO InitCallbackInfo);
#ifdef _UNICODE
#define  RK_Initialize RK_InitializeW
#else
#define  RK_Initialize RK_InitializeA
#endif

/*----------------------------------------------------------------------
Name    :   RK_SetFirmware
Desc    :   Set and analyze firmware
Params  :   (IN)lpszFirmwarePathName:	Image file to be upgraded
            (IN)bCheckFw:true means check firmware it takes much time, default do not check the firmware
Return  :   TRUE:						SUCCESSED
            FALSE:						FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_SetFirmwareW(LPCWSTR lpszFirmwarePathName,BOOL bCheckFw=FALSE);
RKUPGRADE_API BOOL _stdcall RK_SetFirmwareA(LPCSTR lpszFirmwarePathName,BOOL bCheckFw=FALSE);
#ifdef _UNICODE
#define  RK_SetFirmware RK_SetFirmwareW
#else
#define  RK_SetFirmware RK_SetFirmwareA
#endif
/*----------------------------------------------------------------------
Name    :   RK_Uninitialize
Desc    :   Uninitialize global variables
Params  :   NONE
Return  :   TRUE:					SUCCESSED
            FALSE:					FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_Uninitialize();

/*----------------------------------------------------------------------
Name    :   RK_ScanDevice
Desc    :   Scan for the specified rockusb type(ENUM_RKUSB_TYPE)
Params  :   (OUT)pDevs: retrieve connected device info
            (OUT)bExistMsc: judge if existing msc device in the scanning devices	
Return  :   TRUE:            SUCCESSED
            FALSE:           FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API int _stdcall RK_ScanDeviceA(PSTRUCT_DEVICE_DESC_A *ppDevs);
RKUPGRADE_API int _stdcall RK_ScanDeviceW(PSTRUCT_DEVICE_DESC_W *ppDevs);
#ifdef _UNICODE
#define  RK_ScanDevice RK_ScanDeviceW
#else
#define  RK_ScanDevice RK_ScanDeviceA
#endif

/*----------------------------------------------------------------------
Name    :   RK_EraseFlash
Desc    :   Erase flash
Params  :	(IN)dwLayer:device layer value,0:default first device in the scan result,other:specified device's layer value
Return  :   TRUE:					SUCCESSED
            FALSE:					FAILED
Notes   :   Though the callback function, we can retrieve the progress of erase operation.
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_EraseFlash(DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_Upgrade
Desc    :   Upgrade device
Params  :   (IN)upgradeParam:  see the definition
            (IN)dwLayer:device layer value
Return  :   TRUE:             SUCCESSED
            FALSE:            FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_UpgradeW(STRUCT_UPGRADE_PARAM_W &upgradeParam,DWORD dwLayer=0);
RKUPGRADE_API BOOL _stdcall RK_UpgradeA(STRUCT_UPGRADE_PARAM_A &upgradeParam,DWORD dwLayer=0);
#ifdef _UNICODE
#define  RK_Upgrade RK_UpgradeW
#else
#define  RK_Upgrade RK_UpgradeA
#endif

/*----------------------------------------------------------------------
Name    :   RK_Restore
Desc    :   Restore device
Params  :   (IN)upgradeParam:      see the definition
            (IN)dwLayer:    device layer value

Return  :   TRUE:					SUCCESSED
            FALSE:					FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_RestoreW(STRUCT_UPGRADE_PARAM_W &upgradeParam,DWORD dwLayer=0);
RKUPGRADE_API BOOL _stdcall RK_RestoreA(STRUCT_UPGRADE_PARAM_A &upgradeParam,DWORD dwLayer=0);
#ifdef _UNICODE
#define  RK_Restore RK_RestoreW
#else
#define  RK_Restore RK_RestoreA
#endif


/*----------------------------------------------------------------------
Name    :   RK_ReadCustomData
Desc    :   Read Custom Data from device
Params  :   (OUT)pCustomData:			Point to CustomData buffer (Maximum=512 Bytes)
            (OUT)nCustomDataLen:			Length of CustomData
			(OUT)nCustomDataOffset:		Offset of CustomData
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadCustomData(PBYTE pCustomData, INT &nCustomDataLen,INT &nCustomDataOffset,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteCustomData
Desc    :   Write Custom Data to device
Params  :   (IN)pCustomData:        Point to CustomData buffer (Maximum=512 Bytes)
			(IN)nCustomDataOffset:  Offset of CustomData
            (IN)nCustomDataLen:     Length of CustomData
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteCustomData(PBYTE pCustomData, INT nCustomDataOffset,INT nCustomDataLen,DWORD dwLayer=0);


/*----------------------------------------------------------------------
Name    :   RK_ReadSN
Desc    :   Read SN from device
Params  :   (OUT)pSN:			Point to Sn buffer (Maximum=30 Bytes)
            (OUT)nSNLen:		Length of SN
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadSN(PBYTE pSN, INT& nSNLen,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteSN
Desc    :   Write SN to device
Params  :   (IN)pSN:        Point to Sn buffer (Maximum=30 Bytes)
            (IN)nSNLen:     Length of SN
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteSN(PBYTE pSN, INT nSNLen,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadMAC
Desc    :   Read MAC from device
Params  :   (OUT)pMac:			Point to Mac buffer (Maximum=6 Bytes)
            (OUT)nMacLen:		Length of Mac
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadMAC(PBYTE pMac, INT& nMacLen,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteMAC
Desc    :   Write Mac to device
Params  :   (IN)pMac:        Point to Mac buffer (Maximum=6 Bytes)
            (IN)nMacLen:     Length of Mac
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteMAC(PBYTE pMac, INT nMacLen=6,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadWifi
Desc    :   Read Wifi from device
Params  :   (OUT)pWifi:			Point to Wifi buffer (Maximum=6 Bytes)
            (OUT)nWifiLen:		Length of Wifi
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadWifi(PBYTE pWifi, INT& nWifiLen,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteWifi
Desc    :   Write Wifi to device
Params  :   (IN)pWifi:        Point to Wifi buffer (Maximum=6 Bytes)
            (IN)nWifiLen:     Length of Wifi
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteWifi(PBYTE pWifi, INT nWifiLen=6,DWORD dwLayer=0);


/*----------------------------------------------------------------------
Name    :   RK_ReadIMEI
Desc    :   Read IMEI from device
Params  :   (OUT)pImei:			Point to Imei buffer (Maximum=15 Bytes)
            (OUT)nImeiLen:		Length of Imei
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadIMEI(PBYTE pImei, INT& nImeiLen,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteIMEI
Desc    :   Write Imei to device
Params  :   (IN)pImei:        Point to Imei buffer (Maximum=15 Bytes)
            (IN)nImeiLen:     Length of Imei
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteIMEI(PBYTE pImei, INT nImeiLen=15,DWORD dwLayer=0);


/*----------------------------------------------------------------------
Name    :   RK_ReadBT
Desc    :   Read BT from device
Params  :   (OUT)pBT:			Point to Bt buffer (Maximum=6 Bytes)
            (OUT)nBTLen:		Length of Bt
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadBT(PBYTE pBT, INT& nBTLen,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteBT
Desc    :   Write BT to device
Params  :   (IN)pBT:        Point to BT buffer (Maximum=6 Bytes)
            (IN)nBTLen:     Length of BT
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteBT(PBYTE pBT, INT nBTLen=6,DWORD dwLayer=0);


/*----------------------------------------------------------------------
Name    :   RK_ReadAllInfo
Desc    :   Read all info of idb sector 3 
Params  :   (OUT)allInfo:		Include sn,uid,mac,bt and imei 
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadAllInfo(STRUCT_SEC3_DATA &allInfo, DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteAllInfo
Desc    :   Write all info to idb sector 3 
Params  :   (IN)allInfo:	Include sn,uid,mac,bt and imei
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteAllInfo(STRUCT_SEC3_DATA &allInfo,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadBid
Desc    :   Read bid from flash 
Params  :   (OUT)pBid:	this buffer must be larger than 96 Bytes 
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadBid(PBYTE pBid, DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteBid
Desc    :   Write bid to flash
Params  :   (IN)pBid: Bid is a 96 bytes buffer
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteBid(PBYTE pBid,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ClearAllInfo
Desc    :   clear all of sector3 data
Params  :   
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ClearAllInfo(DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadVendorInfo
Desc    :   Read vendor info from flash,1 vendor sector = 504 Bytes
Params  :   (IN)sectorOffset:		number of sectors from begin of vendor info
			(IN)sectorCount:		number of sectors to read
			(OUT)pVendorBuffer:		buffer to save vendor info, malloc by caller,504*sectorCount(Bytes) at least
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadVendorInfo(int sectorOffset,int sectorCount,PBYTE pVendorBuffer, DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteVendorInfo
Desc    :   Write vendor info to flash,1 vendor sector = 504 Bytes
Params  :   (IN)sectorOffset:		number of sectors from begin of vendor info
			(IN)sectorCount:		number of sectors to write
			(OUT)pVendorBuffer:		buffer to write vendor info, malloc by caller,504*sectorCount(Bytes) at least
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteVendorInfo(int sectorOffset,int sectorCount,PBYTE pVendorBuffer, DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadProvisioningData
Desc    :   Read provisioning data by id
Params  :   (IN)nID					id 
			(OUT)pDataBuffer:		buffer to save data, malloc by caller
			(IN|OUT)nBufferSize:	in = size of buffer,out = actual data size
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadProvisioningData(USHORT nID,PBYTE pDataBuffer,USHORT &nBufferSize,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteProvisioningData
Desc    :   Write provisioning data by id
Params  :   (IN)nID					id 
			(IN)pDataBuffer:		buffer to save data, malloc by caller
			(IN)nBufferSize:		size of buffer
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteProvisioningData(USHORT nID,PBYTE pDataBuffer,USHORT nBufferSize,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadEfuse
Desc    :   Read efuse from device
Params  :   (OUT)pEfuse:			Point to efuse buffer (buffer must be larger than usReadSize)
			(IN)usReadSize			size of efuse data
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadEfuse(PBYTE pEfuse,USHORT usReadSize,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadKeyHashFromEfuse
Desc    :   Read key hash from efuse
Params  :   (OUT)pKeyHash:			Point to buffer (buffer size >= 32bytes)
			(OUT)usKeyHashSize		size of key hash
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadKeyHashFromEfuse(PBYTE pKeyHash,USHORT &usKeyHashSize,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteKeyHashToEfuse
Desc    :   Write key hash to efuse
Params  :  
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   get key hash from firmware,call RK_SetFirmware before.
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteKeyHashToEfuse(DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadDataFromEfuse
Desc    :   Read data from efuse
Params  :   (OUT)pBuffer:		save data reading from efuse
			(IN)usPos			position to read
			(IN)usReadSize		size to read
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadDataFromEfuse(PBYTE pBuffer,USHORT usPos,USHORT usReadSize,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_WriteDataToEfuse
Desc    :   Write data to efuse
Params  :   (OUT)pBuffer:		data writing to efuse
			(IN)usPos			position to write
			(IN)usWriteSize		size to write
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_WriteDataToEfuse(PBYTE pBuffer,USHORT usPos,USHORT usWriteSize,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadUID
Desc    :   Read UID from device
Params  :   (OUT)pUID:			Point to UID buffer (Maximum=30 Bytes)
            (OUT)nUIDLen:		Length of UID
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadUID(PBYTE pUID, INT& nUIDLen,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadParameterFile
Desc    :   Read paramter file from device
Params  :   (OUT)pParameter:		Point to parameter buffer
            (OUT)nParamSize:		Length of parameter buffer size
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   when nParamSize=-1,in order to get parameter required size save to nParamSize
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadParameterFile(PBYTE pParameter, INT& nParamSize,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ReadFirmwareParameterFile
Desc    :   Read paramter file from firmware
Params  :   (OUT)pParameter:		Point to parameter buffer
            (OUT)nParamSize:		Length of parameter buffer size
			(IN)dwLayer:device layer value
Return  :   TRUE:				SUCCESSED
            FALSE:				FAILED
Notes   :   when nParamSize=-1,in order to get parameter required size save to nParamSize
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ReadFirmwareParameterFile(PBYTE pParameter, INT& nParamSize);

/*----------------------------------------------------------------------
Name    :   RK_GetFirmwareDiskSize
Desc    :   Get disk size from firmware
Params  :   (OUT)uiSysDiskSize: System disk size(MB)	
            (OUT)uiDataDiskSize:Data disk size(MB)
Return  :   TRUE:               SUCCESSED
            FALSE:              FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_GetFirmwareDiskSize(UINT& uiSysDiskSize,UINT& uiDataDiskSize);

/*----------------------------------------------------------------------
Name    :   RK_GetFirmwareVersion
Desc    :   Get version info from firmware
Params  :   (OUT)dwFwVer: Firmware version
            (OUT)dwBootVer:Boot version
Return  :   TRUE:             SUCCESSED
            FALSE:            FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_GetFirmwareVersion(DWORD &dwFwVer,DWORD &dwBootVer);


/*----------------------------------------------------------------------
Name    :   RK_SwitchToRockusb
Desc    :   Switch mass storage device to rockusb device
Params  :   (IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_SwitchToRockusb(DWORD dwSubCode=0,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_AdbToRockusb
Desc    :   Switch adb device to rockusb device
Params  :   (IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
//RKUPGRADE_API BOOL _stdcall RK_AdbToRockusb(DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_SendMscCommand
Desc    :   Send extended command to msc device
Params  :   (IN)dwCmdCode,extended command code
			(OUT)pOutBuffer,malloc by caller in order to saving output data
			(IN)uiOutBufferSize,need to read size of output data
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_SendMscCommand(DWORD dwCmdCode,PBYTE pOutBuffer=NULL,UINT uiOutBufferSize=0,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_RemoveRockMsc
Desc    :   Disconnect Msc device
Params  :   (IN)dwLayer:device layer value
Return  :   TRUE:                       SUCCESSED
            FALSE:                      FAILED
Notes   :   
Author  :   Steven Chen
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_RemoveRockMsc(DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_ResetRockusb
Desc    :   Reset rockusb device
Params  :   (IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_ResetRockusb(BYTE subCode=0,DWORD dwLayer=0);
RKUPGRADE_API BOOL _stdcall RK_OpenChannel(BYTE *pChannelData,DWORD dwLayer=0);
RKUPGRADE_API BOOL _stdcall RK_WaitDevice(DWORD dwLayer,UINT uiUsbType);
//call rk_setfirmware before calling RK_DownloadBoot 
RKUPGRADE_API BOOL _stdcall RK_DownloadBoot(DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_TestRockusb
Desc    :   test rockusb device
Params  :   (IN)subCode:set subcode to execute different function
			(IN)dwLayer:device layer value
Return  :   TRUE:           SUCCESSED
            FALSE:          FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_TestRockusb(BYTE subCode,DWORD dwLayer=0);

/*----------------------------------------------------------------------
Name    :   RK_UnlockDevice
Desc    :   unlock device
Params  :   (IN)lpszCertPath:  Specify the path of cert
			(IN)dwLayer:device layer value
Return  :   TRUE:                       SUCCESSED
            FALSE:                      FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_UnlockDeviceW(LPCWSTR lpszCertPath,DWORD dwLayer=0);
RKUPGRADE_API BOOL _stdcall RK_UnlockDeviceA(LPCSTR lpszCertPath,DWORD dwLayer=0);
#ifdef _UNICODE
#define RK_UnlockDevice RK_UnlockDeviceW
#else
#define RK_UnlockDevice RK_UnlockDeviceA
#endif

/*----------------------------------------------------------------------
Name    :   RK_DownloadFile
Desc    :   Write file to device by lba
Params  :   (IN)lpszFilePath:  Specify the path of file
			(IN)dwOffset: offset address
			(IN)dwLayer:device layer value
Return  :   TRUE:                       SUCCESSED
            FALSE:                      FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_DownloadFileW(LPCWSTR lpszFilePath,DWORD dwOffset,DWORD dwLayer=0);
RKUPGRADE_API BOOL _stdcall RK_DownloadFileA(LPCSTR lpszFilePath,DWORD dwOffset,DWORD dwLayer=0);
#ifdef _UNICODE
#define RK_DownloadFile RK_DownloadFileW
#else
#define RK_DownloadFile RK_DownloadFileA
#endif
/*----------------------------------------------------------------------
Name    :   RK_UploadFile
Desc    :   read data from device to file
Params  :   (IN)lpszFilePath:  Specify the path of file
			(IN)dwOffset: offset address
			(IN)dwCount:  counts of sector
			(IN)dwLayer:device layer value
Return  :   TRUE:                       SUCCESSED
            FALSE:                      FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API BOOL _stdcall RK_UploadFileW(LPCWSTR lpszFilePath,DWORD dwOffset,DWORD dwCount,DWORD dwLayer=0);
RKUPGRADE_API BOOL _stdcall RK_UploadFileA(LPCSTR lpszFilePath,DWORD dwOffset,DWORD dwCount,DWORD dwLayer=0);
#ifdef _UNICODE
#define RK_UploadFile RK_UploadFileW
#else
#define RK_UploadFile RK_UploadFileA
#endif

/*----------------------------------------------------------------------
Name    :   RKD_WriteLBA
Desc    :   Write data to device at offset
Params  :   (IN)pszDevicePath: device path using to create handle
            (IN)dwOffset: writing position by sector unit
			(IN)dwCount: writing counts by sector unit
			(IN)pBuf:buffer to write
Return  :   0:              SUCCESSED
            minus:             FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API int _stdcall RKD_WriteLBA_A(PCHAR pszDevicePath,DWORD dwOffset,DWORD dwCount,PBYTE pBuf);
RKUPGRADE_API int  _stdcall RKD_WriteLBA_W(PWCHAR pszDevicePath,DWORD dwOffset,DWORD dwCount,PBYTE pBuf);
#ifdef _UNICODE
#define  RKD_WriteLBA RKD_WriteLBA_W
#else
#define  RKD_WriteLBA RKD_WriteLBA_A
#endif

/*----------------------------------------------------------------------
Name    :   RKD_ReadLBA
Desc    :   read data from device at offset
Params  :   (IN)pszDevicePath: device path using to create handle
            (IN)dwOffset: reading position by sector unit
			(IN)dwCount: reading counts by sector unit
			(IN)pBuf:buffer to read
Return  :   0:              SUCCESSED
            minus:             FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API int _stdcall RKD_ReadLBA_A(PCHAR pszDevicePath,DWORD dwOffset,DWORD dwCount,PBYTE pBuf);
RKUPGRADE_API int  _stdcall RKD_ReadLBA_W(PWCHAR pszDevicePath,DWORD dwOffset,DWORD dwCount,PBYTE pBuf);
#ifdef _UNICODE
#define  RKD_ReadLBA RKD_ReadLBA_W
#else
#define  RKD_ReadLBA RKD_ReadLBA_A
#endif

/*----------------------------------------------------------------------
Name    :   RKD_DownloadBoot
Desc    :   loading ddr code and usb code into ram to run,the operation must be at the state of maskrom
Params  :   (IN)pszDevicePath: device path using to create handle
            (IN)pszFile: loader or firmware
Return  :   0:              SUCCESSED
            minus:             FAILED
Notes   :   
Author  :   Seth
----------------------------------------------------------------------*/
RKUPGRADE_API int _stdcall RKD_DownloadBoot_A(PCHAR pszDevicePath,PCHAR pszFile);
RKUPGRADE_API int  _stdcall RKD_DownloadBoot_W(PWCHAR pszDevicePath,PWCHAR pszFile);
#ifdef _UNICODE
#define  RKD_DownloadBoot RKD_DownloadBoot_W
#else
#define  RKD_DownloadBoot RKD_DownloadBoot_A
#endif


#endif


