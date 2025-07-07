
#ifndef __WEBOTS_MESSAGE_HPP__
#define __WEBOTS_MESSAGE_HPP__

#include <cstdint>

namespace travesim {
namespace webots_adapter {
template <uint8_t size>
using message_t = struct {
    uint32_t frame;
    double   left_speed[size];
    double   right_speed[size];
};
}
} // namespace

#endif // __WEBOTS_MESSAGE_HPP__
