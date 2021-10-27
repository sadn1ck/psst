CXX = gcc
CXX_FLAGS = -Wall -Werror

SRC = src/*.c

BUILD = out
EXEC = psst

all: build run

run:
	@echo "exec: ./$(BUILD)/$(EXEC)"
	@./$(BUILD)/$(EXEC)

build:
	@echo "prebuild: mkdir -p $(BUILD)"
	@mkdir -p $(BUILD)
	@echo "build: $(CXX) $(SRC) $(CXX_FLAGS) -o ./$(BUILD)/$(EXEC)"
	@$(CXX) $(SRC) $(CXX_FLAGS) -o ./$(BUILD)/$(EXEC)

clean:
	@echo "clean: rm -r ./$(BUILD)"
	@rm -r ./$(BUILD)