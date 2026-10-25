// HotelService.h : Declaration of the CHotelService

#pragma once
#include "resource.h"       // main symbols

#include "HotelServer_i.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <cwctype>
#include <utility>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CHotelService

class ATL_NO_VTABLE CHotelService :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHotelService, &CLSID_HotelService>,
	public IDispatchImpl<IHotelService, &IID_IHotelService, &LIBID_HotelServerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CHotelService()
	{
		for (LONG id = 101; id <= 110; ++id)
		{
			Room room{};

			room.id = id;
			room.roomNumber = std::to_wstring(id);
			room.floor = id / 100;
			room.type = (id <= 103) ? L"Standart" : L"Deluxe";
			room.status = RoomStatus::Available;

			room.capacity = (id <= 103) ? 2 : 4;
			room.bedCount = (id <= 103) ? 1 : 2;
			room.area = (id <= 103) ? 24.0 : 38.0;
			room.basePrice = (id <= 103) ? 3000.0 : 5000.0;

			room.hasWifi = true;
			room.hasAirConditioning = true;
			room.hasBalcony = (id >= 104);

			room.description = (id <= 103) ? L"Comfortable standart room" : L"Spacious deluxe room";

			room.amenities = { L"WiFi", L"TV" };

			if (room.type == L"Deluxe")
			{
				room.amenities.push_back(L"AirConditioning");
			}

			rooms.push_back(room);
		}
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CHotelService)
	COM_INTERFACE_ENTRY(IHotelService)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(CheckRoom)(
		LONG roomId,
		VARIANT_BOOL* available);

	STDMETHOD(BookRoom)(
		LONG roomId,
		BSTR guestName,
		VARIANT_BOOL* success);

	STDMETHOD(CancelBooking)(
		LONG roomId,
		VARIANT_BOOL* success);

	// Информация о номере
	STDMETHOD(GetRoomInfo)(
		LONG roomId,
		BSTR* roomJson);

	STDMETHOD(GetRoomsByType)(
		BSTR roomType,
		BSTR* roomsJson);

	// Управление статусом
	STDMETHOD(SetRoomStatus)(
		LONG roomId,
		BSTR status,
		VARIANT_BOOL* success);

	// Бронирования
	STDMETHOD(CreateBooking)(
		LONG roomId,
		BSTR guestName,
		BSTR checkIn,
		BSTR checkOut,
		LONG* bookingId);

	STDMETHOD(GetBookingInfo)(
		LONG bookingId,
		BSTR* bookingJson);

	STDMETHOD(UpdateBooking)(
		LONG bookingId,
		BSTR newCheckIn,
		BSTR newCheckOut,
		VARIANT_BOOL* success);

	STDMETHOD(FindAvailableRooms)(
		BSTR checkIn,
		BSTR checkOut,
		BSTR roomType,
		BSTR* roomsJson);

	// Стоимость
	STDMETHOD(CalculateBookingPrice)(
		LONG bookingId,
		DOUBLE* totalPrice);

	STDMETHOD(ApplyDiscount)(
		LONG bookingId,
		DOUBLE discount,
		VARIANT_BOOL* success);

	// Дополнительное управление номерами
	STDMETHOD(AddRoom)(
		BSTR roomJson,
		VARIANT_BOOL* success);

	STDMETHOD(UpdateRoom)(
		LONG roomId,
		BSTR roomJson,
		VARIANT_BOOL* success);

	STDMETHOD(RemoveRoom)(
		LONG roomId,
		VARIANT_BOOL* success);

	// Заселение и выселение
	STDMETHOD(CheckIn)(
		LONG bookingId,
		VARIANT_BOOL* success);

	STDMETHOD(CheckOut)(
		LONG bookingId,
		VARIANT_BOOL* success);

	// Статистика
	STDMETHOD(GetHotelStatistics)(
		BSTR* statisticsJson);

private:
	enum class RoomStatus
	{
		Available,
		Occupied,
		Cleaning,
		Maintenance,
		OutOfService
	};

	struct Room
	{
		LONG id;
		std::wstring roomNumber;
		LONG floor;

		std::wstring type;
		RoomStatus status = RoomStatus::Available;

		LONG capacity = 2;
		LONG bedCount = 1;
		double area = 25.0;
		double basePrice = 3000.0;

		bool smokingAllowed = false;
		bool hasBalcony = false;
		bool hasWifi = true;
		bool hasAirConditioning = true;

		std::wstring description;
		std::vector<std::wstring> amenities;
	};

	struct Booking
	{
		LONG id;
		LONG roomId;
		std::wstring guestName;

		std::wstring checkIn;
		std::wstring checkOut;

		std::wstring status = L"Confirmed";
		double discount = 0.0;
	};

	std::vector<Room> rooms;
	std::vector<Booking> bookings;

	LONG nextBookingId = 1;

	Room* FindRoom(LONG roomId);
	Booking* FindBooking(LONG bookingId);

	bool IsValidDate(const std::wstring& date);
	bool IsRoomAvailable(
		LONG roomId,
		const std::wstring& checkIn,
		const std::wstring& checkOut,
		LONG excludeBookingId = 0
	);

	double CalculatePrice(const Booking& booking);

};

OBJECT_ENTRY_AUTO(__uuidof(HotelService), CHotelService)
