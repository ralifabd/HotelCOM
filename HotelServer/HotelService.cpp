// HotelService.cpp : Implementation of CHotelService

#include "pch.h"
#include "HotelService.h"
#include <climits>


// CHotelService

STDMETHODIMP CHotelService::BookRoom(
    LONG roomId,
    BSTR guestName,
    VARIANT_BOOL* success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    if (!guestName || SysStringLen(guestName) == 0)
        return E_INVALIDARG;

    std::wstring guest(guestName);

    bool hasNonWhitespace = false;
    for (wchar_t ch : guest)
    {
        if (!iswspace(ch))
        {
            hasNonWhitespace = true;
            break;
        }
    }

    if (!hasNonWhitespace)
        return E_INVALIDARG;

    Room* room = FindRoom(roomId);

    if (!room)
        return S_OK;

    if (room->status != RoomStatus::Available)
        return S_OK;

    for (const auto& existing : bookings)
    {
        if (existing.roomId == roomId &&
            (existing.status == L"Confirmed" ||
                existing.status == L"CheckedIn"))
        {
            return S_OK;
        }
    }

    Booking booking{};

    booking.id = nextBookingId;
    booking.roomId = roomId;
    booking.guestName = guest;
    booking.checkIn = L"";
    booking.checkOut = L"";
    booking.status = L"CheckedIn";
    booking.discount = 0.0;
    bookings.push_back(std::move(booking));
    ++nextBookingId;

    room->status = RoomStatus::Occupied;

    *success = VARIANT_TRUE;
    return S_OK;
}



STDMETHODIMP CHotelService::CheckRoom(
    LONG roomId,
    VARIANT_BOOL* available)
{
    if (!available)
        return E_POINTER;

    *available = VARIANT_FALSE;

    Room* room = FindRoom(roomId);

    if (!room)
        return S_OK;

    if (room->status == RoomStatus::Available)
        *available = VARIANT_TRUE;

    return S_OK;
}


STDMETHODIMP CHotelService::CancelBooking(
    LONG roomId,
    VARIANT_BOOL* success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    Room* room = FindRoom(roomId);

    if (!room)
        return S_OK;

    for (auto& booking : bookings)
    {
        if (booking.roomId != roomId)
            continue;

        if (booking.status != L"Confirmed")
            continue;

        booking.status = L"Cancelled";

        *success = VARIANT_TRUE;
        return S_OK;
    }

    return S_OK;
}


CHotelService::Room* CHotelService::FindRoom(LONG roomId)
{
    for (auto& room : rooms)
    {
        if (room.id == roomId)
            return &room;
    }

    return nullptr;
}

CHotelService::Booking* CHotelService::FindBooking(LONG bookingId)
{
    for (auto& booking : bookings)
    {
        if (booking.id == bookingId)
            return &booking;
    }

    return nullptr;
}

bool CHotelService::IsValidDate(const std::wstring& date)
{
    if (date.size() != 10 ||
        date[4] != L'-' ||
        date[7] != L'-')
    {
        return false;
    }

    for (size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;

        if (!iswdigit(date[i]))
            return false;
    }

    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    if (year < 1900 || month < 1 || month > 12)
        return false;

    const int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int maxDay = daysInMonth[month - 1];

    bool leapYear =
        (year % 400 == 0) ||
        (year % 4 == 0 && year % 100 != 0);

    if (month == 2 && leapYear)
        maxDay = 29;

    return day >= 1 && day <= maxDay;
}


bool CHotelService::IsRoomAvailable(
    LONG roomId,
    const std::wstring& checkIn,
    const std::wstring& checkOut,
    LONG excludeBookingId)
{
    Room* room = FindRoom(roomId);

    if (!room || checkIn >= checkOut)
        return false;

    if (room->status == RoomStatus::Maintenance ||
        room->status == RoomStatus::OutOfService ||
        room->status == RoomStatus::Cleaning ||
        room->status == RoomStatus::Occupied)
    {
        return false;
    }

    for (const auto& booking : bookings)
    {
        if (booking.roomId != roomId ||
            booking.id == excludeBookingId)
        {
            continue;
        }

        if (booking.status == L"Cancelled" ||
            booking.status == L"CheckedOut")
        {
            continue;
        }

        bool overlaps =
            checkIn < booking.checkOut &&
            booking.checkIn < checkOut;

        if (overlaps)
            return false;
    }

    return true;
}


