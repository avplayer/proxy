// Copyright David Abrahams 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This is really an incomplete test; should be fleshed out.

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/new_iterator_tests.hpp>

#include <boost/call_traits.hpp>
#include <type_traits>

#include "static_assert_same.hpp"

// This is a really, really limited test so far.  All we're doing
// right now is checking that the postfix++ proxy for single-pass
// iterators works properly.
template <class Ref>
class counter_iterator
  : public boost::iterator_facade<
        counter_iterator<Ref>
      , int const
      , boost::single_pass_traversal_tag
      , Ref
    >
{
 public:
    counter_iterator() {}
    counter_iterator(int* state) : state(state) {}

    void increment()
    {
        ++*state;
    }

    Ref
    dereference() const
    {
        return *state;
    }

    bool equal(counter_iterator const& y) const
    {
        return *this->state == *y.state;
    }

    int* state;
};

struct proxy
{
    proxy(int& x) : state(x) {}

    operator int const&() const
    {
        return state;
    }

    int& operator=(int x) { state = x; return state; }

    int& state;
};

struct value
{
    int increment_count;
    int private_mutator_count;
    int& shared_mutator_count;

    explicit value(int& shared_mutator_count) :
        increment_count(0),
        private_mutator_count(0),
        shared_mutator_count(shared_mutator_count)
    {
    }

    // non-const member function
    void mutator()
    {
        ++private_mutator_count;
        ++shared_mutator_count;
    }
};

struct input_iter
  : boost::iterator_facade<
        input_iter
      , value
      , boost::single_pass_traversal_tag
      , value
    >
{
 public:
    explicit input_iter(value& val) : state(&val) {}

    void increment()
    {
        ++(state->increment_count);
    }
    value
    dereference() const
    {
        return *state;
    }

    bool equal(input_iter const&) const
    {
        return false;
    }

 private:
    value* state;
};

template <class T>
struct wrapper
{
    T m_x;
    explicit wrapper(typename boost::call_traits<T>::param_type x)
        : m_x(x)
    { }
    template <class U>
    wrapper(const wrapper<U>& other,
        typename std::enable_if< std::is_convertible<U,T>::value >::type* = 0)
        : m_x(other.m_x)
    { }
};

struct iterator_with_proxy_reference
    : boost::iterator_facade<
          iterator_with_proxy_reference
        , wrapper<int>
        , boost::incrementable_traversal_tag
        , wrapper<int&>
      >
{
    int& m_x;
    explicit iterator_with_proxy_reference(int& x)
        : m_x(x)
    { }

    void increment()
    { }
    wrapper<int&> dereference() const
    { return wrapper<int&>(m_x); }
};

template <class I, class A>
struct abstract_iterator
    : boost::iterator_facade<
          abstract_iterator<I, A>
        , A&
        // In order to be value type as a reference, traversal category has
        // to satisfy least forward traversal.
        , boost::forward_traversal_tag
        , A&
      >
{
    abstract_iterator(I iter) : iter(iter) {}

    void increment()
    { ++iter; }

    A& dereference() const
    { return *iter; }

    bool equal(abstract_iterator const& y) const
    { return iter == y.iter; }

    I iter;
};

struct base
{
    virtual void assign(const base&) = 0;
    virtual bool equal(const base&) const = 0;
};

struct derived : base
{
    derived(int state) : state(state) { }
    derived(const derived& d) : state(d.state) { }
    derived(const base& b) { derived::assign(b); }

    virtual void assign(const base& b)
    {
        state = dynamic_cast<const derived& >(b).state;
    }

    virtual bool equal(const base& b) const
    {
        return state == dynamic_cast<const derived&>(b).state;
    }

    int state;
};

inline bool operator==(const base& lhs, const base& rhs)
{
    return lhs.equal(rhs);
}

int main()
{
    {
        int state = 0;
        boost::readable_iterator_test(counter_iterator<int const&>(&state), 0);
        state = 3;
        boost::readable_iterator_test(counter_iterator<proxy>(&state), 3);
        boost::writable_iterator_test(counter_iterator<proxy>(&state), 9, 7);
        BOOST_TEST(state == 8);
    }

    {
        // test for a fix to http://tinyurl.com/zuohe
        // These two lines should be equivalent (and both compile)
        int shared_mutator_count = 0;
        value val(shared_mutator_count);
        input_iter p(val);
        (*p).mutator();
        p->mutator();
        BOOST_TEST_EQ(val.increment_count, 0);
        BOOST_TEST_EQ(val.private_mutator_count, 0); // mutator() should be invoked on an object returned by value
        BOOST_TEST_EQ(shared_mutator_count, 2);

        STATIC_ASSERT_SAME(input_iter::pointer, std::remove_cv<std::remove_reference<decltype(p.operator->())>::type>::type);
    }

    {
        // Test that accessing dereferenced value of a post-incremented iterator works
        int shared_mutator_count = 0;
        value val(shared_mutator_count);
        input_iter p(val);
        (*p++).mutator();
        (p++)->mutator();
        BOOST_TEST_EQ(val.increment_count, 2);
        BOOST_TEST_EQ(val.private_mutator_count, 0); // mutator() should be invoked on an object returned by value
        BOOST_TEST_EQ(shared_mutator_count, 2);
    }

    {
        int x = 0;
        iterator_with_proxy_reference i(x);
        BOOST_TEST(x == 0);
        BOOST_TEST(i.m_x == 0);
        ++(*i).m_x;
        BOOST_TEST(x == 1);
        BOOST_TEST(i.m_x == 1);
        ++i->m_x;
        BOOST_TEST(x == 2);
        BOOST_TEST(i.m_x == 2);
    }

    {
        derived d(1);
        boost::readable_iterator_test(abstract_iterator<derived *, base>(&d), derived(1));
    }

    return boost::report_errors();
}
