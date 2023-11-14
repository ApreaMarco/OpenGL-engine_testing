
SHARED_OPTIONS = -lSDL2 -lassimp -lfreetype -lsndfile -I include -I src -I imgui

unix:
	@echo "Compiling for unix..."
	g++ -lopenal $(SHARED_OPTIONS) -L lib -o app.out src/*.* imgui/* src/compile/linux.cpp

unix_build:
	@echo "Building for unix..."
	-@mkdir build
	-@rm build/Engine-unix.zip
	@zip -r build/Engine-unix.zip app.out lib resources

windows:
	@echo "Compiling for windows..."
	x86_64-w64-mingw32-g++ -Wl,-subsystem,windows -static-libgcc -static-libstdc++ -lsoft_oal $(SHARED_OPTIONS) -L bin -o bin/app.exe src/*.* imgui/* src/compile/windows.cpp

windows_build:
	@echo "Building for windows..."
	-@mkdir build
	-@rm build/Engine-w64.zip
	@zip -r build/Engine-w64.zip bin resources

clean:
	@echo "Cleaning up..."
	-@rm app.out bin/app.exe