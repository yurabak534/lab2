// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

long size=10;
long *arr = new long[size];
long i;

struct LoopSettings
{
	long start;
	long limit;
	long sum;
};

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	LoopSettings *loopSettings = (LoopSettings*)lpParam;
	
	cout << loopSettings->start<<endl;

	loopSettings->sum = 0;
	for (i = loopSettings->start; i < loopSettings->limit; i++)
	{
		loopSettings->sum+=arr[i];
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//TODO: add code here
	
	for (i=0; i<size; i++)
	{
		arr[i]=i;
	}

	LoopSettings loop1;
	loop1.start = 0;
	loop1.limit = size/2;
	loop1.sum = 0;

	LoopSettings loop2;
	loop2.start = (size/2);
	loop2.limit = size;
	loop2.sum = 0;

	HANDLE hThreads[2];

    hThreads[0] = CreateThread(NULL, NULL, ThreadProc, &loop1, 0, 0);
	hThreads[1] = CreateThread(NULL, NULL, ThreadProc, &loop2, 0, 0);

	DWORD waitResult = WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

	cout << "sum is " << loop1.sum << endl
		 << loop2.sum << endl
		 << loop1.sum + loop2.sum;

	delete []arr;
	system("pause");

	return 0;
}