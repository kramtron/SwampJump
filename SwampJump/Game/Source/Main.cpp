#include "App.h"
#include "Defs.h"
#include "Log.h"
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <iostream>
#include <chrono>
#include <stack>
using namespace std;

// NOTE: SDL redefines main function
#include "SDL/include/SDL.h"

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2.lib")
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2main.lib")



enum MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

App* app = NULL;

int main(int argc, char* args[])
{
	LOG("Engine starting ...");

	MainState state = CREATE;
	int result = EXIT_FAILURE;

	while(state != EXIT)
	{
		double t = 0.0;
		float dt = 16.0f; //frames
		auto start = chrono::steady_clock::now();

		switch(state)
		{
			// Allocate the engine --------------------------------------------
			case CREATE:
			LOG("CREATION PHASE ===============================");

			app = new App(argc, args);

			if(app != NULL)
				state = AWAKE;
			else
				state = FAIL;

			break;

			// Awake all modules -----------------------------------------------
			case AWAKE:
			LOG("AWAKE PHASE ===============================");
			if(app->Awake() == true)
				state = START;
			else
			{
				LOG("ERROR: Awake failed");
				state = FAIL;
			}

			break;

			// Call all modules before first frame  ----------------------------
			case START:
			LOG("START PHASE ===============================");
			if(app->Start() == true)
			{
				state = LOOP;
				LOG("UPDATE PHASE ===============================");
			}
			else
			{
				state = FAIL;
				LOG("ERROR: Start failed");
			}
			break;

			// Loop all modules until we are asked to leave ---------------------
			case LOOP:
			if(app->Update() == false)
				state = CLEAN;
			break;

			// Cleanup allocated memory -----------------------------------------
			case CLEAN:
			LOG("CLEANUP PHASE ===============================");
			if(app->CleanUp() == true)
			{
				RELEASE(app);
				result = EXIT_SUCCESS;
				state = EXIT;
			}
			else
				state = FAIL;

			break;

			// Exit with errors and shame ---------------------------------------
			case FAIL:
			LOG("Exiting with errors :(");
			result = EXIT_FAILURE;
			state = EXIT;
			break;
		}
		//TOC
		auto end = chrono::steady_clock::now();
		//Check en salida de la diferencia de temps
		LOG("Elapsed time in milliseconds: %d", chrono::duration_cast<chrono::milliseconds>(end - start).count(), " ms");
		auto telapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
 		LOG("dt: %f", dt);
		//Entra si hay diferencia de tiempo
		if (dt - telapsed > 0.0f)
			//Para el programa el tiempo restante
			Sleep((dt - telapsed)/1000);

	}

	
	LOG("... Bye! :)\n");

	// Dump memory leaks
	return result;
}