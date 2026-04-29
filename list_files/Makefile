# Variables del compilador
CC = cc
CFLAGS = -Wall -O2

# 1. EL NOMBRE DE TU COMANDO
TARGET = list_files

# 2. LA CARPETA DONDE TOCA INSTALARLO (Estándar en MINIX)
PREFIX = /usr
BINDIR = $(PREFIX)/bin

# Tus archivos a compilar
OBJS = main.o executor.o fs_engine.o input_handler.o nav_state.o ui_core.o

# Regla por defecto
all: $(TARGET)

# Compilar el programa
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Instalar en el sistema
install: $(TARGET)
	mkdir -p $(BINDIR)
	cp $(TARGET) $(BINDIR)/
	chmod 755 $(BINDIR)/$(TARGET)
	@echo "¡Instalación completada! Ahora puedes usar el comando: $(TARGET)"