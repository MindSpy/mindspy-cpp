#include "Usbstream.hpp"

namespace MindSpy
{

UsbStream::UsbStream() : deviceContext(nullptr), numberOfDevices(0)
{
    // Inicialize library and session
    numberOfDevices = libusb_init(context);
    if(numberOfDevices < 0)
    {
        // if return more than 0 else libusb error
        return;
    }

    libusb_set_debug(context, LOG_LEVEL_USB::LOG_WARNING);

    // Get device
    context = libusb_get_device_list(context, &devices);
    if(context < 0)
    {
        // Not found device
        return;
    }

    std::cout << "Found devices: " << context << std::endl;

    int des  = libusb_get_device_descriptor(&devices, descriptor);
    if(des < 0)
    {
        // If return more than 0 else libusb error
        return;
    }



}

UsbStream::~UsbStream()
{
    // Close session library
    libusb_exit(deviceContext);
}

void UsbStream::PrintDevice()
{
    std::cout << "Configuration : " << descriptor.bNumConfigurations << std::endl;
    std::cout << "Device class : " << descriptor.bDeviceClass << std::endl;
    std::cout << "VendorID : " << descriptor.idVendor << std::endl;
    std::cout << "ProductID : " << descriptor.idProduct << std::endl;
}

} // namespace
