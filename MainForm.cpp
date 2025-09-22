#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include "MainForm.h"
#include "Ball.h"
#include <ctime>

using namespace System;
using namespace System::Windows::Forms;

int main()
{
	Application::EnableVisualStyles();
	PopBallv3::MainForm form;
	srand(time(NULL));
	manager = new Manager(form.frame->Width, form.frame->Height);
	Application::Run(% form);
	delete manager;
}