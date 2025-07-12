#pragma once

namespace SRS22 {
	struct CortexThreadStats {
		int countOfNeuronsProcessed = 0;
		int countOfNeuronsFired = 0;
		double sumOfC = 0.0;
		int countOfConfidence = 0;
		double sumOfConfidence = 0.0;
		int countOfReRoutes = 0;
		int countOfOnes = 0;
		int countOfZeros = 0;
		int countFatigued = 0;
		int countStimulus = 0;

		Histogram neuronChargeHist;
		Histogram neuronEnergyHist;
		Histogram linkWeightHist;
		Histogram linkActivityHist;
		Histogram linkAgeHist;
		Histogram linkConfidenceHist;

		CortexThreadStats()
			: neuronChargeHist("Neuron Charge", 10, 0.0, 1.0),
			neuronEnergyHist("Neuron Energy", 10, 0.0, 1.0),
			linkWeightHist("Link Weight", 10, -1.0, 1.0),
			linkActivityHist("Link Activity", 10, 0.0, 1.0),
			linkAgeHist("Link Age (log2)", 64, 0.0, 64.0),
			linkConfidenceHist("Link Confidence", 10, 0.0, 1.0) {
		}

		void reset() {
			countOfNeuronsProcessed = 0;
			sumOfC = 0.0;
			countOfConfidence = 0;
			sumOfConfidence = 0.0;
			countOfReRoutes = 0;
			countOfOnes = 0;
			countOfZeros = 0;
			countFatigued = 0;
			countStimulus = 0;

			neuronChargeHist.clear();
			neuronEnergyHist.clear();
			linkWeightHist.clear();
			linkActivityHist.clear();
			linkAgeHist.clear();
			linkConfidenceHist.clear();
		}

		void SumIn(CortexThreadStats& threadStats) {
			countOfNeuronsProcessed += threadStats.countOfNeuronsProcessed;
			sumOfC += threadStats.sumOfC;
			countOfConfidence += threadStats.countOfConfidence;
			sumOfConfidence += threadStats.sumOfConfidence;
			countOfReRoutes += threadStats.countOfReRoutes;
			countOfOnes += threadStats.countOfOnes;
			countOfZeros += threadStats.countOfZeros;
			countFatigued += threadStats.countFatigued;
			countStimulus += threadStats.countStimulus;

			neuronChargeHist.SumIn(threadStats.neuronChargeHist);
			neuronEnergyHist.SumIn(threadStats.neuronEnergyHist);
			linkWeightHist.SumIn(threadStats.linkWeightHist);
			linkActivityHist.SumIn(threadStats.linkActivityHist);
			linkAgeHist.SumIn(threadStats.linkAgeHist);
			linkConfidenceHist.SumIn(threadStats.linkConfidenceHist);
		}
	};

	struct CortexStats {
		std::mutex mutex;

		int countOfNeuronsProcessed = 0;
		double sumOfC = 0.0;
		int countOfConfidence = 0;
		double sumOfConfidence = 0.0;
		int countOfNeuronsFired = 0;
		int countOfReRoutes = 0;
		int countOfOnes = 0;
		int countOfZeros = 0;
		int countFatigued = 0;
		int countStimulus = 0;
		float averageNeuronCharge = 0.0f;
		float averageConfidence = 0.0f;

		Histogram neuronChargeHist;
		Histogram neuronEnergyHist;
		Histogram linkWeightHist;
		Histogram linkActivityHist;
		Histogram linkAgeHist;
		Histogram linkConfidenceHist;

		CortexStats()
			: neuronChargeHist("Neuron Charge", 10, 0.0, 1.0),
			neuronEnergyHist("Neuron Energy", 10, 0.0, 1.0),
			linkWeightHist("Link Weight", 10, -1.0, 1.0),
			linkActivityHist("Link Activity", 10, 0.0, 1.0),
			linkAgeHist("Link Age (log2)", 64, 0.0, 64.0),
			linkConfidenceHist("Link Confidence", 10, 0.0, 1.0) {
		}

		void reset() {
			std::lock_guard<std::mutex> lock(mutex);
			countOfNeuronsProcessed = 0;
			sumOfC = 0.0;
			countOfConfidence = 0;
			sumOfConfidence = 0.0;
			countOfNeuronsFired = 0;
			countOfReRoutes = 0;
			countOfOnes = 0;
			countOfZeros = 0;
			countFatigued = 0;
			countStimulus = 0;
			averageNeuronCharge = 0.0f;
			averageConfidence = 0.0f;

			neuronChargeHist.clear();
			neuronEnergyHist.clear();
			linkWeightHist.clear();
			linkActivityHist.clear();
			linkAgeHist.clear();
			linkConfidenceHist.clear();
		}

		void SumInNoLock(CortexThreadStats& threadStats) {
			countOfNeuronsProcessed += threadStats.countOfNeuronsProcessed;
			sumOfC += threadStats.sumOfC;
			countOfConfidence += threadStats.countOfConfidence;
			sumOfConfidence += threadStats.sumOfConfidence;
			countOfNeuronsFired += threadStats.countOfNeuronsFired;
			countOfReRoutes += threadStats.countOfReRoutes;
			countOfOnes += threadStats.countOfOnes;
			countOfZeros += threadStats.countOfZeros;
			countFatigued += threadStats.countFatigued;
			countStimulus += threadStats.countStimulus;
			averageNeuronCharge += threadStats.sumOfC;
			averageConfidence += threadStats.sumOfConfidence;

			neuronChargeHist.SumIn(threadStats.neuronChargeHist);
			neuronEnergyHist.SumIn(threadStats.neuronEnergyHist);
			linkWeightHist.SumIn(threadStats.linkWeightHist);
			linkActivityHist.SumIn(threadStats.linkActivityHist);
			linkAgeHist.SumIn(threadStats.linkAgeHist);
			linkConfidenceHist.SumIn(threadStats.linkConfidenceHist);
		}
	};
}