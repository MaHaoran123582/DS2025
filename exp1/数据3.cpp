#include <iostream>
#include <vector>
#include <stack>
#include <random>

int largestRectangleArea(std::vector<int>& heights) {
    int n = heights.size();
    if (n == 0) return 0;

    std::stack<int> stk;
    int maxArea = 0;

    for (int i = 0; i <= n; ++i) {
        int h = (i == n) ? 0 : heights[i];
        while (!stk.empty() && heights[stk.top()] > h) {
            int height = heights[stk.top()];
            stk.pop();
            int width = stk.empty() ? i : (i - stk.top() - 1);
            maxArea = std::max(maxArea, height * width);
        }
        stk.push(i);
    }

    return maxArea;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 104);

    // 示例测试
    std::vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    std::vector<int> heights2 = {2, 4};
    std::cout << "示例1: " << largestRectangleArea(heights1) << "\n";
    std::cout << "示例2: " << largestRectangleArea(heights2) << "\n";

    // 随机测试10组数据
    std::cout << "\n随机测试数据:\n";
    for (int i = 0; i < 10; ++i) {
        int len = dis(gen) % 100 + 1;
        std::vector<int> test;
        for (int j = 0; j < len; ++j) {
            test.push_back(dis(gen));
        }
        std::cout << "第" << i + 1 << "组，长度" << len << "，最大面积: "
                  << largestRectangleArea(test) << "\n";
    }

    return 0;
}
