#ifndef KMINT_PIGISLAND_RESOURCES_HPP
#define KMINT_PIGISLAND_RESOURCES_HPP

#include "kmint/graphics.hpp"
#include "kmint/map/map.hpp"
#include "rectangle.h"

namespace kmint {
    namespace pigisland {
	// Inaccessible areas for pigs
	std::vector<rectangle> grassIslands();
	map::map map();
	graphics::image shark_image();
	graphics::image pig_image();
	graphics::image boat_image();

    } // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_RESOURCES_HPP */
