#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void heapify(int arr[], int n, int x)
{
	// keep track of the max
	int max = x;

	// the left address
	int leftNode = x * 2 + 1;
	// the left address
	int rightNode = x * 2 + 2;
	// the parent address
	int parent = x;

	// check if the left node exists
	if (leftNode < n)
	{
		// is it greater than the parent?
		if (arr[leftNode] > arr[max])
		{
			max = leftNode;
		}
	}

	// check if the right node exists
	if (rightNode < n)
	{
		// is it greater than the parent?
		if (arr[rightNode] > arr[max])
		{
			max = rightNode;
		}
	}

	if (max != parent)
	{
		// SWAP THEM! swap(arr[parent], arr[max])
		int swap = arr[parent];
		arr[parent] = arr[max];
		arr[max] = swap;

		// check swapped node
		heapify(arr, n, max);
	}
}
//   0, 1, 2, 3, 4, 5
// [ 1, 5, 3, 4, 2, 6]
//      p     l  r
// 	 max = r
// 	 max = 4



// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{

	// total num of parent nodes
	int parentNum = n / 2 - 1;
	// run all heap from last parent node
	for(int i = parentNum; i >= 0; i--){
		heapify (arr, n, i);
	}

	int i = n - 1;
	while(i >= 0){	

		// SWAP THE FIRST AND LAST
		int swap = arr[0];
		arr[0] = arr[i];
		arr[i] = swap;
		
		heapify(arr, i, 0);
		i--;
	}

}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (l < r)
	{
		int x = l + (r - l) / 2;

		mergeSort(pData, l, x);
		mergeSort(pData, x + 1, r);

		int n1 = x - l + 1;
		int n2 = r - x;
		int left[n1];
		int right[n2];

		memcpy(left, &pData[l], n1 * sizeof(int));
		memcpy(right, &pData[x + 1], n2 * sizeof(int));

		int a = 0, b = 0, c = l;

		while (a < n1 && b < n2)
		{
			if (left[a] <= right[b])
			{
				pData[c] = left[a];
				a++;
			}
			else
			{
				pData[c] = right[b];
				b++;
			}

			c++;
		}
		while (a < n1)
		{
			pData[c] = left[a];
			a++;
			c++;
		}
		while (b < n2)
		{
			pData[c] = right[b];
			b++;
			c++;
		}

		extraMemoryAllocated += n1 * sizeof(int) + n2 * sizeof(int);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE *inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			fscanf(inFile, "%d ", &n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i = 0; i < 100; ++i)
	{
		if (i >= dataSz) {
            printf("\n\n");
            return;
        }
		printf("%d ", pData[i]);
	}
	printf("\n\t");

	for (i = sz; i < dataSz; ++i)
	{
		printf("%d ", pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
	double cpu_time_used;
	char *fileNames[] = {"input1.txt", "input2.txt", "input3.txt", "input4.txt"};

	for (i = 0; i < 4; ++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);

		if (dataSz <= 0)
			continue;

		pDataCopy = (int *)malloc(sizeof(int) * dataSz);

		printf("---------------------------\n");
		printf("Dataset Size : %d\n", dataSz);
		printf("---------------------------\n");

		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		free(pDataCopy);
		free(pDataSrc);
	}
}