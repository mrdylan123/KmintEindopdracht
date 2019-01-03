#ifndef KMINT_PIGISLAND_SHARKSTATE_HPP
#define KMINT_PIGISLAND_SHARKSTATE_HPP
#include "state.h"
#include "../shark.hpp"

namespace kmint {
    namespace pigisland {
	class sharkState : public state {
	public:
	    sharkState(shark* shark);
	    ~sharkState() = default;
	    sharkState(const sharkState& other) = delete;
	    sharkState(sharkState&& other) noexcept = delete;
	    sharkState& operator=(const sharkState& other) = delete;
	    sharkState& operator=(sharkState&& other) noexcept = delete;

	    void update(kmint::delta_time deltaTime) override;
	protected:
	    shark* shark_;
	};
    }
}
#endif