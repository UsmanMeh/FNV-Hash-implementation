#include "pch.h"
#include "CppUnitTest.h"
#include "../FNV-HashingAlgo/FNVHash.h"
#include "../FNV-HashingAlgo/FNVHash.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FNVHashingTest
{
	TEST_CLASS(FNVHashingTest)
	{
	public:
		TEST_METHOD(TestFNV_Hash)
		{
			Logger::WriteMessage("TestFNV_Hash");
			unsigned char testSring[] = "The quick brown fox jumps over the lazy dog";
			size_t dataLenght = strlen((char*)testSring);
			uint64_t hash =  FNVHash::CalculateFNVHash(testSring, dataLenght);
			Assert::AreEqual<uint64_t>(17580284887202820368, hash);
		}

		TEST_METHOD(TestFNV_Hash_MultiThreaded)
		{
			Logger::WriteMessage("TestFNV_Hash_MultiThreaded");
			unsigned char testSring[] = "The quick brown fox jumps over the lazy dog";
			size_t dataLenght = strlen((char*)testSring);
			uint64_t hash = FNVHash::CalculateFNVHashMultiThreaded(testSring, dataLenght);
			Assert::AreEqual<uint64_t>(8862519316354193946, hash);
		}
		TEST_METHOD(TestFNV_Hash_Same)
		{
			Logger::WriteMessage("TestFNV_Hash");
			Logger::WriteMessage("hash(123456789) != hash(987654321)");
			unsigned char testSring1[] = "123456789";
			unsigned char testSring2[] = "987654321";
			size_t dataLenght1 = strlen((char*)testSring1);
			size_t dataLenght2 = strlen((char*)testSring2);
			uint64_t hash1 = FNVHash::CalculateFNVHash(testSring1, dataLenght1);
			uint64_t hash2 = FNVHash::CalculateFNVHash(testSring2, dataLenght2);
			Assert::AreNotEqual<uint64_t>(hash1, hash2);
		}
		TEST_METHOD(TestFNV_HashArrayLenth)
		{
			Logger::WriteMessage("TestFNV_HashArrayLenth");
			Logger::WriteMessage("ZeroArra(1024) != ZeroArra(512)");
			int ZeroArray[1024] = { 0 };
			uint64_t hash1024 = FNVHash::CalculateFNVHash(ZeroArray, 1024);
			ZeroArray[512] = { 0 };
			uint64_t hash512 = FNVHash::CalculateFNVHash(ZeroArray, 512);
			Assert::AreNotEqual<uint64_t>(hash1024, hash512);
		}
		TEST_METHOD(TestFNV_Hash_SameData)
		{
			Logger::WriteMessage("TestFNV_Hash_SameData");
			Logger::WriteMessage("ZeroArra(1024) == ZeroArra(1024)");
			int ZeroArray1[1024] = { 0 };
			uint64_t hash1024 = FNVHash::CalculateFNVHash(ZeroArray1, 1024);
			int ZeroArray2[1024] = { 0 };
			uint64_t hash512 = FNVHash::CalculateFNVHash(ZeroArray2, 1024);
			Assert::AreEqual<uint64_t>(hash1024, hash512);
		}

		TEST_METHOD(TestFNV_Hash_MultiThreaded_ArrayLenth)
		{
			Logger::WriteMessage("TestFNV_Hash_MultiThreaded_ArrayLenth");
			Logger::WriteMessage("ZeroArra(1024) != ZeroArra(512)");
			int ZeroArray[1024] = { 0 };
			uint64_t hash1024 = FNVHash::CalculateFNVHashMultiThreaded(ZeroArray, 1024);
			ZeroArray[512] = { 0 };
			uint64_t hash512 = FNVHash::CalculateFNVHashMultiThreaded(ZeroArray, 512);
			Assert::AreNotEqual<uint64_t>(hash1024, hash512);
		}

		TEST_METHOD(TestFNV_Hash_MultiThreaded_SameData)
		{
			Logger::WriteMessage("TestFNV_Hash_MultiThreaded_SameData");
			Logger::WriteMessage("ZeroArra(1024) == ZeroArra(1024)");
			int ZeroArray1[1024] = { 0 };
			uint64_t hash1024 = FNVHash::CalculateFNVHashMultiThreaded(ZeroArray1, 1024);
			int ZeroArray2[1024] = { 0 };
			uint64_t hash512 = FNVHash::CalculateFNVHashMultiThreaded(ZeroArray2, 1024);
			Assert::AreEqual<uint64_t>(hash1024, hash512);
		}

	};
}
