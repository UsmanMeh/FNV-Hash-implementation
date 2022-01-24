#include "FNVHash.h"


using namespace std;

#define FNV64_prime (uint64_t)0x100000001b3ULL
#define Offset_basis (uint64_t)14695981039346656037

#define FNV_64_PRIME_LOW ((uint64_t)0x1b3)
#define FNV_64_PRIME_SHIFT (8)

#define NUM_THREADS 4

struct thread_data {
	int  thread_id;
	uint64_t hash;
	void* data;
	size_t dataSize;
};

void passStringTest(unsigned char* str)
{
	std::cout << str << "\n";
}
uint64_t FNVHash::CalculateFNVHash(void* data)
{
	size_t dataLenght = strlen((char*)data);

	return CalculateFNVHash(data, dataLenght);
}
uint64_t FNVHash::CalculateFNVHash(void* data, size_t dataSize)
{
	unsigned long long hash = Offset_basis;
	unsigned char* octetBuffer = (unsigned char*)data;
	unsigned char* dataEndbuffer = octetBuffer + dataSize;

	while (octetBuffer < dataEndbuffer)
	{
		hash ^= (unsigned long long) * octetBuffer++;
		hash *= FNV64_prime;
	}

	return hash;
}

void* FNVHash::FNVHashThread(void* threadarg)
{
	struct thread_data* my_data;
	my_data = (struct thread_data*)threadarg;

	my_data->hash = CalculateFNVHash(my_data->data, my_data->dataSize);

	pthread_exit(NULL);
	return 0;
}
uint64_t FNVHash::CalculateFNVHashMultiThreaded(void* data, size_t dataSize)
{
	pthread_t threads[NUM_THREADS];
	struct thread_data td[NUM_THREADS];
	int rc;
	int i;
	size_t dataChunkSize = (dataSize / NUM_THREADS);
	for (i = 0; i < NUM_THREADS; i++) {
		td[i].thread_id = i;
		td[i].data = (unsigned char*)data + (dataChunkSize * i);
		td[i].dataSize = dataChunkSize;

		rc = pthread_create(&threads[i], NULL, FNVHashThread, (void*)&td[i]);

		if (rc) {
			cout << "Error:unable to create thread," << rc << endl;
			exit(-1);
		}
	}
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
	unsigned long long hash = Offset_basis;
	for (i = 0; i < NUM_THREADS; i++)
	{
		hash ^= td[i].hash;
		hash *= FNV64_prime;
	}
	return hash;
}


