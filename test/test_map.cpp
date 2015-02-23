/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl

Copyright(c) 2014 jwellbelove, rlindeman

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include <UnitTest++/UnitTest++.h>

#include <map>
#include <array>
#include <algorithm>
#include <utility>
#include <iterator>
#include <string>
#include <vector>

#include <iostream> // FIXME: remove with cout

#include "../map.h"

static const size_t SIZE = 10;

//typedef etl::map<std::string, int, SIZE, std::greater<std::string> >  Data;
//typedef std::map<std::string, int, std::greater<std::string> >        Compare_Data;
typedef etl::map<std::string, int, SIZE, std::less<std::string> >  Data;
typedef std::map<std::string, int, std::less<std::string> >        Compare_Data;
typedef Data::iterator Data_iterator;
typedef Data::const_iterator Data_const_iterator;

//*************************************************************************
std::ostream& operator << (std::ostream& os, const Data_iterator& it)
{
  os << (*it).first << " " << (*it).second;

  return os;
}

//*************************************************************************
std::ostream& operator << (std::ostream& os, const Data_const_iterator& it)
{
  os << (*it).first << " " << (*it).second;

  return os;
}

namespace
{
  SUITE(test_map)
  {
    std::vector<Data::value_type> initial_data;
    std::vector<Data::value_type> excess_data;
    std::vector<Data::value_type> different_data;

    //*************************************************************************
    template <typename T1, typename T2>
    bool Check_Equal(T1 begin1, T1 end1, T2 begin2)
    {
      while (begin1 != end1)
      {
        if ((begin1->first != begin2->first) || (begin1->second != begin2->second))
        {
          return false;
        }

        ++begin1;
        ++begin2;
      }

      return true;
    }

    //*************************************************************************
    struct SetupFixture
    {
      SetupFixture()
      {
        Data::value_type n[] =
        {
          { std::string("0"), 0 },
          { std::string("1"), 1 },
          { std::string("2"), 2 },
          { std::string("3"), 3 },
          { std::string("4"), 4 },
          { std::string("5"), 5 },
          { std::string("6"), 6 },
          { std::string("7"), 7 },
          { std::string("8"), 8 },
          { std::string("9"), 9 },
        };

        Data::value_type n2[] =
        {
          { std::string("0"),   0 },
          { std::string("1"),   1 },
          { std::string("2"),   2 },
          { std::string("3"),   3 },
          { std::string("4"),   4 },
          { std::string("5"),   5 },
          { std::string("6"),   6 },
          { std::string("7"),   7 },
          { std::string("8"),   8 },
          { std::string("9"),   9 },
          { std::string("10"), 10 },
        };

        Data::value_type n3[] =
        {
          { std::string("10"), 10 },
          { std::string("11"), 11 },
          { std::string("12"), 12 },
          { std::string("13"), 13 },
          { std::string("14"), 14 },
          { std::string("15"), 15 },
          { std::string("16"), 16 },
          { std::string("17"), 17 },
          { std::string("18"), 18 },
          { std::string("19"), 19 },
        };

        initial_data.assign(std::begin(n), std::end(n));
        excess_data.assign(std::begin(n2), std::end(n2));
        different_data.assign(std::begin(n3), std::end(n3));
      }
    };

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_default_constructor)
    {
      Data data;

      CHECK_EQUAL(data.size(), size_t(0));
      CHECK(data.empty());
      CHECK_EQUAL(data.capacity(), SIZE);
      CHECK_EQUAL(data.max_size(), SIZE);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_constructor_range)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());

      Data data(compare_data.begin(), compare_data.end());

      CHECK(data.size() == SIZE);
      CHECK(!data.empty());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_assignment)
    {
      Data data(initial_data.begin(), initial_data.end());
      Data otherData;

      otherData = data;

      bool isEqual = Check_Equal(data.begin(),
                                 data.end(),
                                 otherData.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_begin)
    {
      Data data(initial_data.begin(), initial_data.end());
      const Data constData(data);

      CHECK_EQUAL(data.begin(), std::begin(data));
      CHECK_EQUAL(constData.begin(), std::begin(constData));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_end)
    {
      Data data(initial_data.begin(), initial_data.end());
      const Data constData(data);

      CHECK_EQUAL(data.end(), std::end(data));
      CHECK_EQUAL(constData.end(), std::end(constData));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_empty)
    {
      Data data;
      data.insert(initial_data.begin(), initial_data.end());

      CHECK(data.full());
      CHECK(!data.empty());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_full)
    {
      Data data;

      CHECK(!data.full());
      CHECK(data.empty());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_index)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());

      Data data(compare_data.begin(), compare_data.end());

      CHECK_EQUAL(data["0"], compare_data["0"]);
      CHECK_EQUAL(data["1"], compare_data["1"]);
      CHECK_EQUAL(data["2"], compare_data["2"]);
      CHECK_EQUAL(data["3"], compare_data["3"]);
      CHECK_EQUAL(data["4"], compare_data["4"]);
      CHECK_EQUAL(data["5"], compare_data["5"]);
      CHECK_EQUAL(data["6"], compare_data["6"]);
      CHECK_EQUAL(data["7"], compare_data["7"]);
      CHECK_EQUAL(data["8"], compare_data["8"]);
      CHECK_EQUAL(data["9"], compare_data["9"]);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_at)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      Data data(initial_data.begin(), initial_data.end());

      CHECK_EQUAL(data.at("0"), compare_data.at("0"));
      CHECK_EQUAL(data.at("1"), compare_data.at("1"));
      CHECK_EQUAL(data.at("2"), compare_data.at("2"));
      CHECK_EQUAL(data.at("3"), compare_data.at("3"));
      CHECK_EQUAL(data.at("4"), compare_data.at("4"));
      CHECK_EQUAL(data.at("5"), compare_data.at("5"));
      CHECK_EQUAL(data.at("6"), compare_data.at("6"));
      CHECK_EQUAL(data.at("7"), compare_data.at("7"));
      CHECK_EQUAL(data.at("8"), compare_data.at("8"));
      CHECK_EQUAL(data.at("9"), compare_data.at("9"));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_at_const)
    {
      const Compare_Data compare_data(initial_data.begin(), initial_data.end());
      const Data data(initial_data.begin(), initial_data.end());

      CHECK_EQUAL(data.at("0"), compare_data.at("0"));
      CHECK_EQUAL(data.at("1"), compare_data.at("1"));
      CHECK_EQUAL(data.at("2"), compare_data.at("2"));
      CHECK_EQUAL(data.at("3"), compare_data.at("3"));
      CHECK_EQUAL(data.at("4"), compare_data.at("4"));
      CHECK_EQUAL(data.at("5"), compare_data.at("5"));
      CHECK_EQUAL(data.at("6"), compare_data.at("6"));
      CHECK_EQUAL(data.at("7"), compare_data.at("7"));
      CHECK_EQUAL(data.at("8"), compare_data.at("8"));
      CHECK_EQUAL(data.at("9"), compare_data.at("9"));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_assign_range)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());

      Data data;

      data.assign(compare_data.begin(), compare_data.end());

      bool isEqual = Check_Equal(data.begin(),
                                 data.end(),
                                 compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_value)
    {
      Compare_Data compare_data;
      Data data;

      std::pair<Data::iterator, bool> data_result =
        data.insert(Data::value_type(std::string("0"), 0));
      std::pair<Compare_Data::iterator, bool> compare_result =
        compare_data.insert(std::make_pair(std::string("0"), 0));

      // Check that both return successful return results
      CHECK_EQUAL(data_result.first->first, compare_result.first->first);
      CHECK_EQUAL(data_result.second, compare_result.second);

      // Try adding a duplicate (should return iterator pointing to duplicate)
      data_result = data.insert(Data::value_type(std::string("0"), 0));
      compare_result = compare_data.insert(std::make_pair(std::string("0"), 0));

      // Check that both return successful return results
      CHECK_EQUAL(data_result.first->first, compare_result.first->first);
      CHECK_EQUAL(data_result.second, compare_result.second);

      // Check that elements in map are the same
      bool isEqual = Check_Equal(data.begin(),
                                 data.end(),
                                 compare_data.begin());
      CHECK(isEqual);

      data.insert(std::make_pair(std::string("2"), 2));
      compare_data.insert(std::make_pair(std::string("2"), 2));

      isEqual = Check_Equal(data.begin(),
                            data.end(),
                            compare_data.begin());

      CHECK(isEqual);

      data.insert(std::make_pair(std::string("1"), 1));
      compare_data.insert(std::make_pair(std::string("1"), 1));

      isEqual = Check_Equal(data.begin(),
                            data.end(),
                            compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_hint_value)
    {
      Compare_Data compare_data;
      Data data;

      std::pair<Data::iterator, bool> data_result =
        data.insert(Data::value_type(std::string("2"), 2));
      std::pair<Compare_Data::iterator, bool> compare_result =
        compare_data.insert(std::make_pair(std::string("2"), 2));

      // Check that both return successful return results
      CHECK_EQUAL(data_result.first->first, compare_result.first->first);
      CHECK_EQUAL(data_result.second, compare_result.second);

      // Check that elements in map are the same
      bool isEqual = Check_Equal(data.begin(),
        data.end(),
        compare_data.begin());
      CHECK(isEqual);

      data.insert(data_result.first, std::make_pair(std::string("1"), 1));
      compare_data.insert(compare_result.first, std::make_pair(std::string("1"), 1));

      isEqual = Check_Equal(data.begin(),
        data.end(),
        compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_const_hint_value)
    {
      Compare_Data compare_data;
      Data data;

      std::pair<Data::iterator, bool> data_result =
        data.insert(Data::value_type(std::string("2"), 2));
      std::pair<Compare_Data::iterator, bool> compare_result =
        compare_data.insert(std::make_pair(std::string("2"), 2));

      // Check that both return successful return results
      CHECK_EQUAL(data_result.first->first, compare_result.first->first);
      CHECK_EQUAL(data_result.second, compare_result.second);

      // Check that elements in map are the same
      bool isEqual = Check_Equal(data.begin(),
        data.end(),
        compare_data.begin());
      CHECK(isEqual);

      data.insert(Data::const_iterator(data_result.first),
        std::make_pair(std::string("1"), 1));
      compare_data.insert(Compare_Data::const_iterator(compare_result.first),
        std::make_pair(std::string("1"), 1));

      isEqual = Check_Equal(data.begin(),
        data.end(),
        compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_value_excess)
    {
      Data data(initial_data.begin(), initial_data.end());

      CHECK_THROW(data.insert(std::make_pair(std::string("10"), 10)), etl::map_full);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_range)
    {
      Compare_Data compare_data;
      Data data;

      data.insert(initial_data.begin(), initial_data.end());
      compare_data.insert(initial_data.begin(), initial_data.end());

      bool isEqual = Check_Equal(data.begin(),
                                 data.end(),
                                 compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_range_excess)
    {
      Data data;

      CHECK_THROW(data.insert(excess_data.begin(), excess_data.end()), etl::map_full);
    }


    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_equal_range)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      Data data(initial_data.begin(), initial_data.end());

      std::pair<Data::iterator, Data::iterator> data_result =
        data.equal_range("2");
      std::pair<Compare_Data::iterator, Compare_Data::iterator> compare_result =
        compare_data.equal_range("2");

      // Check that both return the same return results
      CHECK_EQUAL(data_result.first->first, compare_result.first->first);
      CHECK_EQUAL(data_result.first->second, compare_result.first->second);
      CHECK_EQUAL(data_result.second->first, compare_result.second->first);
      CHECK_EQUAL(data_result.second->second, compare_result.second->second);

      bool isEqual = Check_Equal(data.begin(),
        data.end(),
        compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_equal_range)
    {
      const Compare_Data compare_data(initial_data.begin(), initial_data.end());
      const Data data(initial_data.begin(), initial_data.end());

      std::pair<Data::const_iterator, Data::const_iterator> data_result =
        data.equal_range("2");
      std::pair<Compare_Data::const_iterator, Compare_Data::const_iterator> compare_result =
        compare_data.equal_range("2");

      // Check that both return the same return results
      CHECK_EQUAL(data_result.first->first, compare_result.first->first);
      CHECK_EQUAL(data_result.first->second, compare_result.first->second);
      CHECK_EQUAL(data_result.second->first, compare_result.second->first);
      CHECK_EQUAL(data_result.second->second, compare_result.second->second);

      bool isEqual = Check_Equal(data.begin(),
        data.end(),
        compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_erase_value)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      Data data(initial_data.begin(), initial_data.end());

      compare_data.erase("5");
      data.erase("5");

      bool isEqual = Check_Equal(data.begin(),
        data.end(),
        compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_erase_single)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      Data data(initial_data.begin(), initial_data.end());

      Compare_Data::iterator i_compare = compare_data.begin();
      Data::iterator i_data            = data.begin();

      std::advance(i_compare, 2);
      std::advance(i_data,    2);

      compare_data.erase(i_compare);
      data.erase(i_data);

      bool isEqual = Check_Equal(data.begin(),
                                 data.end(),
                                 compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_erase_single)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      Data data(initial_data.begin(), initial_data.end());

      Compare_Data::const_iterator i_compare = compare_data.begin();
      Data::const_iterator i_data = data.begin();

      std::advance(i_compare, 2);
      std::advance(i_data, 2);

      bool isEqual = Check_Equal(data.begin(),
        data.end(),
        compare_data.begin());

      CHECK(isEqual);

      Compare_Data::const_iterator i_compare1 = compare_data.erase(i_compare);
      Data::const_iterator i_data1 = data.erase(i_data);

      CHECK_EQUAL(i_compare1->second, i_data1->second);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_erase_range)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      Data data(initial_data.begin(), initial_data.end());

      Compare_Data::iterator i_compare = compare_data.begin();
      Data::iterator i_data            = data.begin();

      Compare_Data::iterator i_compare_end = compare_data.begin();
      Data::iterator i_data_end            = data.begin();

      std::advance(i_compare, 2);
      std::advance(i_data,    2);

      std::advance(i_compare_end, 4);
      std::advance(i_data_end,    4);

      compare_data.erase(i_compare, i_compare_end);
      data.erase(i_data, i_data_end);

      bool isEqual = Check_Equal(data.begin(),
                                 data.end(),
                                 compare_data.begin());
      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_erase_range)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      Data data(initial_data.begin(), initial_data.end());

      Compare_Data::const_iterator i_compare = compare_data.begin();
      Data::const_iterator i_data = data.begin();

      Compare_Data::const_iterator i_compare_end = compare_data.begin();
      Data::const_iterator i_data_end = data.begin();

      std::advance(i_compare, 2);
      std::advance(i_data, 2);

      std::advance(i_compare_end, 4);
      std::advance(i_data_end, 4);

      compare_data.erase(i_compare, i_compare_end);
      data.erase(i_data, i_data_end);

      bool isEqual = Check_Equal(data.begin(),
        data.end(),
        compare_data.begin());
      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_clear)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());

      Data data(compare_data.begin(), compare_data.end());
      data.clear();

      CHECK_EQUAL(data.size(), size_t(0));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_count)
    {
      const Data data(initial_data.begin(), initial_data.end());

      CHECK_EQUAL(data.count("3"), size_t(1));

      CHECK_EQUAL(data.count("A"), size_t(0));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_iterator)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());

      Data data(compare_data.begin(), compare_data.end());

      bool isEqual = Check_Equal(data.begin(),
                                 data.end(),
                                 compare_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_iterator)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());

      Data data(compare_data.begin(), compare_data.end());

      bool isEqual = Check_Equal(data.cbegin(),
                                 data.cend(),
                                 compare_data.cbegin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_reverse_iterator)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());

      Data data(compare_data.begin(), compare_data.end());

      bool isEqual = Check_Equal(data.rbegin(),
                                 data.rend(),
                                 compare_data.rbegin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_reverse_iterator)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());

      Data data(compare_data.begin(), compare_data.end());

      bool isEqual = Check_Equal(data.crbegin(),
                                 data.crend(),
                                 compare_data.crbegin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_find)
    {
      Data data(initial_data.begin(), initial_data.end());

      Data::iterator it = data.find("3");
      CHECK_EQUAL(3, it->second);

      it = data.find("A");
      CHECK_EQUAL(data.end(), it);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_find_const)
    {
      const Data data(initial_data.begin(), initial_data.end());

      Data::const_iterator it = data.find("3");
      CHECK_EQUAL(3, it->second);

      it = data.find("A");
      CHECK_EQUAL(data.end(), it);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_equal)
    {
      const Data initial1(initial_data.begin(), initial_data.end());
      const Data initial2(initial_data.begin(), initial_data.end());

      CHECK(initial1 == initial2);

      const Data different(different_data.begin(), different_data.end());

      CHECK(!(initial1 == different));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_not_equal)
    {
      const Data initial1(initial_data.begin(), initial_data.end());
      const Data initial2(initial_data.begin(), initial_data.end());

      CHECK(!(initial1 != initial2));

      const Data different(different_data.begin(), different_data.end());

      CHECK(initial1 != different);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_lower_bound)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      Data data(initial_data.begin(), initial_data.end());

      Compare_Data::iterator i_compare = compare_data.lower_bound("3");
      Data::iterator i_data = data.lower_bound("3");
      CHECK_EQUAL(i_compare->second, i_data->second);

      i_data = data.lower_bound("A");
      CHECK_EQUAL(data.end(), i_data);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_lower_bound_const)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      const Data data(initial_data.begin(), initial_data.end());

      Compare_Data::const_iterator i_compare = compare_data.lower_bound("3");
      Data::const_iterator i_data = data.lower_bound("3");
      CHECK_EQUAL(i_compare->second, i_data->second);

      i_data = data.lower_bound("A");
      CHECK_EQUAL(data.end(), i_data);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_upper_bound)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      Data data(initial_data.begin(), initial_data.end());

      Compare_Data::iterator i_compare = compare_data.upper_bound("7");
      Data::iterator i_data = data.upper_bound("7");
      CHECK_EQUAL(i_compare->second, i_data->second);

      i_data = data.upper_bound("A");
      CHECK_EQUAL(data.end(), i_data);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_upper_bound_const)
    {
      Compare_Data compare_data(initial_data.begin(), initial_data.end());
      const Data data(initial_data.begin(), initial_data.end());

      Compare_Data::const_iterator i_compare = compare_data.upper_bound("7");
      Data::const_iterator i_data = data.upper_bound("7");
      CHECK_EQUAL(i_compare->second, i_data->second);

      i_data = data.upper_bound("A");
      CHECK_EQUAL(data.end(), i_data);
    }

  };
}