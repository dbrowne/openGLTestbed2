# FinalProject
EXE=final

# Main target
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32 -lglfw -ldl
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -std=c++14 -I/usr/local/include
LIBS=-framework GLUT -framework OpenGL -L/usr/local/lib/ -lglfw
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm -L/usr/local/lib/ -lglfw -ldl
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
main.o: main.cpp extra_funcs.h Camera.h Cylinder.h ellipse.h Parallelogram.h Camera.h khrplatform.h Shader.h dflyGen.h
extra_funcs.o: extra_funcs.cpp extra_funcs.h
Color.o: Color.cpp Color.h
Cylinder.o: Cylinder.cpp Cylinder.h Prim_base.h extra_funcs.h
ellipse.o: ellipse.cpp ellipse.h
glad.o: glad.cpp glad.h
Parallelogram.o: Parallelogram.cpp Parallelogram.h
Prim_base.o: Prim_base.cpp Prim_base.h
primatives.o: primatives.cpp primatives.h Color.h Prim_base.h extra_funcs.h
Sphere.o: Sphere.cpp Sphere.h
box.o: box.cpp box.h
Dragonfly.o: Dragonfly.cpp Dragonfly.h
dflyGen.o: dflyGen.cpp dflyGen.h

#  Create archive
CSCIx229.a:Color.o Cylinder.o ellipse.o extra_funcs.o glad.o Parallelogram.o primatives.o Prim_base.o Sphere.o box.o Dragonfly.o dflyGen.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
final:main.o CSCIx229.a
	g++ -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)
