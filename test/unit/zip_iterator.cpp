/**
 * @copyright 2021 MF
 * @author Brian Cairl
 */

// C++ Standard Library
#include <iterator>
#include <list>
#include <string>
#include <vector>

// GTest
#include <gtest/gtest.h>

// MF
#include <mf/zip_iterator.hpp>

TEST(ZipIterator, ForLoop)
{
  std::string s{"oooo"};
  std::vector<int> v{1, 1, 1, 1};

  ASSERT_EQ(s.size(), v.size());

  for (auto itr = mf::make_zip_iterator(s.begin(), v.begin()); itr != mf::make_zip_iterator(s.end(), v.end()); ++itr)
  {
    ASSERT_EQ(std::get<0>(*itr), 'o');
    ASSERT_EQ(std::get<1>(*itr), 1);
  }
}


TEST(ZipIterator, ForLoopConst)
{
  const std::string s{"oooo"};
  const std::vector<int> v{1, 1, 1, 1};

  ASSERT_EQ(s.size(), v.size());

  for (auto itr = mf::make_zip_iterator(s.begin(), v.begin()); itr != mf::make_zip_iterator(s.cend(), v.end()); ++itr)
  {
    ASSERT_EQ(std::get<0>(*itr), 'o');
    ASSERT_EQ(std::get<1>(*itr), 1);
  }
}

TEST(ZipIterator, TraitsCommonIteratorCatagory)
{
  const std::string s{"oooo"};  // random access
  const std::vector<int> v{1, 1, 1, 1};  // random access

  auto zip_itr = mf::make_zip_iterator(s.begin(), v.begin());

  ASSERT_TRUE((std::is_same_v<
               std::iterator_traits<decltype(zip_itr)>::iterator_category,
               std::iterator_traits<decltype(s.begin())>::iterator_category>));

  ASSERT_TRUE((std::is_same_v<
               std::iterator_traits<decltype(zip_itr)>::iterator_category,
               std::iterator_traits<decltype(v.begin())>::iterator_category>));
}

TEST(ZipIterator, TraitsNoCommonIteratorCatagory)
{
  const std::string s{"oooo"};  // random access
  const std::list<int> l{1, 1, 1, 1};  // bidirectional iterator access

  auto zip_itr = mf::make_zip_iterator(s.begin(), l.begin());

  ASSERT_TRUE((std::is_same_v<std::iterator_traits<decltype(zip_itr)>::iterator_category, void>));
}

TEST(ZipIterator, PositiveOffset)
{
  const std::string s{"oooo"};  // random access
  const std::string l{"bbbb"};  // random access

  auto zip_itr_begin = mf::make_zip_iterator(s.begin(), l.begin());
  auto zip_itr_next = zip_itr_begin + 1;

  ASSERT_EQ(std::distance(zip_itr_begin, zip_itr_next), 1);
}

TEST(ZipIterator, NegativeOffset)
{
  const std::string s{"oooo"};  // random access
  const std::string l{"bbbb"};  // random access

  auto zip_itr_end = mf::make_zip_iterator(s.end(), l.end());
  auto zip_itr_prev = zip_itr_end - 1;

  ASSERT_EQ(std::distance(zip_itr_end, zip_itr_prev), -1);
}

TEST(ZipIterator, StdPrev)
{
  const std::string s{"oooo"};  // random access
  const std::string l{"bbbb"};  // random access

  auto zip_itr_end = mf::make_zip_iterator(s.end(), l.end());
  auto zip_itr_prev = std::prev(zip_itr_end);

  ASSERT_EQ(std::distance(zip_itr_end, zip_itr_prev), -1);
}
