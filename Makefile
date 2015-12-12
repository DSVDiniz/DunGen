#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g -fexpensive-optimizations -Os -O3 -Wunreachable-code -fmax-errors=1000
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS) -s -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm -ljson
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/DunGen

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -fexpensive-optimizations -Os -O3 -Wunreachable-code -fmax-errors=1000
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm -ljson
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/DunGen

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/main.o $(OBJDIR_DEBUG)/src/matrixToQ3Map.o $(OBJDIR_DEBUG)/src/parser.o $(OBJDIR_DEBUG)/src/parsing/mapParser.o $(OBJDIR_DEBUG)/src/lodePNG/lodepng.o $(OBJDIR_DEBUG)/src/render/geometry.o $(OBJDIR_DEBUG)/src/render/input.o $(OBJDIR_DEBUG)/src/render/optimize.o $(OBJDIR_DEBUG)/src/render/renderer.o $(OBJDIR_DEBUG)/src/generate/diamondSquare.o $(OBJDIR_DEBUG)/src/draw/draw.o $(OBJDIR_DEBUG)/src/draw/draw_functions.o $(OBJDIR_DEBUG)/src/draw/draw_geometry.o $(OBJDIR_DEBUG)/src/generate/cavernas.o $(OBJDIR_DEBUG)/src/generate/corredor.o $(OBJDIR_DEBUG)/src/generate/labirinto.o $(OBJDIR_DEBUG)/src/generate/perlinNoise.o $(OBJDIR_DEBUG)/src/generate/sala.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/main.o $(OBJDIR_RELEASE)/src/matrixToQ3Map.o $(OBJDIR_RELEASE)/src/parser.o $(OBJDIR_RELEASE)/src/parsing/mapParser.o $(OBJDIR_RELEASE)/src/lodePNG/lodepng.o $(OBJDIR_RELEASE)/src/render/geometry.o $(OBJDIR_RELEASE)/src/render/input.o $(OBJDIR_RELEASE)/src/render/optimize.o $(OBJDIR_RELEASE)/src/render/renderer.o $(OBJDIR_RELEASE)/src/generate/diamondSquare.o $(OBJDIR_RELEASE)/src/draw/draw.o $(OBJDIR_RELEASE)/src/draw/draw_functions.o $(OBJDIR_RELEASE)/src/draw/draw_geometry.o $(OBJDIR_RELEASE)/src/generate/cavernas.o $(OBJDIR_RELEASE)/src/generate/corredor.o $(OBJDIR_RELEASE)/src/generate/labirinto.o $(OBJDIR_RELEASE)/src/generate/perlinNoise.o $(OBJDIR_RELEASE)/src/generate/sala.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src
	test -d $(OBJDIR_DEBUG)/src/parsing || mkdir -p $(OBJDIR_DEBUG)/src/parsing
	test -d $(OBJDIR_DEBUG)/src/lodePNG || mkdir -p $(OBJDIR_DEBUG)/src/lodePNG
	test -d $(OBJDIR_DEBUG)/src/render || mkdir -p $(OBJDIR_DEBUG)/src/render
	test -d $(OBJDIR_DEBUG)/src/generate || mkdir -p $(OBJDIR_DEBUG)/src/generate
	test -d $(OBJDIR_DEBUG)/src/draw || mkdir -p $(OBJDIR_DEBUG)/src/draw

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/main.cpp -o $(OBJDIR_DEBUG)/src/main.o

$(OBJDIR_DEBUG)/src/matrixToQ3Map.o: src/matrixToQ3Map.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/matrixToQ3Map.cpp -o $(OBJDIR_DEBUG)/src/matrixToQ3Map.o

$(OBJDIR_DEBUG)/src/parser.o: src/parser.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/parser.cpp -o $(OBJDIR_DEBUG)/src/parser.o

