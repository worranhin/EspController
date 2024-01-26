// /**
//  * @brief 指令码 b1b0 位的格式定义
//  *
//  */
// enum ModeCode_10 {
//   GET_STATUS = 0b00,
//   CONFIG = 0b01,
//   CONTROL = 0b10,
//   E_STOP = 0b11  // emergency stop 急停
// };

// /**
//  * @brief 配置模式下 (b1b0 = 01)，b4b3 的位定义
//  *
//  */
// enum ConfigCode_32 {
//   SET_ZERO = 0b00,
//   SET_DIR = 0b01,  // set direction 设置方向
//   SET_SPEED = 0b10,
//   SET_ACC = 0b11  // set acceleration 设置加速度
// };

// /**
//  * @brief 控制模式下 (b1b0 = 10)，b4b3 的位定义
//  *
//  */
// enum ControlCode_32 {
//   RUN = 0b00,
//   STOP = 0b01,
//   GO_MM = 0b10,  // 运行 x mm
//   GO_ZERO = 0b11  // 返回零位
// };

// struct {
//   ModeCode_10 mode;
//   ConfigCode_32 config;
//   ControlCode_32 control;
// };

struct CmdCode {
  /**
   * @brief 指令码 b1b0 位的格式定义
   *
   */
  enum ModeCode_10 {
    GET_STATUS = 0b00,
    CONFIG = 0b01,
    CONTROL = 0b10,
    E_STOP = 0b11  // emergency stop 急停
  };

  /**
   * @brief 配置模式下 (b1b0 = 01)，b4b3 的位定义
   *
   */
  enum ConfigCode_32 {
    SET_ZERO = 0b00,
    SET_DIR = 0b01,  // set direction 设置方向
    SET_SPEED = 0b10,
    SET_ACC = 0b11  // set acceleration 设置加速度
  };

  /**
   * @brief 控制模式下 (b1b0 = 10)，b4b3 的位定义
   *
   */
  enum ControlCode_32 {
    RUN = 0b00,
    STOP = 0b01,
    GO_MM = 0b10,   // 运行 x mm
    GO_ZERO = 0b11  // 返回零位
  };
  int test = 1;
};