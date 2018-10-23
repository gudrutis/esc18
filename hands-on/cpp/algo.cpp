#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

std::ostream& operator<<(std::ostream& os, std::vector<int> const& c);
std::vector<int> make_vector(int N);
int main()
{
    // create a vector of N elements, generated randomly
    int const N = 10;
    std::vector<int> v = make_vector(N);
    std::cout << v << '\n';

    // use std::accumulate
    std::cout << "sum all the elements of the vector" << '\n';
    std::cout << std::accumulate(v.begin(), v.end() ,0) << '\n';

    std::cout << "compute the average of the first half and of the second half of the vector" << '\n';
    auto mid_it = v.begin() + v.size() / 2 ;
    std::cout << std::accumulate(v.begin(), mid_it ,0) << '\n';

    std::cout << "compute the average of the first half and of the second half of the vector" << '\n';
    std::cout << "First: "<< std::accumulate(v.begin(), mid_it ,0) / std::distance(mid_it, v.end())  << '\n';

    std::cout << "move the three central elements to the beginning of the vector" << '\n';
    // use std::rotate
    std::cout << "before rotation: " << v << '\n';
    std::rotate(v.begin(), mid_it - 1 , v.end() );
    std::cout << "after: " << v << '\n';


    std::cout << "remove duplicate elements" << '\n';
    // use std::sort followed by std::unique/unique_copy
     v = { 1,1,1,1,1,2,2,2,2,2};
    std::sort(v.begin(),v.end());
    auto uniq = std::unique(v.begin(),v.end());
    std::cout  << v << '\n';
};

std::ostream& operator<<(std::ostream& os, std::vector<int> const& c)
{
    os << "{ ";
    std::copy(
            std::begin(c),
            std::end(c),
            std::ostream_iterator<int>{os, " "}
    );
    os << '}';

    return os;
}

std::vector<int> make_vector(int N)
{
    std::random_device rd;
    std::mt19937 eng{rd()};

    int const MAX_N = 100;
    std::uniform_int_distribution<int> dist{1, MAX_N};
    std::vector<int> result;
    result.reserve(N);
    std::generate_n(std::back_inserter(result), N, [&]() { return dist(eng); });

    return result;
}
