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
  map<string, int> count_map;
  for (string &order : order_vec) {
    sort(order.begin(), order.end());
  }
  for (string &order : order_vec) {
    for (string &sub_set_string : getPowerSetStringVector(order)) {
      count_map[sub_set_string]++;
    }
  }
  for (auto iter = count_map.begin(); iter != count_map.end();) {
    if (iter->second == 1) {
      iter = count_map.erase(iter);
    } else {
      ++iter;
    }
  }
  vector<vector<pair<int, string>>> count_vec_vec(11);
  vector<string> output_vec;
  for (auto const&[key, value] : count_map) {
    count_vec_vec[key.length()].push_back({value, key});
  }
  for (int course : course_vec) {
    if (!count_vec_vec[course].empty()) {
      sort(count_vec_vec[course].begin(), count_vec_vec[course].end(), greater<>());
      output_vec.push_back(count_vec_vec[course][0].second);
      for (int i = 1; i < count_vec_vec[course].size(); ++i) {
        if (count_vec_vec[course][i].first != count_vec_vec[course][0].first) {
          break;
        }
        output_vec.push_back(count_vec_vec[course][i].second);
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