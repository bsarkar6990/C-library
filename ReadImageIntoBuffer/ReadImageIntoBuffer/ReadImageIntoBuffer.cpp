//--------------------------------------------------------------------------------------
// File: bmpdump.cpp
//
// BMP file content examination utility
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------

#include <windows.h>

#include <stdio.h>
#include <memory>

//---------------------------------------------------------------------------------
struct handle_closer { void operator()(HANDLE h) { if (h) CloseHandle(h); } };

typedef std::unique_ptr<void, handle_closer> ScopedHandle;

inline HANDLE safe_handle(HANDLE h) { return (h == INVALID_HANDLE_VALUE) ? nullptr : h; }


//--------------------------------------------------------------------------------------
static_assert(sizeof(BITMAPFILEHEADER) == 14, "Mis-match size");
static_assert(sizeof(BITMAPCOREHEADER) == 12, "Mis-match size");

//--------------------------------------------------------------------------------------
static HRESULT LoadTextureDataFromFile(_In_z_ const wchar_t* fileName,
	std::unique_ptr<uint8_t[]>& bmpData
)
{
	// open the file
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
	ScopedHandle hFile(safe_handle(CreateFile2(fileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		OPEN_EXISTING,
		nullptr)));
#else
	ScopedHandle hFile(safe_handle(CreateFileW(fileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr)));
#endif
	if (!hFile)
		return HRESULT_FROM_WIN32(GetLastError());

	// Get the file size
	FILE_STANDARD_INFO fileInfo;
	if (!GetFileInformationByHandleEx(hFile.get(), FileStandardInfo, &fileInfo, sizeof(fileInfo)))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// File is too big for 32-bit allocation, so reject read
	if (fileInfo.EndOfFile.HighPart > 0)
	{
		return E_FAIL;
	}

	// Need at least enough data to fill the basic header
	if (fileInfo.EndOfFile.LowPart < (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPCOREHEADER)))
	{
		return E_FAIL;
	}

	// create enough space for the file data
	bmpData.reset(new uint8_t[fileInfo.EndOfFile.LowPart]);
	if (!bmpData)
	{
		return E_OUTOFMEMORY;
	}

	// read the data in
	DWORD BytesRead = 0;
	if (!ReadFile(hFile.get(), bmpData.get(), fileInfo.EndOfFile.LowPart, &BytesRead, nullptr))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (BytesRead < fileInfo.EndOfFile.LowPart)
	{
		return E_FAIL;
	}

	auto filehdr = reinterpret_cast<const BITMAPFILEHEADER*>(bmpData.get());

	// Valid BMP files always start with 'BM' at the top
	if (filehdr->bfType != 0x4D42)
	{
		return E_FAIL;
	}

	// Check we have enough data for the discovered header
	auto header = reinterpret_cast<const BITMAPCOREHEADER*>(bmpData.get() + sizeof(BITMAPFILEHEADER));

	if (BytesRead < (sizeof(BITMAPFILEHEADER) + header->bcSize))
	{
		return E_FAIL;
	}

	return S_OK;
}


