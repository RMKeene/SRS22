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
		}

		//void SumIn(CortexThreadStats& threadStats) {
		//	std::lock_guard<std::mutex> lock(mutex);
		//	countOfNeuronsProcessed += threadStats.countOfNeuronsProcessed;
		//	sumOfC += threadStats.sumOfC;
		//	countOfConfidence += threadStats.countOfConfidence;
		//	sumOfConfidence += threadStats.sumOfConfidence;
		//	countOfNeuronsFired += threadStats.countOfNeuronsFired;
		//	countOfReRoutes += threadStats.countOfReRoutes;
		//	countOfOnes += threadStats.countOfOnes;
		//	countOfZeros += threadStats.countOfZeros;
		//	countFatigued += threadStats.countFatigued;
		//	averageNeuronCharge += threadStats.sumOfC;
		//	averageConfidence += threadStats.sumOfConfidence;
		//}

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
		}
	};
}