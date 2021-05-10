#include <iostream>
#include <ctime>
#include <stdlib.h>    
#include <time.h>  
using namespace std;

template <class Type>
double cpuTime(Type arr[], long length, void (*func)(Type[], int, int));

template <class Type>
void quicksort_median_element_insertion(Type arr[], int first, int last);

template <class Type>
void quicksort_median_element(Type arr[], int first, int last);

template <class Type>
void quicksort_middle_element_insertion(Type arr[], int first, int last);

template <class Type>
void quicksort_middle_element(Type arr[], int first, int last);

template <class Type>
int partition(Type list[], int first, int last);

template <class Type>
void swap(Type list[], int first, int second);

template <class Type>
void insertionSort(Type list[], int length);

int findMedianIndex(int first, int last, int mid);

template <class Type>
int lengthOfArray(Type arr[]);

int main()
{
	int arr[10000];

	// fill the array with random integers
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
		arr[i] =rand();
	
	cout << "Quicksort -middle pivot- :  ";
	cout <<  cpuTime(arr, 10000, quicksort_middle_element) << " sec CPU time\n";

	cout << "Quicksort -median pivot- :  ";
	cout << cpuTime(arr, 10000, quicksort_median_element) << " sec CPU time\n\n";

	cout << "Quicksort -middle pivot- with insertion :  ";
	cout << cpuTime(arr, 10000, quicksort_middle_element_insertion) << " sec CPU time\n";

	cout << "Quicksort -median pivot- with insertion :  ";
	cout << cpuTime(arr, 10000, quicksort_median_element_insertion) << " sec CPU time\n";

	return 0;
}

template <class Type>
int lengthOfArray(Type arr[])
{
	return (sizeof(arr) / sizeof(*arr));
}

// determines which one is the median of those three 
int findMedianIndex(int first, int last, int mid)
{
	if ((first < last && last < mid) || (mid < last && last < first))
		return last;
	else if ((last < first && first < mid) || (mid < first && first < last))
		return first;
	else
		return mid;
}

template <class Type>
void insertionSort(Type list[], int length) 
{
	for (int firstOutOfOrder = 1; firstOutOfOrder < length; firstOutOfOrder++)
		if (list[firstOutOfOrder] < list[firstOutOfOrder - 1])
		{
			Type temp = list[firstOutOfOrder];
			int location = firstOutOfOrder;
			do
			{
				list[location] = list[location - 1];
				location--;
			} while (location > 0 && list[location - 1] > temp);

			list[location] = temp;
		}
}

// swap the first index of the array with second index
template <class Type>
void swap(Type list[], int first, int second)
{
	Type temp;
	temp = list[first];
	list[first] = list[second];
	list[second] = temp;
}

// divide the array into parts 
template <class Type>
int partition(Type list[], int first, int last)
{
	Type pivot;
	int index, smallIndex, midElement;

	// make the first element of the part pivot
	pivot = list[first];
	smallIndex = first;

	//  put the values which is smaller than the pivot left of the pivot,
	//  those which are bigger than pivot will go to the right of the pivot 
	for (index = first + 1; index <= last; index++)
		if (list[index] < pivot)
		{
			smallIndex++;
			swap(list, smallIndex, index);
		}

	swap(list, first, smallIndex);
	return smallIndex;
}

template <class Type>
void quicksort_middle_element(Type arr[], int first, int last)
{
	int partitionIndex;

	if (first < last)
	{
		// pivot is in the middle 
		// and puts it in the first index
		swap(arr, first, ((first + last) / 2));

		partitionIndex = partition(arr, first, last);
		quicksort_middle_element(arr, first, partitionIndex - 1);
		quicksort_middle_element(arr, partitionIndex + 1, last);
	}
}

template <class Type>
void quicksort_middle_element_insertion(Type arr[], int first, int last)
{
	int partitionIndex;

	if (first < last)
	{
		// pivot is in the middle 
		// and puts it in the first index
		swap(arr, first, ((first + last) / 2));

		partitionIndex = partition(arr, first, last);
		quicksort_middle_element(arr, first, partitionIndex - 1);
		quicksort_middle_element(arr, partitionIndex + 1, last);
	}

	// if the sublist's length is smaller than 20, make insertion sort for the rest. 
	if ((last - first + 1) < 20)
	{
		insertionSort(arr, (last - first + 1));
		return;
	}
}

template <class Type>
void quicksort_median_element(Type arr[], int first, int last)
{
	int partitionIndex, medianIndex;
	medianIndex = findMedianIndex(first, last, (first + last) / 2);

	if (first < last)
	{
		// determine which one is the median: first, last or mid
		if (medianIndex == first)
			swap(arr, first, first);
		else if (medianIndex == last)
			swap(arr, first, last);
		else
			swap(arr, first, (first + last) / 2);

		partitionIndex = partition(arr, first, last);
		quicksort_middle_element(arr, first, partitionIndex - 1);
		quicksort_middle_element(arr, partitionIndex + 1, last);
	}
}

template <class Type>
void quicksort_median_element_insertion(Type arr[], int first, int last)
{
	int partitionIndex, medianIndex;
	medianIndex = findMedianIndex(first, last, (first + last) / 2);

	if (first < last)
	{
		// determine which one is the median: first, last or mid
		if (medianIndex == first)
			swap(arr, first, first);
		else if (medianIndex == last)
			swap(arr, first, last);
		else
			swap(arr, first, (first + last) / 2);

		partitionIndex = partition(arr, first, last);
		quicksort_middle_element(arr, first, partitionIndex - 1);
		quicksort_middle_element(arr, partitionIndex + 1, last);
	}

	// if the sublist's length is smaller than 20, make insertion sort for the rest. 
	if ((last - first + 1) < 20)
	{
		insertionSort(arr, (last - first + 1));
		return;
	}
}

template <class Type>
double cpuTime(Type arr[], long length, void (*func)(Type[], int, int))
{
	clock_t t1 = clock();
	func(arr, 0, length - 1);
	clock_t t2 = clock();
	return (double(t2 - t1) / CLOCKS_PER_SEC);  // difference between t1 and t2 will give us cpu time of func().
}