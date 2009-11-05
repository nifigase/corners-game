/*
 * int_applicator.hpp
 *
 *  Created on: Sep 29, 2009
 *      Author: andrew
 */
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/type_traits/is_same.hpp>

#ifndef APPLICATOR_HPP_
#define APPLICATOR_HPP_

namespace aux {

template< typename P, template<P> class F, bool done = true >
struct applicator_impl
{
    template<
          typename Iterator
        , typename LastIterator
        >
    static void execute(
          Iterator*
        , LastIterator*
        )
    {}

    ///for 1 arg

	template<
		  typename Arg1
		, typename Iterator
		, typename LastIterator
		>
	static void execute(
		  Arg1&
		, Iterator*
		, LastIterator*
		)
	{}

	///for 2 arg

	template<
		  typename Arg1
		, typename Arg2
		, typename Iterator
		, typename LastIterator
		>
	static void execute(
		  Arg1&
		, Arg2&
		, Iterator*
		, LastIterator*
		)
	{}

	///for 3 arg

	template<
		  typename Arg1
		, typename Arg2
		, typename Arg3
		, typename Iterator
		, typename LastIterator
		>
	static void execute(
		  Arg1&
		, Arg2&
		, Arg3&
		, Iterator*
		, LastIterator*
		)
	{}

	///for 4 arg

	template<
		  typename Arg1
		, typename Arg2
		, typename Arg3
		, typename Arg4
		, typename Iterator
		, typename LastIterator
		>
	static void execute(
		  Arg1&
		, Arg2&
		, Arg3&
		, Arg4&
		, Iterator*
		, LastIterator*
		)
	{}
};

//specialization for non-terminal case
template<typename P, template<P> class F>
struct applicator_impl<P, F, false>
{

    template<
          typename Iterator
        , typename LastIterator
        >
	struct helper {
        typedef typename boost::mpl::deref<Iterator>::type item_t;
        typedef F<item_t::value> F_t;
        typedef typename boost::mpl::next<Iterator>::type next_iter_t;
        typedef applicator_impl<P, F, boost::is_same<next_iter_t,LastIterator>::value> next_applicator_t;
	};

    template<
          typename Iterator
        , typename LastIterator
        >
    static void execute(
          Iterator*
        , LastIterator*
        )
    {
    	typedef helper<Iterator, LastIterator> h;
        typename h::F_t f;
        f();
        typedef typename h::next_applicator_t at;
        at::execute((typename h::next_iter_t*)0, (LastIterator*)0);
    }

    ///for 1 arg

    template<
		  typename Arg1
        , typename Iterator
        , typename LastIterator
        >
    static void execute(
    	  Arg1& arg1
        , Iterator*
        , LastIterator*
        )
    {
    	typedef helper<Iterator, LastIterator> h;
    	typename h::F_t f;
        f(arg1);
        typedef typename h::next_applicator_t at;
        at::execute(arg1, (typename h::next_iter_t *)0, (LastIterator*)0);
    }

    ///for 2 arg

    template<
		  typename Arg1
		, typename Arg2
        , typename Iterator
        , typename LastIterator
        >
    static void execute(
    	  Arg1& arg1
    	, Arg2& arg2
        , Iterator*
        , LastIterator*
        )
    {
    	typedef helper<Iterator, LastIterator> h;
    	typename h::F_t f;
        f(arg1, arg2);
        h::next_applicator_t::execute(arg1, arg2, (typename h::next_iter_t*)0, (LastIterator*)0);
    }

    ///for 3 arg

    template<
		  typename Arg1
		, typename Arg2
		, typename Arg3
        , typename Iterator
        , typename LastIterator
        >
    static void execute(
    	  Arg1& arg1
    	, Arg2& arg2
    	, Arg3& arg3
        , Iterator*
        , LastIterator*
        )
    {
    	typedef helper<Iterator, LastIterator> h;
    	typename h::F_t f;
        f(arg1, arg2, arg3);
        h::next_applicator_t::execute(arg1, arg2, arg3, (typename h::next_iter_t*)0, (LastIterator*)0);
    }

    ///for 4 arg

    template<
		  typename Arg1
		, typename Arg2
		, typename Arg3
		, typename Arg4
        , typename Iterator
        , typename LastIterator
        >
    static void execute(
    	  Arg1& arg1
    	, Arg2& arg2
    	, Arg3& arg3
    	, Arg4& arg4
        , Iterator*
        , LastIterator*
        )
    {
    	typedef helper<Iterator, LastIterator> h;
    	typename h::F_t f;
        f(arg1, arg2, arg3, arg4);
        h::next_applicator_t::execute(arg1, arg2, arg3, arg4, (typename h::next_iter_t*)0, (LastIterator*)0);
    }
};

template<
	  typename P
	, template<P> class F
	, typename Sequence
	>
struct seq_type_resolver {

	BOOST_MPL_ASSERT(( boost::mpl::is_sequence<Sequence> ));

    typedef typename boost::mpl::begin<Sequence>::type first;
    typedef typename boost::mpl::end<Sequence>::type last;
    typedef applicator_impl<P, F, boost::is_same<first,last>::value> type;
};

template<
	typename P
	, template<P> class F
    , typename Sequence //of P
    >
inline
void apply(/* for deduction?: */Sequence* = 0) {
	typedef seq_type_resolver<P, F, Sequence> str;
	str::type::execute((typename str::first*)0, (typename str::last*)0);
}

template<
	typename P
	, template<P> class F
    , typename Sequence //of P
    , typename Arg1
    >
inline
void apply(Arg1& arg1, /* for deduction?: */Sequence* = 0) {
	typedef seq_type_resolver<P, F, Sequence> str;
	str::type::execute(arg1, (typename str::first*)0, (typename str::last*)0);
}

template<
	typename P
	, template<P> class F
    , typename Sequence //of P
    , typename Arg1
    , typename Arg2
    >
inline
void apply(Arg1& arg1, Arg2& arg2, /* for deduction?: */Sequence* = 0) {
	typedef seq_type_resolver<P, F, Sequence> str;
	str::type::execute(arg1, arg2, (typename str::first*)0, (typename str::last*)0);
}

template<
	typename P
	, template<P> class F
    , typename Sequence //of P
    , typename Arg1
    , typename Arg2
    , typename Arg3
    >
inline
void apply(Arg1& arg1, Arg2& arg2, Arg3& arg3, /* for deduction?: */Sequence* = 0) {
	typedef seq_type_resolver<P, F, Sequence> str;
	str::type::execute(arg1, arg2, arg3, (typename str::first*)0, (typename str::last*)0);
}

template<
	typename P
	, template<P> class F
    , typename Sequence //of P
    , typename Arg1
    , typename Arg2
    , typename Arg3
    , typename Arg4
    >
inline
void apply(Arg1& arg1, Arg2& arg2, Arg3& arg3, Arg4& arg4, /* for deduction?: */Sequence* = 0) {
	typedef seq_type_resolver<P, F, Sequence> str;
	str::type::execute(arg1, arg2, arg3, arg4, (typename str::first*)0, (typename str::last*)0);
}

}//NS
#endif /* INT_APPLICATOR_HPP_ */
