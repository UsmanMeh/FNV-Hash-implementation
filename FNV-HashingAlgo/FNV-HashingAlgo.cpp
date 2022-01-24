// FNV-HashingAlgo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "FNVHash.h"

int main()
{

    // Get ending timepoint

    // Get duration. Substart timepoints to 
    // get durarion. To cast it to proper unit
    // use duration cast method

	unsigned char testSring[] = "The quick brown fox jumps over the lazy dog";
    unsigned char buff_a[] = "1234567890";
    unsigned char buff_b[] = "qwerty";
    unsigned char buff_c[] = "1234567890qwerty";
    unsigned char buff_d[] = "";
	size_t dataLenght = strlen((char*)testSring);

    auto start = high_resolution_clock::now();
	cout <<"Multi Threaded Hash "<< FNVHash::CalculateFNVHashMultiThreaded(testSring, dataLenght) << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
        << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    cout << "Single Threaded Hash " << FNVHash::CalculateFNVHash(testSring) << "\n";
    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
        << duration.count() << " microseconds" << endl;
    cout << FNVHash::CalculateFNVHash(buff_a) << "\n";
    cout << FNVHash::CalculateFNVHash(buff_b) << "\n";
    cout << FNVHash::CalculateFNVHash(buff_c) << "\n";
    cout << FNVHash::CalculateFNVHash(buff_d) << "\n";
}