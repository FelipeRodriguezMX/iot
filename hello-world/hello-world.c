#include "contiki.h"

#include <stdio.h>

PROCESS(hello_world, "hello world");
AUTOSTART_PROCESSES(&hello_world);

PROCESS_THREAD(hello_world, ev, data){
    PROCESS_BEGIN();

    printf("hello world!\n");
    
    PROCESS_END();
}