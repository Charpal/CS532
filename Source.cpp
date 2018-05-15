#include <iostream>
#include <time.h>
#include <vector>
#include <queue>
#include "Comparitor.h"
#include "ReplacementSelectionHelper.h"

using namespace std;
#define ARRAY_SIZE 21

void generateSortedRuns(int arr[], int arraySize, int M);
void replacementSelection(int arr[], int arraySize, int start_of_next_records, priority_queue<int, vector<int>, comparitor> pq1, priority_queue<int, vector<int>, comparitor> pq2, int M, int & runNum, int & runLength);

int main()
{

	int arr[ARRAY_SIZE] = {109, 49, 34, 68, 45, 2, 60, 38, 28, 47, 16,
				 19, 34, 55, 98, 78, 76, 40, 35, 86, 10};
	vector<int> first_array_to_be_sorted{ 109, 49, 34, 68, 45, 2, 60, 38, 28, 47, 16,
		19, 34, 55, 98, 78, 76, 40, 35, 86, 10 };
	cout << "First Sorted Run:" << endl;
	generateSortedRuns(arr, ARRAY_SIZE, 5);

	int arr2[100];
	for (int i = 1; i < 101; i++)
		arr2[i - 1] = i;
	for (int i = 0; i < 100; i++)
	{
		srand(time(NULL));
		int r = rand() % (i + 1);
		swap(arr2[i], arr2[r]);
	}
	
	cout << endl << "Second Sorted Run:" << endl;
	generateSortedRuns(arr2, 100, 10);

	system("pause");
	return 0;
}

void generateSortedRuns(int arr[], int arraySize, int M)
{
	priority_queue<int, vector<int>, comparitor> pq1;
	priority_queue<int, vector<int>, comparitor> pq2;
	int length_of_runs = 0;
	int number_of_runs = 1;
	replacementSelection(arr, arraySize, 0, pq1, pq2, M, number_of_runs, length_of_runs);
	cout << "Average length of runs: " << length_of_runs / ((number_of_runs - 1) * 1.0) << endl;//float()?
}

void replacementSelection(int arr[], int arraySize, int start_of_next_records, priority_queue<int, vector<int>, comparitor> pq1, priority_queue<int, vector<int>, comparitor> pq2, int M, int & runNum, int & runLength)
{
	if (start_of_next_records >= arraySize && pq1.empty() && pq2.empty())
		return;
	for (start_of_next_records; start_of_next_records < M && start_of_next_records < arraySize; start_of_next_records++)
	{
		/*cout << "Input: " << arr[start_of_next_records] << endl;*/
		pq1.push(arr[start_of_next_records]);
	}
	cout << "Run #" << runNum << ": ";
	bool firstNum = true;
	while (!pq1.empty())// what happens if start of record is at max?
	{
		runLength++;
		if (firstNum)
		{
			firstNum = false;
			cout << pq1.top();
		}
		else
			cout << ", " << pq1.top();
		if (start_of_next_records < arraySize)
		{
			int nextRecord = arr[start_of_next_records];
			if (nextRecord < pq1.top())
			{
				pq2.push(nextRecord);
				pq1.pop();
			}
			else
			{
				pq1.pop();
				pq1.push(nextRecord);
			}
			start_of_next_records++;
		}
		else
		{
			pq1.pop();
		}
	}
	runNum++;
	cout << endl;
	replacementSelection(arr, arraySize, start_of_next_records, pq2, pq1, M, runNum, runLength);
}