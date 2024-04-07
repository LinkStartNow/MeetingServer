#ifndef PROTOCOL_H
#define PROTOCOL_H

#define IP          ("192.168.59.129")
#define PORT        (12345)
#define PRO_CNT     (4)
#define MD5_KEY     ("1234")

// 协议
#define PRO_BASE    (6666)

// 登录
#define LOG_RQ      (PRO_BASE)
#define LOG_RS      (PRO_BASE + 1)

// 注册
#define REG_RQ      (PRO_BASE + 2)
#define REG_RS      (PRO_BASE + 3)

// 登录回复
#define LOG_SUCCESS (0)
#define USER_MISS   (1)
#define PASS_ERROR  (2)

// 注册回复
#define REG_SUCCESS (0)
#define NAME_USED   (1)
#define TEL_USED    (2)

#endif // PROTOCOL_H
