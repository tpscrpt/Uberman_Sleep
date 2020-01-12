CC      := gcc
BIN     := ./.bin
OBJ     := ./.obj
INCLUDE := ./include
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.c)
OBJS    := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
CFLAGS  :=-I$(INCLUDE)
LDLIBS  := -lm

TITANIC := ./experiments/titanic/src/titanic.c

titanic: $(OBJS) | $(BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TITANIC) $^ -o $(BIN)/$@ $(LDLIBS)


$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@


$(BIN) $(OBJ):
	$(MKDIR) $@