$(OBJDIR_DEBUG)/src/parsing/mapParser.o: src/parsing/mapParser.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/parsing/mapParser.cpp -o $(OBJDIR_DEBUG)/src/parsing/mapParser.o

$(OBJDIR_DEBUG)/src/lodePNG/lodepng.o: src/lodePNG/lodepng.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/lodePNG/lodepng.cpp -o $(OBJDIR_DEBUG)/src/lodePNG/lodepng.o

$(OBJDIR_DEBUG)/src/render/geometry.o: src/render/geometry.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/render/geometry.cpp -o $(OBJDIR_DEBUG)/src/render/geometry.o

$(OBJDIR_DEBUG)/src/render/input.o: src/render/input.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/render/input.cpp -o $(OBJDIR_DEBUG)/src/render/input.o

$(OBJDIR_DEBUG)/src/render/optimize.o: src/render/optimize.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/render/optimize.cpp -o $(OBJDIR_DEBUG)/src/render/optimize.o

$(OBJDIR_DEBUG)/src/render/renderer.o: src/render/renderer.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/render/renderer.cpp -o $(OBJDIR_DEBUG)/src/render/renderer.o

$(OBJDIR_DEBUG)/src/generate/diamondSquare.o: src/generate/diamondSquare.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/generate/diamondSquare.cpp -o $(OBJDIR_DEBUG)/src/generate/diamondSquare.o

$(OBJDIR_DEBUG)/src/draw/draw.o: src/draw/draw.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/draw/draw.cpp -o $(OBJDIR_DEBUG)/src/draw/draw.o

$(OBJDIR_DEBUG)/src/draw/draw_functions.o: src/draw/draw_functions.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/draw/draw_functions.cpp -o $(OBJDIR_DEBUG)/src/draw/draw_functions.o

$(OBJDIR_DEBUG)/src/draw/draw_geometry.o: src/draw/draw_geometry.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/draw/draw_geometry.cpp -o $(OBJDIR_DEBUG)/src/draw/draw_geometry.o

$(OBJDIR_DEBUG)/src/generate/cavernas.o: src/generate/cavernas.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/generate/cavernas.cpp -o $(OBJDIR_DEBUG)/src/generate/cavernas.o

$(OBJDIR_DEBUG)/src/generate/corredor.o: src/generate/corredor.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/generate/corredor.cpp -o $(OBJDIR_DEBUG)/src/generate/corredor.o

$(OBJDIR_DEBUG)/src/generate/labirinto.o: src/generate/labirinto.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/generate/labirinto.cpp -o $(OBJDIR_DEBUG)/src/generate/labirinto.o

$(OBJDIR_DEBUG)/src/generate/perlinNoise.o: src/generate/perlinNoise.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/generate/perlinNoise.cpp -o $(OBJDIR_DEBUG)/src/generate/perlinNoise.o

$(OBJDIR_DEBUG)/src/generate/sala.o: src/generate/sala.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/generate/sala.cpp -o $(OBJDIR_DEBUG)/src/generate/sala.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src
	rm -rf $(OBJDIR_DEBUG)/src/parsing
	rm -rf $(OBJDIR_DEBUG)/src/lodePNG
	rm -rf $(OBJDIR_DEBUG)/src/render
	rm -rf $(OBJDIR_DEBUG)/src/generate
	rm -rf $(OBJDIR_DEBUG)/src/draw

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src
	test -d $(OBJDIR_RELEASE)/src/parsing || mkdir -p $(OBJDIR_RELEASE)/src/parsing
	test -d $(OBJDIR_RELEASE)/src/lodePNG || mkdir -p $(OBJDIR_RELEASE)/src/lodePNG
	test -d $(OBJDIR_RELEASE)/src/render || mkdir -p $(OBJDIR_RELEASE)/src/render
	test -d $(OBJDIR_RELEASE)/src/generate || mkdir -p $(OBJDIR_RELEASE)/src/generate
	test -d $(OBJDIR_RELEASE)/src/draw || mkdir -p $(OBJDIR_RELEASE)/src/draw

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/main.cpp -o $(OBJDIR_RELEASE)/src/main.o

