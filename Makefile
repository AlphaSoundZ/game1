all: compile link clean

test: compile link clean run

compile:
	g++ -Isrc/include -c main.cpp

link:
	g++ main.o -o ./make/app -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del *.o

run:
	./make/app.exe