.PHONY: clean run

SRC = src/
EXECUTABLE = othelloAI

all:
	cd $(SRC); make; mv $(EXECUTABLE) ..;

run:
	./$(EXECUTABLE);

clean:
	rm $(EXECUTABLE); cd $(SRC); make clean;
