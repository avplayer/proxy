// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_SERVICES_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_SERVICES_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/static_assert.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace simplify
{

namespace services
{

template
<
    typename Geometry,
    typename CSTag = geometry::cs_tag_t<Geometry>
>
struct default_strategy
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry's coordinate systems.",
        Geometry, CSTag);
};

template <typename Strategy>
struct strategy_converter
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Strategy.",
        Strategy);
};


} // namespace services

}} // namespace strategies::simplify

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_SERVICES_HPP
