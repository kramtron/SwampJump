#include "App.h"
#include "Defs.h"
#include "Log.h"
#include "Input.h"
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
#define DELTA_TIME 16.0f

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2.lib")
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2main.lib")

int delta_time = 16.0f;

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
	long long telapsed = 0;

	while(state != EXIT)
	{
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
			app->SetDt((float)telapsed/(float)DELTA_TIME);
			LOG("DtMain: %.4f", (float)telapsed / (float)DELTA_TIME);
			if(app->Update() == false)
				state = CLEAN;
	
			if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN) {
				if (delta_time == 16.0f) {
					delta_time = 32.0f;
				}
				else {
					delta_time = 16.0f;
				}
			}
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
		telapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
 		LOG("dt: %f", delta_time);
		//Entra si hay diferencia de tiempo
		if (delta_time - telapsed > 0.0f) {
			//Para el programa el tiempo restante
			SDL_Delay((delta_time - telapsed)/1000);
			//telapsed = delta_time / 2.5f;
		}
		LOG("ALGO QUE NO FUNCIONA: %.4f", (telapsed / delta_time));

	}

	
	LOG("... Bye! :)\n");

	// Dump memory leaks
	return result;
}