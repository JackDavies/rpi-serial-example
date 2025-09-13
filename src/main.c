#include <stdio.h>
#include "pico/stdlib.h"
#include "../utils/src/button.h"
#include "../utils/src/macros.h"
#include "defs.h"

void turn_on(){
    gpio_put(LED_PIN, 1);    
}

void turn_off(){
    gpio_put(LED_PIN, 0);    
}

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_set_pulls(BUTTON_PIN, false, true);
    
    struct Button buttons[1];
    init_buttons(buttons, ARRAY_LENGTH(buttons)); 
    
    buttons[0].pin = BUTTON_PIN;
    buttons[0].on_down = turn_on;
    buttons[0].on_up = turn_off;
    
    while (true) {
        process_button_events(buttons, ARRAY_LENGTH(buttons));
    }
}
