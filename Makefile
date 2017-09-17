CC=g++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LIBS=-framework OpenGL -framework glut
else
	LIBS=-lglut -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW
endif
COMPILER_FLAGS=-Wno-deprecated-declarations
MKDIR_P = mkdir -p

all: dirs sierpinski_gasket draw_sphere

sierpinski_gasket: sierpinski_gasket.cpp
	$(CC) $< -o bin/$@ $(LIBS) $(COMPILER_FLAGS)

draw_sphere: draw_sphere.cpp
	$(CC) $< -o bin/$@ $(LIBS) $(COMPILER_FLAGS)

dirs:
	${MKDIR_P} bin/
