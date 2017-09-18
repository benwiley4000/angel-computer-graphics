CC=g++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LIBS=-framework OpenGL -framework glut
else
	LIBS=-lglut -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW
endif
COMPILER_FLAGS=-Wno-deprecated-declarations
MKDIR_P = mkdir -p

all: dirs copy_shaders sierpinski_points sierpinski_tri draw_sphere

sierpinski_points: sierpinski_points.cpp
	$(CC) $< -o bin/$@ $(LIBS) $(COMPILER_FLAGS)

sierpinski_tri: sierpinski_tri.cpp
	$(CC) $< -o bin/$@ $(LIBS) $(COMPILER_FLAGS)

draw_sphere: draw_sphere.cpp
	$(CC) $< -o bin/$@ $(LIBS) $(COMPILER_FLAGS)

dirs:
	${MKDIR_P} bin/

copy_shaders:
	cp ./*.glsl bin/

clean:
	rm -f bin/*
