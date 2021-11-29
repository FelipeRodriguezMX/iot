CONTIKI-PROJECT = coap-server
all: $(CONTIKI-PROJECT)

MODULES_REL += ./resources
PROJECT_SOURCEFILES += virtual-sensor.c

CONTIKI = ../..

#INCLUDE COAP IMPLEMENTATION
include $(CONTIKI)/Makefile.dir-variables
MODULES += $(CONTIKI_NG_APP_LAYER_DIR)/coap

include $(CONTIKI)/Makefile.include