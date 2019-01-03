#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/rectangle.h"

namespace kmint {
namespace pigisland {
namespace {
constexpr const char *graph_description = R"graph(32 24 32
resources/pigisland.png
W 1 1
1 1 1
2 1 1
3 1 1
R 1 4
L 0 0
S 0 0
K 1 1

LLLLLLWW1WWWWRWWWWWWWWWWRWWWLLLL
LLLLLLLLLWWWWRWWWWWWWWWWRWWWLLLL
LLLLLLWWWWWWRRWWWWWWWWWWRRWWWWWL
WWWWWWWWWWWRRWWWWWWWWWWWWRRWWW2L
WWWWWWWWWWRRWWWWWWWWWWWWWRRRWWWW
WRRRRRRRRRRWWWWWWWWWWWWWWWRRWWWW
WWRRRRRRRRWWWWWWWWWWWWWWWRRRRWWW
WRRWWWRWWWWWWWWWWWWWWWWWWWWRRRRW
WWWWWWWWWWWWWLLLLLWWWWWWWWWWWWWW
WWWWWWWWWWWWWLLLLLLWWWWWWWWWWWWW
WWWWWWWWWWWWWLLLLLLWWWWWWWWWWWWW
WWWWWWWWWWWWWLLLLLLLWWWWWWWWWWWW
WWWWWWWWWWWWWLLLLLLLWWWWWWWWWWWW
WWWWWWWWWWWWWWLLLLLWWWWWWRRRRRWW
WWWWWWWWWWWWWWWWWWWWWWWWRRWRRRRW
WWWWWRRRWWWWWWWWWWWWWWWWRRRWWWWW
WWWWWWWWRWWWWWWWWWWWWWWWWRWWWWWW
WWLLLLLWWRWWWWWWWWWWWWWRRWWWL3WW
WWLLLLLWWRRWWWWWWWWWWWRRWWWWLWLL
WWLLLLLWWWRRWWWWWWWWWWRWWWLLLLLL
SSLLLLWWWWWRRRWWWWWWWWWWWLLLLLLL
SSLLLLWWWWWWWRRRRWWWWWWWWLLLLLLL
SSWWWWWWWWWWWWWWWWWWWWWWWLLLLLLL
KWWWWWWWWWWWWWWWWWWWWWWWWLLLLLLL
)graph";
}


std::vector<rectangle> grassIslands()
{
    return std::vector<rectangle>{
    	{
	    rectangle{ 0, 0, 320, 96 },
	    rectangle{ 896, 0, 128, 128 },
	    rectangle{ 0, 512, 192, 192 },
	    rectangle{ 768, 480, 192, 224 }
	}
    };
}

map::map map() { return map::read_map(graph_description); }

graphics::image shark_image() { return graphics::image{"resources/shark.png"}; }
graphics::image pig_image() { return graphics::image{"resources/pig.png"}; }

graphics::image boat_image() { return graphics::image{"resources/boat.png"}; }



} // namespace pigisland

} // namespace kmint
