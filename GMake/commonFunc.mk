#(call source-to-object,source files)
source-to-object = $(subst .c,.o,$(filter %.c,$1))


# subdirectory
subdirectory = $(patsubst $(SOURCE_DIR)/%/module.mk,%, \
		 $(word 		
		   $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

source-dir-bin-dir = $(addprefix $(BINARY_DIR)/,$1)


