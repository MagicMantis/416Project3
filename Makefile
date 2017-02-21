# Change the following values to suit your system.

CFLAGS=`sdl2-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0 -I `sdl2-config --prefix`/include/
SDL_LIB=`sdl2-config --libs` -lSDL2_image
CCC=clang++

OBJECTS = frameGenerator.o gameObject.o rain.o building.o detective.o criminal.o \
stageObject.o lightning.o fadeout.o textureManager.o objectManager.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp frameGenerator.h
	$(CCC) $(CFLAGS) -c main.cpp

frameGenerator.o: frameGenerator.cpp frameGenerator.h
	$(CCC) $(CFLAGS) -c frameGenerator.cpp

gameObject.o: gameObject.cpp gameObject.h
	$(CCC) $(CFLAGS) -c gameObject.cpp

textureManager.o: textureManager.cpp textureManager.h
	$(CCC) $(CFLAGS) -c textureManager.cpp

objectManager.o: objectManager.cpp objectManager.h
	$(CCC) $(CFLAGS) -c objectManager.cpp

stageObject.o: stageObject.cpp stageObject.h gameObject.h
	$(CCC) $(CFLAGS) -c stageObject.cpp

clean:
	rm -f run *.o
	rm -f *~
	rm -f frames/*.bmp
