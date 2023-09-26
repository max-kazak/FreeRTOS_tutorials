// Use only 1 core
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Pins
static const int led_pin = LED_BUILTIN;

// Task: blink an LED
void toggleLED(void* parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // vTask is none blocking and works in RTOS
    digiatlWrite(led_pin, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);

  // task to run forever
  xTaskCreatePinnedToCore(        // Use xTaskCreate in vanilla RTOS, in esp-idf it will assign task to both cores
    toggleLED,    // task to run
    "Toggle LED", // name of the task
    1024,         // Stack size (bytes in ESP32, words in FreeRTOS)
    NULL,         // parameeters
    1,            // task priority (between 0 and config MAX_PRIORITIES, 24 by default)
    NULL,         // task handle (to handle this task from other tasks)
    app_cpu       // run on core 1
    ); 

    // Note: for vanilla RTOS you want to call vTaskStartScheduler() in main afetr setting up your tasks.
    // In arduino framework for esp32 setup and loop exist in their own task aside from main program entrypoint,
    // so scheduler is already started and new task is created right after xTaskCreate


}

void loop() {
  // loop and setup are running in its own task with priority 1

}
