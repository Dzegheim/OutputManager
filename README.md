# OutputManager
A library for output managing in a form resembling that of python's `print()`, with support for column and row-by-row formatting.

# Usage
Clone the library and use it. For documentation see [here](https://dzegheim.github.io/OutputManager/html/index.html). The most simple usage is simply creating an object and using it to print stuff.
**Example:**
```.cpp
#include "OutputManager.h"
#include <vector>
#include <string>

int main () {
    OutputManager A;
    A(5, 5.5, L"Salmon Dance");
    std::vector<int> Numbers {1, 2, 3, 4};
    std::vector<double> Floats {1.1, 2.2, 3.3, 4.4};
    std::vector<std::wstring> Words {L"Cat", L"Dog", L"Bee", L"Cow"};
    A.FormatToColumns(Numbers.begin(), Numbers.end(), Floats.begin(), Words.begin());
    A.FormatToRows(Numbers.begin(), Numbers.end(), Floats.begin(), Words.begin());
}
```
**Output:**
```
5 5.5 Salmon Dance
1 1.1 Cat
2 2.2 Dog
3 3.3 Bee
4 4.4 Cow
1 2 3 4 
1.1 2.2 3.3 4.4 
Cat Dog Bee Cow 
```

# License
This code is licensed under [CC0 1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/).