$(OBJDIR_RELEASE)/src/matrixToQ3Map.o: src/matrixToQ3Map.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/matrixToQ3Map.cpp -o $(OBJDIR_RELEASE)/src/matrixToQ3Map.o

$(OBJDIR_RELEASE)/src/parser.o: src/parser.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/parser.cpp -o $(OBJDIR_RELEASE)/src/parser.o

$(OBJDIR_RELEASE)/src/parsing/mapParser.o: src/parsing/mapParser.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/parsing/mapParser.cpp -o $(OBJDIR_RELEASE)/src/parsing/mapParser.o

$(OBJDIR_RELEASE)/src/lodePNG/lodepng.o: src/lodePNG/lodepng.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/lodePNG/lodepng.cpp -o $(OBJDIR_RELEASE)/src/lodePNG/lodepng.o

$(OBJDIR_RELEASE)/src/render/geometry.o: src/render/geometry.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/render/geometry.cpp -o $(OBJDIR_RELEASE)/src/render/geometry.o

$(OBJDIR_RELEASE)/src/render/input.o: src/render/input.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/render/input.cpp -o $(OBJDIR_RELEASE)/src/render/input.o

$(OBJDIR_RELEASE)/src/render/optimize.o: src/render/optimize.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/render/optimize.cpp -o $(OBJDIR_RELEASE)/src/render/optimize.o

$(OBJDIR_RELEASE)/src/render/renderer.o: src/render/renderer.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/render/renderer.cpp -o $(OBJDIR_RELEASE)/src/render/renderer.o

$(OBJDIR_RELEASE)/src/generate/diamondSquare.o: src/generate/diamondSquare.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/generate/diamondSquare.cpp -o $(OBJDIR_RELEASE)/src/generate/diamondSquare.o

$(OBJDIR_RELEASE)/src/draw/draw.o: src/draw/draw.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/draw/draw.cpp -o $(OBJDIR_RELEASE)/src/draw/draw.o

$(OBJDIR_RELEASE)/src/draw/draw_functions.o: src/draw/draw_functions.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/draw/draw_functions.cpp -o $(OBJDIR_RELEASE)/src/draw/draw_functions.o

$(OBJDIR_RELEASE)/src/draw/draw_geometry.o: src/draw/draw_geometry.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/draw/draw_geometry.cpp -o $(OBJDIR_RELEASE)/src/draw/draw_geometry.o

$(OBJDIR_RELEASE)/src/generate/cavernas.o: src/generate/cavernas.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/generate/cavernas.cpp -o $(OBJDIR_RELEASE)/src/generate/cavernas.o

$(OBJDIR_RELEASE)/src/generate/corredor.o: src/generate/corredor.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/generate/corredor.cpp -o $(OBJDIR_RELEASE)/src/generate/corredor.o

$(OBJDIR_RELEASE)/src/generate/labirinto.o: src/generate/labirinto.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/generate/labirinto.cpp -o $(OBJDIR_RELEASE)/src/generate/labirinto.o

$(OBJDIR_RELEASE)/src/generate/perlinNoise.o: src/generate/perlinNoise.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/generate/perlinNoise.cpp -o $(OBJDIR_RELEASE)/src/generate/perlinNoise.o

$(OBJDIR_RELEASE)/src/generate/sala.o: src/generate/sala.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/generate/sala.cpp -o $(OBJDIR_RELEASE)/src/generate/sala.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)/src
	rm -rf $(OBJDIR_RELEASE)/src/parsing
	rm -rf $(OBJDIR_RELEASE)/src/lodePNG
	rm -rf $(OBJDIR_RELEASE)/src/render
	rm -rf $(OBJDIR_RELEASE)/src/generate
	rm -rf $(OBJDIR_RELEASE)/src/draw

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

