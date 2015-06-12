//#pragma once
#include "ipp.h"
#include "umc_defs.h"
#include "umc_video_decoder.h"
#include "umc_video_data.h"
#include "umc_h264_dec.h"
#include "umc_structures.h"

class CH264IPPDecoder
{
private:
	UMC::MediaData m_IPPMediaDataIn;
	UMC::VideoData m_IPPVideoDataOut;
	UMC::H264VideoDecoder m_IPPH264Decoder;
	UMC::VideoDecoderParams m_IPPH264DParams;
	int m_nWidth;
	int m_nHeight;
public:
	CH264IPPDecoder(void);
	BOOL m_F_tH264DInit(Ipp8u *pVideoData,DWORD dwVideoSize,int nWidth,int nHeight);
	UMC::Status m_F_tH264DGetFrame();
	UMC::Status m_F_tH264DGetInfo();
	UMC::Status m_F_tH264DSetParams();
	BOOL m_F_tH264DReset();
	BOOL m_F_tH264DClose();
public:
	~CH264IPPDecoder(void);
};
