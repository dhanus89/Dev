#ifndef TARGA_H
#define TARGA_H

///-------------------------------------------------------------------------------------------------
///<Author>Dhanus</Author>
///-------------------------------------------------------------------------------------------------

#include <vector>
#include <string>
#include <fstream>

/************************************************************* 
   Table 1 Targa Image Type Codes
   
   [Code]   [Description]
	0		No image data included
	1		Uncompressed color mapped image
	2		Uncompressed RGB image
	3		Uncompressed black-and-white image
	9		Compressed (RLE) color mapped image
	10		Compressed (RLE) RGB image
	11		Compressed black-and-white image
**************************************************************/
/**************************************************************
    Table 2 Targa Image Origin

	[First Pixel Position]   [Bit 5]  [Bit 4] [Hex Value]
	Bottom left				    0		0		0x00
	Bottom right				0		1		0x10
	Top left					1		0		0x20
	Top right					1		1		0x30
**************************************************************/


class TargaImg
{
public:
	///-------------------------------------------------------------------------------------------------
	/// <summary> TargaHeader Store information about the image file </summary>
	///-------------------------------------------------------------------------------------------------
	typedef struct TargaHeader
	{
		unsigned char idLength;// how much data to skip
		unsigned char colorMapType;
		unsigned char imgTypeCode;// type of image (see table 1)
		unsigned char colorMapSpec[5];
		unsigned short xOrigin, yOrigin;
		unsigned short width, height;// dimesion of the image in texels
		unsigned char bpp;
		unsigned char desc;// store imformation about the pixel data
		
	}TargaHeader;

	enum FILE_TYPE
	{
		TFT_NO_DATA = 0, TFT_INDEXED = 1, TFT_RGB = 2, TFT_GRAYSCALE = 3,
		TFT_RLE_INDEXED = 9, TFT_RLE_RGB = 10, TFT_RLE_GRAYSCALE = 11
	};

	enum ORIENTATION{BOTTOM_LEFT = 0x00, BOTTOM_RIGHT = 0x10, TOP_LEFT = 0x20, TOP_RIGHT = 0x30};

	TargaImg();
	~TargaImg();
	bool LoadImg(const std::string& _fileName);
	void Release(void);
	inline unsigned int GetWidth(void)const;
	inline unsigned int GetHeight(void)const;
	inline unsigned int GetBitsPerPixel()const;
	inline const std::vector<unsigned char>& GetImageData(void)const;


private:
	// Hidden Interface.
	TargaImg(const TargaImg& _lhs);
	TargaImg& operator=(const TargaImg& _lhs);


	//************* Helper Functions**********************
	bool LoadUnCompressedImg(std::istream& _fileIn);
	bool LoadCompressedImg(std::istream& _fileIn);
	bool IsImageTypeSupported(const TargaHeader& _header);
	void FlipVertically(void);
	bool IsUnCompressedImg(const TargaHeader& _header)const;
	bool IsCompressedImg(const TargaHeader& _header)const;


	TargaHeader m_imgHeader;
	std::vector<unsigned char>m_imgData;



};

unsigned int TargaImg::GetHeight()const
{
	return m_imgHeader.height;
}

unsigned int TargaImg::GetWidth()const
{
	return m_imgHeader.width;
}

const std::vector<unsigned char>& TargaImg::GetImageData(void)const
{
	return m_imgData;
}


#endif // TARGA_H
