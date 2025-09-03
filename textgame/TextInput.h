#ifndef TICTACTOE_TEXTINPUT_H
#define TICTACTOE_TEXTINPUT_H

#include <climits>
#include <istream>

/// istream adapters for bounded ints and yes/no prompts.
namespace textinput {
    /// Reads an int into target, enforcing range [min, max].
    /// If int < min or int > max, then std::ios::failbit will be set to in.
    std::istream &ReadIntBound(std::istream &in, int &target,
                               int min = INT_MIN, int max = INT_MAX);

    /// Reads a single 'y' or 'n' (case-insensitive) into target.
    /// If 'y' is read, then target = true.
    /// If 'n' is read, then target = false.
    /// Otherwise, std::ios::failbit will be set to in.
    std::istream &ReadYesOrNo(std::istream &in, bool &target);
}

#endif // TICTACTOE_TEXTINPUT_H
