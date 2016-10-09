#include "MainForm.h"
/*Жадобин Юрий
Vs 2015
Выполнил все пункты.
*/
using namespace task1; //name of your project

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainForm());
	return 0;
}

