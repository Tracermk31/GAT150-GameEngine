#pragma once

#include "JSON.h"
#include "Vector2.h"

namespace ChiefEngine {
    struct Transform {
        Vector2 position{ 0.0f, 0.0f };
        float rotation{ 0.0f };
        float scale{ 1.0f };

        void Read(const JSON::value_t& value) {
            JSON_READ_BY_DATA(value, position);
            JSON_READ_BY_DATA(value, rotation);
            JSON_READ_BY_DATA(value, scale);
        }
    };
}