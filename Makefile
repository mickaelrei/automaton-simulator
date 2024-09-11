BIN := ./bin

all: $(BIN) $(BIN)/main

$(BIN):
	@if [ ! -d $(BIN) ]; then mkdir $(BIN); fi

$(BIN)/main: automaton.hpp main.cpp
	$(CXX) main.cpp -o $(BIN)/main

clean:
	@if [ -d $(BIN) ]; then rm -rf $(BIN); fi