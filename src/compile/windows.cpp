

#include <windows.h>
#include <unistd.h>

#include "main.h"


// cross-compile for windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    chdir("..");
    return Main::engine_main(__argc, __argv);
}

