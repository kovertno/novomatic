#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants {
inline constexpr int WINDOW_WIDTH = 1200;
inline constexpr int WINDOW_HEIGHT = 800;

inline constexpr float NODE_WIDTH = 140;
inline constexpr float NODE_HEIGHT = 30;

inline constexpr int X_OFFSET = 100;
inline constexpr int Y_OFFSET =
    WINDOW_HEIGHT / 2 + 60; // visual center offset, 60 came with trial and
                            // error playing with NODE height

inline constexpr int X_SPACING = 200;
inline constexpr int Y_SPACING = 200;
} // namespace constants

#endif