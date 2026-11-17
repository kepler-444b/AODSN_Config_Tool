#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdint.h>

#define SCENE_INFO_SIZE  185 // 设置场景信息字节数

#define PANEL_DEV_MAX    32 // 面板最大个数
#define LED_NUM_MAX      64 // 最大led路数
#define RELAY_NUM_MAX    16


// 主机下发到面板的数据帧相关宏定义
#define PANEL_FRAME_TX_HEAD_1 0xFF // 固定帧头
#define PANEL_FRAME_TX_HEAD_2 0xAA // 固定帧头
#define PANEL_FRAME_TX_TYPE   0x01 // 报文类型:暂固定为 0x01


#define PANEL_FRAME_RX_SUB_LEN  27 // 子帧长度
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

// 场景中的面板数据
typedef struct
{
    uint8_t id;
    uint8_t panel_ctrl[PANEL_DEV_MAX];
    uint8_t panel_status[PANEL_DEV_MAX];
    uint8_t panel_reserve_1[PANEL_DEV_MAX];
    uint8_t panel_reserve_2[PANEL_DEV_MAX];
} scene_id_panel_t;

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
    uint8_t reserve_1;  // 亮度值
    uint8_t reserve_2;  // 色温值
} panel_sub_idx;

// 面板子帧设备的状态信息
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

// 发送给面板的数据帧
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

// 场景结构体
typedef struct {
    uint8_t id;
    uint8_t led[LED_NUM_MAX * 2]; // 64路led状态(亮度+色温)
    uint8_t relay[RELAY_NUM_MAX]; // 64路继电器状态
} scene_id_t;

// 主机下发到扩展设备的数据帧相关宏定义
#define EXTEND_FRAME_TX_HEAD 0xFB
#define EXTEND_FRAME_TX_TYPE 0x01

// 扩展设备的状态表

typedef struct {
    uint8_t lum;  // 亮度值 (0-100/最高位使能)
    uint8_t cct;  // 色温值 (0-100/最高位使能)
} led_channel_t;

typedef struct
{
    uint8_t relay[8];
    led_channel_t led[64];

} extend_all_status_t;


typedef struct
{
    uint8_t       fh_1;          // [0] 帧头1: 0xFB
    uint8_t       fh_2;          // [1] 帧头2: 0xFC
    uint8_t       led_tag[4];    // [2~5] LED识别码: "LED:" (0x4C, 0x45, 0x44, 0x3A)
    led_channel_t led[64];       // [6~133] 64路LED数据 (包含第1路至第64路，每路2字节，共128字节)
    uint8_t       relay_tag[6];  // [134~139] Relay识别码: "RELAY:" (0x52, 0x45, 0x4C, 0x41, 0x59, 0x3A)
    uint8_t       relay[8];      // [140~147] 64个继电器字节 (每字节按Bit控制8路，共64个字节，控制512路/64模块)
    uint8_t       crc16_h;       // [148] CRC16 校验高位
    uint8_t       crc16_l;       // [149] CRC16 校验低位
    uint8_t       ft_1;          // [150] 帧尾1: 0x0D
    uint8_t       ft_2;          // [151] 帧尾2: 0x0A

} extend_tx_buf_t;

#endif // COMMON_TYPES_H