STDMETHODIMP CHotelService::CreateBooking(
    LONG roomId,
    BSTR guestName,
    BSTR checkIn,
    BSTR checkOut,
    LONG* bookingId)
{
    if (!bookingId)
        return E_POINTER;

    *bookingId = 0;

    if (!guestName || !checkIn || !checkOut)
        return E_INVALIDARG;

    std::wstring guest(guestName);
    std::wstring start(checkIn);
    std::wstring end(checkOut);

    if (guest.empty() ||
        !IsValidDate(start) ||
        !IsValidDate(end) ||
        start >= end)
    {
        return S_OK;
    }

    if (!IsRoomAvailable(roomId, start, end))
        return S_OK;

    Booking booking{};

    booking.id = nextBookingId++;
    booking.roomId = roomId;
    booking.guestName = guest;
    booking.checkIn = start;
    booking.checkOut = end;
    booking.status = L"Confirmed";
    booking.discount = 0.0;

    *bookingId = booking.id;
    bookings.push_back(std::move(booking));

    return S_OK;
}


STDMETHODIMP CHotelService::UpdateBooking(
    LONG bookingId,
    BSTR newCheckIn,
    BSTR newCheckOut,
    VARIANT_BOOL* success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    if (!newCheckIn || !newCheckOut)
        return E_INVALIDARG;

    Booking* booking = FindBooking(bookingId);

    if (!booking || booking->status != L"Confirmed")
        return S_OK;

    std::wstring start(newCheckIn);
    std::wstring end(newCheckOut);

    if (!IsValidDate(start) ||
        !IsValidDate(end) ||
        start >= end)
    {
        return S_OK;
    }

    if (!IsRoomAvailable(
        booking->roomId,
        start,
        end,
        bookingId))
    {
        return S_OK;
    }

    booking->checkIn = start;
    booking->checkOut = end;

    *success = VARIANT_TRUE;
    return S_OK;
}


STDMETHODIMP CHotelService::SetRoomStatus(
    LONG roomId,
    BSTR status,
    VARIANT_BOOL* success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    if (!status)
        return E_INVALIDARG;

    Room* room = FindRoom(roomId);

    if (!room)
        return S_OK;

    std::wstring value(status);

    if (value == L"Available")
        room->status = RoomStatus::Available;
    else if (value == L"Occupied")
        room->status = RoomStatus::Occupied;
    else if (value == L"Cleaning")
        room->status = RoomStatus::Cleaning;
    else if (value == L"Maintenance")
        room->status = RoomStatus::Maintenance;
    else if (value == L"OutOfService")
        room->status = RoomStatus::OutOfService;
    else
        return S_OK;

    *success = VARIANT_TRUE;
    return S_OK;
}

static long long DaysFromCivil(int y, unsigned m, unsigned d)
{
    y -= (m <= 2);

    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);

    const unsigned doy =
        (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;

    const unsigned doe =
        yoe * 365 + yoe / 4 - yoe / 100 + doy;

    return static_cast<long long>(era) * 146097
        + static_cast<long long>(doe) - 719468;
}

static int DaysBetween(
    const std::wstring& start,
    const std::wstring& end)
{
    int y1 = std::stoi(start.substr(0, 4));
    unsigned m1 = static_cast<unsigned>(
        std::stoi(start.substr(5, 2)));
    unsigned d1 = static_cast<unsigned>(
        std::stoi(start.substr(8, 2)));

    int y2 = std::stoi(end.substr(0, 4));
    unsigned m2 = static_cast<unsigned>(
        std::stoi(end.substr(5, 2)));
    unsigned d2 = static_cast<unsigned>(
        std::stoi(end.substr(8, 2)));

    long long days =
        DaysFromCivil(y2, m2, d2) -
        DaysFromCivil(y1, m1, d1);

    if (days < 0 || days > 2147483647LL)
        return 0;

    return static_cast<int>(days);
}


double CHotelService::CalculatePrice(const Booking& booking)
{
    Room* room = FindRoom(booking.roomId);

    if (!room)
        return 0.0;

    int nights = DaysBetween(booking.checkIn, booking.checkOut);

    if (nights <= 0)
        return 0.0;

    double subtotal = room->basePrice * nights;
    return subtotal * (1.0 - booking.discount / 100.0);
}


STDMETHODIMP CHotelService::CalculateBookingPrice(
    LONG bookingId,
    DOUBLE* totalPrice)
{
    if (!totalPrice)
        return E_POINTER;
    *totalPrice = 0.0;
    Booking* booking = FindBooking(bookingId);

    if (!booking)
        return S_OK;

    *totalPrice = CalculatePrice(*booking);
    return S_OK;
}


