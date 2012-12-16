include ../common.mk
sources = main.c MathHelper.c
all: $(subst .c,.o,$(sources))

%.o: %.c
	$(CC) -I../includes -c $< -o ../$(BIN_DIR)/$@


main: ../$(BIN_DIR)/main.o ../$(BIN_DIR)/MathHelper.o
	$(CC) -o ../$(BIN_DIR)/$@ $^

clean:
	-rm -r ../$(BIN_DIR)/*.o
