CC = gcc
SRC_DIR = ./src
BIN_DIR = ./bin

all: server client

# server build
server: server.o server_helper.o server_game.o
	$(CC) -o server $(BIN_DIR)/server.o $(BIN_DIR)/server_helper.o $(BIN_DIR)/server_game.o -lpthread -lm

server.o:
	$(CC) -o $(BIN_DIR)/server.o -c $(SRC_DIR)/server.c

server_helper.o:
	$(CC) -o $(BIN_DIR)/server_helper.o -c $(SRC_DIR)/helpers/server_helper.c

server_game.o:
	$(CC) -o $(BIN_DIR)/server_game.o -c $(SRC_DIR)/server/server_game.c

# client build
client: client.o client_helper.o client_game.o
	$(CC) -o client $(BIN_DIR)/client.o $(BIN_DIR)/client_helper.o $(BIN_DIR)/client_game.o -lpthread -lncurses

client.o:
	$(CC) -o $(BIN_DIR)/client.o -c $(SRC_DIR)/client.c

client_helper.o:
	$(CC) -o $(BIN_DIR)/client_helper.o -c $(SRC_DIR)/helpers/client_helper.c

client_game.o:
	$(CC) -o $(BIN_DIR)/client_game.o -c $(SRC_DIR)/client/client_game.c

# client_test build
client_test: client_test.o client_game.o
	$(CC) -o client_test $(BIN_DIR)/client_test.o $(BIN_DIR)/client_game.o -lncurses -lm

client_test.o:
	$(CC) -o $(BIN_DIR)/client_test.o -c $(SRC_DIR)/client_test.c