STDMETHODIMP CHotelService::ApplyDiscount(
    LONG bookingId,
    DOUBLE discount,
    VARIANT_BOOL* success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    if (!std::isfinite(discount) ||
        discount < 0.0 ||
        discount > 100.0)
    {
        return S_OK;
    }

    Booking* booking = FindBooking(bookingId);

    if (!booking || booking->status != L"Confirmed")
        return S_OK;

    booking->discount = discount;
    *success = VARIANT_TRUE;
    return S_OK;
}

STDMETHODIMP CHotelService::GetRoomInfo(
    LONG roomId,
    BSTR* roomJson)
{
    if (!roomJson)
        return E_POINTER;

    *roomJson = nullptr;

    Room* room = FindRoom(roomId);

    if (!room)
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);

    std::wostringstream json;

    json << std::fixed << std::setprecision(2);
    json << L"{";
    json << L"\"roomId\":" << room->id << L",";
    json << L"\"roomNumber\":\"" << room->roomNumber << L"\",";
    json << L"\"floor\":" << room->floor << L",";
    json << L"\"type\":\"" << room->type << L"\",";
    json << L"\"capacity\":" << room->capacity << L",";
    json << L"\"bedCount\":" << room->bedCount << L",";
    json << L"\"area\":" << room->area << L",";
    json << L"\"basePrice\":" << room->basePrice;
    json << L"}";

    *roomJson = SysAllocString(json.str().c_str());

    if (!*roomJson)
        return E_OUTOFMEMORY;

    return S_OK;
}


STDMETHODIMP CHotelService::GetRoomsByType(
    BSTR roomType,
    BSTR* roomsJson)
{
    if (!roomsJson)
        return E_POINTER;

    *roomsJson = nullptr;

    if (!roomType)
        return E_INVALIDARG;

    std::wstring requestedType(roomType);
    std::wstring json = L"[";
    bool first = true;

    for (const auto& room : rooms)
    {
        if (_wcsicmp(room.type.c_str(), requestedType.c_str()) != 0)
            continue;

        if (!first)
            json += L",";

        json += L"{\"id\":" + std::to_wstring(room.id)
            + L",\"roomNumber\":\"" + room.roomNumber
            + L"\",\"type\":\"" + room.type
            + L"\",\"capacity\":" + std::to_wstring(room.capacity)
            + L",\"basePrice\":" + std::to_wstring(room.basePrice)
            + L"}";

        first = false;
    }

    json += L"]";

    *roomsJson = SysAllocString(json.c_str());

    return *roomsJson ? S_OK : E_OUTOFMEMORY;
}


STDMETHODIMP CHotelService::FindAvailableRooms(
    BSTR checkIn,
    BSTR checkOut,
    BSTR roomType,
    BSTR* roomsJson)
{
    if (!roomsJson)
        return E_POINTER;

    *roomsJson = nullptr;

    if (!checkIn || !checkOut || !roomType)
        return E_INVALIDARG;

    std::wstring start(checkIn);
    std::wstring end(checkOut);
    std::wstring requestedType(roomType);

    if (!IsValidDate(start) || !IsValidDate(end) || start >= end)
        return E_INVALIDARG;

    std::wstring json = L"[";
    bool first = true;

    for (const auto& room : rooms)
    {
        if (!requestedType.empty() &&
            _wcsicmp(room.type.c_str(), requestedType.c_str()) != 0)
        {
            continue;
        }

        if (!IsRoomAvailable(room.id, start, end))
            continue;

        if (!first)
            json += L",";

        json += L"{\"id\":" + std::to_wstring(room.id)
            + L",\"roomNumber\":\"" + room.roomNumber
            + L"\",\"type\":\"" + room.type
            + L"\",\"capacity\":" + std::to_wstring(room.capacity)
            + L",\"basePrice\":" + std::to_wstring(room.basePrice)
            + L"}";

        first = false;
    }

    json += L"]";

    *roomsJson = SysAllocString(json.c_str());

    return *roomsJson ? S_OK : E_OUTOFMEMORY;
}

// Вспомогательные функции для чтения простых JSON-полей.
// Добавь их перед реализациями методов, тоже в HotelService.cpp.

