
SHARED_OPTIONS = -lSDL2 -lassimp -lfreetype -lsndfile -I include -I src -I imgui

unix:
	@echo "Compiling for unix..."
	g++ -lopenal $(SHARED_OPTIONS) -L lib -o app.out src/*.* imgui/* src/compile/linux.cpp

windows:
	@echo "Compiling for windows..."
	x86_64-w64-mingw32-g++ -Wl,-subsystem,windows -static-libgcc -static-libstdc++ -lsoft_oal $(SHARED_OPTIONS) -L bin -o bin/winApp.exe src/*.* imgui/* src/compile/windows.cpp

windows_build:
	@echo "Building for windows..."
	-rm Engine.zip
	zip -r Engine.zip bin resources

clean:
	@echo "Cleaning up..."
	-rm *.out bin/*.exe