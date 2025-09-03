#include "TextInput.h"

namespace textinput {
    std::istream &ReadIntBound(std::istream &in, int &target,
                               const int min, const int max) {
        int num{};
        if (!(in >> num)) return in;

        if (num < min || num > max) {
            in.setstate(std::ios::failbit);
        } else {
            target = num;
        }

        return in;
    }

    std::istream &ReadYesOrNo(std::istream &in, bool &target) {
        char yn{};
        if (!(in >> yn)) return in;

        // Safe cast for non-ASCII
        const auto unsignedYn{static_cast<unsigned char>(yn)};
        yn = static_cast<char>(std::tolower(unsignedYn));

        if (yn == 'y' || yn == 'n') {
            target = (yn == 'y');
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
}
