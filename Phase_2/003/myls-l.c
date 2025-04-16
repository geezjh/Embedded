#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void getfiletype(const struct stat *p, char *pinfo)
{
    if (S_ISDIR(p->st_mode))
        pinfo[0] = 'd';
    else if (S_ISREG(p->st_mode))
        pinfo[0] = '-';
    else if (S_ISSOCK(p->st_mode))
        pinfo[0] = 's';
    else if (S_ISLNK(p->st_mode))
        pinfo[0] = 'l';
    else if (S_ISCHR(p->st_mode))
        pinfo[0] = 'c';
    else if (S_ISBLK(p->st_mode))
        pinfo[0] = 'b';
    else if (S_ISFIFO(p->st_mode))
        pinfo[0] = 'p';
}
void getownerperm(const struct stat *p, char *pinfo)
{
    switch (p->st_mode & 0700)
    {
    case 0700:
        strcat(pinfo, "rwx");
        break;
    case 0600:
        strcat(pinfo, "rw-");
        break;
    case 0500:
        strcat(pinfo, "r-x");
        break;
    case 0400:
        strcat(pinfo, "r--");
        break;
    case 0300:
        strcat(pinfo, "-wx");
        break;
    case 0200:
        strcat(pinfo, "-w-");
        break;
    case 0100:
        strcat(pinfo, "--x");
        break;
    default:
        strcat(pinfo, "---");
    }
}
void getgroupperm(const struct stat *p, char *pinfo)
{
    switch (p->st_mode & 0070)
    {
    case 0070:
        strcat(pinfo, "rwx");
        break;
    case 0060:
        strcat(pinfo, "rw-");
        break;
    case 0050:
        strcat(pinfo, "r-x");
        break;
    case 0040:
        strcat(pinfo, "r--");
        break;
    case 0030:
        strcat(pinfo, "-wx");
        break;
    case 0020:
        strcat(pinfo, "-w-");
        break;
    case 0010:
        strcat(pinfo, "--x");
        break;
    default:
        strcat(pinfo, "---");
    }
}
void getotherperm(const struct stat *p, char *pinfo)
{
    switch (p->st_mode & 0007)
    {
    case 0007:
        strcat(pinfo, "rwx");
        break;
    case 0006:
        strcat(pinfo, "rw-");
        break;
    case 0005:
        strcat(pinfo, "r-x");
        break;
    case 0004:
        strcat(pinfo, "r--");
        break;
    case 0003:
        strcat(pinfo, "-wx");
        break;
    case 0002:
        strcat(pinfo, "-w-");
        break;
    case 0001:
        strcat(pinfo, "--x");
        break;
    default:
        strcat(pinfo, "---");
    }
}
void getnlink(const struct stat *p, char *pinfo)
{
    if (S_ISDIR(p->st_mode))
    {
        // 功能待实现...
    }
    else
    {
        char buf[32] = {0};
        sprintf(buf, " %lu ", p->st_nlink);
        strcat(pinfo, buf);
    }
}
void getusername(const struct stat *p, char *pinfo)
{
    char buf[32] = {0};
    sprintf(buf, "%s ", getpwuid(p->st_uid)->pw_name);
    strcat(pinfo, buf);
}
void getgroupname(const struct stat *p, char *pinfo)
{
    char buf[32] = {0};
    sprintf(buf, "%s ", getgrgid(p->st_uid)->gr_name);
    strcat(pinfo, buf);
}
void getfilesize(const struct stat *p, char *pinfo)
{
    char buf[16] = {0};
    sprintf(buf, "%ld ", p->st_size);
    strcat(pinfo, buf);
}
void getmtime(const struct stat *p, char *pinfo)
{
    time_t now = time(NULL);
    struct tm *pc = localtime(&now);
    int year = pc->tm_year;

    struct tm *t = localtime(&p->st_mtime);
    char buf[32] = {0};
    if (year == t->tm_year)
        sprintf(buf, "%d月   %d %02d:%02d ", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
    else
        sprintf(buf, "%d月   %d %4d ", t->tm_mon + 1, t->tm_mday, t->tm_year + 1900);

    strcat(pinfo, buf);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        write(STDERR_FILENO, "Usage programm file\n", strlen("Usage programm file\n"));
        return -1;
    }
    struct stat s = {0};
    if (-1 == stat(argv[1], &s))
    {
        perror("stat");
        return -1;
    }

    char info[128] = {0};

    getfiletype(&s, info);
    getownerperm(&s, info);
    getgroupperm(&s, info);
    getotherperm(&s, info);

    getnlink(&s, info);

    getusername(&s, info);
    getgroupname(&s, info);

    getfilesize(&s, info);
    getmtime(&s, info);

    puts(info);
    return 0;
}