#include <iostream>
#include <fstream>
#include <string>
#include "knn.h"
#include "gnuplot-iostream.h"
#include <boost\tuple\tuple.hpp>

#define K 4
#define PRECISION 3

int main(void) {
	pointset_t points_init;
	int num_labels = 0;

	std::ifstream in("kmeans_result.txt");

	int row = 0;
	while (true) {
		std::string line;
		std::getline(in, line);
		if (in.eof()) break;
		num_labels++;

		std::stringstream lstream(line);
		int count;
		lstream >> count;

		for (int i = 0; i < count; i++) {
			value_t a, b;
			lstream >> a >> b;

			points_init.push_back({ { a, b }, row });
		}

		row++;
	}
	in.close();

	knn knn_engine(points_init, num_labels, K);

	std::vector<data_t> newPoints{
		{ 8, 1 }, { 6, -1 }, { 3, 5 }, { 2, -7 }, { -5, 0 }, { -6, 3 },
	};

	for (auto v : newPoints)
		knn_engine.addPoint(v);

	auto result = knn_engine.getResult();

	////////////// Gnuplot //////////////
	Gnuplot gp("C:\\Program\" \"Files\\gnuplot\\bin\\gnuplot -persist");
	
	std::string color[] = { "red", "green", "blue", "black" };
	for (int i = 0; i < num_labels; i++) {
		gp << "set style line " << (i+1) << " lc rgb '" << color[i%4] << "' pt " << (i+1) << std::endl;
	}

	gp << "set key off" << std::endl;
	gp << "plot ";
	for (int i = 0; i < result.size(); i++) {
		gp << "'-' w p ls " << (result[i].second + 1);
		if (i != result.size() - 1)
			gp << ", ";
	}
	gp << std::endl;

	for (int i = 0; i < result.size(); i++) {
		gp << std::setprecision(PRECISION) << result[i].first.first << " " << result[i].first.second << std::endl;
		gp << "e" << std::endl;
	}

	gp.close();
	////////////// Gnuplot End //////////////

	std::ofstream out("knn_result.txt");
	for (int i = 0; i < result.size(); i++) {
		out << "[" << result[i].second << "] " << result[i].first.first << ", " << result[i].first.second << std::endl;
	}
	out.close();
	return 0;
}