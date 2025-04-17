#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define I2C_MASTER_SCL_IO (33)                  // GPIO SCL
#define I2C_MASTER_SDA_IO (32)                  // GPIO SDA
#define I2C_MASTER_NUM I2C_NUM_0                // I2C port
#define I2C_MASTER_FREQ_HZ 100000               // I2C  hz
#define I2C_MASTER_TX_BUF_DISABLE 0             // buffer TX
#define I2C_MASTER_RX_BUF_DISABLE 0             // buffer RX

/**
 * @brief Initialize I2C master interface
 * 
 * Configures the I2C controller as master with specified GPIO pins,
 * pull-up resistors, and clock speed.
 */
void i2c_master_init() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,        // SDA
        .sda_pullup_en = GPIO_PULLUP_ENABLE,    // Enable internal pull-up
        .scl_io_num = I2C_MASTER_SCL_IO,        // SCL
        .scl_pullup_en = GPIO_PULLUP_ENABLE,    // Enable internal pull-up
        .master.clk_speed = I2C_MASTER_FREQ_HZ, // clock speed
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}
/**
 * @brief Scan I2C bus for connected devices
 * 
 * Scans all possible I2C addresses (1-127) and reports found devices.
 * Uses I2C write operation to detect device presence.
 */
void i2c_scanner() {
    int devices_found = 0;
    for (int address = 1; address < 127; address++) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);
        esp_err_t espRc = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 10 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);

        if (espRc == ESP_OK) {
            printf("The device was found at the address: 0x%02x\n", address);
            devices_found++;
        }
    }
    if (devices_found == 0) {
        printf("No devices found\n");
    } else {
        printf("Devices found: %d\n", devices_found);
    }
}

void app_main() {
    i2c_master_init();  // Initialize I2C
    
    // Continuous scanning loop
    while (1){
        i2c_scanner();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
