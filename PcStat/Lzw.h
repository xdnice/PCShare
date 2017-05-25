//////////////////////////////////////////////////////////////////
//																//
//		用途 : LZW 压缩算法										//
//		创建 : [Foolish] / 2001-9-17							//
//		更新 : 2002-6-7											//
//		主页 :													//
//		邮箱 : crazybit@263.net									//
//									(c) 1999 - 2002 =USTC= 付黎	//
//////////////////////////////////////////////////////////////////
#ifndef		__FOO_LZW_COMPRESS_H__
#define		__FOO_LZW_COMPRESS_H__
#include <windows.h>
#pragma once

//===================================================================
//	定义
//===================================================================
//	解码程序用到String Table的最大长度
#define		LZW_MAX_TABLE_SIZE		4096

//	编码程序只用到Hash表, 不需要String Table, 因为它不需要知道String Table中的内容, 
//	只需要知道Old + Pixel字串是否在表中和表中的index
//	Hash表设计为  :  (Old << 8) | Pixel 其中存放的是String Table的Index
#define		LZW_MAX_HASH_SIZE		0x1000FF // (4096 << 8) + 0xFF

//	解码程序用到String Table - string结构
//	每个string可以形成一棵二叉树, 此二叉树仅有一个右节点
//	因为wPrefix总是指向String Table中的另一位置, 而wSuffix指向0 ~ (clear-1)
typedef struct tagLZW_STRING
{
	WORD	wPrefix ;	// 为 Old
	WORD	wSuffix ;	// 为 GetFirstChar (Old) 或 GetFirstChar (Code)
} LZW_STRING, * PLZW_STRING ;

//===================================================================
//	LZW - 压缩算法
//===================================================================
class FCLzw
{
public :
	 FCLzw () ;
	~FCLzw () ;

	/********************************************************************/
	/*	功  能 ：通用LZW编码											*/
	/*	说  明 ：OutBuffer必须预先置0									*/
	/*			 输出的OutBuffer按 8 + ...data... 格式存储				*/
	/********************************************************************/
	DWORD	LZW_Encode (BYTE * InBuffer, DWORD dwLength,
						BYTE * OutBuffer) ;

	/********************************************************************/
	/*	功  能 ：通用LZW解码											*/
	/*	说  明 ：InBuffer必须按 8 + ...data... 格式存储					*/
	/********************************************************************/
	void	LZW_Decode (BYTE * InBuffer, BYTE * OutBuffer) ;

	/********************************************************************/
	/*	功  能 ：编码DIB为GIF											*/
	/*	参  数 ：把DIB左上角的指针传给DibBuffer							*/
	/*	返回值 ：写入OutBuffer中的字节数								*/
	/*	说  明 ：OutBuffer必须预先置0									*/
	/*			 暂时只支持4, 8位色位图编码，不支持1位色位图			*/
	/********************************************************************/
	DWORD	LZW_GIF_Encode (BYTE * DibBuffer, BYTE * OutBuffer,
							DWORD dwDibWidth, DWORD dwDibHeight,
							WORD wColorBit) ;

	/********************************************************************/
	/*	功  能 ：解码GIF到DIB											*/
	/*	参  数 ：把DIB左上角的指针传给DibBuffer							*/
	/*	说  明 ：所有位色GIF一律解码为8位色DIB, DibBuffer为8位色		*/
	/*			 InBuffer必须按 Min_Code_Length + ...data... 格式存储	*/
	/*				所以GIF数据(InBuffer)先要解包						*/
	/********************************************************************/
	void	LZW_GIF_Decode (BYTE * InBuffer, BYTE * DibBuffer,
							DWORD dwDibWidth, DWORD dwDibHeight,
							bool bInterlace) ;

private :
	LZW_STRING	* m_pStrBegin ;	// String Table
	WORD		* m_pHash ;		// Hash Table (16bit存放m_pStrBegin的Index)
	WORD		m_LZW_CLEAR, m_LZW_END ; // clear和end标志

	//	交错存储用---------------------------------------------------+
	BYTE		m_byInterval ;	// 用在交错存储的gif中, 作为m_Interval的索引, 0xFF为非交错存储
	BYTE		m_Interval[7] ; // 交错排列 : 8 8 4 2
	//	交错存储用---------------------------------------------------+

	BYTE		* m_pOrigin ;
	BYTE		* m_pCurIn ;
	BYTE		* m_pCurOut ;
	BYTE		m_byInBit ;		// 输入缓冲Bit位置
	BYTE		m_byOutBit ;	// 输出缓冲Bit位置

