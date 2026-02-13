//
// Created by Quinn on 13.2.2026.
//

#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "Cache.h"
#include "Memory.h"


// Compute analytic AMAT for an N-level cache
inline double computeAnalyticAMAT(const std::vector<Cache*>& levels, const Memory* mainMem)
{
    double amat = 0.0;
    double missChainProb = 1.0;

    for (const Cache* L : levels)
    {
        amat += missChainProb * L->getAccessTime();
        missChainProb *= (double)L->getMisses() / (double)(L->getHits() + L->getMisses());
    }

    amat += missChainProb * mainMem->getAccessTime();
    return amat;
}


// Print human-readable summary
inline void printCacheSummary(const std::vector<Cache*>& levels,
                              const Memory* mainMem,
                              double measuredAvg = -1.0)
{
    using std::cout;

    cout << "\n=========== CACHE SUMMARY ===========\n";

    for (size_t i = 0; i < levels.size(); ++i)
    {
        const Cache* C = levels[i];
        int hits = C->getHits();
        int misses = C->getMisses();
        int acc = hits + misses;

        cout << "L" << (i+1) << " Cache\n";
        cout << "  Hit time:       " << C->getAccessTime() << "\n";
        cout << "  Accesses:       " << acc << "\n";
        cout << "  Hits:           " << hits << "\n";
        cout << "  Misses:         " << misses << "\n";
        cout << std::fixed << std::setprecision(2);
        cout << "  Hit rate:       " << (acc ? (100.0 * hits / acc) : 0.0) << "%\n";
        cout << "  Miss rate:      " << (acc ? (100.0 * misses / acc) : 0.0) << "%\n\n";
    }

    cout << "Main Memory\n";
    cout << "  Access time:    " << mainMem->getAccessTime() << "\n";

    double amat = computeAnalyticAMAT(levels, mainMem);

    cout << "\nAnalytic AMAT:     " << amat << "\n";
    if (measuredAvg >= 0.0)
        cout << "Measured Average:  " << measuredAvg << "\n";

    cout << "=====================================\n";
}