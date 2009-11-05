/*
 * data.hpp
 *
 *  Created on: Sep 5, 2009
 *      Author: andrew
 */
#include <vector>
#include <algorithm>

#include "boost/multi_array.hpp"

#ifndef DATA_HPP_
#define DATA_HPP_

namespace cornerspp { namespace core {

typedef char cell_data_t;

/// colors

namespace colors {
	typedef cell_data_t color_t;

	const color_t green = 'G';
	const color_t yellow = 'Y';

	color_t opposite(color_t clr);
};

/// corners

enum corners { NW, SE };

corners opposite(corners c);

class position {
public:
	position() : x_(0), y_(0) {}
	position(size_t x, size_t y) : x_(x), y_(y) {}

	inline size_t x() const { return x_; }
	inline size_t y() const { return y_; }

	inline size_t& x() { return x_; }
	inline size_t& y() { return y_; }

	bool operator==(const position& rhs) const {
		return (x_ == rhs.x_ && y_ == rhs.y_);
	}
	bool operator!=(const position& rhs) const {
		return !(*this == rhs);
	}
private:
	size_t x_;
	size_t y_;
};

class cell {
public:
	static const cell_data_t no_caps = ' ';

	cell(const cell_data_t value, size_t x, size_t y) : value_(value), pos_(x, y) {}
	cell(const cell_data_t value, const position& pos) : value_(value), pos_(pos) {}

	cell(const cell& rhs) : value_(rhs.value_), pos_(rhs.pos_) {}

	bool free() const { return value_ == no_caps; }
	cell_data_t value() const { return value_; }

	inline position pos() const { return pos_; }
private:
	cell_data_t value_;
	position pos_;
};

class move {
public:
	/**
	 * create 'empty' move (cap stays where it is)
	 */
	explicit move(const cell& src) : path_(), estimate_(0.), estimate_stage_(0) {
		path_.push_back(src.pos());
	}
	explicit move(const position& src) : path_(), estimate_(0.), estimate_stage_(0) {
		path_.push_back(src);
	}

	move(const cell& src, const position& dst) : path_(), estimate_(0.), estimate_stage_(0) {
		path_.push_back(src.pos());
		path_.push_back(dst);
	}
	move(const position& src, const position& dst) : path_(), estimate_(0.), estimate_stage_(0) {
		path_.push_back(src);
		path_.push_back(dst);
	}
	move(const move& rhs) : path_(rhs.path_), estimate_(0.), estimate_stage_(0) {}

	void advance(const position& dst) {
		path_.push_back(dst);
	}

	const position& last() const {
		return path_.back();
	}
	const position& first() const {
		return path_.front();
	}

	inline double estimate() const {
		return estimate_;
	}
	inline int estimate_stage() const { return estimate_stage_; }

	void save_estimate(int estimate_stage, double estimate) const {
		estimate_stage_ = estimate_stage;
		estimate_ = estimate;
	}

	bool contains(const position& pos) const {
		return std::find(path_.begin(), path_.end(), pos) != path_.end();
	}

	size_t size() const { return path_.size(); }

	bool operator==(const move& rhs) const {
		return (first() == rhs.first() && last() == rhs.last());
	}

private:
	typedef std::vector<position> path_t;
	path_t path_;

	mutable double estimate_;
	mutable int estimate_stage_;

public:
	typedef path_t::const_iterator path_iter_t;

	inline path_iter_t begin() const { return path_.begin(); }
	inline path_iter_t end() const { return path_.end(); }
};

class player;
class caps_iterator;

class board {
private:
	template <typename DataRef>
	struct row_handle;

	typedef boost::multi_array<cell_data_t, 2> data_t;
public:
	const size_t DIM, CAP_DIM;

	/**
	 * Initializes clear board: (ex. for DIM = 4 and CAP_DIM = 2)
	 * |YY--|
	 * |Y---|
	 * |---G|
	 * |--GG|
	 * Where nwColor = Y
	 * 		 seColor = G
	 */
	board(colors::color_t nwColor = colors::yellow, colors::color_t seColor = colors::green,
			size_t dim = 8, size_t cap_dim = 5);

