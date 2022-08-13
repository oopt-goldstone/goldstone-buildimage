CNETDIR = $(SDK)/sdklt/bcmcnet
KNETDIR = $(SDK)/sdklt/linux/knet
SRCIDIR = $(CNETDIR)/include/bcmcnet
DSTIDIR = $(KNETDIR)/include/bcmcnet
R = 2>/dev/null

$(shell rm -rf $(DSTIDIR) && mkdir -p $(DSTIDIR))
$(shell	ln -s $(KNETDIR)/ngknet_dep.h $(DSTIDIR)/bcmcnet_dep.h $(R))
$(shell	ln -s $(KNETDIR)/ngknet_buff.h $(DSTIDIR)/bcmcnet_buff.h $(R))
$(shell	ln -s $(SRCIDIR)/bcmcnet_types.h $(DSTIDIR) $(R))
$(shell	ln -s $(SRCIDIR)/bcmcnet_internal.h $(DSTIDIR) $(R))
$(shell	ln -s $(SRCIDIR)/bcmcnet_core.h $(DSTIDIR) $(R))
$(shell	ln -s $(SRCIDIR)/bcmcnet_dev.h $(DSTIDIR) $(R))
$(shell	ln -s $(SRCIDIR)/bcmcnet_rxtx.h $(DSTIDIR) $(R))
$(shell ln -s $(SRCIDIR)/bcmcnet_cmicd.h $(DSTIDIR) $(R))
$(shell	ln -s $(SRCIDIR)/bcmcnet_cmicx.h $(DSTIDIR) $(R))
$(shell	ln -s $(SRCIDIR)/bcmcnet_cmicr.h $(DSTIDIR) $(R))
$(shell	ln -s $(SRCIDIR)/bcmcnet_cmicr_acc.h $(DSTIDIR) $(R))
$(shell	ln -s $(CNETDIR)/chip/*/*attach.c $(KNETDIR) $(R))
$(shell	ln -s $(CNETDIR)/hmi/cmicd/*.c $(KNETDIR) $(R))
$(shell	ln -s $(CNETDIR)/hmi/cmicx/*.c $(KNETDIR) $(R))
$(shell	ln -s $(CNETDIR)/hmi/cmicr/*.c $(KNETDIR) $(R))
$(shell	ln -s $(CNETDIR)/main/bcmcnet_core.c $(KNETDIR) $(R))
$(shell	ln -s $(CNETDIR)/main/bcmcnet_dev.c $(KNETDIR) $(R))
$(shell	ln -s $(CNETDIR)/main/bcmcnet_rxtx.c $(KNETDIR) $(R))

export MODULE_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
export KBUILD_EXTRA_SYMBOLS := $(abspath ../linux-ngbde/Module.symvers)
include ../common.mk
