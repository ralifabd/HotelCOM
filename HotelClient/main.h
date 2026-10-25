#include <Windows.h>
#include <iostream>
#include <atlbase.h>

// Подключим COM-интерфейс и CLSID,
// сгенерированные проектом HotelServer.
// Этот include добавим на следующем шаге,
// когда настроим путь к файлу.

int main()
{
    HRESULT hr = CoInitialize(nullptr);

    if (FAILED(hr))
    {
        std::cout << "COM initialization failed: " << std::hex << hr << std::endl;
        return 1;
    }

    std::cout << "COM initialized successfully!" << std::endl;

    CoUninitialize();
    return 0;
}
