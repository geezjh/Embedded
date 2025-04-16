#include <mysql/mysql.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage %s DatabaseName TableName\n", argv[0]);
        return -1;
    }
    MYSQL *mysql = mysql_init(NULL);
    if (mysql == NULL)
    {
        fprintf(stderr, "连接对象初始化失败.\n");
        return -1;
    }
    if (mysql_real_connect(mysql, NULL, "root", "123456", NULL, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "connect error:%s\n", mysql_error(mysql));
        mysql_close(mysql);
        return -1;
    }
    printf("数据库连接成功\n");
    char sql[512] = {0};
    sprintf(sql, "create database if not exists %s", argv[1]);
    if (mysql_real_query(mysql, sql, strlen(sql)))
    {
        fprintf(stderr, "Create failed:%s\n", mysql_error(mysql));
        mysql_close(mysql);
        return -1;
    }
    printf("数据库%s创建成功!\n", argv[1]);
    bzero(sql, sizeof(sql));
    sprintf(sql, "use %s", argv[1]);
    mysql_real_query(mysql, sql, strlen(sql));
    bzero(sql, sizeof(sql));
    sprintf(sql, "create table if not exists %s (id int primary key auto_increment,name varchar(20),num int) default charset=utf8", argv[2]);
    if (mysql_real_query(mysql, sql, strlen(sql)))
    {
        fprintf(stderr, "Create failed:%s\n", mysql_error(mysql));
        mysql_close(mysql);
        return -1;
    }
    printf("表%s创建成功!\n", argv[2]);
    bzero(sql, sizeof(sql));
    sprintf(sql, "insert into %s (name,num) values ('%s',%d),('%s',%d)", argv[2], "C语言", 1, "Java", 3);
    if (mysql_real_query(mysql, sql, strlen(sql)))
    {
        fprintf(stderr, "Insert failed:%s\n", mysql_error(mysql));
        mysql_close(mysql);
        return -1;
    }
    printf("插入数据成功!\n");
    bzero(sql, sizeof(sql));
    sprintf(sql, "select * from %s", argv[2]);
    if (mysql_real_query(mysql, sql, strlen(sql)))
    {
        fprintf(stderr, "Select failed:%s\n", mysql_error(mysql));
        mysql_close(mysql);
        return -1;
    }
    printf("查询成功!\n");
    do
    {
        MYSQL_RES *res = NULL;
        if (!(res = mysql_store_result(mysql)))
        {
            if (0 == mysql_field_count(mysql))
                printf("%llu row affected!\n", mysql_affected_rows(mysql));
            else
                fprintf(stderr, "Failed reason:%s\n", mysql_error(mysql));
        }
        else
        {
            uint32_t fn = mysql_num_fields(res);
            MYSQL_FIELD *fields = mysql_fetch_fields(res);
            for (int i = 0; i < fn; i++)
                printf("%10s", fields[i].name);
            printf("\n");
            my_ulonglong rn = mysql_num_rows(res);
            MYSQL_ROW row = NULL;
            for (int i = 0; i < rn; i++)
            {
                row = mysql_fetch_row(res);
                for (int j = 0; j < fn; j++)
                    printf("%10s", row[j]);
                printf("\n");
            }
        }
        mysql_free_result(res);
    } while (mysql_next_result(mysql) == 0);

    mysql_close(mysql);
    return 0;
}