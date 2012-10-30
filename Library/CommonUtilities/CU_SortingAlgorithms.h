#ifndef _CU_SORTING_ALGORITHMS_H_
#define _CU_SORTING_ALGORITHMS_H_
#include <limits>
#include <queue>

namespace CommonUtilities
{
	template<class Type> inline void QuickSort(CU::GrowingArray<Type>& someData, int aStart, int aEnd);
	template<class Type, int Size> inline void QuickSort(CU::StaticArray<Type, Size>& someData, int aStart, int aEnd);
	template<class Type> inline void HeapSort(CU::GrowingArray<Type>& someData);
	template<class Type> inline void ShellSort(CU::GrowingArray<Type>& someData);
	template<class Type> inline void MergeSort(CU::GrowingArray<Type>& someData, int aStart, int aEnd);
	template<class Type> inline void RadixSort(CU::GrowingArray<Type>& someData);

	namespace HelpFunctions
	{
		template<class Type> inline void HeapSortMoveDown(CU::GrowingArray<Type>& someData, int aFirstIndex, int aLastIndex);
		template<class Type> inline void HeapSortSwap(Type& aValue1, Type& aValue2);
		template<class Type> inline void MergeSortMerge(CU::GrowingArray<Type>& someData, int aStart, int aEnd);
	}
}

namespace CU = CommonUtilities;

template<class Type>
void CU::QuickSort<Type>(CU::GrowingArray<Type>& someData, int aStart, int aEnd)
{
	int i = aStart, j = aEnd;
	Type tmp;
	Type pivot = someData[(aStart + aEnd) / 2];

	while (i <= j) 
	{
		while (someData[i] < pivot)
		{
			i++;

			if (i >= aEnd)
			{
				break;
			}
		}

		while (someData[j] > pivot)
		{
			j--;

			if (j <= aStart)
			{
				break;
			}
		}

		if (i <= j) 
		{
			tmp = someData[i];
			someData[i] = someData[j];
			someData[j] = tmp;
			i++;
			j--;
		}
	};

	if (aStart < j)
	{
		QuickSort<Type>(someData, aStart, j);
	}

	if (i < aEnd)
	{
		QuickSort<Type>(someData, i, aEnd);
	}
}



template<class Type, int Size>
void CU::QuickSort<Type, Size>(CU::StaticArray<Type, Size>& someData, int aStart, int aEnd)
{
	int i = aStart, j = aEnd;
	Type tmp;
	Type pivot = someData[(aStart + aEnd) / 2];

	while (i <= j) 
	{
		while (someData[i] < pivot)
		{
			i++;

			if (i >= aEnd)
			{
				break;
			}
		}

		while (someData[j] > pivot)
		{
			j--;

			if (j <= aStart)
			{
				break;
			}
		}

		if (i <= j) 
		{
			tmp = someData[i];
			someData[i] = someData[j];
			someData[j] = tmp;
			i++;
			j--;
		}
	};

	if (aStart < j)
	{
		QuickSort<Type>(someData, aStart, j);
	}

	if (i < aEnd)
	{
		QuickSort<Type>(someData, i, aEnd);
	}
}


template<class Type>
void CU::HeapSort(CU::GrowingArray<Type>& someData)
{
	for (int i = someData.Count()/2 - 1; i >= 0; --i)
	{
		HelpFunctions::HeapSortMoveDown(someData, i, someData.Count()-1);	
	}
	for (int i = someData.Count()-1; i >= 1; --i)
	{
		HelpFunctions::HeapSortSwap(someData[0], someData[i]);
		HelpFunctions::HeapSortMoveDown(someData, 0, i-1);
	}
}

template<class Type>
void CU::ShellSort<Type>(CU::GrowingArray<Type>& someData)
{
	int i = 0;
	int j = 0;
	int hCnt = 0;
	int h = 0;
	int increments[20];
	int k = 0;

	for(h = 1; h < someData.Count(); i++)
	{
		increments[i] = h;
		h = (3*h) + 1;
	}

	for (i--; i >= 0; i--)
	{
		h = increments[i];

		for (hCnt = h; hCnt < 2*h; hCnt++)
		{
			for (j = hCnt; j < someData.Count();)
			{
				Type tmp = someData[j];
				k = j;

				while(k-h >= 0 && tmp < someData[k-h])
				{
					someData[k] = someData[k-h];
					k -= h;
				}

				someData[k] = tmp;
				j += h;
			}
		}
	}
}

template<class Type>
void CU::MergeSort(CU::GrowingArray<Type>& someData, int aStart, int aEnd)
{
	if (aStart < aEnd)
	{
		const int middle = (aStart + aEnd) / 2;
		MergeSort(someData, aStart, middle);
		MergeSort(someData, middle+1, aEnd);
		HelpFunctions::MergeSortMerge(someData, aStart, aEnd);
	}
}

template<class Type>
void CU::RadixSort(CU::GrowingArray<Type>& someData)
{
	int j = 0;
	int k = 0;
	int factor = 1;
	const int radix = 10;
	const int digits = std::numeric_limits<Type>::digits;

	std::queue<Type> queues[radix];

	for (int i = 0; i < digits; i++)
	{
		factor *= radix;

		for (j = 0; j < someData.Count(); j++)
		{
			queues[(someData[j] / factor) % radix].push(someData[j]);
		}
		for (j = k = 0; j < radix; j++)
		{
			while(queues[j].empty() == false)
			{
				someData[k++] = queues[j].front();
				queues[j].pop();
			}
		}
	}
}

template<class Type>
void CU::HelpFunctions::HeapSortMoveDown(CU::GrowingArray<Type>& someData, int aFirstIndex, int aLastIndex)
{
	int largestValue = 2*aFirstIndex+1;

	while(largestValue <= aLastIndex)
	{
		if (largestValue < aLastIndex && someData[largestValue] < someData[largestValue+1])
		{
			largestValue++;
		}
		if (someData[aFirstIndex] < someData[largestValue])
		{
			HelpFunctions::HeapSortSwap(someData[aFirstIndex],someData[largestValue]);
			aFirstIndex = largestValue;
			largestValue = 2*aFirstIndex+1;
		}
		else
		{
			largestValue = aLastIndex+1;
		}
	}
}

template<class Type>
void CU::HelpFunctions::HeapSortSwap(Type& aValue1, Type& aValue2)
{
	Type tmp = aValue1;
	aValue1 = aValue2;
	aValue2 = tmp;
}

template<class Type>
void CU::HelpFunctions::MergeSortMerge(CU::GrowingArray<Type>& someData, int aStart, int aEnd)
{
	int mid = (aStart + aEnd)/2;
	int i2 = aStart;
	int i3 = mid + 1;

	CU::GrowingArray<Type> temp((aEnd-aStart)+1,1);

	while (i2 <= mid && i3 <= aEnd)
	{
		if (someData[i2] <= someData[i3])
		{
			temp.Add(someData[i2++]);
		}
		else
		{
			temp.Add(someData[i3++]);
		}
	}

	while (i2 <= mid)
	{
		temp.Add(someData[i2++]);
	}

	while (i3 <= aEnd)
	{
		temp.Add(someData[i3++]);
	}

	int tempIndex = 0;
	for (int index = aStart; index <= aEnd; index++)
	{
		someData[index] = temp[tempIndex++];
	}
}

#endif