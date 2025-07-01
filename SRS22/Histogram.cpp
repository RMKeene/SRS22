#include "Histogram.h"

namespace SRS22 {

	Histogram::Histogram(std::string name, int numBins, double minValue, double maxValue)
		: name(name), numBins(numBins), minValue(minValue), maxValue(maxValue) {
		binWidth = (maxValue - minValue) / numBins;
		bins = new int[numBins]();
	}

	Histogram::~Histogram() {
		delete[] bins;
	}

	void Histogram::addValueD(double value) {
		if (value < minValue || value > maxValue) return;
		int binIndex = static_cast<int>((value - minValue) / binWidth);
		if (binIndex >= numBins) binIndex = numBins - 1;
		if (binIndex >= 0 && binIndex < numBins) {
			std::lock_guard<std::mutex> lock(binsMutex);
			bins[binIndex]++;
		}
	}

	void Histogram::addValue(float value) {
		if (value < minValue || value > maxValue) return;
		int binIndex = static_cast<int>((value - minValue) / binWidth);
		if (binIndex >= numBins) binIndex = numBins - 1;
		if (binIndex >= 0 && binIndex < numBins) {
			std::lock_guard<std::mutex> lock(binsMutex);
			bins[binIndex]++;
		}
	}

	void Histogram::clear() {
		for (int i = 0; i < numBins; i++) {
			bins[i] = 0;
		}
	}

	int Histogram::getBinCount() const {
		return numBins;
	}

	double Histogram::getBinMin(int binIndex) const {
		return minValue + binIndex * binWidth;
	}

	double Histogram::getBinMax(int binIndex) const {
		return getBinMin(binIndex) + binWidth;
	}

	int Histogram::getBinValue(int binIndex) const {
		if (binIndex >= 0 && binIndex < numBins) {
			return bins[binIndex];
		}
		return 0;
	}

	void Histogram::printHistogram() const {
		printf("Histogram: %s\n", name.c_str());
		for (int i = 0; i < numBins; i++) {
			printf("Bin %d [%f - %f]: %d\n", i, getBinMin(i), getBinMax(i), bins[i]);
		}
	}
} 