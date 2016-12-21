
###############################################################################
# Path
CC  = $(CROSS_COMPILE)gcc
AR  = $(CROSS_COMPILE)ar

DESTDIR		:= $(CURDIR)/out

PREFIX		:= /system
BINDIR		:= /system/sbin
BINDIR_CONF	:= /system/sbin
INITRCDIR   := /etc/init.d


SOCK_PATH   := /var/log

###############################################################################
# Compile

CC	:= $(CROSS_COMPILE)gcc

CFLAGS	:= $(EXTRA_CFLAGS)
LDFLAGS	:= $(EXTRA_LDFLAGS)

###############################################################################
# Options

###############################################################################
# board

#BOARD	:= 
CFLAGS	+= -DBOARD_$(BOARD)

###############################################################################
# Target rules

CFLAGS	+= -Wall
CFLAGS	+= -Iinc -D_REENTRANT -DCONFIG_FILE_PATH=\"$(BINDIR_CONF)/$(CONFIG_FILE)\"
CFLAGS	+= -DLOGD_SOCK=\"$(SOCK_PATH)/LOGD\"
LDFLAGS	+= -lpthread -liniparser
#LDFLAGS	+= -lm -lnsl -loauthcpp

OBJS	:= src/wdprog.o src/watchdog_util.o 


define checkver
ifeq ($$(VER),0)
	$$(error VER is not found, please define VER)
endif
endef

DEBUG_MODE  ?= 0
VER   ?= sbin

WORK_PATH   := /system/$(VER)




APP	:= wdprog3

all: all-before	$(APP)

all-before:
	$(eval $(call checkboard))

$(APP):		$(OBJS)
	$(Q)$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

install:	install-binary

install-binary:	$(APP)
	$(Q)$(call check_install_dir, $(DESTDIR)$(WORK_PATH))
	$(Q)fakeroot cp -v $(APP) $(DESTDIR)$(WORK_PATH)/$(APP)
	$(Q)fakeroot cp -v $(APP) $(DESTDIR)$(BINDIR)/$(APP)


clean:
	$(Q)rm -vrf $(APP) $(OBJS) \
		$(CONFIG_FILE)

uninstall:
	$(Q)rm -vrf $(DESTDIR)$(BINDIR)/$(APP)
	$(Q)rm -vrf $(DESTDIR)$(BINDIR)/$(CONFIG_FILE)


###############################################################################
# Extra rules
$(CONFIG_FILE):		src/$(CONFIG_FILE).in
	$(Q)echo Create $@ ...
	$(Q)cp -v $^ $@
	$(Q)#sed "s,@app.path@,$(BINDIR)/$(APP),g" $^ > $@
	$(Q)#chmod 755 $@
	
###############################################################################
# Functions

define check_install_dir
	if [ ! -d "$1" ]; then mkdir -p $1; fi
endef

define checkboard
ifeq ($(BOARD),)
$$(error BOARD is not found, BOARD=NEO_W100/NEO_W200)
endif
endef

