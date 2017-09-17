CC=g++
UNAME_S := $(shell uname -s)
ifeq ($(uname_S), Darwin)
	LIBS=-framework OpenGL -lglut
else
	LIBS=-lglut -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW
endif
MKDIR_P = mkdir -p

all: dirs sierpinski_gasket draw_sphere

sierpinski_gasket: sierpinski_gasket.cpp
	$(CC) $< -o bin/$@ $(LIBS)

draw_sphere: draw_sphere.cpp
	$(CC) $< -o bin/$@ $(LIBS)

dirs:
	${MKDIR_P} bin/
