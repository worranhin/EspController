/**
 * @file CmdCode.h
 * @author worranhin (worranhin@foxmail.com)
 * @brief 本文件定义用于简单串口通讯的指令码。
 * @version 0.1
 * @date 2024-01-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef CMD_CODE_H
#define CMD_CODE_H

enum CmdCode : uint8_t {
  E_STOP        = 0x00,  // emergency stop 急停
  GET_STATUS    = 0x04,
  SET_ZERO      = 0x08,
  SET_DIR       = 0x09,  // set direction 设置方向
  SET_SPEED     = 0x0a,  
  SET_ACC       = 0x0b,  // set acceleration 设置加速度
  CTRL_RUN      = 0x0c,
  CTRL_STOP     = 0x0d,
  CTRL_GO_MM    = 0x0e,  // 运行 x mm
  CTRL_GO_ZERO  = 0x0f   // 返回零位
};

#endif