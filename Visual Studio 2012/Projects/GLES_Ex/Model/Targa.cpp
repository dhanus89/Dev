#include "Targa.h"
#include <iostream>

TargaImg::TargaImg()
{
	memset(&m_imgHeader,0,sizeof(TargaHeader));
}

TargaImg::~TargaImg()
{
	Release();
}

void TargaImg::Release()
{
	memset(&m_imgHeader, 0, sizeof(m_imgHeader));
	m_imgData.clear();
}


void TargaImg::FlipVertically()
{
	//Allocate some space to store the flipped data
	std::vector<unsigned char> flippedData;
	flippedData.reserve(m_imgData.size());
	unsigned int bytePerPix(m_imgHeader.bpp / 8);
	//This is 3 for RGB, 4 for RGBA
	int step = bytePerPix;

	//Go backward through the rows of image data
	for (int row = m_imgHeader.height - 1; row >= 0; row--) {
		//Get a pointer to the start of the row
		unsigned char* rowData = &m_imgData[row * m_imgHeader.width * step];
		//Store this row of data one channel at a time
		for (unsigned int i = 0; i < m_imgHeader.width * step; ++i)  {
			flippedData.push_back(*rowData);
			rowData++;
		}
	}

	//Copy the flipped image data to the original array
	m_imgData.assign(flippedData.begin(), flippedData.end());
}

bool TargaImg::IsUnCompressedImg(const TargaHeader& header)const
{
	return (m_imgHeader.imgTypeCode  == TFT_RGB || 
		m_imgHeader.imgTypeCode  == TFT_GRAYSCALE);
}

bool TargaImg::IsCompressedImg(const TargaHeader& header)const
{
	return (m_imgHeader.imgTypeCode == TFT_RLE_RGB || 
		m_imgHeader.imgTypeCode == TFT_RLE_GRAYSCALE);
}


bool TargaImg::IsImageTypeSupported(const TargaHeader& header)
{
	//If this image is not one of the supported types, 
	//then return false (currently only support color images)
	if (((header.imgTypeCode != TFT_RGB) &&
		//(header.imageTypeCode != TFT_GRAYSCALE) &&
			(header.imgTypeCode != TFT_RLE_RGB)) ||
			//(header.imageTypeCode != TFT_RLE_GRAYSCALE)) ||
			(header.colorMapType != 0))
	{
		return false;
	}

	return true;
}

bool TargaImg::LoadImg(const std::string& _fileName)
{
	std::ifstream fIn(_fileName.c_str(), std::ios::binary);
	if(!fIn.good())return false;// validate filed opeed successfully
	// read the header 
	fIn.read(reinterpret_cast<char*>(&m_imgHeader), sizeof(TargaHeader));

	// validate the image type is supported
	if(!IsImageTypeSupported(m_imgHeader))
	{
		std::cerr << " Image type is not supported "<<std::endl;
		return false;
	}
	unsigned bytePerPix = m_imgHeader.bpp / 8;
	if(bytePerPix < 3) // minimum RGB = 3
	{
		std::cerr << "Color is not supported " << std::endl;
		return false;
	}

	// process the image data
	unsigned int imgSize(m_imgHeader.width * m_imgHeader.height * bytePerPix);
	m_imgData.resize(imgSize);
	// skip thee id
	if(m_imgHeader.idLength > 0)
		fIn.ignore(m_imgHeader.idLength);

	bool rslt(false);
	// Uncomporessed Image
	if(IsUnCompressedImg(m_imgHeader))
		rslt = LoadUnCompressedImg(fIn);
	else
	{
		rslt = LoadCompressedImg(fIn);
	}

	/// flip the image if necessary
	if((m_imgHeader.desc & TOP_LEFT) == ORIENTATION::TOP_LEFT)
	{
		FlipVertically();
	}
	return rslt;
}

bool TargaImg::LoadCompressedImg(std::istream& fileIn)
{
	unsigned pixCount(m_imgHeader.width * m_imgHeader.height);
	unsigned int currentPix(0), currentByte(0);
	unsigned int bytePerPixel(m_imgHeader.bpp /8);
	unsigned int pixelcount	= m_imgHeader.height * m_imgHeader.width;    // Number of pixels in the image
	unsigned int currentpixel	= 0;    // Current pixel being read
	unsigned int currentbyte	= 0;    // Current byte

	std::vector<unsigned char> colorBuffer(bytePerPixel);

	do {
		unsigned char chunkheader = 0;
		fileIn.read(reinterpret_cast<char*>(&chunkheader), sizeof(unsigned char));

		if(chunkheader < 128) 
		{
			chunkheader++;

			for(short counter = 0; counter < chunkheader; counter++) 
			{
				fileIn.read(reinterpret_cast<char*>(&colorBuffer[0]), bytePerPixel);

				m_imgData[currentbyte] = colorBuffer[2];
				m_imgData[currentbyte + 1] = colorBuffer[1];
				m_imgData[currentbyte + 2] = colorBuffer[0];

				if(bytePerPixel == 4)
				{
					m_imgData[currentbyte + 3] = colorBuffer[3];
				}

				currentbyte += bytePerPixel;
				currentpixel++;

				if(currentpixel > pixelcount) 
				{
					return false;
				}
			}
		} 
		else 
		{
			chunkheader -= 127;

			fileIn.read(reinterpret_cast<char*>(&colorBuffer[0]), bytePerPixel);

			for(short counter = 0; counter < chunkheader; counter++) 
			{
				m_imgData[currentbyte] = colorBuffer[2];
				m_imgData[currentbyte + 1] = colorBuffer[1];
				m_imgData[currentbyte + 2] = colorBuffer[0];

				if(bytePerPixel == 4) 
				{
					m_imgData[currentbyte + 3] = colorBuffer[3];
				}

				currentbyte += bytePerPixel;
				currentpixel++;

				if(currentpixel > pixelcount) 
				{
					return false;
				}
			}
		}
	} while(currentpixel < pixelcount);

	return true;
}

bool TargaImg::LoadUnCompressedImg(std::istream& _fileIn)
{
	unsigned int imgSize(m_imgData.size());
	_fileIn.read(reinterpret_cast<char*>(&m_imgData[0]), imgSize);
	unsigned int bytePerPix(m_imgHeader.bpp / 8);
	char tempSwap(0);
	for(unsigned int i(0); i < imgSize; i +=bytePerPix)
	{
		tempSwap = m_imgData[i];
		m_imgData[i] = m_imgData[i+2];
		m_imgData[i+2] = tempSwap;
	}
	return true;
}