MAKEFLAGS += -s

MODULES := bios

.PHONY: all clean $(MODULES)

all : $(MODULES)

$(MODULES):
	$(MAKE) -C $@ DEBUG=$(DEBUG)

clean:
	@for module in $(MODULES); do \
		$(MAKE) -C $$module clean; \
	done