static std::wstring JsonString(
    const std::wstring& json,
    const std::wstring& key,
    const std::wstring& defaultValue = L"")
{
    std::wstring marker = L"\"" + key + L"\"";
    size_t pos = json.find(marker);

    if (pos == std::wstring::npos)
        return defaultValue;

    pos = json.find(L':', pos + marker.size());
    if (pos == std::wstring::npos)
        return defaultValue;

    pos = json.find(L'"', pos + 1);
    if (pos == std::wstring::npos)
        return defaultValue;

    size_t end = json.find(L'"', pos + 1);
    if (end == std::wstring::npos)
        return defaultValue;

    return json.substr(pos + 1, end - pos - 1);
}

static double JsonNumber(
    const std::wstring& json,
    const std::wstring& key,
    double defaultValue)
{
    std::wstring marker = L"\"" + key + L"\"";
    size_t pos = json.find(marker);

    if (pos == std::wstring::npos)
        return defaultValue;

    pos = json.find(L':', pos + marker.size());
    if (pos == std::wstring::npos)
        return defaultValue;

    ++pos;
    while (pos < json.size() && iswspace(json[pos]))
        ++pos;

    try
    {
        size_t used = 0;
        double value = std::stod(json.substr(pos), &used);

        if (used == 0 || !std::isfinite(value))
            return defaultValue;

        return value;
    }
    catch (...)
    {
        return defaultValue;
    }
}

STDMETHODIMP CHotelService::GetBookingInfo(
    LONG bookingId,
    BSTR* bookingJson)
{
    if (!bookingJson)
        return E_POINTER;

    *bookingJson = nullptr;

    Booking* booking = FindBooking(bookingId);
    if (!booking)
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);

    std::wostringstream json;
    json << L"{"
        << L"\"id\":" << booking->id << L","
        << L"\"roomId\":" << booking->roomId << L","
        << L"\"guestName\":\"" << booking->guestName << L"\","
        << L"\"checkIn\":\"" << booking->checkIn << L"\","
        << L"\"checkOut\":\"" << booking->checkOut << L"\","
        << L"\"status\":\"" << booking->status << L"\","
        << L"\"discount\":" << booking->discount
        << L"}";

    *bookingJson = SysAllocString(json.str().c_str());
    return *bookingJson ? S_OK : E_OUTOFMEMORY;
}


STDMETHODIMP CHotelService::AddRoom(
    BSTR roomJson,
    VARIANT_BOOL* success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    if (!roomJson || SysStringLen(roomJson) == 0)
        return E_INVALIDARG;

    std::wstring json(roomJson);

    Room room{};
    LONG maxId = 100;

    for (const auto& existing : rooms)
        maxId = (std::max)(maxId, existing.id);

    if (maxId == LONG_MAX)
        return E_FAIL;

    room.id = maxId + 1;
    room.roomNumber = JsonString(json, L"roomNumber",
        std::to_wstring(room.id));
    room.floor = static_cast<LONG>(JsonNumber(json, L"floor", 1));
    room.type = JsonString(json, L"type", L"Standart");
    room.capacity = static_cast<LONG>(
        JsonNumber(json, L"capacity", 2));
    room.bedCount = static_cast<LONG>(
        JsonNumber(json, L"bedCount", 1));
    room.area = JsonNumber(json, L"area", 25.0);
    room.basePrice = JsonNumber(json, L"basePrice", 3000.0);
    room.status = RoomStatus::Available;
    room.hasWifi = true;
    room.hasAirConditioning = true;

    if (room.roomNumber.empty() || room.type.empty() ||
        room.capacity < 1 || room.bedCount < 1 ||
        room.area <= 0 || room.basePrice < 0)
    {
        return E_INVALIDARG;
    }

    for (const auto& existing : rooms)
    {
        if (existing.roomNumber == room.roomNumber)
            return S_OK;
    }

    rooms.push_back(std::move(room));
    *success = VARIANT_TRUE;
    return S_OK;

}

STDMETHODIMP CHotelService::UpdateRoom(
    LONG roomId,
    BSTR roomJson,
    VARIANT_BOOL * success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    if (!roomJson || SysStringLen(roomJson) == 0)
        return E_INVALIDARG;

    Room* room = FindRoom(roomId);
    if (!room)
        return S_OK;

    std::wstring json(roomJson);

    // Обновляем только поля, которые переданы в JSON.
    std::wstring roomNumber = JsonString(json, L"roomNumber");
    std::wstring type = JsonString(json, L"type");

    if (!roomNumber.empty())
        room->roomNumber = roomNumber;

    if (!type.empty())
        room->type = type;

    room->floor = static_cast<LONG>(
        JsonNumber(json, L"floor", room->floor));
    room->capacity = static_cast<LONG>(
        JsonNumber(json, L"capacity", room->capacity));
    room->bedCount = static_cast<LONG>(
        JsonNumber(json, L"bedCount", room->bedCount));
    room->area = JsonNumber(json, L"area", room->area);
    room->basePrice = JsonNumber(json, L"basePrice", room->basePrice);

    if (room->capacity < 1 || room->bedCount < 1 ||
        room->area <= 0 || room->basePrice < 0)
    {
        return E_INVALIDARG;
    }

    *success = VARIANT_TRUE;
    return S_OK;
}


