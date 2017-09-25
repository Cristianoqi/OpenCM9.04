/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehoon Lim (Darby) */

#ifndef DYNAMIXEL_WORKBENCH_DYNAMIXEL_DRIVER_H
#define DYNAMIXEL_WORKBENCH_DYNAMIXEL_DRIVER_H

#include "dynamixel_tool.h"

#if defined(__OPENCR__) || defined(__OPENCM904__)
  #include <DynamixelSDK.h>
#elif defined(__linux__)
  #include "dynamixel_sdk/dynamixel_sdk.h"
#endif

#define DXL_NUM 10

class DynamixelDriver
{
 private:
  dynamixel::PortHandler   *portHandler_;
  dynamixel::PacketHandler *packetHandler_;

  dynamixel::GroupSyncWrite *groupSyncWrite_;
  dynamixel::GroupSyncRead  *groupSyncRead_;

  dynamixel::GroupBulkWrite *groupBulkWrite_;
  dynamixel::GroupBulkRead  *groupBulkRead_;
 
  DynamixelTool tools_[DXL_NUM];

  uint8_t tools_cnt_;

 public:
  DynamixelDriver();
  ~DynamixelDriver();

  void setTools(uint16_t model_num, uint8_t id);
  uint8_t findTools(uint8_t id);
  uint8_t theNumberOfTools();

  bool begin(char* model_series, char* device_name = "/dev/ttyUSB0", uint32_t baud_rate = 57600);

  void setPortHandler(char* device_name, bool *error);
  void setPacketHandler(float protocol_version, bool *error);
  void setBaudrate(uint32_t baud_rate, bool *error);

  uint8_t  scan(uint8_t *get_id, uint8_t num = 252);
  uint16_t ping(uint8_t id);

  bool reboot(uint8_t id);
  bool reset(uint8_t id);

  bool writeRegister(uint8_t id, char* item_name, int32_t data);
  bool readRegister(uint8_t id, char* item_name, int32_t* data);

  void initSyncWrite(uint8_t id, char* item_name);
  bool syncWrite(int32_t *data);

  void initSyncRead(uint8_t id, char* item_name);
  bool syncRead(char* item_name, int32_t *data);

  void initBulkWrite();
  bool addBulkWriteParam(uint8_t id, char* item_name, int32_t data);
  void bulkWrite();

  void initBulkRead();
  void addBulkReadParam(uint8_t id, char* item_name);
  void sendBulkReadPacket();
  bool bulkRead(uint8_t id, char* item_name, int32_t *data);

  int32_t convertRadian2Value(int8_t id, float radian);
  float convertValue2Radian(int8_t id, int32_t value);
};

#endif //DYNAMIXEL_WORKBENCH_DYNAMIXEL_DRIVER_H
