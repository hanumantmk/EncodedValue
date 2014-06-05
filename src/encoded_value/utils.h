#pragma once

namespace encoded_value {
template <int A, int B>
class _max {
public:
    static const int result = A > B ? A : B;
};
}
