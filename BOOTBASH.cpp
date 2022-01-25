#include <iostream>
#include <Windows.h>

/*
program requirements:
    while counting:
        run in the background (doesn't show up in taskbar/system tray)

    payload:
        create fullscreen window
        show some ominous looking text in window and also "press any key to continue..."
        destroy window if any key is pressed
*/

void WinLog(const wchar_t* text, int n)
{
    /*
        this function is taken from a Microsoft Docs article, namely "Displaying debug messages - Windows app development".
        here is a link to that article:
        https://docs.microsoft.com/en-us/previous-versions/windows/apps/dn313274(v=win.10)
    */
    wchar_t buf[1024];
    _snwprintf_s(buf, 1024, _TRUNCATE, L"%s %d\n", text, n);
    OutputDebugString(buf);
}

//max/min keystrokes
int max = 1000;

int min = 300;

int main()
{
    //should hide the window but for testing purposes isn't
    //to make it hide the window change SW_SHOW to SW_HIDE
    ShowWindow(::GetConsoleWindow(), SW_SHOW);

    //seeds random number with time function
    std::srand(time(NULL));

    while (true)
    {
        //sets random number
        int random_number = (std::rand() % (max - min)) + min;

        //resets the counter after the random number has been reached
        int counter = 0;

        //keyboard vkeys
        bool keyboard[254]{};

        //while less keys pressed than random number
        while (counter < random_number)
        {
            //basic "for" loop, but instead of "int i" has "SHORT i"
            for (SHORT i = 1; i < 255; i++)
            {
                //stops the program thinking that either ctrl key being pressed is two keypresses
                if (i != 18 && i != 17 && i != 16)
                {
                    //bool converts asynckeystate to 0=false, 1=true. the & 0x8000 sees if the key is down somehow
                    if (bool(GetAsyncKeyState(i) & 0x8000) != keyboard[i])
                    {
                        //i=current key
                        keyboard[i] = bool(GetAsyncKeyState(i) & 0x8000);

                        //sees if the array was changed and if it was it increases the counter
                        if (!keyboard[i])
                        {
                            counter++;
                        }
                    }
                }
            }
            //std::cout << counter << "\n";
            WinLog(L"keycount:", counter);
            Sleep(1);
        }
#pragma region Payload
        //Payload goes here
#pragma endregion Payload
    }
}