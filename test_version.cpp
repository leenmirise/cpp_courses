#define BOOST_TEST_MODULE test_varsion

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUIT(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(version() > 0)
}

BOOST_AUTO_TEST_SUIT_END()