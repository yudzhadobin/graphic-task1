#include "MainForm.h"
/*������� ����
Vs 2015
�������� ��� ������.
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

