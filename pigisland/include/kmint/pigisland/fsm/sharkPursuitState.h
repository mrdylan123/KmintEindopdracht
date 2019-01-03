#ifndef KMINT_PIGISLAND_SHARKPURSUITSTATE_HPP
#define KMINT_PIGISLAND_SHARKPURSUITSTATE_HPP
#include "sharkState.h"

namespace kmint {
    namespace pigisland {
	class pig;

	class sharkPursuitState : public sharkState {
	public:
	    sharkPursuitState(shark* shark, pig* pig);
	    ~sharkPursuitState() = default;
	    sharkPursuitState(const sharkPursuitState& other) = delete;
	    sharkPursuitState(sharkPursuitState&& other) noexcept = delete;
	    sharkPursuitState& operator=(const sharkPursuitState& other) = delete;
	    sharkPursuitState& operator=(sharkPursuitState&& other) noexcept = delete;


	    void update(kmint::delta_time deltaTime) override;
	};
    }
}

#endif