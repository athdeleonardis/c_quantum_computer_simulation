CC=gcc
CFLAGS=-Wall -std=c99 -lm
SRC=src
SRCS=$(wildcard $(SRC)/*.c)
TST=test
TSTS_SRC=$(wildcard $(SRC)/$(TST)/*.c)
TSTS=$(patsubst $(SRC)/$(TST)/%.c, $(BLD)/%, $(TSTS_SRC))
OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BLD=out

.PHONY: all prebuild clean tests

all: prebuild $(OBJS) tests

prebuild:
	mkdir -p $(OBJ) $(BLD)

tests: prebuild $(TSTS)

$(BLD)/%: $(SRC)/$(TST)/%.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -r -f $(OBJ) $(BLD)
