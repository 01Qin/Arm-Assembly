#pragma once
#include <regex>
#include <vector>
#include "Memory.h"
#include "CacheSet.h"

class Cache :
	public Memory
{
public:
	Cache(int accessTime, int size, int blockSize, int associativity, Memory *lowerLevel);
	~Cache(void);

	int read(uint64_t address) override;
	int write(uint64_t address) override;
	int getMisses(void);
	int getHits(void);

	int getAccess(void) const { return hits + misses; }

	double getMissRate (void) const {
		int a = getAccess();
		return a ? static_cast<double> (misses) / static_cast<double> (a) : 0.0;
	}

	double getHitRate (void) const {
		int a = getAccess();
		return a ? static_cast<double>(hits) / static_cast<double>(a) : 0.0;
	}

	int getBlockSize() const { return blockSize; }
	int getAssociativity() const { return associativity; }
	size_t getNumSets() const { return sets.size();}
	Memory* getLower() const { return lower; }
private:
	Memory *lower;
	std::vector<CacheSet *> sets;
	int blockSize{};
	int associativity{};
	int hits{};
	int misses{};
};

