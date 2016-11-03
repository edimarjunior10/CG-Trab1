all: BCommandLine bmp meu

BCommandLine: BCommandLine.cpp
	g++ -c -g BCommandLine.cpp -lGL -lGLU -lglut

bmp: bmp.cpp
	g++ -c -g bmp.cpp -lGL -lGLU -lglut

meu: meu.cpp BCommandLine.o bmp.o
	g++ -g meu.cpp -lGL -lGLU -lglut -o meu BCommandLine.o bmp.o

clean:
	rm BCommandLine bmp meu
