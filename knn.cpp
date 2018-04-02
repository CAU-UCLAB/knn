#include "knn.h"
#include <algorithm>

knn::knn(pointset_t _ps, int _n_labels, int _k) : points(_ps), num_labels(_n_labels), k(_k) {

}

knn::~knn() {

}

value_t knn::distance(const data_t&& v1, const data_t&& v2) {
	return std::sqrtf(std::pow(v1.first - v2.first, 2) + std::pow(v1.second - v2.second, 2));
}

value_t knn::distance(const data_t& v1, const data_t& v2) {
	return std::sqrtf(std::pow(v1.first - v2.first, 2) + std::pow(v1.second - v2.second, 2));
}

void knn::addPoint(data_t data) {

	auto rank = points;
	auto predicate = [&data, this](labeled_t d1, labeled_t d2) { return distance(d1.first, data) < distance(d2.first, data); };

	std::sort(rank.begin(), rank.end(), predicate);

	std::vector<int> count;
	count.assign(num_labels, 0);

	for (int i = 0; i < k; i++) {
		count[rank[i].second]++;
	}

	int classified = (int)(std::max_element(count.begin(), count.end()) - count.begin());

	points.push_back({ data, classified });
}

pointset_t knn::getResult() {
	return points;
}