	row_handle<data_t&> operator[] (size_t r) {
		return row_handle<data_t&>(cells_, r);
	}
	const row_handle<const data_t&> operator[] (size_t r) const {
		return row_handle<const data_t&>(cells_, r);
	}

	cell_data_t operator[] (const position& pos) const {
		return cells_[pos.y()][pos.x()];
	}

	cell_data_t& operator[] (const position& pos) {
		return cells_[pos.y()][pos.x()];
	}

	caps_iterator caps_begin(const player& p) const;
	caps_iterator caps_end(const player& p) const;

	caps_iterator caps_begin(const colors::color_t& c) const;
	caps_iterator caps_end(const colors::color_t& c) const;

	cell get_cell(size_t x, size_t y) const {
		return get_cell(position(x, y));
	}
	cell get_cell(const position& pos) const {
		return cell::cell((*this)[pos], pos);
	}

	colors::color_t color(corners c) const {
		if (c == NW)
			return nwColor_;
		return seColor_;
	}

	bool pos_in_corner(const position& pos, corners c) const {
		if (c == NW)
			return pos.x() + pos.y() < CAP_DIM;
		else
			return ((DIM - 1) - pos.x() + (DIM - 1) - pos.y()) < CAP_DIM;
	}

	void apply(const move& m) {
		std::swap( (*this)[m.first()], (*this)[m.last()] );
	}

	void applyPartial(const position& p1, const position& p2) {
		std::swap( (*this)[p1], (*this)[p2] );
	}

	void revert(const move& m) {
		apply(m);
	}

private:
	const colors::color_t nwColor_;
	const colors::color_t seColor_;

	data_t cells_;

	template <typename DataRef>
	struct row_handle {
		DataRef cells_;
		const size_t row_;

		row_handle(DataRef cells, size_t row) : cells_(cells), row_(row) {}

		data_t::reference::reference operator[] (size_t c) {
			return cells_[row_][c];
		}
		data_t::const_reference::const_reference operator[] (size_t c) const {
			return cells_[row_][c];
		}
	};
};

class caps_iterator {
public:
	static caps_iterator end(const board& b, colors::color_t c) {
		return caps_iterator(b, c, position(0, b.DIM));
	}

	caps_iterator(const board& b, colors::color_t c) : b_(b), color_(c), pos_(-1, 0) {
		++*this;
	}

	cell operator* () const {
		return cell(color_, pos_);
	}

	caps_iterator& operator++() {
		do {
			move_next();
			if (pos_.y() >= b_.DIM) return *this; //end reached
			if (b_[pos_] == color_)
				return *this;
		} while(true);
	}
	caps_iterator operator++(int) {
		caps_iterator tmp = *this;
		++(*this);
		return tmp;
	}

	bool operator==(const caps_iterator& rhs) const {
		return (&b_ == &(rhs.b_) && color_ == rhs.color_ && pos_ == rhs.pos_);
	}
	bool operator!=(const caps_iterator& rhs) const {
		return ! (*this == rhs);
	}
private:
	caps_iterator(const board& b, colors::color_t c, position pos) : b_(b), color_(c), pos_(pos) {}
	void move_next() {
		++pos_.x();
		if (pos_.x() >= b_.DIM) {
			pos_.x() = 0;
			++pos_.y();
		}
	}

	const board& b_;
	const colors::color_t color_;
	position pos_;
};

/**
 * May be a user agent or an automatic player
 */
class player {
public:
	player(corners corner) : corner_(corner) {}

	virtual move make_move(const board& b) const = 0;

	corners corner() const { return corner_; }
private:
	corners corner_;
};

const size_t MAX_STAGES = 4; //compile-time constant

/**
 * Selected moves per iteration. For example:
 * 7 - 1st iteration. 7 most profitable moves selected
 * 3 - 2nd iteration. 3 most profitable moves selected
 * 2 - 3rd iteration. 2 most profitable moves selected
 * 0 (or MAX_STAGES reached) - no more iterations, will use ANY of 2 previously selected moves
 */
typedef boost::array<int, MAX_STAGES> select_factor_t;

}}//NS

#endif /* DATA_HPP_ */
