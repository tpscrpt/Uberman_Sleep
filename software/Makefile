CC      := gcc
BIN     := ./.bin
OBJ     := ./.obj
INCLUDE := ./include
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.c)
OBJS    := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
CFLAGS  :=-I$(INCLUDE)
LDLIBS  := -lm

TITANIC_LOGREG := ./experiments/titanic/src/titanic_logreg.c
TITANIC_MLP := ./experiments/titanic/src/titanic_mlp.c

titanic_logreg: $(OBJS) | $(BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TITANIC_LOGREG) $^ -o $(BIN)/$@ $(LDLIBS)

titanic_mlp: $(OBJS) | $(BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TITANIC_MLP) -g $^ -o $(BIN)/$@ $(LDLIBS)


$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@


$(BIN) $(OBJ):
	$(MKDIR) $@

