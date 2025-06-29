#pragma once

namespace SRS22
{

    /// <summary>
    /// The Histogram class provides a thread-safe way to collect and analyze the distribution of numerical values
    /// by dividing a specified range into a fixed number of bins. It supports adding values, clearing data, and
    /// retrieving bin statistics such as counts and range boundaries. The class is useful for statistical analysis,
    /// debugging, and logging purposes.
	/// 
	/// The minRange and maxRange are inclusive, 
	/// meaning that values equal to minRange or maxRange will be counted in the histogram.
    /// </summary>
	class Histogram {
	public:
		std::string name; // Optional name for the histogram, can be used for debugging or logging.
		Histogram(std::string name, int numBins, double minValue, double maxValue);
		~Histogram();
		void addValue(double value);
		void clear();
		int getBinCount() const;
		double getBinMin(int binIndex) const;
		double getBinMax(int binIndex) const;
		int getBinValue(int binIndex) const;
		void printHistogram() const;
	private:
		std::mutex binsMutex;
		int numBins;
		double minValue;
		double maxValue;
		double binWidth;
		int* bins;
	};
}