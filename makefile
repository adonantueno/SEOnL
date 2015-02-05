#Variables

CXX = g++

DIRECTORIO = librerias
LIB_1= estructurasSEOnL
LIB_2 = datosMensajesSEOnL
LIB_3 = archivosSEOnL

LIBS = $(DIRECTORIO)/$(LIB_1).o $(DIRECTORIO)/$(LIB_2).o $(DIRECTORIO)/$(LIB_3).o

SERVER = servidor.cpp
CLIENT = cliente.cpp

#Ejecuta mas alla de que crea que esta actualizado
.PHONY: cliente servidor libs all


#Reglas
libs:
	$(MAKE) -C $(DIRECTORIO) crear

servidor:
	$(CXX) $(LIBS) $(SERVER) -o servidor

cliente:
	$(CXX) $(LIBS) $(CLIENT) -o cliente 

all: libs servidor cliente


clean:
	rm *.o *.~ *~
