#include <gtest/gtest.h>
#include <ixxor/itl/ring.hpp>
#include <vector>
#include <algorithm>
#include <string>

static_assert(
    std::is_same<
        typename std::iterator_traits<
            ixxor::itl::ring<double>::iterator
            >::iterator_category,
        std::random_access_iterator_tag
        >::value,
    "Must be random access iterator."
    );


TEST(itl_test, ring_empty)
{
    ixxor::itl::ring<double> r;
    EXPECT_TRUE(r.empty());
}

TEST(itl_test, ring_size)
{
    ixxor::itl::ring<double> r(4);
    EXPECT_EQ(4, r.max_size());
    r.push_back(1.0);
    EXPECT_EQ(1, r.size());
    r.push_back(2.0);
    EXPECT_EQ(2, r.size());
    r.push_back(3.0);
    EXPECT_EQ(3, r.size());
    r.push_back(4.0);
    EXPECT_EQ(4, r.size());
    r.push_back(5.0);
    EXPECT_EQ(4, r.size());
    // And it begins with 2.0;
}

TEST(itl_test, ring_iterators)
{
    ixxor::itl::ring<double> r_empty;
    EXPECT_EQ(r_empty.begin(), r_empty.end());
    ixxor::itl::ring<double> r{1.0, 2.0, 3.0, 4.0};
    EXPECT_EQ(4, r.size());
    std::vector<double> z_copy;
    std::copy(r.begin(), r.end(), std::back_inserter(z_copy));
    EXPECT_EQ(1.0, z_copy[0]);
    EXPECT_EQ(2.0, z_copy[1]);
    EXPECT_EQ(3.0, z_copy[2]);
    EXPECT_EQ(4.0, z_copy[3]);
    // OK add one more.
    r.push_back(5.0);
    z_copy.clear();
    std::copy(r.begin(), r.end(), std::back_inserter(z_copy));
    EXPECT_EQ(4, z_copy.size());
    EXPECT_EQ(2.0, z_copy[0]);
    EXPECT_EQ(3.0, z_copy[1]);
    EXPECT_EQ(4.0, z_copy[2]);
    EXPECT_EQ(5.0, z_copy[3]);
    // Add another one
    r.push_back(6.0);
    z_copy.clear();
    std::copy(r.begin(), r.end(), std::back_inserter(z_copy));
    EXPECT_EQ(4, z_copy.size());
    EXPECT_EQ(3.0, z_copy[0]);
    EXPECT_EQ(4.0, z_copy[1]);
    EXPECT_EQ(5.0, z_copy[2]);
    EXPECT_EQ(6.0, z_copy[3]);
}

TEST(itl_test, ring_constructors_1)
{
    // A plain one (filled)
    ixxor::itl::ring<double> r1{1.0, 2.0, 3.0, 4.0};
    ixxor::itl::ring<double> r2(r1);
    // Must be the same.
    EXPECT_EQ(4, r1.size());
    EXPECT_EQ(r1.size(), r2.size());
    EXPECT_EQ(r1.max_size(), r2.max_size());
    std::vector<double> z_copy;
    std::copy(r2.begin(), r2.end(), std::back_inserter(z_copy));
    EXPECT_EQ(1.0, z_copy[0]);
    EXPECT_EQ(2.0, z_copy[1]);
    EXPECT_EQ(3.0, z_copy[2]);
    EXPECT_EQ(4.0, z_copy[3]);
}

TEST(itl_test, ring_constructors_2)
{
    // A moved one (filled)
    ixxor::itl::ring<double> r1{1.0, 2.0, 3.0, 4.0};
    EXPECT_EQ(4, r1.size());
    r1.push_back(5.0);
    EXPECT_EQ(4, r1.size());
    ixxor::itl::ring<double> r2(r1);
    EXPECT_EQ(r1.size(), r2.size());
    EXPECT_EQ(r1.max_size(), r2.max_size());
    std::vector<double> z_copy;
    std::copy(r2.begin(), r2.end(), std::back_inserter(z_copy));
    EXPECT_EQ(2.0, z_copy[0]);
    EXPECT_EQ(3.0, z_copy[1]);
    EXPECT_EQ(4.0, z_copy[2]);
    EXPECT_EQ(5.0, z_copy[3]);
}

