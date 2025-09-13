#include <stdio.h>
#include "pico/stdlib.h"
#include "tusb.h"
#include "../utils/src/button.h"
#include "../utils/src/macros.h"
#include "../utils/src/bargraph.h"
#include "defs.h"

struct Bargraph bargraphA;
struct Bargraph bargraphB;

void turn_on(){
    gpio_put(LED_PIN, 1);   
}

void turn_off(){
    gpio_put(LED_PIN, 0);  
}

void click(){  
    printf("Click!\0");
}

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_set_pulls(BUTTON_PIN, false, true);
    
    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    
    struct Button buttons[2];
    init_buttons(buttons, ARRAY_LENGTH(buttons)); 
    
    buttons[0].pin = BUTTON_PIN;
    buttons[0].on_down = turn_on;
    buttons[0].on_up = turn_off;
    buttons[0].on_click = click;
        
    init_bargraph(&bargraphA, BAR_A_PIN_LIST, 5);
    set_bargraph_value(&bargraphA, 5);
    
    init_bargraph(&bargraphB, BAR_B_PIN_LIST, 5);
    set_bargraph_value(&bargraphB, 5);    
        
    while (true) {
        process_button_events(buttons, ARRAY_LENGTH(buttons));
        
        while(tud_cdc_available()){
            static char message[MAX_MESSAGE_LENGTH];
            static unsigned int message_pos = 0;
            char byteIn = getchar();
            
            if (byteIn != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1)) {
                message[message_pos] = byteIn;
                message_pos++;
            }
            else {
                message[message_pos] = '\0';
                if (strcmp(message,"red-on") == 0){
                    gpio_put(RED_PIN, 1);                     
                }                
                if (strcmp(message,"red-off") == 0){
                    gpio_put(RED_PIN, 0);                     
                }
                if (strcmp(message,"green-on") == 0){
                    gpio_put(GREEN_PIN, 1);                     
                }                
                if (strcmp(message,"green-off") == 0){
                    gpio_put(GREEN_PIN, 0);                     
                }
                if (strcmp(message,"blue-on") == 0){
                    gpio_put(BLUE_PIN, 1);                     
                }                
                if (strcmp(message,"blue-off") == 0){
                    gpio_put(BLUE_PIN, 0);                     
                }
                if (strcmp(message,"inca") == 0){
                    inc_bargraph(&bargraphA);
                }                
                if (strcmp(message,"deca") == 0){
                    dec_bargraph(&bargraphA);
                }                   
                if (strcmp(message,"incb") == 0){
                    inc_bargraph(&bargraphB);
                }                
                if (strcmp(message,"decb") == 0){
                    dec_bargraph(&bargraphB);
                } 
                if (strcmp(message,"aoff") == 0){
                    turn_off_bargraph(&bargraphA);
                }
                if (strcmp(message,"aon") == 0){
                    turn_on_bargraph(&bargraphA);
                }
                if (strcmp(message,"a2b") == 0){
                    set_bargraph_value(&bargraphB, get_bargraph_value(&bargraphA));
                } 
                if (strcmp(message,"b2a") == 0){
                    set_bargraph_value(&bargraphA, get_bargraph_value(&bargraphB));
                }  
                
                turn_on();
                printf("%s", message);
                turn_off();
                message_pos = 0;
            }
        }        
    }
}
