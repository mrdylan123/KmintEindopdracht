#ifndef KMINT_PIGISLAND_RECTANGLE_HPP
#define KMINT_PIGISLAND_RECTANGLE_HPP

namespace kmint {
    namespace pigisland {
	class rectangle {
	public:
	    rectangle(int x, int y, int w, int h);
	    ~rectangle() = default;
	    rectangle(const rectangle& other) = default;
	    rectangle(rectangle&& other) noexcept = default;
	    rectangle& operator=(const rectangle& other) = default;
	    rectangle& operator=(rectangle&& other) noexcept = default;

	    int x() const { return x_; }
	    int y() const { return y_; }
	    int w() const { return w_; }
	    int h() const { return h_; }

	    bool overlaps(int x, int y, int w, int h) const;

	private:
	    int x_;
	    int y_;
	    int w_;
	    int h_;
	};
    }
}

#endif