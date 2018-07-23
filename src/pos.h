// Copyright (c) 2015-2018 The Blackcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/* 
 * Stake cache by Qtum
 * Copyright (c) 2016-2018 The Qtum developers
 */

#ifndef BLACKCOIN_POS_H
#define BLACKCOIN_POS_H

#include "txdb.h"
#include "arith_uint256.h"
#include "consensus/validation.h"
#include "validation.h"
#include "hash.h"
#include "timedata.h"
#include "chainparams.h"
#include "script/sign.h"
#include <stdint.h>

using namespace std;

/** Compute the hash modifier for proof-of-stake */
uint256 ComputeStakeModifier(const CBlockIndex* pindexPrev, const uint256& kernel);

struct CStakeCache{
    CStakeCache(uint32_t blockFromTime_, Amount amount_) : blockFromTime(blockFromTime_), amount(amount_){
    }
    uint32_t blockFromTime;
    Amount amount;
};

// Check whether the coinstake timestamp meets protocol
bool CheckCoinStakeTimestamp(int64_t nTimeBlock, int64_t nTimeTx);
bool CheckStakeBlockTimestamp(int64_t nTimeBlock);
bool CheckKernel(CBlockIndex* pindexPrev, unsigned int nBits, uint32_t nTime, const COutPoint& prevout, uint32_t* pBlockTime = nullptr);
bool CheckKernel(CBlockIndex* pindexPrev, unsigned int nBits, uint32_t nTime, const COutPoint& prevout, uint32_t* pBlockTime, const std::map<COutPoint, CStakeCache>& cache);
bool CheckStakeKernelHash(const CBlockIndex* pindexPrev, unsigned int nBits, unsigned int nBlockFromTime, Amount prevOutAmount, const COutPoint &prevout, unsigned int nTime);
bool IsConfirmedInNPrevBlocks(const CDiskTxPos& txindex, const CBlockIndex* pindexFrom, int nMaxDepth, int& nActualDepth);
bool CheckProofOfStake(CBlockIndex* pindexPrev, const CTransaction& tx, unsigned int nBits, uint32_t nTimeBlock, CCoinsViewCache& view, CValidationState &state);
void CacheKernel(std::map<COutPoint, CStakeCache>& cache, const COutPoint& prevout, CBlockIndex* pindexPrev, CCoinsViewCache& view);
#endif // BLACKCOIN_POS_H
