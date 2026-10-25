// HotelClient.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <windows.h>
#include <iostream>
#include "../HotelServer/HotelServer_i.h"
#include <atlstr.h>

int main()
{
    HRESULT hr = CoInitialize(nullptr);

    if (FAILED(hr))
    {
        std::cout << "COM initialization failed\n";
        return 1;
    }

    IHotelService* hotel = nullptr;

    hr = CoCreateInstance(
        CLSID_HotelService,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_IHotelService,
        reinterpret_cast<void**>(&hotel)
    );

    VARIANT_BOOL available;
    hotel->CheckRoom(107, &available);
    std::cout << "Room 101 available: "  << (available == VARIANT_TRUE) << std::endl;

    CComBSTR guestName(L"Ivan Ivanov");
    VARIANT_BOOL success;
    hotel->BookRoom(107,guestName, &success);
    std::cout << "Booking: " << (success == VARIANT_TRUE) << std::endl;

    hotel->CheckRoom(101, &available);
    std::cout << "Room 101 available: " << (available == VARIANT_TRUE) << std::endl;

    hotel->CancelBooking(107, &success);
    std::cout << "Cancel booking: " << (success == VARIANT_TRUE) << std::endl;

    hotel->CheckRoom(101, &available);
    std::cout << "Room 101 available: " << (available == VARIANT_TRUE) << std::endl;

    CoUninitialize();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
