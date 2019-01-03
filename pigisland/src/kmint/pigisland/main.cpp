#include "kmint/main.hpp" // voor de main loop
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/ui/app.hpp"
#include "kmint/ui/window.hpp"
#include "kmint/play/stage.hpp"
#include "kmint/play/background.hpp"
#include "kmint/math/size.hpp"
#include "kmint/graphics/image.hpp"
#include "kmint/play/graph_actor.hpp"
#include "kmint/ui/events/event.hpp"
#include "kmint/primitives.hpp"
#include "kmint/math/vector2d.hpp"
#include "kmint/pigisland/genetics.h"
#include "kmint/pigisland/geneticAlgorithm.h"

using namespace kmint;

play::background* background;
play::map_actor* background2;
pigisland::shark* shark;
pigisland::boat* boat;
std::vector<pigisland::pig*> pigs;

void resetStage(play::stage& s, map::map& map)
{
    std::vector<play::actor*> actorsToRemove{};

    for (play::actor& actor : s)
    {
	if (&actor != boat && &actor != background && &actor != background2)
	{
	    actorsToRemove.emplace_back(&actor);
	}
    }

    for (play::actor* actor : actorsToRemove)
    {
	s.remove_actor(*actor);
    }

    pigs.clear();

    shark = &s.build_actor<pigisland::shark>(map.graph());
    for (int i = 0; i < 100; ++i) {
	pigs.emplace_back(&s.build_actor<pigisland::pig>(math::vector2d(i * 10.0f, i * 6.0f), shark, boat));
    }
}

int main() {
    // een app object is nodig om
    ui::app app{};

    //  maak een venster aan
    ui::window window{ app.create_window({1024, 768}, "Pig Island", 0.9) };

    // maak een podium aan
    play::stage s{};
    auto map = pigisland::map();

    background = &s.build_actor<play::background>(math::size(1024, 768), graphics::image{ map.background_image() });
    background2 = &s.build_actor<play::map_actor>(math::vector2d{ 0.f, 0.f }, map.graph());
    boat = &s.build_actor<pigisland::boat>(map.graph());
    resetStage(s, map);

    pigisland::geneticAlgorithm geneticAlgorithm{};

    std::vector<pigisland::genetics> currentPopulation{};

    // Maak een event_source aan (hieruit kun je alle events halen, zoals
    // toetsaanslagen)
    ui::events::event_source event_source{};

    // main_loop stuurt alle actors aan.
    main_loop(s, window, [&](delta_time dt, loop_controls &ctl) {
	// gebruik dt om te kijken hoeveel tijd versterken is
	// sinds de vorige keer dat deze lambda werd aangeroepen
	// loop controls is een object met eigenschappen die je kunt gebruiken om de
	// main-loop aan te sturen.

	if (shark->isResting())
	{
	    for (pigisland::pig* pig : pigs) {
		geneticAlgorithm.addGenetics(pig->genetics());
	    }

	    geneticAlgorithm.generatePopulation();

	    resetStage(s, map);
	}

	pigs.erase(std::remove_if(pigs.begin(), pigs.end(), [&geneticAlgorithm, &s](pigisland::pig* p)
	{
	    if (p->isDead())
	    {
		geneticAlgorithm.addGenetics(p->genetics());
		s.remove_actor(*p);
	    }

	    return p->isDead();
	}), pigs.end());

	for (ui::events::event &e : event_source) {
	    // event heeft een methode handle_quit die controleert
	    // of de gebruiker de applicatie wilt sluiten, en zo ja
	    // de meegegeven functie (of lambda) aanroept om met het
	    // bijbehorende quit_event
	    //
	    e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
	}
    });
}
