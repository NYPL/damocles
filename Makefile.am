
.DELETE_ON_ERROR:


# TODO: objects in build directory


HAS_DLOG_SO_P := $(shell test -f bin/dlog-make.so && test -f bin/dlog-r.so && echo yes)
 ifeq ($(HAS_DLOG_SO_P), yes)
load bin/dlog-make.so
 endif


export NYPL_RAW_DATA_LOC=/home/tony/data

export NONEXTANTENVVAR=hi


CC 			:= @CC@

LOG_FILE 	:= build.log

ISO8601D	:= $(shell date -I)
ISO8601DT	:= $(shell date -Iseconds)
CY          := $(shell date +%Y)

# EZPROXY_LOGS := $(realpath $(NYPL_RAW_DATA_LOC)


# ----------------------------------------------------------------------- #
### Putting together all the targets 								  	###

 ifneq ($(HAS_DLOG_SO_P), yes)

all: begin bin/dlog-make.so bin/dlog-r.so end

 else

all: begin bin/dlog-make.so bin/dlog-r.so debug end

 endif
# ----------------------------------------------------------------------- #


bin/dlog-make.so: src/dlog.c
	@ echo bin thing
	$(CC) -shared -fPIC -o $@ $< -lsystemd -DFOR_GNU_MAKE -DLOG_FILE=\"$(LOG_FILE)\"


bin/dlog-r.so: src/dlog.c
	@ echo bin thing
	R CMD SHLIB -c -o $@ $< -lsystemd



.PHONY: debug
debug:
	$(dlog hi, hi)
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
	@ echo "cleaning"
	rm -rf build bin

.PHONY: mrproper
mrproper:
	rm -rf autom4te.cache/
	rm -f config.log Makefile Makefile.in config.status configure configure~

