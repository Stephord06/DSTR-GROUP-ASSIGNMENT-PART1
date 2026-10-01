#include "sortArrayByAge.hpp"

void copyDataset(const arrayDataset &source, arrayDataset &destination)
{
    destination.clear();
    for (int i = 0; i < source.size; i++)
    {
        destination.data[i] = source.data[i];
    }

    destination.size = source.size;
}

static void mergeParts(record *leftArray, int leftSize, record *rightArray, int rightSize, record *result)
{
    int l = 0, r = 0, i = 0; // indices

    while (l < leftSize && r < rightSize)
    {
        if (leftArray[l].age <= rightArray[r].age)
        {
            result[i] = leftArray[l];
            i++;
            l++;
        }

        else
        {
            result[i] = rightArray[r];
            i++;
            r++;
        }
    }

    while (l < leftSize)
    {
        result[i] = leftArray[l];
        i++;
        l++;
    }

    while (r < rightSize)
    {
        result[i] = rightArray[r];
        i++;
        r++;
    }
}

static void mergeSortRecords(record *arr, int length)
{
    if (length <= 1)
        return;

    int middle = length / 2;
    int rightLength = length - middle;

    record *leftArray = new record[middle];
    record *rightArray = new record[rightLength];

    for (int i = 0; i < length; i++)
    {
        if (i < middle)
        {
            leftArray[i] = arr[i];
        }

        else
        {
            rightArray[i - middle] = arr[i];
        }
    }

    mergeSortRecords(leftArray, middle);
    mergeSortRecords(rightArray, rightLength);
    mergeParts(leftArray, middle, rightArray, rightLength, arr);

    delete[] leftArray;
    delete[] rightArray;
}

void mergeSortByAge(arrayDataset &dataset)
{
    mergeSortRecords(dataset.data, dataset.size);
}
