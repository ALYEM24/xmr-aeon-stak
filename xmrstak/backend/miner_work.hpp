#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <cstring>

namespace xmrstak
{
	struct miner_work
	{
		char        sJobID[64];
		uint8_t     bWorkBlob[112];
		uint32_t    iWorkSize;
		uint64_t    iTarget;
		// \todo remove workaround needed for amd
		uint32_t    iTarget32;
		bool        bNiceHash;
		bool        bStall;
		size_t      iPoolId;

		miner_work() : iWorkSize(0), bNiceHash(false), bStall(true), iPoolId(0) { }

		miner_work(const char* sJobID, const uint8_t* bWork, uint32_t iWorkSize,
			uint64_t iTarget, bool bNiceHash, size_t iPoolId) : iWorkSize(iWorkSize),
			iTarget(iTarget), bNiceHash(bNiceHash), bStall(false), iPoolId(iPoolId)
		{
			assert(iWorkSize <= sizeof(bWorkBlob));
			memcpy(this->sJobID, sJobID, sizeof(miner_work::sJobID));
			memcpy(this->bWorkBlob, bWork, iWorkSize);
		}

		miner_work(miner_work const&) = delete;

		miner_work& operator=(miner_work const& from)
		{
			assert(this != &from);

			iWorkSize = from.iWorkSize;
			iTarget = from.iTarget;
			iTarget32 = from.iTarget32;
			bNiceHash = from.bNiceHash;
			bStall = from.bStall;
			iPoolId = from.iPoolId;

			assert(iWorkSize <= sizeof(bWorkBlob));
			memcpy(sJobID, from.sJobID, sizeof(sJobID));
			memcpy(bWorkBlob, from.bWorkBlob, iWorkSize);

			return *this;
		}

		miner_work(miner_work&& from) : iWorkSize(from.iWorkSize), iTarget(from.iTarget),iTarget32(from.iTarget32),
			bStall(from.bStall), iPoolId(from.iPoolId)
		{
			assert(iWorkSize <= sizeof(bWorkBlob));
			memcpy(sJobID, from.sJobID, sizeof(sJobID));
			memcpy(bWorkBlob, from.bWorkBlob, iWorkSize);
		}

		miner_work& operator=(miner_work&& from)
		{
			assert(this != &from);

			iWorkSize = from.iWorkSize;
			iTarget = from.iTarget;
			iTarget32 = from.iTarget32;
			bNiceHash = from.bNiceHash;
			bStall = from.bStall;
			iPoolId = from.iPoolId;

			assert(iWorkSize <= sizeof(bWorkBlob));
			memcpy(sJobID, from.sJobID, sizeof(sJobID));
			memcpy(bWorkBlob, from.bWorkBlob, iWorkSize);

			return *this;
		}
	};
} // namepsace xmrstak
