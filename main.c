#include <stdio.h>
#include <Windows.h>
#include <stdint.h>


int main(int argc, char** argv){
    HANDLE hFind;
    WIN32_FIND_DATA wFindData;

    uint32_t argv1Str = strlen(argv[1]);
    char translatedDir[256];
    strcpy(translatedDir,argv[1]);
    ((uint32_t)translatedDir[argv1Str-1] == 92) ? strcat(&translatedDir[argv1Str],"*.*") : NULL;
    hFind = FindFirstFile(translatedDir, &wFindData);
    printf("\nDirectory: %s\n\r\n",translatedDir);

    uint32_t files = 0;
    uint32_t folders = 0;

    puts("-------------------------------");
    while (FindNextFile(hFind, &wFindData))
    {
        if(strcmp("..", wFindData.cFileName)){
            uint64_t fileSize = wFindData.nFileSizeHigh;
            fileSize <<= sizeof(wFindData.nFileSizeHigh) * 8;
            fileSize |= wFindData.nFileSizeLow;
            if(fileSize >= 1024*1024){
                printf("%s | %d MiB\n",wFindData.cFileName, fileSize / 1024 / 1024); files++;
            } else if(fileSize >= 1024){
                 printf("%s | %d KiB\n",wFindData.cFileName, fileSize / 1024); files++;
            }
            else if(fileSize <= 1024 && fileSize > 0){
                 printf("%s | %d bytes\n",wFindData.cFileName, fileSize); files++;
            } else if(fileSize == 0){
                printf("%s | Folder\n\r", wFindData.cFileName); folders++;
            }
        }
    }
    puts("-------------------------------\n");
    FindClose(hFind);
    printf("\nFiles: %d | Folders: %d\n\r", files,folders);
}