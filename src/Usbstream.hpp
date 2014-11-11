#ifndef USBSTREAM_HPP
#define USBSTREAM_HPP

#include <libusb.h>

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

private:

    /*
     * Open usb device.s
     */
    libusb_device **device;

    /*
     * Device handle for I/O operation.
     */
    libusb_device_handle *dev_handle;

    /*
     * Create usb context.
     */
    libusb_context *context;
};

} // namespace

#endif // USBSTREAM_HPP
