#ifndef TICTACTOE_SCALABLE_H
#define TICTACTOE_SCALABLE_H

#include <cassert>

/// Interface for widgets that support scaling.
///
/// Classes implementing this interface allow their contents
/// to be resized proportionally, for example to support
/// high-DPI displays or user-controlled zoom.
class Scalable {
public:
    virtual ~Scalable() = default;

    /// Sets the current scale factor.
    ///
    /// \param newScale A positive factor by which the widget should adjust
    ///                 its contents. A value of 1.0 means normal size;
    ///                 2.0 means twice as large; 0.5 means half size.
    /// \pre scale > 0
    void setScale(const double newScale) {
        assert(newScale > 0);

        scale = newScale;
        onScale(newScale);
    }

private:
    double scale{1.0};

    /// Called whenever the scale factor changes.
    /// Subclasses must update their layout or rendering accordingly.
    virtual void onScale(double scale) = 0;
};

#endif // TICTACTOE_SCALABLE_H
