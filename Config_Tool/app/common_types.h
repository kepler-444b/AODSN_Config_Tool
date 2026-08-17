#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdint.h>

#define SCENE_INFO_SIZE  185 // 设置场景信息字节数

#define PANEL_DEV_MAX    32 // 面板最大个数
#define LED_NUM_MAX      32 // 最大led路数
#define RELAY_NUM_MAX    18


// 主机下发到面板的数据帧相关宏定义
#define PANEL_FRAME_TX_HEAD_1 0xFF // 固定帧头
#define PANEL_FRAME_TX_HEAD_2 0xAA // 固定帧头
#define PANEL_FRAME_TX_TYPE   0x01 // 报文类型:暂固定为 0x01


#define PANEL_FRAME_RX_SUB_LEN  19 // 子帧长度
#define PANEL_FRAME_RX_ADDR_LEN 8  // 子帧中的地址个数
// 面板通讯结构体
typedef struct
{
    uint8_t src_addr;  // 面板地址
    uint8_t level;     // 触发类型
    uint8_t status;    // 面板状态(上报面板状态)
    uint8_t key_num;   // 按键编号(上报按键编号)
    uint8_t reserve_1; // 保留值(旋钮值)
    uint8_t reserve_2; // 保留
} panel_src_info_t;

typedef struct
{
    uint8_t panel_tx_head;
    uint8_t panel_tx_type;
    uint8_t panel_tx_length;

    panel_src_info_t panel_info;
    uint8_t panel_tx_crc;
    uint8_t panel_tx_tail_1;
    uint8_t panel_tx_tail_2;
} panel_frame_t;



typedef struct {
    uint8_t status;
    uint8_t reserve;
} panel_sub_idx;

// 子帧设备的状态信息
typedef struct {
    panel_sub_idx idx[8];
    uint8_t bl;
    uint8_t reserve1;
    uint8_t reserve2;
} panel_sub_status_t;

// 所有面板设备的状态表
typedef struct
{
    panel_sub_status_t sub_frame[PANEL_DEV_MAX / 8];
} panel_full_status_t;

// 场景结构体
typedef struct {
    uint8_t id;
    uint8_t led[LED_NUM_MAX];           // 64路led状态
    uint8_t relay[RELAY_NUM_MAX];       // 72路继电器状态
    uint8_t key_ctrl[PANEL_DEV_MAX];    // 32个面板控制状态
    uint8_t key_status[PANEL_DEV_MAX];  // 32个面板实际状态
    uint8_t key_reserve[PANEL_DEV_MAX]; // 32个面板保留
} scene_id_t;


typedef struct {

    uint8_t fh_1;
    uint8_t fh_2;
    uint8_t length;
    uint8_t type;
    panel_full_status_t full_frame;
    uint8_t crc;
    uint8_t ft_1;
    uint8_t ft_2;
} panel_tx_buf_t;


// 主机下发到扩展设备的数据帧相关宏定义
#define EXTEND_FRAME_TX_HEAD 0xFB
#define EXTEND_FRAME_TX_TYPE 0x01

// 扩展设备的状态表
typedef struct
{
    uint8_t relay_sel_1[6];
    uint8_t relay_sel_2[3];
    uint8_t tg_value[4]; // 4路可控硅调光

    uint8_t led_sel_1[4];  // 4 路LED PWM调光(1~4)
    uint8_t led_sel_2[12]; // 12路LED PWM调光(5~16)
    uint8_t led_sel_3[8];  // 8 路LED PWM调光(17~24)
    uint8_t led_sel_4[8];  // 8 路LED PWM调光(25~32)

    uint8_t air_dev[3]; // 空调模块

} extend_all_status_t;

typedef struct
{
    uint8_t fh;
    uint8_t type;
    uint8_t relay_sel_1[6];
    uint8_t tg_value[4];
    uint8_t crc_1;
    uint8_t led_sel_1[4];
    uint8_t reserve;
    uint8_t crc_2;
    uint8_t led_sel_2[12];
    uint8_t crc_3;
    uint8_t led_sel_3[8];
    uint8_t air_dev[3];
    uint8_t relay_sel_2[3];
    uint8_t led_sel_4[8];

} extend_tx_buf_t;

#endif // COMMON_TYPES_H
