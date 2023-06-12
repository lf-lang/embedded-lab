/// @file imu.c
/// contains implementations for the imu library
#include <imu.h>
#include <hardware/i2c.h>
#include <hardware/gpio.h>

void imu_init(imu_inst_t* imu_inst) {
    uint8_t w_cmd;
    uint8_t r_buf;
    // i2c peripheral instance 0
    // initialize instance and record baudrate
    // configure as master
    imu_inst->set_baud = i2c_init(i2c0, _IMU_I2C0_BAUDRATE);
    // sda: data line
    /// TODO: use the header pin defines? 
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    // scl: clk line 
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(5);

    // detect imu sensor
    // read from WHO AM I register
    w_cmd = _IMU_REG_WHO_AM_I;
    // keep bus control
    /// TODO: add time outs to blocking calls
    /// TODO: read i2c reg abstraction hal agnostic
    i2c_write_blocking(i2c0, _IMU_ADDR, &w_cmd, 1, true);
    i2c_read_blocking(i2c0, _IMU_ADDR, &r_buf, 1, false);
    // successfully initialize imu communication
    // WHO_AM_I response is 0x6C 
    imu_inst->status = (r_buf == 0x6C);

    /// TODO: check error conditions and modify status flag in instance
    //imu_reset(imu_inst);
    //imu_set_default(imu_inst); 
}


void imu_reset(imu_inst_t* imu_inst) {
    if (!imu_inst->status) {
        // TODO: error reporting
        // imu not setup correctly
        return;
    } 
    uint8_t cmd_buf[2] = {_IMU_REG_CTRL3_C, 0x00};
    // read and store CTRL3
    i2c_write_blocking(i2c0, _IMU_ADDR, &(cmd_buf[0]), 1, true);
    i2c_read_blocking(i2c0, _IMU_ADDR, &(cmd_buf[1]), 1, false);
    // mask and write
    // write to _CTRL3_C.BOOT (0x80)
    cmd_buf[1] |= 0x80;
    i2c_write_blocking(i2c0, _IMU_ADDR, cmd_buf, 2, false);
    // blocking read until _CTRL3_C.BOOT flag resets
    do {
        i2c_write_blocking(i2c0, _IMU_ADDR, &(cmd_buf[0]), 1, true);
        i2c_read_blocking(i2c0, _IMU_ADDR, &(cmd_buf[1]), 1, false);
    } while(cmd_buf[1] & 0x80);

    /// TODO: sleep and check at end or poll check
    /// use an interrupt to fire when reset complete
    /// callback update the imu_ins->status

    // mask and write
    // write to _CTRL3_C.SW_RESET (0x01)
    cmd_buf[1] |= 0x01;
    i2c_write_blocking(i2c0, _IMU_ADDR, cmd_buf, 2, false);
    // blocking read until _CTRL3_C.SW_RESET flag resets
    do {
        i2c_write_blocking(i2c0, _IMU_ADDR, &(cmd_buf[0]), 1, true);
        i2c_read_blocking(i2c0, _IMU_ADDR, &(cmd_buf[1]), 1, false);
    } while(cmd_buf[1] & 0x01);
}
void _imu_set(imu_settings_t* config) {
    uint8_t cmd_acc_buf[2] = {_IMU_REG_CTRL1_XL, 0x00};
    uint8_t cmd_gyro_buf[2] = {_IMU_REG_CTRL2_G, 0x00};
    // mask and set
    // write to CTRL1_XL.ODR_XL = acc_dr
    cmd_acc_buf[1] &= ~0xF0;
    cmd_acc_buf[1] |= config->acc_dr << 4;
    // write to CTRL1_XL.FS_XL = acc_fs
    cmd_acc_buf[1] &= ~0x0C;
    cmd_acc_buf[1] |= config->acc_fs << 2;
    i2c_write_blocking(i2c0, _IMU_ADDR, cmd_acc_buf, 2, false);

    // mask and set
    // write to CTRL2_G.ODR_G = gyro_dr
    cmd_gyro_buf[1] &= ~0xF0;
    cmd_gyro_buf[1] |= config->gyro_dr << 4;
    // write to CTRL2_G.FS_G = gyro_fs
    cmd_gyro_buf[1] &= ~0x0E;
    cmd_gyro_buf[1] |= config->gyro_fs << 1;
    i2c_write_blocking(i2c0, _IMU_ADDR, cmd_gyro_buf, 2, false);
    // blocking read until _CTRL3_C.SW_RESET flag resets
}

void imu_set_default(imu_inst_t* imu_inst) {
    if (!imu_inst->status) {
        // TODO: error reporting
        // imu not setup correctly
        return;
    }
    // imu general configuration
    uint8_t cmd_buf[2] = {_IMU_REG_CTRL3_C, 0x00};
    // read and store CTRL3
    i2c_write_blocking(i2c0, _IMU_ADDR, &(cmd_buf[0]), 1, true);
    i2c_read_blocking(i2c0, _IMU_ADDR, &(cmd_buf[1]), 1, false);
    // write to _CTRL3_C.BDU (0x40)
    cmd_buf[1] |= 0x40;
    i2c_write_blocking(i2c0, _IMU_ADDR, cmd_buf, 2, false);

    // sensor specific configuration 
    imu_settings_t conf = {
        .gyro_dr = HZ208,
        .gyro_fs = GYRO_SCALE2000, 
        .acc_dr = HZ52,
        .acc_fs = ACC_SCALE2,
    };
    /// TODO: this sucks, find a better way to assign the two values 
    /// TODO: encode a sensor bias?
    imu_inst->gyro_sen = _gyro_full_scale_to_sensitivity[4];
    imu_inst->acc_sen = _acc_full_scale_to_sensitivity[0];
    _imu_set(&conf);
}

void imu_read_acc(imu_inst_t* imu_inst, axes_data_t* acc_data) {
    uint8_t reg = _IMU_OUTX_L_XL;
    uint8_t buf[6];
    int16_t raw[3];
    // read from the register 
    i2c_write_blocking(i2c0, _IMU_ADDR, &reg, 1, true);
    i2c_read_blocking(i2c0, _IMU_ADDR, buf, 6, false);
    /// TODO: might be other way
    for (int i = 0; i < 3; i++) {
        raw[i] = (buf[i * 2] << 8 | buf[(i * 2) + 1]);
    }
    acc_data->x = (raw[0] * imu_inst->acc_sen) / 1000.0;
    acc_data->y = (raw[1] * imu_inst->acc_sen) / 1000.0;
    acc_data->z = (raw[2] * imu_inst->acc_sen) / 1000.0;
}

void imu_read_gyro(imu_inst_t* imu_inst, axes_data_t* gyro_data) {
    uint8_t reg = _IMU_OUTX_L_G;
    uint8_t buf[6];
    int16_t raw[3];
    /// TODO: abstract this subroutine
    /// TODO: add imu_inst checks
    // read from the register 
    i2c_write_blocking(i2c0, _IMU_ADDR, &reg, 1, true);
    i2c_read_blocking(i2c0, _IMU_ADDR, buf, 6, false);
    /// TODO: might be other way
    for (int i = 0; i < 3; i++) {
        raw[i] = (buf[i * 2] << 8 | buf[(i * 2) + 1]);
    }
    gyro_data->x = (raw[0] * imu_inst->gyro_sen) / 1000.0;
    gyro_data->y = (raw[1] * imu_inst->gyro_sen) / 1000.0;
    gyro_data->z = (raw[2] * imu_inst->gyro_sen) / 1000.0;
}