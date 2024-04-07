#include "Mysql.h"


CMysql::~CMysql()
{
    DisConnect();
}

bool CMysql::ConnectMysql(const char* server,const char* user,const char* password, const char* database)
{
    conn = mysql_init(NULL);  // 创建MYSQL对象。NULL表示加载默认值。
    mysql_set_character_set(conn,"utf8");//设置字符集为UTF8
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))//连接数据库
    {
        return false;// 连接失败，返回false
    }
    pthread_mutex_init(&m_lock , NULL); // 初始化互斥锁

    return true;  // 连接成功，返回true
}

bool CMysql::SelectMysql(char* szSql,int nColumn,list<string>& lst)
{
    lst.clear();

    MYSQL_RES * results = NULL;

    pthread_mutex_lock(&m_lock ); // 加锁

    if(mysql_query(conn,szSql)) {  // 查询SQL是否合法
        pthread_mutex_unlock(&m_lock );  // 查询失败，解锁并返回false
        return false;
    }
    results = mysql_store_result(conn);  // 将结果放在result中
    pthread_mutex_unlock(&m_lock );   // 解锁

    if(NULL == results)return false;   // result为空，返回false
    MYSQL_ROW record;     // 定义记录行
    while((record = mysql_fetch_row(results)))  // 遍历查询结果
    {
        for(int i=0; i<nColumn; i++)   
        {
            lst.push_back( record[i] );  // 将查询结果存入list
        }
    }
    return true;  // 查询成功，返回true
}


bool CMysql::UpdataMysql(char *szsql)
{
    if(!szsql)return false;   // SQL为空，返回false
    pthread_mutex_lock(&m_lock );   // 加锁
    if(mysql_query(conn,szsql)){    // 执行SQL语句
        pthread_mutex_unlock(&m_lock );  // 执行失败，解锁并返回false
        return false;
    }
    pthread_mutex_unlock(&m_lock );  // 解锁
    return true;   // SQL执行成功，返回true
}

void CMysql::DisConnect()
{
    mysql_close(conn);  // 关闭数据库连接
}
