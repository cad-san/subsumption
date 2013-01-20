#include "UtilTime.h"

const int UtilTime::MSEC_BASE = 1000 * 1000;
const int UtilTime::NSEC_BASE = 1000 * 1000 * 1000;

const UtilTime::util_sec
UtilTime::add_sec(const UtilTime& base, const UtilTime& addition) const
{
    return (base.sec + addition.sec) + (base.nsec + addition.nsec) / NSEC_BASE;
}

const UtilTime::util_nsec
UtilTime::add_nsec(const UtilTime& base, const UtilTime& addition) const
{
    return (base.nsec + addition.nsec) % NSEC_BASE;
}

UtilTime UtilTime::operator+(const UtilTime& time) const
{
    UtilTime result;

    result.sec = add_sec(*this, time);
    result.nsec = add_nsec(*this, time);

    return result;
}

UtilTime UtilTime::operator+=(const UtilTime& time)
{
    sec = add_sec(*this, time);
    nsec = add_nsec(*this, time);

    return *this;
}
