#ifndef PROTOCOL_H
#define PROTOCOL_H

#define IP          ("192.168.59.129")
#define PORT        (12345)
#define PRO_CNT     (11)
#define MD5_KEY     ("1234")

#define USE_NO_JSON_AUDIO (1)

// 协议
#define PRO_BASE    (6666)

// 登录
#define LOG_RQ          (PRO_BASE)
#define LOG_RS          (PRO_BASE + 1)

// 注册
#define REG_RQ          (PRO_BASE + 2)
#define REG_RS          (PRO_BASE + 3)

// 创建房间
#define CREATE_ROOM_RQ  (PRO_BASE + 4)
#define CREATE_ROOM_RS  (PRO_BASE + 5)

// 加入房间
#define JOIN_ROOM_RQ    (PRO_BASE + 6)
#define JOIN_ROOM_RS    (PRO_BASE + 7)

// 通知加入
#define JOIN_INFO       (PRO_BASE + 8)

// 通知下线
#define LEAVE_INFO      (PRO_BASE + 9)

// 音频信息
#define AUDIO           (PRO_BASE + 10)

// 加入房间回复
#define JOIN_SUCCESS    (0)
#define JOIN_FAILED     (1)
#define ROOM_NOTEXIST   (2)

// 房间人员信息的获取flag
#define NEW_IN          (1)

// 登录回复
#define LOG_SUCCESS (0)
#define USER_MISS   (1)
#define PASS_ERROR  (2)

// 注册回复
#define REG_SUCCESS (0)
#define NAME_USED   (1)
#define TEL_USED    (2)

#endif // PROTOCOL_H
