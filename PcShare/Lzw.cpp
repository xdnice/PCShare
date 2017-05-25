#include "stdafx.h"
#include "Lzw.h"

//===================================================================
// 目标为8位色
void  FCLzw::Decode_WriteString_to8 (WORD Code)
{
	if (Code < m_LZW_CLEAR)
	{
		m_pCurOut[m_dwCurrPixel++] = (BYTE) m_pStrBegin[Code].wSuffix ;
		if (m_dwCurrPixel == m_dwDibWidth) // 写完一行, 切换值至下一行
			this->Decode_SwitchToFollowLine () ;
	}
	else
	{
		this->Decode_WriteString_to8 (m_pStrBegin[Code].wPrefix) ;
		this->Decode_WriteString_to8 (m_pStrBegin[Code].wSuffix) ;
	}
}
//===================================================================
void  FCLzw::LZW_GIF_Decode (BYTE * InBuffer, BYTE * DibBuffer, DWORD dwDibWidth, DWORD dwDibHeight, bool bInterlace)
{
	m_pStrBegin = new LZW_STRING [LZW_MAX_TABLE_SIZE + 32] ;
	if ((m_pStrBegin == NULL) || (InBuffer == NULL) || (DibBuffer == NULL))
		 return ;
	//	初始化设置-----------------------------------------+
	m_pCurIn = InBuffer + 1 ;
	m_pCurOut = DibBuffer ;
	m_byInBit = 0 ; // 输入从0开始, 输出为8位色位图
	m_byMinCode = *InBuffer ; // 获得最小码长度
	m_LZW_CLEAR = 1 << m_byMinCode ; // clear
	m_LZW_END = m_LZW_CLEAR + 1 ; // end

	m_dwDibWidth = dwDibWidth ; // DIB宽
	m_dwCurrPixel = 0 ;
	m_dwPitch = 4 * ((dwDibWidth * 8 + 31) / 32) ;

	m_byInterval = bInterlace ? 0 : 0xFF ; // 设置交错索引
	if (m_byInterval == 0) // 交错存储
	{
		m_pOrigin = m_pCurOut ;
		m_dwDibHeight = dwDibHeight ; // DIB高
		m_dwCurrHeight = 0 ; // 从最顶行开始
	}
	//	初始化设置完成-------------------------------------+

	WORD		Code, Old ;
	this->Decode_InitStringTable () ;
	while ((Code = this->Decode_GetNextCode ()) != m_LZW_END)
	{
		if (Code == m_LZW_CLEAR)
		{
			this->Decode_InitStringTable () ;
			while ((Code = this->Decode_GetNextCode ()) == m_LZW_CLEAR) ;
		}
		else
			if (this->Decode_IsInTable (Code))
				this->Decode_AddStringToTable (Old, this->Decode_GetFirstChar (Code)) ;
			else
				this->Decode_AddStringToTable (Old, this->Decode_GetFirstChar (Old)) ;

		this->Decode_WriteString_to8 (Code) ;
		Old = Code ;
	}
	delete[] m_pStrBegin ;
}
//===================================================================
DWORD  FCLzw::LZW_GIF_Encode (BYTE * DibBuffer, BYTE * OutBuffer,
							  DWORD dwDibWidth, DWORD dwDibHeight,
							  WORD wColorBit)
{
	//	编码阶段不需要String Table，只需要m_CurrTableIndex来获知写位数
	m_pHash = new WORD [LZW_MAX_HASH_SIZE] ;
	if ((m_pHash == NULL) || (DibBuffer == NULL) || (OutBuffer == NULL))
		return 0 ;
	//	初始化设置-----------------------------------------+
	m_byMinCode = (wColorBit == 1) ? 2 : wColorBit ; // 1, 4, 8位色(最小码长度)，1位色为2
	m_LZW_CLEAR = 1 << m_byMinCode ;
	m_LZW_END = m_LZW_CLEAR + 1 ;
	m_pOrigin = m_pCurIn = DibBuffer ;
	m_pCurOut = OutBuffer ;
	m_byInBit = 8 ;
	m_byOutBit = 0 ; // 输出从0开始

	m_dwDibWidth = dwDibWidth ;		// DIB宽
	m_dwDibHeight = dwDibHeight ;	// DIB高
	m_dwCurrPixel = 0 ;
	m_dwCurrHeight = 0 ; // 从最顶行开始
	m_dwPitch = 4 * ((dwDibWidth * m_byMinCode + 31) / 32) ;
	//	初始化设置完成-------------------------------------+

	WORD		Old ;	// 保留字串
	BYTE		Pixel ;	// 当前读入字符
	this->Encode_InitStringTable () ;
	this->Encode_WriteIndex (m_LZW_CLEAR) ; // 首先写clear
	Old = this->Encode_GetNextPixel () ;
	// 编码
	while (m_dwCurrHeight < m_dwDibHeight)
	{
		Pixel = this->Encode_GetNextPixel () ;
		if (this->Encode_IsInTable (Old, Pixel))
			Old = m_pHash[(Old << 8) | Pixel] ; // 已在表中, 取出索引, Hash Table中存放的是String Table的Index
		else
		{
			//	不在表中, 把Old + Pixel添加到String Table中
			this->Encode_WriteIndex (Old) ;
			this->Encode_AddStringToTable (Old, Pixel) ;
			Old = Pixel ;
			if (m_CurrTableIndex == LZW_MAX_TABLE_SIZE) // 表填满
			{
				this->Encode_WriteIndex (Pixel) ;
				this->Encode_WriteIndex (m_LZW_CLEAR) ;
				this->Encode_InitStringTable () ;
				Old = this->Encode_GetNextPixel () ;
			}
		}
	}
	this->Encode_WriteIndex (Old) ;
	this->Encode_WriteIndex (m_LZW_END) ;
	delete[] m_pHash ;
	return (m_pCurOut - OutBuffer + 1) ;
}
//===================================================================