	BYTE		m_byMinCode ;		// 最小码长度 (即原始颜色位数)
	BYTE		m_byCurrBits ;		// 现阶段码长
	WORD		m_CurrTableIndex ;	// 当前的String Table Index	
	BYTE		m_Padding[2] ;

	DWORD		m_dwDibHeight ;  // DIB的高度
	DWORD		m_dwDibWidth ;   // DIB的宽度
	DWORD		m_dwCurrPixel ;	 // 当前行写入的像素个数
	DWORD		m_dwCurrHeight ; // 当前的高
	DWORD		m_dwPitch ;		 // DIB每行的字节数

private :
	//	解码
	void	Decode_InitStringTable () ;
	WORD	Decode_GetNextCode () ; // 最长12位
	bool	Decode_IsInTable (WORD Code) ;
	void	Decode_AddStringToTable (WORD wPrefix, WORD wSuffix) ;
	BYTE	Decode_GetFirstChar (WORD Code) ;
	void	Decode_WriteString_to8 (WORD Code) ; // 解码到目标8位色位图
	void	Decode_SwitchToFollowLine () ; // 使m_pCurOut切换到下一行
	//	编码
	void	Encode_InitStringTable () ;
	BYTE	Encode_GetNextPixel () ;
	bool	Encode_IsInTable (WORD Old, WORD Pixel) ; // Old和Pixel都指向在m_pStrBegin中的index。
	void	Encode_AddStringToTable (WORD Old, WORD Pixel) ;
	void	Encode_WriteIndex (DWORD wIndex) ; // 压缩时写String Index
} ;

