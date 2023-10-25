#ifndef __GUARD_THE_HASH_TABLE_H__
#define __GUARD_THE_HASH_TABLE_H__

#include <chrono>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <iostream>
#include <numeric>
#include <assert.h>

#ifdef __USEVOXARPARAGRAPH__
#include "voxarparagraph/geometry/point2.h"
#else
#include "geometry/point2.h"
#endif

#define W_COMPRESSION
#define W_POINTS


#ifdef W_COMPRESSION
class BufferedFile{
	size_t mBufferLength = 0, mBufferReadPos = 0, mBufferWritePos = 0;
	char *mBuff = NULL;
public:
	BufferedFile() {
		mBufferLength = 4;
		mBuff = (char*)malloc(mBufferLength);
		if (!mBuff) {
			mBufferLength = 0;
			assert(mBuff);
		}
	};
	~BufferedFile() {
		free(mBuff);
	};
	size_t write(char* dBuff, size_t dSize) {
		size_t r = 0;
		if (mBufferWritePos + dSize >= mBufferLength) {
			mBufferLength = (mBufferLength + dSize) << 1;
			char *tBuff = (char*)realloc(mBuff, mBufferLength);
			assert(tBuff);
			if (tBuff == NULL) return -1;
			mBuff = tBuff;
		}
		memcpy(mBuff + mBufferWritePos, dBuff, dSize);
		mBufferWritePos += dSize;
		r = dSize;
		return r;
	}
	size_t read(char* dBuff, size_t dSize) {
		size_t r = 0;
		if (mBufferReadPos == mBufferWritePos) {
			r = 0;
		} else if (mBufferReadPos + dSize > mBufferWritePos) {
			memcpy(dBuff, mBuff + mBufferReadPos, std::min(dSize,mBufferWritePos-mBufferReadPos));
			r = mBufferWritePos - mBufferReadPos;
			mBufferReadPos += r;
		}
		else {
			memcpy(dBuff, mBuff + mBufferReadPos, dSize);
			mBufferReadPos += dSize;
			r = dSize;
		}
		return r;
	}
	size_t getAvailableBytes() {
		return mBufferWritePos - mBufferReadPos;
	}
	char* getBufferAddress() {
		return mBuff;
	}
	void resetRead() { mBufferReadPos = 0; };
};

typedef BufferedFile outStreamType;
typedef BufferedFile inStreamType;

bool readFileToBuf(std::ifstream &f, BufferedFile &b);

bool writeBufToFile(BufferedFile &b, std::ofstream &f);


template<class Tipo>
bool write(outStreamType &ofs, Tipo value) {
	return ofs.write((char*)&value, sizeof(Tipo)) > 0;
}

template<class Tipo>
bool read(inStreamType &ifs, Tipo &value) {
	bool r = ifs.read((char*)&value, sizeof(Tipo)) >= sizeof(Tipo);
	assert(r);
	return r;//ifs.good();
}
#else

typedef std::ostream outStreamType;
typedef std::istream inStreamType;

#endif

template<class Tipo>
bool write(std::ostream &ofs, Tipo value) {
	ofs.write((char*)&value, sizeof(Tipo));
	return ofs.good();
}

template<class Tipo>
bool read(std::istream &ifs, Tipo &value) {
	ifs.read((char*)&value, sizeof(Tipo));
	bool r = ifs.gcount() >= sizeof(Tipo);
	assert(r);
	return r;//ifs.good();
}

typedef ushort document_id_type;

class HashTable {
public:
	// Accessor functions
	virtual unsigned int hash_size() const { return 0; };
	virtual unsigned int num_pages() const { return 0; };
	virtual unsigned int page() const { return 0; };
	virtual const std::string& page_filename() const { return "hash - table - 0 - page - "; };

	virtual unsigned int page_number(unsigned int key) const { return -1; };

	virtual void clear() {};

	virtual bool insert(unsigned int key, const std::pair<document_id_type, Point2>& value) { return false; };

	virtual void get_entries(unsigned int key, std::list<std::pair<document_id_type, Point2> >& dst) {};

	virtual bool serialize(outStreamType& os) { return false; };
	virtual bool serialize(const std::string& filename) { return false; };

	virtual bool deserialize(inStreamType& is, bool adjust_pages = true) { return false; };
	virtual bool deserialize(const std::string& filename, bool adjust_pages = true) { return false; };

};

class HashWikiFile {
private:
	FILE *outFile;
	static HashWikiFile& getInstance() {
		static HashWikiFile instance;
		return instance;
	}
public:
	static FILE* getOutFile() {
		return getInstance().outFile;
	}
	static bool setFile(std::string fileName) {
#ifdef _WIN32
		fopen_s(&(getInstance().outFile), fileName.c_str(), "w");
#else
		getInstance().outFile = fopen(fileName.c_str(),"w");
#endif
		return getInstance().outFile != 0;
	}

	static bool checkOut() {
		if (getInstance().outFile) return true;
		else {
#ifdef _WIN32
			fopen_s(&(getInstance().outFile), "statistics.csv", "w");
#else
			getInstance().outFile = fopen("statistics.csv", "w");
#endif
			return getInstance().outFile != 0;
		}
	}
};

typedef std::vector < std::pair<unsigned int, unsigned int> > SizesType;

namespace HashWiki {
	static void doMetrics(std::vector<unsigned int> &v, double &sum, double &mean, double &stdev) {
		assert(v.size() > 0);
		sum = std::accumulate(v.begin(), v.end(), 0.0);
		mean = sum / v.size();

		static double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
		stdev = std::sqrt(sq_sum / v.size() - mean * mean);
	}

	static void doExtraction(SizesType &sizes, std::vector<unsigned int> &v) {
		v.clear();
		for (auto &e : sizes) {
			v.push_back(e.first);
		}
	}
	

	static void printMetrics(SizesType &sizes) {
		if (sizes.size() > 0) {
			double sum, mean, std_deviation;
			std::vector<unsigned int> v;
			doExtraction(sizes, v);
			doMetrics(v, sum, mean, std_deviation);
			fprintf(HashWikiFile::getOutFile(), "Sum;Mean;StdDev\n");
			fprintf(HashWikiFile::getOutFile(), "%lf;%lf;%lf\n", sum, mean, std_deviation);
		}
		else fprintf(HashWikiFile::getOutFile(), "HashWiki::printMetrics: No data available.\n");
	}
};

#endif
