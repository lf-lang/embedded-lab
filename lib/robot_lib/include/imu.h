/// @file imu.h
/// Methods for accessing accelerometer and gyro data from
/// lsm6dso sensor
// TODO: just read the datasheet
#pragma once
#include <hardware/i2c.h>

// 100KHz I2C Bus0 baudrate 
#define _IMU_I2C0_BAUDRATE 100000
#define _IMU_ADDR 0b1101011

#define _IMU_REG_WHO_AM_I 0x0F
#define _IMU_REG_CTRL1_XL 0x10
#define _IMU_REG_CTRL2_G 0x11
#define _IMU_REG_CTRL3_C 0x12
#define _IMU_STATUS_REG 0x1E
#define _IMU_OUTX_L_G 0x22
#define _IMU_OUTX_L_XL 0x28

enum out_data_rate {
    HZ0 = 0b0000,
    HZ12_5 = 0b0001,
    HZ26 = 0b0010,   
    HZ52 = 0b0011,   
    HZ104 = 0b0100,   
    HZ208 = 0b0101,   
    HZ416 = 0b0110,   
    HZ833 = 0b0111,   
    HZ1666 = 0b1000,   
    HZ3332 = 0b1001,   
    HZ6664 = 0b1010,   
};


enum acc_full_scale_encoding {
    ACC_SCALE2 = 0b00, // 0
    ACC_SCALE4 = 0b10, // 1
    ACC_SCALE8 = 0b11, // 2
    ACC_SCALE16 = 0b01 // 3
};

enum gyro_full_scale_encoding {
    GYRO_SCALE125 = 0b001,  // 0
    GYRO_SCALE250 = 0b000,  // 1
    GYRO_SCALE500 = 0b010,  // 2
    GYRO_SCALE1000 = 0b100, // 3
    GYRO_SCALE2000 = 0b110  // 4
};

/// TODO: to save space (maybe set these at compile time)
/// TODO: find a better way to do this
// learn more about c macros and setup  
// gyro sensitivity (G_So) in mdps/LSB
static const float _gyro_full_scale_to_sensitivity[] = {
    4.375,
    8.75,
    17.5,
    35,
    70
};

// accelerometer sensitivity (LA_So) mg/LSB
static const float _acc_full_scale_to_sensitivity[] = {
    0.061,
    0.122,
    0.244,
    0.488
};

typedef struct _imu_inst {
    uint32_t set_baud;
    bool status;
    // accelerometer sensitivity
    float acc_sen;
    // gyro sensitivity
    float gyro_sen;
} imu_inst_t;

typedef struct _imu_settings {
    // gyro settings
    enum out_data_rate gyro_dr;
    enum gyro_full_scale_encoding gyro_fs;
    // accelerometer settings
    enum out_data_rate acc_dr;
    enum acc_full_scale_encoding acc_fs;
} imu_settings_t;

typedef struct _axes_data {
    float x;
    float y;
    float z;
} axes_data_t;

// TODO: determine return type for error reporting and
// fault handling

/// @brief 
/// initialize the i2c instance and set pins
void imu_init(imu_inst_t* imu_inst);

/// @brief write to imu reset register on i2c
void imu_reset(imu_inst_t* imu_inst);

/// @brief use preset default config and assign
/// struct with sensitivity parameters
void imu_set_default(imu_inst_t* imu_inst);

/// @brief fills the provided memory space
/// with the acceleration in TODO: units
/// for each axis.
/// @param acc_data 
void imu_read_acc(imu_inst_t* imu_inst, axes_data_t* acc_data);

/// @brief fills the provided memory space
/// with the gyro data in TODO: units
/// for each axis.
/// @param gyro_data 
void imu_read_gyro(imu_inst_t* imu_inst, axes_data_t* gyro_data);

/// @brief write to control registers for various
/// configurations of the imu 
/// @param config 
void _imu_set(imu_settings_t* config);