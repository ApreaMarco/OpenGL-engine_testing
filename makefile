
INCLUDE_DIRECTORIES = -I include -I src -I imgui
LINKED_LIBRARIES = -lSDL2 -lbsd -lassimp -lfreetype -lsndfile

unix:
	@echo "Compiling for unix..."
	g++ imgui/* src/compile/linux.cpp $(INCLUDE_DIRECTORIES) -L lib $(LINKED_LIBRARIES) -lopenal -o app.out src/*.*

unix_build:
	@echo "Building for unix..."
	-@mkdir build
	-@rm build/Engine-unix.zip
	@zip -r build/Engine-unix.zip app.out lib resources

windows:
	@echo "Compiling for windows..."
	x86_64-w64-mingw32-g++ src/*.* imgui/* src/compile/windows.cpp -Wl,-subsystem,windows -static-libgcc -static-libstdc++ $(INCLUDE_DIRECTORIES) -L bin $(LINKED_LIBRARIES) -lsoft_oal -o bin/app.exe

windows_build:
	@echo "Building for windows..."
	-@mkdir build
	-@rm build/Engine-w64.zip
	@zip -r build/Engine-w64.zip bin resources

clean:
	@echo "Cleaning up..."
	-@rm app.out bin/app.exe