TEST(itl_test, ring_constructors_3)
{
    // A moved one (filled) -- move constructor
    ixxor::itl::ring<double> r1{1.0, 2.0, 3.0, 4.0};
    r1.push_back(5.0);
    ixxor::itl::ring<double> r2{std::move(r1)};
    EXPECT_EQ(4, r1.size());
    // Must be the same.
    EXPECT_EQ(4, r2.size());
    EXPECT_EQ(4, r2.max_size());
    std::vector<double> z_copy;
    std::copy(r2.begin(), r2.end(), std::back_inserter(z_copy));
    EXPECT_EQ(2.0, z_copy[0]);
    EXPECT_EQ(3.0, z_copy[1]);
    EXPECT_EQ(4.0, z_copy[2]);
    EXPECT_EQ(5.0, z_copy[3]);
}

TEST(itl_test, ring_constructors_4)
{
    // A plain one (filled) -- move constructor
    ixxor::itl::ring<double> r1{1.0, 2.0, 3.0, 4.0};
    ixxor::itl::ring<double> r2{std::move(r1)};
    EXPECT_EQ(4, r1.size());
    // Must be the same.
    EXPECT_EQ(4, r2.size());
    EXPECT_EQ(4, r2.max_size());
    std::vector<double> z_copy;
    std::copy(r2.begin(), r2.end(), std::back_inserter(z_copy));
    EXPECT_EQ(1.0, z_copy[0]);
    EXPECT_EQ(2.0, z_copy[1]);
    EXPECT_EQ(3.0, z_copy[2]);
    EXPECT_EQ(4.0, z_copy[3]);
}


TEST(itl_test, ring_assignment)
{
    // A moved one (filled) -- move constructor
    ixxor::itl::ring<double> r1{1.0, 2.0, 3.0, 4.0};
    r1.push_back(5.0);
    ixxor::itl::ring<double> r2{1.1,2.2,3.3,4.4,5.5,6.6,7.7};
    EXPECT_EQ(4, r1.size());
    EXPECT_EQ(7, r2.size());
    EXPECT_EQ(7, r2.max_size());
    // Copy assignment
    r2 = r1;
    EXPECT_EQ(4, r2.size());
    EXPECT_EQ(4, r2.max_size());
    std::vector<double> z_copy;
    std::copy(r2.begin(), r2.end(), std::back_inserter(z_copy));
    EXPECT_EQ(2.0, z_copy[0]);
    EXPECT_EQ(3.0, z_copy[1]);
    EXPECT_EQ(4.0, z_copy[2]);
    EXPECT_EQ(5.0, z_copy[3]);
    ixxor::itl::ring<double> r4{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8};
    r4 = std::move(r1);
    EXPECT_EQ(4, r4.size());
    EXPECT_EQ(4, r4.max_size());
    z_copy.clear();
    std::copy(r4.begin(), r4.end(), std::back_inserter(z_copy));
    EXPECT_EQ(2.0, z_copy[0]);
    EXPECT_EQ(3.0, z_copy[1]);
    EXPECT_EQ(4.0, z_copy[2]);
    EXPECT_EQ(5.0, z_copy[3]);
}

TEST(itl_test, ring_back_inserter)
{
    ixxor::itl::ring<double> r1 = {2.0, 3.0, 4.0, 5.0};
    // back-inserter
    ixxor::itl::ring<double> r2(4);
    std::copy(r1.begin(), r1.end(), std::back_inserter(r2));
    EXPECT_EQ(4, r2.size());
    std::vector<double> z_copy;
    std::copy(r2.begin(), r2.end(), std::back_inserter(z_copy));
    EXPECT_EQ(2.0, z_copy[0]);
    EXPECT_EQ(3.0, z_copy[1]);
    EXPECT_EQ(4.0, z_copy[2]);
    EXPECT_EQ(5.0, z_copy[3]);
}

TEST(itl_test, ring_of_ints)
{
    ixxor::itl::ring<int> r1{1,2,3,4};
    r1.push_back(5);
    auto beg = r1.begin();
    EXPECT_EQ(2, *beg);
    EXPECT_EQ(2, beg[0]);
    EXPECT_EQ(3, beg[1]);
    EXPECT_EQ(4, beg[2]);
    EXPECT_EQ(5, beg[3]);
}

TEST(itl_test, ring_of_strings)
{
    ixxor::itl::ring<std::string> r1{"a","b","c","d"};
    r1.push_back("e");
    auto beg = r1.begin();
    EXPECT_EQ("b", *beg);
    EXPECT_EQ("b", beg[0]);
    EXPECT_EQ("c", beg[1]);
    EXPECT_EQ("d", beg[2]);
    EXPECT_EQ("e", beg[3]);
}