//===================================================================
//	Implement
//===================================================================
inline  FCLzw::FCLzw () {
	m_Interval[0] = m_Interval[1] = 8 ;
	m_Interval[2] = 4 ; m_Interval[3] = 2 ; // 交错行数
}
inline  FCLzw::~FCLzw () {
}
inline void  FCLzw::Decode_InitStringTable () {
	memset (m_pStrBegin, 0xFF, LZW_MAX_TABLE_SIZE * sizeof(LZW_STRING)) ;
	for (WORD i = 0 ; i < m_LZW_CLEAR ; i++) // 初始化String Table
		m_pStrBegin[i].wSuffix = i ;
	m_CurrTableIndex = m_LZW_END + 1 ;
	m_byCurrBits = m_byMinCode + 1 ;
}
inline void  FCLzw::Decode_SwitchToFollowLine () {
	m_dwCurrPixel = 0 ; // 到行开头
	if (m_byInterval == 0xFF) // 非交错存储, 直接到下一行
		m_pCurOut -= m_dwPitch ;
	else
	{
		m_dwCurrHeight += m_Interval[m_byInterval] ; // 交错存储的gif, 计算下一行
		if (m_dwCurrHeight >= m_dwDibHeight)
			if (++m_byInterval < 4)
				m_dwCurrHeight = m_Interval[m_byInterval]/2 ;
			else
				return ;
		m_pCurOut = m_pOrigin - m_dwCurrHeight * m_dwPitch ;
	}
}
inline WORD  FCLzw::Decode_GetNextCode () {
	// 与Encode_WriteIndex ()是相对应的, 最长为12位(最多跨越2-BYTE)
	register DWORD			dwRet = 0 ;
	register unsigned int	uiAdd = m_byInBit + m_byCurrBits ;

	if (uiAdd <= 8) // 在当前BYTE内
		dwRet |= * m_pCurIn ;
	else
		if (uiAdd <= 16) // 跨1-BYTE
			dwRet |= * (WORD *) m_pCurIn ;
		else // 跨2-BYTE
		{
			dwRet |= * (m_pCurIn + 2) ;
			dwRet <<= 16 ;
			dwRet |= * (WORD *) m_pCurIn ;
		}
	m_pCurIn += uiAdd / 8 ;
	m_byInBit = uiAdd % 8 ;
	dwRet <<= 32 - uiAdd ;
	dwRet >>= 32 - m_byCurrBits ; // 左右清零
	return (WORD)dwRet ;
}
inline bool  FCLzw::Decode_IsInTable (WORD Code) {
	return (Code < m_CurrTableIndex) ;
}
inline BYTE  FCLzw::Decode_GetFirstChar (WORD Code) {
	while (m_pStrBegin[Code].wPrefix != 0xFFFF)
		Code = m_pStrBegin[Code].wPrefix ;
	return (BYTE) m_pStrBegin[Code].wSuffix ;
}
inline void  FCLzw::Decode_AddStringToTable (WORD wPrefix, WORD wSuffix) {
	m_pStrBegin[m_CurrTableIndex  ].wPrefix = wPrefix ;
	m_pStrBegin[m_CurrTableIndex++].wSuffix = wSuffix ;
	if ((m_CurrTableIndex == 0x008) || (m_CurrTableIndex == 0x010) ||
		(m_CurrTableIndex == 0x020) || (m_CurrTableIndex == 0x040) ||
		(m_CurrTableIndex == 0x080) || (m_CurrTableIndex == 0x100) ||
		(m_CurrTableIndex == 0x200) || (m_CurrTableIndex == 0x400) ||
		(m_CurrTableIndex == 0x800))
		m_byCurrBits++ ;
}
inline void  FCLzw::LZW_Decode (BYTE * InBuffer, BYTE * OutBuffer) {
	//	给dwDibWidth传入0则不换行
	this->LZW_GIF_Decode (InBuffer, OutBuffer, 0, 0, false) ;
}
//===================================================================
//	Encode
//===================================================================
inline void  FCLzw::Encode_InitStringTable () {
	m_CurrTableIndex = m_LZW_END + 1 ;
	m_byCurrBits = m_byMinCode + 1 ;
	memset (m_pHash, 0x00, LZW_MAX_HASH_SIZE * sizeof(WORD)) ; // Hash Table置位0
}
inline BYTE  FCLzw::Encode_GetNextPixel () {
	//	目前只支持1, 4, 8位色, 所以不会跨BYTE
	register BYTE		byRet ;
	switch (m_byMinCode)
	{
		case 8 : byRet = m_pCurIn[m_dwCurrPixel] ; break ;
		case 4 : byRet = (m_dwCurrPixel % 2 == 0)
						 ? m_pCurIn[m_dwCurrPixel / 2] >> 4
						 : m_pCurIn[m_dwCurrPixel / 2] & 0x0F ; break ;
		case 1 : byRet = 0x01 & (m_pCurIn[m_dwCurrPixel / 8] >> (7 - (m_dwCurrPixel & 7))) ; break ;
	}
	if (++m_dwCurrPixel == m_dwDibWidth) // 行结束
	{
		m_dwCurrPixel = 0 ;
		m_dwCurrHeight++ ; // DIB下一行
		m_pCurIn = m_pOrigin - m_dwCurrHeight * m_dwPitch ;
	}
	return byRet ;
}
inline bool  FCLzw::Encode_IsInTable (WORD Old, WORD Pixel) {
	return (m_pHash[(Old << 8) | Pixel] != 0) ;
}
inline void  FCLzw::Encode_AddStringToTable (WORD Old, WORD Pixel) {
	m_pHash[(Old << 8) | Pixel] = m_CurrTableIndex++ ;
	if ((m_CurrTableIndex == 0x009) || (m_CurrTableIndex == 0x011) ||
		(m_CurrTableIndex == 0x021) || (m_CurrTableIndex == 0x041) ||
		(m_CurrTableIndex == 0x081) || (m_CurrTableIndex == 0x101) ||
		(m_CurrTableIndex == 0x201) || (m_CurrTableIndex == 0x401) ||
		(m_CurrTableIndex == 0x801))
		m_byCurrBits++ ;
}
inline void  FCLzw::Encode_WriteIndex (DWORD Index) {
	// 压缩时写String Index, 最长为12位(最多跨越2-BYTE)
	// 与Decode_GetNextCode ()是相对应的
	register unsigned int	uiAdd = m_byOutBit + m_byCurrBits ;

	// 与解码不一样, 压缩时会预留一些内存, 可以用DWORD
	* (DWORD *) m_pCurOut |= (Index << m_byOutBit) ;
	m_byOutBit = uiAdd % 8 ;
	m_pCurOut += uiAdd / 8 ;
}
inline DWORD  FCLzw::LZW_Encode (BYTE * InBuffer, DWORD dwLength, BYTE * OutBuffer) {
	//	给dwDibWidth传入0则不换行
	*OutBuffer++ = 8 ;
	return 1 + this->LZW_GIF_Encode (InBuffer, OutBuffer, dwLength, 1, 8) ;
}

#endif