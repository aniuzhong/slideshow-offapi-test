#ifndef OFFICECLIENT_H
#define OFFICECLIENT_H

class OfficeClient
{
public:
    OfficeClient() noexcept;
    OfficeClient(const OfficeClient&) = delete;
    OfficeClient& operator=(const OfficeClient &) = delete;
    OfficeClient(OfficeClient&&) noexcept = default;
    OfficeClient & operator=(OfficeClient&&) noexcept = default;
};

#endif // OFFICECLIENT_H
