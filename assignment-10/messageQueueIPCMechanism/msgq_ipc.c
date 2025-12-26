#include <windows.h>
#include <stdio.h>

#define PIPE_NAME "\\\\.\\pipe\\MsgPipe"

int main() {
    HANDLE pipe;
    int arr[5] = {8, 2, 6, 4, 1};
    DWORD bytes;

    pipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 1024, 1024, 0, NULL
    );

    ConnectNamedPipe(pipe, NULL);

    printf("Before Sorting:\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    ReadFile(pipe, arr, sizeof(arr), &bytes, NULL);

    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 5; j++)
            if (arr[i] > arr[j]) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }

    WriteFile(pipe, arr, sizeof(arr), &bytes, NULL);

    printf("After Sorting:\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    CloseHandle(pipe);
    return 0;
}
