#include "contiki.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"

#include "sys/log.h"
#define LOG_MODULE "SENSOR NODE APP"
#define LOG_LEVEL LOG_LEVEL_INFO

#define SEND_INTERVAL (10 * CLOCK_SECOND)



static struct simple_udp_connection connection;

PROCESS(sensor_node, "send node");
AUTOSTART_PROCESSES(&sensor_node);

PROCESS_THREAD(sensor_node, ev, data){
    static struct etimer perodic_timer;
    static unsigned counter;
    static char buffer[32];
    uip_ipaddr_t server_address;

    PROCESS_BEGIN();

    simple_udp_register(&connection, CLIENTE_PORT, NULL, SERVER_PORT, NULL);
    etimer_set(&perodic_timer, SEND_INTERVAL);

    while(1){
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&perodic_timer));
        uint8_t is_node_reachable = NETSTACK_ROUTING.node_is_reachable();
        uint8_t got_server_address = NETSTACK_ROUTING.get_root_ipaddr(&server_address);

        if(is_node_reachable && got_server_address){
            LOG_INFO("Sending request %u to ", counter);
            LOG_INFO_6ADDR(&server_address);
            LOG_INFO("\n");

            snprintf(buffer, sizeof(buffer), "Packet No, %d", counter++);
            simple_udp_sendto(&connection, buffer, strlen(buffer), &server_address);
        }else{
            LOG_INFO("Root not reachable yet. \n");
        }
        etimer_reset(&perodic_timer);
    }
    PROCESS_END();
}