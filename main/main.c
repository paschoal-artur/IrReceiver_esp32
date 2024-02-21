#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define IR_RECEIVER_PIN GPIO_NUM_4 //!Will be configured as input

void emitter_and_receiver_config (void *pvParameters)
{
    //! Configure IR receiver as input
    esp_rom_gpio_pad_select_gpio(IR_RECEIVER_PIN);
    gpio_set_direction(IR_RECEIVER_PIN, GPIO_MODE_INPUT);

}

void ir_receive_task (void *pvParameters)
{
    int last_state = gpio_get_level(IR_RECEIVER_PIN);
    while (1)
    {
        int current_state = gpio_get_level(IR_RECEIVER_PIN);

        if(current_state != last_state)
        {
            printf("IR Receiver Signal: %d\n", current_state);
        }
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


void app_main(void)
{
    emitter_and_receiver_config(NULL);

    //! Create tasks
    xTaskCreate(ir_receive_task, "ir_receive_task", 2048, NULL, 5, NULL);
}
