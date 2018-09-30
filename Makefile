CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra
LDFLAGS =
SOURCES = copymaster.c
HEADERS = 
OBJDIR = build
EXECUTABLE = copymaster

_OBJ = $(SOURCES:.c=.o)
_DEPS = $(HEADERS)

# DEPS = $(patsubst %,./%,$(_DEPS))
DEPS = $(_DEPS)
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXECUTABLE): $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)

directories:
	mkdir -p $(OBJDIR)
	
all: $(EXECUTABLE)

clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)
	if [ -d $(OBJDIR) ]; then rmdir $(OBJDIR); fi
	
.PHONY: all clean
