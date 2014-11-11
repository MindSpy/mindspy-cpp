#ifndef USBSTREAM_HPP
#define USBSTREAM_HPP

#include <libusb.h>

namespace MindSpy
{

/*
 * This class implement read and write from usb.
 */
class UsbStream
{
public:
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
