all: compile link-d clean

release: compile link clean

test: compile link-d clean run

compile:
	g++ -Isrc/include -c main.cpp

link:
	g++ main.o -o ./make/app-release -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

link-d:
	g++ main.o -o ./make/app -Lsrc/lib -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d -lsfml-network-d

clean:
	del *.o

run:
	./make/app.exe

run-release:
	./make/app-release.exe