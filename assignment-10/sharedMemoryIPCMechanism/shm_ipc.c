#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hMap;
    int *data;

    hMap = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(int) * 5,
        "MySharedMemory"
    );

    data = (int *)MapViewOfFile(
        hMap,
        FILE_MAP_ALL_ACCESS,
        0, 0,
        sizeof(int) * 5
    );

    int arr[5] = {7, 3, 9, 1, 4};

    for (int i = 0; i < 5; i++)
        data[i] = arr[i];

    printf("Before Sorting:\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", data[i]);
    printf("\n");

    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 5; j++)
            if (data[i] > data[j]) {
                int t = data[i];
                data[i] = data[j];
                data[j] = t;
            }

    printf("After Sorting:\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", data[i]);
    printf("\n");

    UnmapViewOfFile(data);
    CloseHandle(hMap);
    return 0;
}
