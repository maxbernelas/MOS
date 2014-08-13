# Retrieve the directory containing this makefile
ROOT_DIR := $(shell dirname $(lastword $(MAKEFILE_LIST)))

# List of object files to build in this directory
OBJ += $(ROOT_DIR)/vectors.o $(ROOT_DIR)/svc.o $(ROOT_DIR)/utils.o             \
       $(ROOT_DIR)/nvic.o
