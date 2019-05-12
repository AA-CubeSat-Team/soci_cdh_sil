CC = gcc
CFLAGS = -Wall
LDFLAGS =

OBJFILES = ert_main.o target_generation_lib0.o #change this line
TARGET = ert_main
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~