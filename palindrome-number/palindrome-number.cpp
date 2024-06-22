#include <iostream>
#include <cmath>

int countFigures(int n) {
    int ret = 1;
    while (n > 9) {
        n /= 10;
        ret++;
    }
    return (ret);
}

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return (false);
	int figures = countFigures(x);
	while (figures > 1) {
		int div = (int)pow(10, figures - 1);
		int n1 = x / div;
		int n2 = x % 10;
		std::cout << n1 << " " <<  n2 << std::endl;
		std::cout << "Figures: " << figures << std::endl;
		if (n1 != n2)
			return (false);
		x = (x - (n1 * div + n2)) / 10;
		std::cout << "New x: " << x << std::endl;
		figures -= 2;
	}
	return (true);
    }
};

int main(void) {
	Solution sol;
	sol.isPalindrome(12341);
}
