#include <iostream>
#include <iterator>
#include "array.h"

int main()
{
    {
        fixed_arrays::ConstantSizeArray<int> arr = {1, 2, 3, 4, 5, 6};
        fixed_arrays::ConstantSizeArray<int> arr1(3);
        arr1 = arr;

        std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        std::copy(arr1.begin(), arr1.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    return 0;
}

