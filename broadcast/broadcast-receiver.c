#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"

#include <string.h>
#include "sys/log.h"

#define LOG_MODULE "Broadcase Sending App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define WAIT_INTERVAL (8 *CLOCK_SECOND)

PROCESS(broadcast_reciver, "boradcast reciver example");
AUTOSTART_PROCESSES(&broadcast_reciver);

void input_callback(const void *data, uint16_t len, const linkaddr_t *source, const linkaddr_t *destination){
    if(len == sizeof(unsigned)){
        unsigned counter;
        memcpy(&counter,data, sizeof(counter));

        LOG_INFO("recived %u from ", counter);
        LOG_INFO_LLADDR(source);
        LOG_INFO("\n");
    }
}

PROCESS_THREAD(broadcast_reciver, ev, data){
    static struct etimer periodic_timer;
    static unsigned counter = 0;
    
    PROCESS_BEGIN();

    nullnet_buf = (uint8_t *) counter;
    nullnet_len = sizeof(counter);
    nullnet_set_input_callback(input_callback);

    etimer_set(&periodic_timer, WAIT_INTERVAL);
    while(1){
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
        LOG_INFO("Waiting for data.. \n");
        etimer_reset(&periodic_timer);
    }

    PROCESS_END();
}
