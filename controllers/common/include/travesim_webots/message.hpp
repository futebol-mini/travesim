
#ifndef __WEBOTS_MESSAGE_HPP__
#define __WEBOTS_MESSAGE_HPP__

#include <cstdint>

namespace travesim {
namespace webots_adapter {
typedef struct {
    uint32_t frame;
    double   left_speed;
    double   right_speed;
} message_t;
}
} // namespace

#endif // __WEBOTS_MESSAGE_HPP__
