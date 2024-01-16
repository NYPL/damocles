
.DELETE_ON_ERROR:


HAS_DLOG_SO_P := $(shell test -f bin/dlog-make.so && test -f bin/dlog-r.so && echo yes)
ifeq ($(HAS_DLOG_SO_P), yes)
load bin/dlog-make.so
endif


export NYPL_RAW_DATA_LOC=/home/tony/data

export NONEXTANTENVVAR=hi


CC := gcc

ISO8601D	:= $(shell date -I)
ISO8601DT	:= $(shell date -Iseconds)
CY          := $(shell date +%Y)

# EZPROXY_LOGS := $(realpath $(NYPL_RAW_DATA_LOC)


# ----------------------------------------------------------------------- #
### Putting together all the targets 								  	###

ifneq ($(HAS_DLOG_SO_P), yes)

all: begin bin/dlog-make.so bin/dlog-r.so end

else

all: begin debug end

endif
# ----------------------------------------------------------------------- #



.PHONY: debug
debug:
	@ echo $(ISO8601D)
	@ echo $(ISO8601DT)
	@ echo $(CY)
	@ ./test.sh
	@ echo HAS MAKE SO: $(HAS_DLOG_SO_P)

# TODO: do better with necessary directories
.PHONY: begin
begin:
	@ echo starting
	@ mkdir -p build
	@ mkdir -p bin

.PHONY: end
end:
	@ echo ending

# TODO: PARAMETERIZE!

.PHONY: clean
clean:
	@ rm -rf build bin

bin/dlog-make.so: src/dlog.c
	@ echo bin thing
	$(CC) -shared -fPIC -o $@ $< -lsystemd -DFOR_GNU_MAKE

bin/dlog-r.so: src/dlog.c
	@ echo bin thing
	R CMD SHLIB -c -o $@ $< -lsystemd
