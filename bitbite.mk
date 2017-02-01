BITBITE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
BITBITE_SRC := $(BITBITE_DIR)/bitbuffer.c
BITBITE_INC := -I$(BITBITE_DIR)
$(info Using bitbite $(BITBITE_DIR))