void OutputHeader(const uint8_t* bmpData, const wchar_t* fname)
{
	auto coreHeader = reinterpret_cast<const BITMAPCOREHEADER*>(bmpData + sizeof(BITMAPFILEHEADER));

	if (coreHeader->bcSize >= sizeof(BITMAPV5HEADER))
	{
		wprintf(L"BMP %ls\n\tV5 header (%u bytes)\n", fname, coreHeader->bcSize);

		auto header = reinterpret_cast<const BITMAPV5HEADER*>(bmpData + sizeof(BITMAPFILEHEADER));

		wprintf(L"%d x %d\n", header->bV5Width, header->bV5Height);
		wprintf(L"%u planes\n", header->bV5Planes);
		wprintf(L"%u bits\n", header->bV5BitCount);

		switch (header->bV5Compression)
		{
		case BI_RGB:        wprintf(L"BI_RGB\n"); break;
		case BI_RLE8:       wprintf(L"BI_RLE8\n"); break;
		case BI_RLE4:       wprintf(L"BI_RLE4\n"); break;
		case BI_BITFIELDS:  wprintf(L"BI_BITFIELDS\n"); break;
		case BI_JPEG:       wprintf(L"BI_JPEG\n"); break;
		case BI_PNG:        wprintf(L"BI_PNG\n"); break;
		default:
			wprintf(L"%u compression type\n", header->bV5Compression);
			break;
		}

		wprintf(L"%u image size\n", header->bV5SizeImage);
		wprintf(L"%d x %d pels per meter\n", header->bV5XPelsPerMeter, header->bV5YPelsPerMeter);
		wprintf(L"%u colors used\n", header->bV5ClrUsed);
		wprintf(L"%u colors important\n", header->bV5ClrImportant);

		if (header->bV5Compression == BI_BITFIELDS)
		{
			wprintf(L"R: %08X, G: %08X, B: %08X, A: %08X\n", header->bV5RedMask, header->bV5GreenMask, header->bV5BlueMask, header->bV5AlphaMask);
		}

		switch (header->bV5CSType)
		{
		case LCS_CALIBRATED_RGB:        wprintf(L"LCS_CALIBRATED_RGB\n"); break;
		case LCS_sRGB:                  wprintf(L"LCS_sRGB\n"); break;
		case LCS_WINDOWS_COLOR_SPACE:   wprintf(L"LCS_WINDOWS_COLOR_SPACE\n"); break;
		case PROFILE_LINKED:            wprintf(L"PROFILE_LINKED\n"); break;
		case PROFILE_EMBEDDED:          wprintf(L"PROFILE_EMBEDDED\n"); break;
		default:
			wprintf(L"%u color space type\n", header->bV5CSType);
			break;
		}

		switch (header->bV5Intent)
		{
		case LCS_GM_ABS_COLORIMETRIC:   wprintf(L"LCS_GM_ABS_COLORIMETRIC\n"); break;
		case LCS_GM_BUSINESS:           wprintf(L"LCS_GM_BUSINESS\n"); break;
		case LCS_GM_GRAPHICS:           wprintf(L"LCS_GM_GRAPHICS\n"); break;
		case LCS_GM_IMAGES:             wprintf(L"LCS_GM_IMAGES\n"); break;
		default:
			wprintf(L"%u color space type\n", header->bV5Intent);
			break;
		}
	}
	else if (coreHeader->bcSize >= sizeof(BITMAPV4HEADER))
	{
		wprintf(L"BMP %ls\n\tV4 header (%u bytes)\n", fname, coreHeader->bcSize);
		auto header = reinterpret_cast<const BITMAPV4HEADER*>(bmpData + sizeof(BITMAPFILEHEADER));

		wprintf(L"%d x %d\n", header->bV4Width, header->bV4Height);
		wprintf(L"%u planes\n", header->bV4Planes);
		wprintf(L"%u bits\n", header->bV4BitCount);

		switch (header->bV4V4Compression)
		{
		case BI_RGB:        wprintf(L"BI_RGB\n"); break;
		case BI_RLE8:       wprintf(L"BI_RLE8\n"); break;
		case BI_RLE4:       wprintf(L"BI_RLE4\n"); break;
		case BI_BITFIELDS:  wprintf(L"BI_BITFIELDS\n"); break;
		case BI_JPEG:       wprintf(L"BI_JPEG\n"); break;
		case BI_PNG:        wprintf(L"BI_PNG\n"); break;
		default:
			wprintf(L"%u compression type\n", header->bV4V4Compression);
			break;
		}

		wprintf(L"%u image size\n", header->bV4SizeImage);
		wprintf(L"%d x %d pels per meter\n", header->bV4XPelsPerMeter, header->bV4YPelsPerMeter);
		wprintf(L"%u colors used\n", header->bV4ClrUsed);
		wprintf(L"%u colors important\n", header->bV4ClrImportant);

		if (header->bV4V4Compression == BI_BITFIELDS)
		{
			wprintf(L"R: %08X, G: %08X, B: %08X, A: %08X\n", header->bV4RedMask, header->bV4GreenMask, header->bV4BlueMask, header->bV4AlphaMask);
		}

		switch (header->bV4CSType)
		{
		case LCS_CALIBRATED_RGB:    wprintf(L"LCS_CALIBRATED_RGB\n"); break;
		default:
			wprintf(L"%u color space type\n", header->bV4CSType);
			break;
		}
	}
	else if (coreHeader->bcSize >= sizeof(BITMAPINFOHEADER))
	{
		wprintf(L"BMP %ls\n\tINFO header (%u bytes)\n", fname, coreHeader->bcSize);

		auto header = reinterpret_cast<const BITMAPINFOHEADER*>(bmpData + sizeof(BITMAPFILEHEADER));

		wprintf(L"%d x %d\n", header->biWidth, header->biHeight);
		wprintf(L"%u planes\n", header->biPlanes);
		wprintf(L"%u bits\n", header->biBitCount);

		switch (header->biCompression)
		{
		case BI_RGB:        wprintf(L"BI_RGB\n"); break;
		case BI_RLE8:       wprintf(L"BI_RLE8\n"); break;
		case BI_RLE4:       wprintf(L"BI_RLE4\n"); break;
		case BI_BITFIELDS:  wprintf(L"BI_BITFIELDS\n"); break;
		case BI_JPEG:       wprintf(L"BI_JPEG\n"); break;
		case BI_PNG:        wprintf(L"BI_PNG\n"); break;
		case 0x31545844:    wprintf(L"DXT1 (Extended BMP)\n"); break;
		case 0x33545844:    wprintf(L"DXT3 (Extended BMP)\n"); break;
		case 0x35545844:    wprintf(L"DXT5 (Extended BMP)\n"); break;
		default:
			wprintf(L"%u compression type\n", header->biCompression);
			break;
		}

		wprintf(L"%u image size\n", header->biSizeImage);
		wprintf(L"%d x %d pels per meter\n", header->biXPelsPerMeter, header->biYPelsPerMeter);
		wprintf(L"%u colors used\n", header->biClrUsed);
		wprintf(L"%u colors important\n", header->biClrImportant);
	}
	else
	{
		wprintf(L"BMP %ls\n\tCORE header (%u bytes)\n", fname, coreHeader->bcSize);

		wprintf(L"%u x %u\n", coreHeader->bcWidth, coreHeader->bcHeight);
		wprintf(L"%u planes\n", coreHeader->bcPlanes);
		wprintf(L"%u bits\n", coreHeader->bcBitCount);
	}

}


int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
	UNREFERENCED_PARAMETER(envp);
	if (argc < 2 || argc > 2)
	{
		printf("Usage: bmpdump <filename.bmp>\n");
		return 0;
	}

	std::unique_ptr<uint8_t[]> bmpData;
	HRESULT hr = LoadTextureDataFromFile(argv[1], bmpData);
	if (FAILED(hr))
	{
		wprintf(L"ERROR: failed to load %ls\n", argv[1]);
		return -1;
	}

	OutputHeader(bmpData.get(), argv[1]);

	return 0;
}
