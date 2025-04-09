#ifndef _BUSYBIN_UNORDERED_PAIR_SET_INDEXER_H_
#define _BUSYBIN_UNORDERED_PAIR_SET_INDEXER_H_

#include <array>
using std::array;
#include <cstdint>
#include "../../Util/math.h"

namespace busybin
{
  template <size_t N>
  class UnorderedPairSetIndexer
  {
    typedef array<uint8_t, 2> pair_t;

    array<pair_t, N *(N - 1) / 2> pairs;
    array<uint32_t, (N - 2) / 2> bases;

    // ✅ Overload without the reference
    void generatePairs(unsigned pairInd, pair_t &pair)
    {
      unsigned tmp = 0;
      generatePairs(pairInd, pair, tmp);
    }

    // ✅ Correct declaration (no default for reference)
    void generatePairs(unsigned pairInd, pair_t &pair, unsigned &pairsInd)
    {
      if (pairInd == 2)
      {
        this->pairs[pairsInd++] = {pair[0], pair[1]};
        return;
      }

      unsigned start = pairInd == 0 ? 0 : pair[pairInd - 1] + 1;

      for (unsigned i = start; i < N; ++i)
      {
        pair[pairInd] = i;
        this->generatePairs(pairInd + 1, pair, pairsInd);
      }
    }

  public:
    UnorderedPairSetIndexer()
    {
      pair_t pair;
      unsigned pairsInd = 0;
      this->generatePairs(0, pair, pairsInd);

      this->bases[(N - 2) / 2 - 1] = 1;

      for (int i = (N - 2) / 2 - 2; i >= 0; --i)
        this->bases[i] = this->bases[i + 1] * choose((N - 2) - 2 * i, 2);
    }

    uint32_t rank(const array<pair_t, N / 2> &set) const
    {
      uint32_t rank = 0;
      unsigned numRemaining = N * (N - 1) / 2;
      array<pair_t, N *(N - 1) / 2> remaining = this->pairs;

      for (unsigned n = 0; n < (N - 2) / 2; ++n)
      {
        unsigned remainingInd = 0;
        const pair_t &sPair = set[n];

        for (unsigned r = 0; r < numRemaining; ++r)
        {
          const pair_t &rPair = remaining[r];

          if (sPair == rPair)
          {
            rank += r * this->bases[n];
          }
          else if (
              sPair[0] != rPair[0] && sPair[0] != rPair[1] &&
              sPair[1] != rPair[0] && sPair[1] != rPair[1])
          {
            remaining[remainingInd++] = rPair;
          }
        }

        numRemaining = remainingInd;
      }

      return rank;
    }
  };
}

#endif
