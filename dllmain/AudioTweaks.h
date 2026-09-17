#pragma once
#include <cstddef>
#include <cstdint>

class cModel;

namespace re4t
{
	namespace AudioTweaks
	{
		void UpdateVolume();

		struct SndKey
		{
			void* ret_addr;
			uint16_t blk;
			uint16_t call_no;
			cModel* pMod;
			uint32_t flag;
			uint32_t sndCallHandle;
			double tick;
		};

		struct SndSlice
		{
			static constexpr size_t MAX_ENTRIES = 256;
			SndKey entries[MAX_ENTRIES];
			size_t count = 0;

			SndKey* find(void* ret, uint16_t blk, uint16_t call_no, uint32_t flag, cModel* pMod)
			{
				for (size_t i = 0; i < count; i++)
				{
					if (entries[i].pMod == pMod &&
						entries[i].flag == flag &&
						entries[i].call_no == call_no &&
						entries[i].blk == blk &&
						entries[i].ret_addr == ret)
						return &entries[i];
				}
				return nullptr;
			}

			bool add(const SndKey& key)
			{
				if (count >= MAX_ENTRIES)
					return false;
				entries[count++] = key;
				return true;
			}
		};
	}
}
