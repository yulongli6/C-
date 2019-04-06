#pragma once

size_t GetNextPrime(size_t num);

template<class K>
struct KTOINTDef
{
	const K& operator()(const K& key)
	{
		return key;
	}
};