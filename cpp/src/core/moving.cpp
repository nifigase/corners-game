/*
 * detail.hpp
 *
 *  Created on: Sep 7, 2009
 *      Author: andrew
 */
#include <vector>
#include "boost/mpl/vector_c.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/insert_range.hpp"

#include "lib/applicator.hpp"

#include "moving.hpp"

namespace cornerspp { namespace core { namespace moving {

using ::cornerspp::core::board;
using ::cornerspp::core::position;
using ::cornerspp::core::cell;
using ::cornerspp::core::move;

enum directions {
	NW, N, NE, E, SE, S, SW, W
};

/// neighbors

template<directions DIR>
bool has_neighbor(const board& b, const position& p);

template<>
bool has_neighbor<E>(const board& b, const position& p) { return p.x() < b.DIM - 1; }

template<>
bool has_neighbor<S>(const board& b, const position& p) { return p.y() < b.DIM - 1; }

template<>
bool has_neighbor<W>(const board&, const position& p) { return p.x() > 0; }

template<>
bool has_neighbor<N>(const board&, const position& p) { return p.y() > 0; }

template<>
bool has_neighbor<SE>(const board& b, const position& p) {
	return has_neighbor<S>(b, p) && has_neighbor<E>(b, p);
}
template<>
bool has_neighbor<SW>(const board& b, const position& p) {
	return has_neighbor<S>(b, p) && has_neighbor<W>(b, p);
}
template<>
bool has_neighbor<NW>(const board& b, const position& p) {
	return has_neighbor<N>(b, p) && has_neighbor<W>(b, p);
}
template<>
bool has_neighbor<NE>(const board& b, const position& p) {
	return has_neighbor<N>(b, p) && has_neighbor<E>(b, p);
}

template<directions DIR>
cell neighbor(const board& b, const position& p);

template<>
cell neighbor<E>(const board& b, const position& p) {
	return b.get_cell(p.x()+1, p.y());
}
template<>
cell neighbor<SE>(const board& b, const position& p) {
	return b.get_cell(p.x()+1, p.y()+1);
}
template<>
cell neighbor<S>(const board& b, const position& p) {
	return b.get_cell(p.x(), p.y()+1);
}
template<>
cell neighbor<SW>(const board& b, const position& p) {
	return b.get_cell(p.x()-1, p.y()+1);
}
template<>
cell neighbor<W>(const board& b, const position& p) {
	return b.get_cell(p.x()-1, p.y());
}
template<>
cell neighbor<NW>(const board& b, const position& p) {
	return b.get_cell(p.x()-1, p.y()-1);
}
template<>
cell neighbor<N>(const board& b, const position& p) {
	return b.get_cell(p.x(), p.y()-1);
}
template<>
cell neighbor<NE>(const board& b, const position& p) {
	return b.get_cell(p.x()+1, p.y()-1);
}

/// hops

/**
 * one in line (vertical, horizontal)
 * new move (with hop) is appended to moves.
 */
template<directions DIR>
bool add_line_hop(const board& b, const move& m, std::vector<move>& moves) {

	if (!has_neighbor<DIR>(b, m.last())) return false;
	cell n = neighbor<DIR>(b, m.last());
	if (n.free()) return false;

	if (!has_neighbor<DIR>(b, n.pos())) return false;
	cell dst = neighbor<DIR>(b, n.pos());
	if (!dst.free()) return false;

	if (m.contains(dst.pos())) return false;

	moves.push_back(m);
	moves.back().advance(dst.pos());
	return true;
}

/**
 * hatched hop.
 * new move (with hop) is appended to moves.
 * If DIR is NW then N1 is N and N2 is W
 */
template<directions DIR, directions N1, directions N2>
bool add_hatch_hop(const board& b, const move& m, std::vector<move>& moves) {

	if (!has_neighbor<DIR>(b, m.last())) return false;
	cell dst = neighbor<DIR>(b, m.last());
	if (!dst.free()) return false;
	if (m.contains(dst.pos())) return false;

	cell n1 = neighbor<N1>(b, m.last());
	cell n2 = neighbor<N2>(b, m.last());
	if (n1.free() && n2.free()) return false;

	moves.push_back(m);
	moves.back().advance(dst.pos());
	return true;
}

//defaults to line hops
template<directions DIR>
bool add_hop(const board& b, const move& m, std::vector<move>& moves) {
	return add_line_hop<DIR>(b, m, moves);
}

template<>
bool add_hop<SE>(const board& b, const move& m, std::vector<move>& moves) {
	return add_hatch_hop<SE, S, E>(b, m, moves);
}

template<>
bool add_hop<SW>(const board& b, const move& m, std::vector<move>& moves) {
	return add_hatch_hop<SW, S, W>(b, m, moves);
}

template<>
bool add_hop<NW>(const board& b, const move& m, std::vector<move>& moves) {
	return add_hatch_hop<NW, N, W>(b, m, moves);
}

template<>
bool add_hop<NE>(const board& b, const move& m, std::vector<move>& moves) {
	return add_hatch_hop<NE, N, E>(b, m, moves);
}

typedef boost::mpl::vector_c<directions,N,E,S,W> direct_dirs_seq;
typedef boost::mpl::vector_c<directions,NE,SE,SW,NW> hatched_dirs_seq;
typedef boost::mpl::insert_range<
	direct_dirs_seq, boost::mpl::end<direct_dirs_seq>::type, hatched_dirs_seq
>::type dirs_seq;

//typedef boost::mpl::vector_c<directions,N,NE,E,SE,S,SW,W,NW> dirs_seq;

template <directions DIR>
struct direct_moves_adder {
	void operator()(const board& b, const cell& c, std::vector<move>& moves) {
		if (has_neighbor<DIR>(b, c.pos())) {
			cell n = neighbor<DIR>(b, c.pos());
			if (n.free())
				moves.push_back(move(c, n.pos()));
		}
	}
};

void append_hops(const board& b, const move& m, std::vector<move>& moves);

template <directions DIR>
struct hops_appender {
	void operator()(const board& b, const move& m, std::vector<move>& moves) {
		if (m.size() > b.DIM) return;
		if (add_hop<DIR>(b, m, moves)) {
			move added = moves.back(); //cannot use reference cause vector will probably reallocate
			append_hops(b, added, moves);
		}
	}
};

void append_hops(const board& b, const move& m, std::vector<move>& moves) {
	aux::apply<directions, hops_appender, dirs_seq>(b, m, moves);
}

//public
void add_legal_moves(const board& b, const cell& c, std::vector<move>& moves) {

	aux::apply<directions, direct_moves_adder, direct_dirs_seq>(b, c, moves);

	move m(c);
	append_hops(b, m, moves);
}

///locking

template<directions DIR>
struct free_cells_counter {
	void operator()(const board& b, const cell& c, int remoteness, int& free_count) {
		if (remoteness == 0 || free_count > 0) return;
		if (!has_neighbor<DIR>(b, c.pos())) return;
		cell n = neighbor<DIR>(b, c.pos());
		if (n.free()) ++free_count;
		(*this)(b, n, remoteness-1, free_count);
	}
};

bool is_locked(const board& b, const cell& c) {
	int free_count = 0;
	const int direct_depth = 2;
	const int hatched_depth = 1;
	aux::apply<directions, free_cells_counter, direct_dirs_seq>(b, c, direct_depth, free_count);
	aux::apply<directions, free_cells_counter, hatched_dirs_seq>(b, c, hatched_depth, free_count);
	return free_count == 0;
}

bool has_locked_caps(const board& b, const player& p) {
	for (caps_iterator it = b.caps_begin(p); it != b.caps_end(p); ++it) {
		cell c = *it;
		if (is_locked(b, c))
			return true;
	}
	return false;
}

class move_cmp {
private:
	size_t DIM;
	//unique coef for each not-equal move
	int coef(const move& m) {
		return (m.first().y() * DIM + m.first().x()) * DIM * DIM + (m.last().y() * DIM + m.last().x());
	}
public:
	explicit move_cmp(const board& b) : DIM(b.DIM) {}
	bool operator()(const move& m1, const move& m2) {
		int c1 = coef(m1);
		int c2 = coef(m2);
		if (c1 != c2) return c1 < c2;
		//between equivalent moves we choose the shortest one
		return m1.size() < m2.size();
	}
};

void unique(const board& b, std::vector<move>& moves) {
	std::sort(moves.begin(), moves.end(), move_cmp(b));
	moves.erase(std::unique(moves.begin(), moves.end()), moves.end());
}

class hop_area {
public:
	hop_area(const position& p1, const position& p2) :
		p1_(p1), p2_(p2),
		x1(std::min(p1.x(), p2.x())),
		y1(std::min(p1.y(), p2.y())),
		x2(std::max(p1.x(), p2.x())),
		y2(std::max(p1.y(), p2.y())) {}

	bool in(const position& p) {
		return p.x() >= x1 && p.x() <= x2 && p.y() >= y1 && p.y() <= y2 &&
			p != p1_ && p != p2_;
	}
private:
	const position& p1_;
	const position& p2_;
	size_t x1, y1, x2, y2;
};
/**
 * Is move m is hopped through last position of move target
 */
bool is_hopped_through(const move& m, const move& target) {
	const position& pos = target.last();

	for (move::path_iter_t it = m.begin() + 1; it != m.end(); ++it) {
		const position& prev = *(it-1);
		const position& cur = *it;
		hop_area area(prev, cur);
		if (area.in(pos)) return true;
	}
	return false;
}

}}}
