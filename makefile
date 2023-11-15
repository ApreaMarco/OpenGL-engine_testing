
INCLUDE_DIRECTORIES = -I include -I src -I imgui
LINKED_LIBRARIES = -lm -ldl -lSDL2 -lassimp -lfreetype

unix:
	@echo "Compiling for unix..."
	g++ src/*.* imgui/* src/compile/linux.cpp -o app.out $(INCLUDE_DIRECTORIES) -L lib $(LINKED_LIBRARIES) -lopenal

unix_build:
	@echo "Building for unix..."
	-@mkdir build
	-@rm build/Engine-unix.zip
	@zip -r build/Engine-unix.zip app.out lib resources

windows:
	@echo "Compiling for windows..."
	x86_64-w64-mingw32-g++ src/*.* imgui/* src/compile/windows.cpp -o bin/app.exe -Wl,-subsystem,windows -static-libgcc -static-libstdc++ $(INCLUDE_DIRECTORIES) -L bin $(LINKED_LIBRARIES) -lsoft_oal

windows_build:
	@echo "Building for windows..."
	-@mkdir build
	-@rm build/Engine-w64.zip
	@zip -r build/Engine-w64.zip bin resources

clean:
	@echo "Cleaning up..."
	-@rm app.out bin/app.exe
