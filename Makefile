.PHONY: all clean install uninstall

# Variables #
CC = gcc
BIN = caja_nod32.so
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

LIBDIR=/usr/lib/x86_64-linux-gnu

# Flags pour le Compilateur et l'editeur de liens #

CFLAGS = -fPIC -g \
	$(shell pkg-config --cflags libcaja-extension)

LFLAGS = -shared \
	$(shell pkg-config --libs libcaja-extension)

all: $(BIN)

%.o: %.c *.h
	$(CC) -c $< $(CFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN): $(OBJ)
	$(CC) -s $^ $(LFLAGS) -o $@

install: all
	mkdir -p $(LIBDIR)/caja/extensions-2.0/
	sudo cp $(BIN) $(LIBDIR)/caja/extensions-2.0/
	sudo cp nod32.png /usr/share/icons/Adwaita/64x64/devices/nod32.png
	sudo update-icon-caches /usr/share/icons/Adwaita/

uninstall: all
	sudo rm -f $(LIBDIR)/caja/extensions-2.0/$(BIN)
	sudo rm /usr/share/icons/Adwaita/64x64/devices/nod32.png
	sudo update-icon-caches /usr/share/icons/Adwaita/

# Nettoyage #
clean:
	rm -f $(OBJ) $(BIN)
