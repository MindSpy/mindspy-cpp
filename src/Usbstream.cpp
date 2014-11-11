#include "Usbstream.hpp"

namespace MindSpy
{

UsbStream::UsbStream() : deviceContext(nullptr), numberOfDevices(0)
{
    // Inicialize library and session
    numberOfDevices = libusb_init(deviceContext);
    if(numberOfDevices < 0)
    {
        // if return more than 0 else libusb error
    }

    libusb_set_debug(deviceContext, LOG_LEVEL_USB::LOG_WARNING);





}

UsbStream::~UsbStream()
{
    libusb_exit(deviceContext);
}

} // namespace
