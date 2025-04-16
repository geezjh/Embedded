// 2.创建一个子进程,要求子进程对某个指定文件内容
// 转存到当前目录指定文件,父进程输出转存后文件的前10行内容。
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int save(const char *old_path, const char *new_path)
{
    FILE *old_file = fopen(old_path, "r");
    if (old_file == NULL)
    {
        perror("fopen old file");
        return -1;
    }

    FILE *new_file = fopen(new_path, "w");
    if (new_file == NULL)
    {
        perror("fopen new file");
        fclose(old_file);
        return -1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), old_file) != NULL)
    {
        if (fputs(buffer, new_file) == EOF)
        {
            perror("fputs");
            fclose(old_file);
            fclose(new_file);
            return -1;
        }
    }

    fclose(old_file);
    fclose(new_file);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage %s old new\n", argv[0]);
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }

    if (pid == 0)
    {
        if (save(argv[1], argv[2]) != 0)
        {
            fprintf(stderr, "Failed to save file\n");
            exit(1);
        }
        exit(0);
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return -1;
        }

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            FILE *new_file = fopen(argv[2], "r");
            if (new_file == NULL)
            {
                perror("fopen new file for reading");
                return -1;
            }

            char buffer[1024];
            int line_conut = 0;
            while (fgets(buffer, sizeof(buffer), new_file) != NULL)
            {
                printf("%s", buffer);
                line_conut++;
            }

            fclose(new_file);
        }
        else
        {
            fprintf(stderr, "Child process failed\n");
            return -1;
        }
    }
    printf("\n");
    return 0;
}