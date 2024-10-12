#include <files.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace File
{
    char* readAllText(const char* path)
    {
        FILE* file = fopen(path, "r");
        if (!file)
        {
            fprintf(stderr, "Failed to read file '%s'!\n", path);
            return nullptr;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        rewind(file);

        char* source = (char*) malloc(fileSize);
        if (!source)
        {
            fprintf(stderr, "Failed to allocate memory for file '%s'!\n", path);
            return nullptr;
        }

        memset(source, 0, fileSize);

        size_t out = fread(source, 1, fileSize, file);
        if (out > fileSize)
        {
            fprintf(stderr, "Failed to read contents of file '%s'!\n", path);
            free(source);
            return nullptr;
        }

        if (fclose(file) != 0)
        {
            printf("Failed to close file '%s'!\n", path);
        }

        return source;
    }
}
