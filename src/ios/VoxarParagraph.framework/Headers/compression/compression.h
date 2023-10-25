#pragma once

#ifndef __GUARD_COMPRESSION_H_
#define __GUARD_COMPRESSION_H_
#ifdef W_COMPRESSION

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include "zlib.h"

//#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
//#  include <fcntl.h>
//#  include <io.h>
//#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
//#else
//#  define SET_BINARY_MODE(file)
//#endif
#define windowBits 15
#define GZIP_ENCODING 16
#define CHUNK 16384

class BufferedFile;

class Compressor {



	/* Compress from file source to file dest until EOF on source.
	def() returns Z_OK on success, Z_MEM_ERROR if memory could not be
	allocated for processing, Z_STREAM_ERROR if an invalid compression
	level is supplied, Z_VERSION_ERROR if the version of zlib.h and the
	version of the library linked do not match, or Z_ERRNO if there is
	an error reading or writing the files. */
	static int def(BufferedFile &source, BufferedFile &dest, int level)
	{
		uLongf outsize = source.getAvailableBytes();
		char *outbuff = new char[source.getAvailableBytes()];
		int ret = Z_OK;
		if ((ret = compress((Bytef*)outbuff, &outsize, (const Bytef*)source.getBufferAddress(), source.getAvailableBytes())) != Z_OK) {
			delete[] outbuff;
			return ret;
		}
		size_t si = dest.write(outbuff, outsize);
		if (si != outsize) {
			fputs("compressed size is different from sent to file.",stderr);
			delete[] outbuff;
			return Z_ERRNO;
		}
		//printf("\n outsize %u\n", outsize);

		// writing last four bytes for saving original size
		unsigned int original_len = source.getAvailableBytes();
		//printf("\noriginal length %u\n", original_len);
		dest.write((char*)&original_len, 4);

		//unsigned int original_len2 = *((unsigned int*)(dest.getBufferAddress() + dest.getAvailableBytes() - 4));
		//printf("\noriginal len2 %u\n", original_len2);

		delete outbuff;
		return Z_OK;

	}

	/* Decompress from file source to file dest until stream ends or EOF.
	inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
	allocated for processing, Z_DATA_ERROR if the deflate data is
	invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
	the version of the library linked do not match, or Z_ERRNO if there
	is an error reading or writing the files. */
	static int inf(BufferedFile &source, BufferedFile &dest)
	{
		unsigned int available = source.getAvailableBytes();
		unsigned int original_len = *((unsigned int*)(source.getBufferAddress()+ available-4));
		//printf("\noriginal len %u\n", original_len);
		//printf("size of unsigned int %u\n", sizeof(unsigned int));
		uLongf outsize = original_len;
		char *outbuff = new char[outsize];
		int ret = Z_OK;
		// the minus four bytes is to ignore the original file size
		const Bytef *address = (const Bytef*)source.getBufferAddress();
		if ((ret = uncompress((Bytef*)outbuff, &outsize, address, available - 4)) != Z_OK) {
			delete[] outbuff;
			return ret;
		}
		size_t si = dest.write(outbuff, outsize);
		//printf("\n%u %u %u available %u dest %u\n", outsize, original_len, si, available, dest.getAvailableBytes());
		if (si != original_len) {
			fputs("\nuncompressed size is different from original size.",stderr);
			
			delete[] outbuff;
			return Z_ERRNO;
		}
		delete[] outbuff;

		return Z_OK;
	}

	/* report a zlib or i/o error */
	static void zerr(int ret)
	{
		fputs("zpipe: ", stderr);
		switch (ret) {
		case Z_ERRNO:
			fputs("error writing to stringstream\n", stderr);
			break;
		case Z_STREAM_ERROR:
			fputs("invalid compression level\n", stderr);
			break;
		case Z_DATA_ERROR:
			fputs("invalid or incomplete deflate data\n", stderr);
			break;
		case Z_MEM_ERROR:
			fputs("out of memory\n", stderr);
			break;
		case Z_VERSION_ERROR:
			fputs("zlib version mismatch!\n", stderr);
		}
	}

public:

	static int Compress(BufferedFile &in, BufferedFile &out) {
		int ret;
		ret = def(in, out, Z_BEST_COMPRESSION);
		if (ret != Z_OK)
			zerr(ret);
        else fprintf(stderr,"comprimiu com sucesso!\n");
		return ret;
	}

	static int Expand(BufferedFile &in, BufferedFile &out) {
		int ret = Z_OK;
		unsigned char headerchar = *((unsigned char*)(in.getBufferAddress()));
		if (headerchar == 0x78) {
			ret = inf(in, out);
			if (ret != Z_OK)
				zerr(ret);
			else fprintf(stderr, "descomprimiu com sucesso!\n");
		}
		else ret = Z_VERSION_ERROR;
		return ret;
	}
};

#endif

#endif // __GUARD_COMPRESSION_H_
