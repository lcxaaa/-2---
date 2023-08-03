CC = gcc
CFLAGS = -lpthread -lssl -lcrypto -I./include/

TARGET  = ./app
OBJ_DIR = ./obj
SRC_DIR = ./source
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, %.o, $(SRC))

VPATH = $(SRC_DIR)
vpath %.o $(OBJ_DIR)

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) -g -o $@ $(addprefix $(OBJ_DIR)/, $(OBJECTS)) $(CFLAGS)

%.o : %.c
	$(CC) -c $< -o $(OBJ_DIR)/$@

.PHONY : clean
clean:
	rm -rf $(TARGET) $(OBJ_DIR)/*.o ./*.o
