// AVIFile.cpp : implementation file
//

#include "stdafx.h"
#include "MyPlayH264Decode.h"
#include "AVIFile.h"


// CAVIFile

CAVIFile::CAVIFile()
{
	::AVIFileInit();
}

CAVIFile::~CAVIFile()
{
	::AVIFileExit();
}


// CAVIFile member functions
void CAVIFile::m_S_AviFileInit()
{
	m_pAviFile=NULL;
	m_pAviStream=NULL;
	memset(&m_aviStreamInfo,0,sizeof(AVISTREAMINFO));
	m_pBitmapInfo=NULL;
	m_pGetFrame=NULL;
	m_lEndTime=0;
	m_nFirstFrame=0;
	m_nNumFrames=0;
}
int CAVIFile::m_F_bReadAviFileBegin(LPCTSTR strFileName)
{
	if(::AVIFileOpen(&m_pAviFile,strFileName,OF_READ,NULL))
	{
		::AVIFileRelease(m_pAviFile);
		return AVIOPENERROR;
	}
	AVIFILEINFO aviFileInfo;
	::AVIFileInfo(m_pAviFile,&aviFileInfo,sizeof(aviFileInfo));
	HRESULT hr=::AVIFileGetStream(m_pAviFile,&m_pAviStream,streamtypeVIDEO,0);
	if(hr)
	{
		::AVIStreamRelease(m_pAviStream);
		::AVIFileRelease(m_pAviFile);
		return AVIGETSTREAMERROR;
	}
	m_nFirstFrame=::AVIStreamStart(m_pAviStream);
	if(m_nFirstFrame==-1)
	{
		::AVIStreamRelease(m_pAviStream);
		::AVIFileRelease(m_pAviFile);
		return AVIGETSTREAMERROR;
	}
	m_nNumFrames=::AVIStreamLength(m_pAviStream);
	if(m_nNumFrames==-1)
	{
		::AVIStreamRelease(m_pAviStream);
		::AVIFileRelease(m_pAviFile);
		return AVIGETSTREAMERROR;
	}
	m_F_bGetVideoFormat();
	return TRUE;
}
BOOL CAVIFile::m_F_bGetVideoFormat()
{

	m_pGetFrame=::AVIStreamGetFrameOpen(m_pAviStream,NULL);
	if(m_pGetFrame==NULL)
		return FALSE;
	//取得AVISTREAMINFO所有資訊
	::AVIStreamInfo(m_pAviStream,&m_aviStreamInfo,sizeof(AVISTREAMINFO));
	//決定格式
	LONG lSize;
	if(::AVIStreamReadFormat(m_pAviStream,m_nFirstFrame,NULL,&lSize))
	{
		return FALSE;
	}
	//BYTE *pChunk=new BYTE[lSize];
	//if(::AVIStreamReadFormat(m_pAviStream,m_nFirstFrame,pChunk,&lSize))
	//{
	//	return FALSE;
	//}
	//memcpy(m_pBitmapInfo,pChunk,sizeof(m_pBitmapInfo));
	//m_pBitmapInfo=(LPBITMAPINFO)pChunk;
	//pChunk=NULL;
	return TRUE;

}
BOOL CAVIFile::m_F_bStartVideoRetrieve()
{
	//m_pGetFrame=::AVIStreamGetFrameOpen(m_pAviStream,NULL);
	//if(m_pGetFrame==NULL)
	//	return FALSE;
	//m_lEndTime=::AVIStreamEndTime(m_pAviStream);	
	BITMAPINFOHEADER bih;
	long lSize =sizeof(BITMAPINFOHEADER);
	int index=0;
	for(int i=m_nFirstFrame;i<m_nNumFrames;i++)
	{
		index=i-m_nFirstFrame;
		//BYTE* pDIBInfo=(BYTE*)::AVIStreamGetFrame(m_pGetFrame,index);
		//::AVIStreamReadFormat(m_pAviStream,index,&bih,&lSize);
		AVIStreamSampleSize(m_pAviStream,index,&lSize);
		BYTE* pDIB = new BYTE[lSize];
		::AVIStreamRead(m_pAviStream,index,1,pDIB,lSize,NULL,NULL);
		delete [] pDIB;
		pDIB=NULL;
	}
	return TRUE;
}
BOOL CAVIFile::m_F_bGetVideoFrameAtTime(long lTime,LPBITMAPINFOHEADER *pBmp)
{
	LONG lFrame=0;
	if(lTime<=m_lEndTime)
	{
		lFrame=::AVIStreamTimeToSample(m_pAviStream,lTime);
	}
	else
	{
		*pBmp=NULL;
		return FALSE;
	}
	*pBmp=(LPBITMAPINFOHEADER)::AVIStreamGetFrame(m_pGetFrame,lFrame);
	return TRUE;
}
void CAVIFile::m_S_GetVideoFrame(long lFrame,LPBITMAPINFOHEADER *pBmp)
{
	*pBmp=(LPBITMAPINFOHEADER)::AVIStreamGetFrame(m_pGetFrame,lFrame);
}
BOOL CAVIFile::m_F_bEndVideoRetrieve()
{
	if(m_pGetFrame)
	{
		if(::AVIStreamGetFrameClose(m_pGetFrame))
		{
			return FALSE;
		}
		m_pGetFrame=NULL;
	}
	return TRUE;
}
BOOL CAVIFile::m_F_bReadAviFileEnd()
{
	if(m_pAviStream)
	{
		::AVIStreamRelease(m_pAviStream);
		m_pAviStream=NULL;
	}
	if(m_pAviFile)
	{
		::AVIFileRelease(m_pAviFile);
		m_pAviFile=NULL;
	}
	return TRUE;
}