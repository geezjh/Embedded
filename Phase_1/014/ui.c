#include "ui.h"
#include "file.h"
#include "function.h"
#include <stdio.h>

void welcome(void)
{
      puts("==================");
      puts("欢迎使用公交调度子系统");
      puts("\n==按任意键继续==");
      puts("==================");

      getchar();
}

int mainmenu(node_t **head, const char *file)
{
      puts("====主菜单====");
      puts("\n====1.显示记录====");
      puts("====2.添加记录====");
      puts("====3.删除记录====");
      puts("====4.查询记录====");
      puts("====5.修改记录====");
      puts("====0.退出系统====");
      puts("\n===========");

      printf("\n\n请选择功能:");
      int i = -1;
      scanf("%d", &i);

      switch (i)
      {
      case 0:
            return 0;
      case 1:
            while (browsermenu(*head))
                  ;
            break;
      case 2:
            while (addmenu(head, file))
                  ;
            break;
      case 3:
            while (delmenu(head, file))
                  ;
            break;
      case 4:
            break;
      case 5:
            break;
      default:
            puts("功能开发中,敬请期待...");
      }
      return i;
}

int browsermenu(node_t *head)
{
      puts("====浏览菜单====");
      puts("\n====1.车次排序====");
      puts("====2.站点排序====");
      puts("====3.里程排序====");
      puts("====4.原始顺序====");
      puts("====0.返回上级====");
      puts("\n===========");

      printf("\n\n请选择功能:");
      int i = -1;
      scanf("%d", &i);
      switch (i)
      {
      case 0:
            return 0;
      case 1:
      case 2:
      case 3:
            Sort(head, i);
            break;
      case 4:
            slist_showall(head);
            break;
      default:
            puts("功能开发中,敬请期待...");
      }
      return i;
}

int addmenu(node_t **head, const char *file)
{
      puts("====添加菜单====");
      puts("\n====1.头部添加====");
      puts("====2.尾部添加====");
      puts("====0.返回上级====");
      puts("\n===========");

      printf("\n\n请选择功能:");
      int i = -1;
      scanf("%d", &i);
      switch (i)
      {
      case 0:
            return 0;
      case 1:
      case 2:
            if (0 == addrecord(head, i))
                  save(*head, file);
            break;
      default:
            puts("功能开发中,敬请期待...");
      }
      return i;
}
int delmenu(node_t **head, const char *file)
{
      puts("====删除菜单====");
      puts("\n====1.按车次删除====");
      puts("====2.按站点删除====");
      puts("====0.返回上级====");
      puts("\n===========");

      printf("\n\n请选择功能:");
      int i = -1;
      scanf("%d", &i);
      switch (i)
      {
      case 0:
            return 0;
      case 1:
      case 2:
            if (0 == delrecord(head, i))
                  save(*head, file);
            break;
      default:
            puts("功能开发中,敬请期待...");
      }
      return i;
}