#pragma once

#include <vfw.h>
#include "DefAVIMsg.h"
// CAVIFile command target

class CAVIFile : public CObject
{
private:
	PAVIFILE m_pAviFile;
	PAVISTREAM m_pAviStream;
	AVISTREAMINFO m_aviStreamInfo;
	LPBITMAPINFO m_pBitmapInfo;
	PGETFRAME m_pGetFrame;
	long m_lEndTime;
	int m_nFirstFrame;
	int m_nNumFrames;
public:
	CAVIFile();
	virtual ~CAVIFile();
	void m_S_AviFileInit();
	int m_F_bReadAviFileBegin(LPCTSTR strFileName);
	BOOL m_F_bGetVideoFormat();
	BOOL m_F_bStartVideoRetrieve();
	BOOL m_F_bGetVideoFrameAtTime(long lTime,LPBITMAPINFOHEADER *pBmp);
	void m_S_GetVideoFrame(long lFrame,LPBITMAPINFOHEADER *pBmp);
	BOOL m_F_bEndVideoRetrieve();
	BOOL m_F_bReadAviFileEnd();
};


