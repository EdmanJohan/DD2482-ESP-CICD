AMAZON_FREERTOS_ABSTRACTIONS_DIR := ../../../../../libraries/abstractions
AMAZON_FREERTOS_3RD_PARTY_DIR := ../../../../../libraries/3rdparty
AMAZON_FREERTOS_PORTS_DIR := ../../ports

COMPONENT_SRCDIRS := $(AMAZON_FREERTOS_ABSTRACTIONS_DIR)/secure_sockets/lwip

COMPONENT_ADD_INCLUDEDIRS := include

ifdef AMAZON_FREERTOS_ENABLE_UNIT_TEST
COMPONENT_SRCDIRS += $(AMAZON_FREERTOS_ABSTRACTIONS_DIR)/secure_sockets/test
COMPONENT_PRIV_INCLUDEDIRS += $(AMAZON_FREERTOS_3RD_PARTY_DIR)/unity/extras/fixture/src
tests/common/secure_sockets/aws_test_tcp.o: CFLAGS+=-Wno-uninitialized
endif
