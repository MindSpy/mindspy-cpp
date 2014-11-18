#ifndef USBSTREAM_HPP
#define USBSTREAM_HPP

#include <iostream>

// Defined for linux platform
#ifdef __linux__
#include <libusb-1.0/libusb.h>

// Defined for windows platform
#ifdef _WIN32
#include <libusb.h>
#endif

namespace MindSpy
{

/*
 * This class implement reading stream
 * from USB and writing stream to USB-
 */
class UsbStream
{
public:

    /*
     * Constructor. The USB device initialization.
     */
    UsbStream();

    ~UsbStream();

    /*
     * Print information from device.
     */
    void PrintDevice();

private:

    /*
     * Open usb devices.
     */
    libusb_device **devices;

    /*
     * Device handle for I/O operation.
     */
    libusb_device_handle *deviceHandle;


    /*
     * Create usb context.
     */
    libusb_context *context;

    /*
     * Create device descriptor.
     */
    libusb_device_descriptor descriptor;

    /*
     * Number of find devices.
     */
    int numberOfDevices;

    /*
     * Log level messages from USB.
     */
    enum class LOG_LEVEL_USB {
        LOG_NONE    = LIBUSB_LOG_LEVEL_NONE,
        LOG_ERROR   = LIBUSB_LOG_LEVEL_ERROR,
        LOG_WARNING = LIBUSB_LOG_LEVEL_WARNING,
        LOG_INFO    = LIBUSB_LOG_LEVEL_INFO,
        LOG_DEBUG   = LIBUSB_LOG_LEVEL_DEBUG
    };
};

} // namespace

#endif // USBSTREAM_HPP
