IAS=heuri

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
	cd $(notdir $@) && make debug
rel/%:
	cd $(notdir $@) && make release
cln/%:
	cd $(notdir $@) && make clean
