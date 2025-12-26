#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE rPipe, wPipe;
    SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };
    int arr[5] = {5, 1, 4, 2, 3};
    DWORD bytes;

    CreatePipe(&rPipe, &wPipe, &sa, 0);

    printf("Before Sorting:\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    WriteFile(wPipe, arr, sizeof(arr), &bytes, NULL);
    ReadFile(rPipe, arr, sizeof(arr), &bytes, NULL);

    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 5; j++)
            if (arr[i] > arr[j]) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }

    printf("After Sorting:\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    CloseHandle(rPipe);
    CloseHandle(wPipe);
    return 0;
}
