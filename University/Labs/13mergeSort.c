// 13 - Merge Sort. Divide, then Merge.
#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *arr, int start, int end);
void merge(int *arr, int start, int mid, int end);

int main(void)
{
    int size;
    printf("Size: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter the array\n");
    for (int i = 0; i < size; i++)
        scanf("%d", (arr + i));

    printf("\n== BEFORE ==\n");
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);

    mergeSort(arr, 0, size - 1);

    printf("\n== AFTER ==\n");
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");
    return 0;
}

void merge(int *arr, int start, int mid, int end)
{
      int i = start, j = mid + 1;
      int tmp[end-start+1];
      int index = 0;
      // Merging in the ascending order.
      while(i <= mid && j <= end) {
            if (arr[i] < arr[j])
                tmp[index++] = arr[i++];
            else
                tmp[index++] = arr[j++];
      }
      // Merging the remaning elements.
      while (i <= mid) {
          tmp[index++] = arr[i++];
      }
      while (j <= end) {
          tmp[index++] = arr[j++];
      }
      for (int i = start, k = 0; i <= end; i++, k++) {
          arr[i] = tmp[k];
      }
      return;
}

void mergeSort(int *arr, int start, int end)
{
    // Arrays with single elements will have start == end.
    if (start < end) {
        int mid = (start + end) / 2;
        // Sort the first half.
        mergeSort(arr, start, mid);
        // Sort the second half.
        mergeSort(arr, mid + 1, end);
        // Merge the two sorted halves.
        merge(arr, start, mid, end);
    }
}
