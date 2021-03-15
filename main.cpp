#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

vector<string> getPowerSetStringVector(const string &order) {
  vector<string> subset_string_vec;
  int order_size = order.size();
  for (int i = 1; i < pow(2, order_size); ++i) {
    string subset_string;
    for (int j = 0; j < order_size; ++j) {
      if (i & (1 << j)) {
        subset_string += order[j];
      }
    }
    if (subset_string.length() > 1) {
      subset_string_vec.push_back(subset_string);
    }
  }
  return subset_string_vec;
}

vector<string> solution(vector<string> order_vec, vector<int> course_vec) {
  vector<map<string, int>> count_map_vec(11);
  for (string &order : order_vec) {
    sort(order.begin(), order.end());
    for (string &sub_set_string : getPowerSetStringVector(order)) {
      count_map_vec[sub_set_string.length()][sub_set_string]++;
    }
  }
  vector<string> output_vec;
  for (int course : course_vec) {
    int max_value = 0;
    for (auto const&[key, value] : count_map_vec[course]) {
      max_value = max(max_value, value);
    }
    if (max_value < 2) {
      continue;
    }
    for (auto const&[key, value] : count_map_vec[course]) {
      if (value == max_value) {
        output_vec.push_back(key);
      }
    }
  }
  sort(output_vec.begin(), output_vec.end());
  return output_vec;
}

int main() {
  for (string &output : solution({"XYZ", "XWY", "WXA"}, {2, 3, 4})) {
    cout << output << endl;
  }
  return 0;
}