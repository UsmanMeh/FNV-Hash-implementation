#pragma once
#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <pthread.h>
#include <cstdio>
#include <chrono>
using namespace std;
using namespace std::chrono;

class FNVHash
{
public:
	FNVHash(void);
	~FNVHash(void);
	static uint64_t CalculateFNVHash(void* data, size_t dataSize);
	static uint64_t CalculateFNVHash(void* data);
	static uint64_t CalculateFNVHashMultiThreaded(void* data, size_t dataSize);
private:
	static void* FNVHashThread(void* threadarg);
};

