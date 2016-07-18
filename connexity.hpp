#ifndef CONNEXITY_HPP_INCLUDED
#define CONNEXITY_HPP_INCLUDED

#include "utils.hpp"

enum Mode {FOUR, EIGHT};

IterationResult connexity(Province2DMap& pMap, int sharpness, Mode mode = Mode::EIGHT);

#endif // CONNEXITY_HPP_INCLUDED
