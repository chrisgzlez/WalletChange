#opciones de compilación, muestra todos los warnings (-Wall)
CC=gcc -Wall
#si incluye una librería estándar, en este caso la matemática (fichero libm.a)
#todas tienen el formato de fichero libNOMBRE.a
#y al incluirla en el compilador se pone -lNOMBRE
#si no hay librerías adicionales, se elimina esta línea
#carpeta de las librerias estaticas propias
LIBS_FILES_DIR=.
#opciones de compilacion, indica donde estan nuestra libreria estatica
#si es una libreria estandar, no es necesario
LIBRARIES= -L $(LIBS_FILES_DIR)
#si incluye librerias, se cambia la m por el nombre de la libreria
LIBS = -lm
#carpeta de las cabeceras (si están en la actual, ponemos .)
HEADER_FILES_DIR = .
#opciones de compilación, indica dónde están los archivos .h
INCLUDES = -I $(HEADER_FILES_DIR)
#nombre del ejecutable o archivo de salida
OUTPUT = executable
#ficheros .h. Si hay varios, se precede cada uno con $(HEADER_FILES_DIR)/
HEADERS = $(HEADER_FILES_DIR)/TAD/vectordinamico.h $(HEADER_FILES_DIR)/utilities.h $(HEADER_FILES_DIR)/wallet.h 

#FUENTES: todos los archivos .c necesarios separados por espacios
# Ejemplo:  SRCS = main.c potencia.c factorial.c
SRCS = main.c $(HEADER_FILES_DIR)/TAD/vectordinamico.c $(HEADER_FILES_DIR)/utilities.c $(HEADER_FILES_DIR)/wallet.c
#ficheros .o: todos los .o con un análogo .c en SRCS
OBJS = $(SRCS:.c=.o)

#REGLA 1: genera el ejecutable, dependencia de los .o
#si no hay librerías adicionales, no existe la variable $(LIBS),
#por lo que se elimina $(LIBS) de la regla siguiente
#$(LIBRARIES) es para las librerias estaticas
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIBS)

#REGLA 2: genera los .o cuando es necesario, dependencia de los .c y .h
#sólo genera los .o necesarios por cambios en los .c o .h
#$@ es el nombre del fichero que se genera con la regla (.o)
#$< es el nombre del primer prerrequisito (archivo .c cuyo .o se está generando)
%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)

# REGLA 3: borra el ejecutable (prerrequisito: clean)
cleanall: clean
	rm -f $(OUTPUT)

# REGLA 4: borra los ficheros .o y los de backup (terminan en ~)
clean:
	rm -f *.o *~ && rm -f $(HEADER_FILES_DIR)/TAD/*.o *~
