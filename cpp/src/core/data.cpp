
#include "core/data.hpp"

namespace cornerspp { namespace core {

namespace colors {
color_t opposite(color_t clr) {
	if (clr == green) return yellow;
	else return green;
}
}//NS

corners opposite(corners c) {
	if (c == NW) return SE;
	else return NW;
}

board::board(
		colors::color_t nwColor, colors::color_t seColor, size_t dim, size_t cap_dim) :
			DIM(dim), CAP_DIM(cap_dim), nwColor_(nwColor), seColor_(seColor),
			cells_(boost::extents[DIM][DIM]) {

	assert(CAP_DIM < DIM);
	for (size_t r = 0; r < DIM; ++r) {
		for (size_t c = 0; c < DIM; ++c) {
			position pos(c, r);
			if (pos_in_corner(pos, NW)) {
				cells_[r][c] = nwColor;
				continue;
			}
			if (pos_in_corner(pos, SE)) {
				cells_[r][c] = seColor;
				continue;
			}
			cells_[r][c] = cell::no_caps;
		}
	}

}

caps_iterator board::caps_begin(const player& p) const {
	return caps_iterator(*this, color(p.corner()));
}

caps_iterator board::caps_end(const player& p) const {
	return caps_iterator::end(*this, color(p.corner()));
}

caps_iterator board::caps_begin(const colors::color_t& c) const {
	return caps_iterator(*this, c);
}
caps_iterator board::caps_end(const colors::color_t& c) const {
	return caps_iterator::end(*this, c);
}

}}

