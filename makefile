#Variables

CXX = g++
CXXFLAGS = -std=c++11

DIRECTORIO = librerias
LIB_1= estructurasSEOnL
LIB_2 = datosMensajesSEOnL

LIBS = $(DIRECTORIO)/$(LIB_1).o $(DIRECTORIO)/$(LIB_2).o

SERVER = servidor.cpp
CLIENT = cliente.cpp

#Ejecuta mas alla de que crea que esta actualizado
.PHONY: cliente servidor libs all


#Reglas
libs:
	$(MAKE) -C $(DIRECTORIO) crear

servidor:
	$(CXX) $(LIBS) $(SERVER) -o servidor $(CXXFLAGS)

cliente:
	$(CXX) $(LIBS) $(CLIENT) -o cliente  $(CXXFLAGS)

all: libs servidor cliente


clean:
	rm *.o *.~ *~
