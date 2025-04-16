// 将给定目录下的所有文件名改为大写，例如 game.data  改为  GAME.DAT
// 将字符串转换为大写
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
void to_upper(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] = toupper((unsigned char)str[i]);
}
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage %s directory\n", argv[0]);
        return -1;
    }
    DIR *dir = opendir(argv[1]);
    if (dir == NULL)
    {
        perror("opendir");
        return -1;
    }
    struct dirent *entry;
    while (entry = readdir(dir))
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        char old[1024], new[1024];
        snprintf(old, sizeof(old), "%s/%s", argv[1], entry->d_name);
        snprintf(new, sizeof(new), "%s/%s", argv[1], entry->d_name);
        to_upper(new + strlen(argv[1]) + 1);
        if (rename(old, new) != 0)
            perror("rename");
    }
    closedir(dir);
    return 0;
}