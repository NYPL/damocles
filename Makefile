


export NYPL_RAW_DATA_LOC=/home/tony/data

export NONEXTANTENVVAR=hi


ISO8601D	:= $(shell date -I)
ISO8601DT	:= $(shell date -Iseconds)
CY          := $(shell date +%Y)

# EZPROXY_LOGS := $(realpath $(NYPL_RAW_DATA_LOC)


all: debug



.PHONY: debug
debug:
	@ echo $(ISO8601D)
	@ echo $(ISO8601DT)
	@ echo $(CY)
	@ ./test.sh

