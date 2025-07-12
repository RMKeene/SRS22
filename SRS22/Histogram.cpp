#include "Histogram.h"

namespace SRS22 {

	Histogram::Histogram(std::string name, int numBins, double minValue, double maxValue)
		: name(name), numBins(numBins), minValue(minValue), maxValue(maxValue) {
		if (numBins <= 0) {
			throw std::invalid_argument("numBins must be positive");
		}
		binWidth = (maxValue - minValue) / numBins;
		bins = new int[numBins]();
	}

	Histogram::Histogram(const Histogram& other)
		: name(other.name),
		numBins(other.numBins),
		minValue(other.minValue),
		maxValue(other.maxValue),
		binWidth(other.binWidth)
	{
		if (other.bins) {
			bins = new int[numBins];
			for (int i = 0; i < numBins; ++i) {
				bins[i] = other.bins[i];
			}
		}
		else {
			bins = nullptr;
		}
	}

	Histogram::~Histogram() {
		delete[] bins;
	}

	void Histogram::addValueD(double value) {
		if (value < minValue || value > maxValue) return;
		int binIndex = static_cast<int>((value - minValue) / binWidth);
		if (binIndex >= numBins) binIndex = numBins - 1;
		if (binIndex >= 0 && binIndex < numBins) {
			bins[binIndex]++;
		}
	}

	void Histogram::addValue(float value) {
		if (value < minValue || value > maxValue) return;
		int binIndex = static_cast<int>((value - minValue) / binWidth);
		if (binIndex >= numBins) binIndex = numBins - 1;
		if (binIndex >= 0 && binIndex < numBins) {
			bins[binIndex]++;
		}
	}

	void Histogram::SumIn(const Histogram& other) {
		if (numBins != other.numBins || minValue != other.minValue || maxValue != other.maxValue) {
			throw std::invalid_argument("Histograms must have the same configuration to sum.");
		}
		for (int i = 0; i < numBins; i++) {
			bins[i] += other.bins[i];
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