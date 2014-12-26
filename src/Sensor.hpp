#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "Proto.hpp"

namespace mindspy {

namespace sensor {

class Sensor
{
public:

    virtual ~Sensor();

    /*!
     * \brief Get Samples from the sensor.
     * \param Count of samples to get.
     * \return Result.
     */
    virtual bool getSamples(uint32_t, protobufs::Sample*) = 0;

    /*!
     * \brief Get State of the sensor (get the registers).
     * \param Addresses to get
     * \param Addresses count
     * \return Result states
     */
    virtual bool getState(uint32_t*, uint32_t, protobufs::State*) = 0;

    /*!
     * \brief Set State of the sensor (set the registers).
     * \param States to set up
     */
    virtual bool setState(uint32_t, protobufs::State*, void*) = 0;

    /*!
     * \brief Get model name.
     * \param Result model name
     */
    virtual bool getModelName(char*) = 0;

    /*!
     * \brief Check if data is ready in this module.
     */
    virtual bool operator!(void) = 0;

    /*!
     * \brief begin
     */
    virtual void begin() = 0;

    /*!
     * \brief end
     */
    virtual void end() = 0;

}; // sensor

} // namespace

} // namespace

#endif
