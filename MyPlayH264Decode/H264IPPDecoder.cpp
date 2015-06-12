#include "StdAfx.h"
#include "H264IPPDecoder.h"

CH264IPPDecoder::CH264IPPDecoder(void)
{
	m_nWidth=0;
	m_nHeight=0;
}

CH264IPPDecoder::~CH264IPPDecoder(void)
{
}
BOOL CH264IPPDecoder::m_F_tH264DInit(Ipp8u *pVideoData,DWORD dwVideoSize,int nWidth,int nHeight)
{
	UMC::Status tStatus=UMC::UMC_OK;
	m_nWidth=nWidth;
	m_nHeight=nHeight;
	return TRUE;
}
UMC::Status CH264IPPDecoder::m_F_tH264DGetInfo()
{
	UMC::Status tStatus=UMC::UMC_OK;
	return tStatus;
}
UMC::Status CH264IPPDecoder::m_F_tH264DGetFrame()
{
	UMC::Status tStatus=UMC::UMC_OK;
	return tStatus;
}
UMC::Status CH264IPPDecoder::m_F_tH264DSetParams()
{
	UMC::Status tStatus=UMC::UMC_OK;
	return tStatus;
}
BOOL CH264IPPDecoder::m_F_tH264DReset()
{
	UMC::Status tStatus=UMC::UMC_OK;
	return TRUE;
}
BOOL CH264IPPDecoder::m_F_tH264DClose()
{
	UMC::Status tStatus=UMC::UMC_OK;
	return tStatus;
}
