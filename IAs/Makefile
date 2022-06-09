IAS=heuri montecarlo

#DEBUG1
DBGIAS = $(addprefix dbg/, $(IAS))
#RELEASE
RELIAS = $(addprefix rel/, $(IAS))
#CLEAN
CLNIAS = $(addprefix cln/, $(IAS))

release : $(RELIAS)
debug : $(DBGIAS)
clean: $(CLNIAS)

dbg/%:
	cd $(notdir $@) && $(MAKE) debug
rel/%:
	cd $(notdir $@) && $(MAKE) release
cln/%:
	cd $(notdir $@) && $(MAKE) clean
