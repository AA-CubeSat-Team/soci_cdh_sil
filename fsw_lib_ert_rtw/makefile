CC = gcc
CFLAGS = -Wall
LDFLAGS =

OBJFILES = sil_main.o fsw_lib.o fsw_lib_data.o #change this line
TARGET = sil_main
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~