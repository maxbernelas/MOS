# Retrieve the directory containing this makefile
ROOT_DIR := $(shell dirname $(lastword $(MAKEFILE_LIST)))

# List of object files to build in this directory
OBJ += $(ROOT_DIR)/handlers.o $(ROOT_DIR)/entry.o $(ROOT_DIR)/irq.o            \
       $(ROOT_DIR)/string.o $(ROOT_DIR)/list.o $(ROOT_DIR)/kalloc.o            \
       $(ROOT_DIR)/sched.o
