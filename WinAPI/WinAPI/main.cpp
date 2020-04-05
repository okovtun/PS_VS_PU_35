#include<Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	if (MessageBox(NULL, "Hello WinAPI ;-) Это сообщение", "Hello - это заголовок окна", MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON2 | MB_SYSTEMMODAL) ==	IDOK)
	{
		//MessageBox()
	}
}