STDMETHODIMP CHotelService::RemoveRoom(
    LONG roomId,
    VARIANT_BOOL* success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    auto roomIt = std::find_if(
        rooms.begin(), rooms.end(),
        [roomId](const Room& room)
        {
            return room.id == roomId;
        });

    if (roomIt == rooms.end())
        return S_OK;

    for (const auto& booking : bookings)
    {
        if (booking.roomId == roomId &&
            (booking.status == L"Confirmed" ||
                booking.status == L"CheckedIn"))
        {
            return S_OK;
        }
    }

    rooms.erase(roomIt);
    *success = VARIANT_TRUE;
    return S_OK;
}


STDMETHODIMP CHotelService::CheckIn(
    LONG bookingId,
    VARIANT_BOOL* success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    Booking* booking = FindBooking(bookingId);
    if (!booking || booking->status != L"Confirmed")
        return S_OK;

    Room* room = FindRoom(booking->roomId);
    if (!room || room->status != RoomStatus::Available)
        return S_OK;

    room->status = RoomStatus::Occupied;
    booking->status = L"CheckedIn";

    *success = VARIANT_TRUE;
    return S_OK;
}


STDMETHODIMP CHotelService::CheckOut(
    LONG bookingId,
    VARIANT_BOOL* success)
{
    if (!success)
        return E_POINTER;

    *success = VARIANT_FALSE;

    Booking* booking = FindBooking(bookingId);
    if (!booking || booking->status != L"CheckedIn")
        return S_OK;

    Room* room = FindRoom(booking->roomId);
    if (!room)
        return S_OK;

    booking->status = L"CheckedOut";
    room->status = RoomStatus::Cleaning;

    *success = VARIANT_TRUE;
    return S_OK;
}


STDMETHODIMP CHotelService::GetHotelStatistics(
    BSTR* statisticsJson)
{
    if (!statisticsJson)
        return E_POINTER;

    *statisticsJson = nullptr;

    LONG totalRooms = static_cast<LONG>(rooms.size());
    LONG available = 0;
    LONG occupied = 0;
    LONG cleaning = 0;
    LONG maintenance = 0;
    LONG outOfService = 0;

    for (const auto& room : rooms)
    {
        switch (room.status)
        {
        case RoomStatus::Available:
            ++available;
            break;
        case RoomStatus::Occupied:
            ++occupied;
            break;
        case RoomStatus::Cleaning:
            ++cleaning;
            break;
        case RoomStatus::Maintenance:
            ++maintenance;
            break;
        case RoomStatus::OutOfService:
            ++outOfService;
            break;
        }
    }

    LONG totalBookings = static_cast<LONG>(bookings.size());
    LONG confirmed = 0;
    LONG checkedIn = 0;
    LONG checkedOut = 0;
    LONG cancelled = 0;

    for (const auto& booking : bookings)
    {
        if (booking.status == L"Confirmed")
            ++confirmed;
        else if (booking.status == L"CheckedIn")
            ++checkedIn;
        else if (booking.status == L"CheckedOut")
            ++checkedOut;
        else if (booking.status == L"Cancelled")
            ++cancelled;
    }

    std::wostringstream json;
    json << L"{"
        << L"\"totalRooms\":" << totalRooms << L","
        << L"\"availableRooms\":" << available << L","
        << L"\"occupiedRooms\":" << occupied << L","
        << L"\"cleaningRooms\":" << cleaning << L","
        << L"\"maintenanceRooms\":" << maintenance << L","
        << L"\"outOfServiceRooms\":" << outOfService << L","
        << L"\"totalBookings\":" << totalBookings << L","
        << L"\"confirmedBookings\":" << confirmed << L","
        << L"\"checkedInBookings\":" << checkedIn << L","
        << L"\"checkedOutBookings\":" << checkedOut << L","
        << L"\"cancelledBookings\":" << cancelled
        << L"}";

    *statisticsJson = SysAllocString(json.str().c_str());
    return *statisticsJson ? S_OK : E_OUTOFMEMORY;
}