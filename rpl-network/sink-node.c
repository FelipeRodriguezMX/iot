#include "contiki.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"

#include "sys/log.h"
#define LOG_MODULE "SINK NODE APP"
#define LOG_LEVEL LOG_LEVEL_INFO

static struct simple_udp_connection connection;

PROCESS(sink_node, "sink node");
AUTOSTART_PROCESSES(&sink_node);

static void rx_callback(struct simple_udp_connection *client_connection, 
    const uip_ipaddr_t *sender_address,
    uint16_t sender_port,
    const uip_ipaddr_t *reciever_address,
    uint16_t reciever_port,
    const uint8_t *data,
    uint16_t data_length){
    LOG_INFO("Recievied packet: '%.*s' from node ", data_length, (char *) data);
    LOG_INFO_6ADDR(sender_address);
    LOG_INFO_("\n");
}

PROCESS_THREAD(sink_node, ev, data){
    PROCESS_BEGIN();

    NETSTACK_ROUTING.root_start();
    simple_udp_register(&connection, SERVER_PORT, NULL, CLIENTE_PORT, rx_callback);

    PROCESS_END();
}