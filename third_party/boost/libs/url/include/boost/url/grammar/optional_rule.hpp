//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//

#ifndef BOOST_URL_GRAMMAR_OPTIONAL_RULE_HPP
#define BOOST_URL_GRAMMAR_OPTIONAL_RULE_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/optional.hpp>
#include <boost/url/error_types.hpp>
#include <boost/url/grammar/type_traits.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace urls {
namespace grammar {

namespace implementation_defined {
template<class Rule>
struct optional_rule_t
    : private empty_value<Rule>
{
    using value_type = boost::optional<
        typename Rule::value_type>;

    system::result<value_type>
    parse(
        char const*& it,
        char const* end) const;

    constexpr
    optional_rule_t(
        Rule const& r) noexcept
        : empty_value<Rule>(
            empty_init,
            r)
    {
    }
};
} // implementation_defined

/** Match a rule, or the empty string

    Optional BNF elements are denoted with
    square brackets. If the specified rule
    returns any error it is treated as if
    the rule did not match.

    @par Value Type
    @code
    using value_type = optional< typename Rule::value_type >;
    @endcode

    @par Example
    Rules are used with the function @ref grammar::parse.
    @code
    system::result< optional< core::string_view > > rv = parse( "", optional_rule( token_rule( alpha_chars ) ) );
    @endcode

    @par BNF
    @code
    optional     = [ rule ]
    @endcode

    @par Specification
    @li <a href="https://datatracker.ietf.org/doc/html/rfc5234#section-3.8"
        >3.8.  Optional Sequence (rfc5234)</a>

    @param r The rule to match
    @return The adapted rule

    @see
        @ref alpha_chars,
        @ref parse,
        @ref optional,
        @ref token_rule.
*/
template<BOOST_URL_CONSTRAINT(Rule) R>
auto
constexpr
optional_rule(
    R const& r) ->
        implementation_defined::optional_rule_t<R>
{
    BOOST_STATIC_ASSERT(grammar::is_rule<R>::value);
    return { r };
}

} // grammar
} // urls
} // boost

#include <boost/url/grammar/impl/optional_rule.hpp>

#endif
