CC=gcc
CFLAGS=-Wall -Wextra -g
LIBS=
SRC=src/
BUILD=build/
BIN=bin/

DEPS=  $(BUILD)toylang.o $(BUILD)ast.o $(BUILD)lexer.o $(BUILD)regexp.o $(BUILD)string_view.o $(BUILD)toylang_lexer.o $(BUILD)toylang_parser.o
all: init lines toylang
lines:
	@echo "C:"
	@wc -l $$( find -wholename './*.[hc]') | tail -n 1
$(BUILD)%.o: $(SRC)%.c
	 $(CC) $(CFLAGS) -o $@ $^ -c
$(BIN)toylang: $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
toylang: $(BIN)toylang
clean:
	rm -rf $(BIN)*
	rm -rf $(BUILD)*
install:
	cp $(BIN)toylang /bin/
init:
	