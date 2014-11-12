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
        return 1;
    }

    libusb_set_debug(deviceContext, LOG_LEVEL_USB::LOG_WARNING);

    // Get device
    deviceContext = libusb_get_device(deviceContext, &devices);
    if(deviceContext < 0)
    {
        // not found device
        return 1;
    }

}

UsbStream::~UsbStream()
{
    // Deinicialize library
    libusb_exit(deviceContext);
}

} // namespace
