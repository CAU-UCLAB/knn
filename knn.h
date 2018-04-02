#pragma once
#include <vector>

using value_t = float;
using data_t = std::pair<value_t, value_t>;
using label_t = int;
using labeled_t = std::pair<data_t, label_t>;
using pointset_t = std::vector<labeled_t>;

class knn {
	pointset_t points;
	const int k;
	const int num_labels;

	value_t distance(const data_t&&, const data_t&&);
	value_t distance(const data_t&, const data_t&);

public:
	knn(pointset_t points, int num_labels, int K);
	virtual ~knn();

	void addPoint(data_t);
	pointset_t getResult();

};