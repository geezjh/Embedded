// 1.编程实现对非空目录的递归删除
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
int delDir(char *p)
{
    DIR *dir = opendir(p);
    if (dir == NULL)
    {
        perror("opendir");
        return -1;
    }
    struct dirent *entry;
    struct stat statbuf;
    while (entry = readdir(dir))
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", p, entry->d_name);
        if (stat(fullpath, &statbuf) == -1)
        {
            perror("stat");
            closedir(dir);
            return -1;
        }
        if (S_ISDIR(statbuf.st_mode))
        {
            if (delDir(fullpath) == -1)
            {
                closedir(dir);
                return -1;
            }
        }
        else if (unlink(fullpath) == -1)
        {
            perror("unlink");
            closedir(dir);
            return -1;
        }
    }
    closedir(dir);
    if (rmdir(p) == -1)
    {
        perror("rmdir");
        return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage %s directory\n", argv[0]);
        return -1;
    }
    if (-1 == delDir(argv[1]))
    {
        perror("delDir");
        return -1;
    }
    return 0;
}