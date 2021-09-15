#include "contiki.h"
#include "sys/etimer.h"
#include <stdio.h>
#include "virtual-sensor.h"

PROCESS(sensor_node, "sensor node");
AUTOSTART_PROCESSES(&sensor_node);

static struct etimer timer;

PROCESS_THREAD(sensor_node, ev, data){
    PROCESS_BEGIN();

    etimer_set(&timer, 5 *CLOCK_SECOND);
    while(1){
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
        
        float tempature = read_tempature();
        float humidity = read_humidity();

        printf("temperature readinf: %.2f C\n", tempature);
        printf("humidity reading: %.2f %%\n", humidity);

        etimer_reset(&timer);
    }

    PROCESS_END();
}