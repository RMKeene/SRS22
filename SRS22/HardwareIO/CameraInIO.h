#pragma once
#include "IOCommon.h"
#include "../Rect.h"
#include "../HardwareRaw/VideoHelper.h"

namespace SRS22 {
	class CameraInIO : IOCommon
	{
	public:
		/// <summary>
		/// Contains a 3 x H x W image for the fovea. Also contains the 8U versions.  Knows how to convert back and forth.
		/// This lets us do 32 bit float and 8 bit pixel operations in OpenCV as needed.
		/// </summary>
		class FoveaBundle {
		public:
			cv::Mat red32F;
			cv::Mat green32F;
			cv::Mat blue32F;
			cv::Mat red8U;
			cv::Mat green8U;
			cv::Mat blue8U;

			/// <summary>
			/// Copy in fovea and setup the 32F and 8U versions.
			/// </summary>
			/// <param name="fovea32F3"></param>
			FoveaBundle(cv::Mat fovea32F3);

			/// <summary>
			/// Make 3 Mat of the same size as the fovea, and type CV_8UC1.
			/// </summary>
			/// <param name="r"></param>
			/// <param name="g"></param>
			/// <param name="b"></param>
			void Allocate8UCSpaces(Mat& r, Mat& g, Mat& b) {
				r = Mat(red8U.size(), CV_8UC1);
				g = Mat(red8U.size(), CV_8UC1);
				b = Mat(red8U.size(), CV_8UC1);
			}

			/// <summary>
			/// Make 3 Mat of the same size as the fovea, and type CV_32FC1.
			/// </summary>
			/// <param name="r"></param>
			/// <param name="g"></param>
			/// <param name="b"></param>
			void Allocate32FCSpaces(Mat& r, Mat& g, Mat& b) {
				r = Mat(red8U.size(), CV_32FC1);
				g = Mat(red8U.size(), CV_32FC1);
				b = Mat(red8U.size(), CV_32FC1);
			}

			/// <summary>
			/// Take the 8U versions and put them back into the 8U and 32F versions.
			/// Clones the data in the 8U's and 32F's.
			/// </summary>
			/// <param name="red8"></param>
			/// <param name="green8"></param>
			/// <param name="blue8"></param>
			/// <returns></returns>
			cv::Mat TakeBack8U(cv::Mat red8, cv::Mat green8, cv::Mat blue8);

			/// <summary>
			/// Takes the 32F versions and puts them back into the 8U and 32F versions.
			/// </summary>
			/// <param name="red32"></param>
			/// <param name="green32"></param>
			/// <param name="blue32"></param>
			/// <returns></returns>
			void TakeBack32F(cv::Mat red32, cv::Mat green32, cv::Mat blue32);

			/// <summary>
			/// Converts the 8U version to 32F, combines into 3 x H x W size single matrix. Range of elements will be 0.0f to 1.0f
			/// </summary>
			/// <returns></returns>
			cv::Mat GetOut32F3Clone();

		};
		VideoHelper vidHelper;

		int w = 0;
		int h = 0;


		/// 3 x 480(rows) x 640(cols) range 0.0 to 1.0 for RGB colors.
		cv::Mat currentFrame;
		cv::Mat previousFrame;

		/// <summary>
		/// On every tick the fovea map fills this in. It then is used to efficiently derive various fovea
		/// concept representations.
		/// </summary>
		Rect currentFoveaRect;

		/// <summary>
		/// The current fovea pixel values in the Camera.
		/// Size is 3 (being RGB), CameraFoveaMap_Height, CameraFoveaMap_Width
		/// </summary>
		cv::Mat fovea;
		cv::Mat foveaPreviousFrame;
		cv::Mat foveaBlurred;
		/// <summary>
		/// The Canny Edge Detection for the fovea. (or Sobel maybe)
		/// Size is 3 (being RGB), CameraFoveaMap_Height, CameraFoveaMap_Width
		/// </summary>
		cv::Mat foveaEdges;
		/// <summary>
		/// The convolution on rotations of edges in the fovea. There are 5 angles detected, 0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5
		/// Size is 3 (being RGB), CameraFoveaMap_Height, CameraFoveaMap_Width
		/// </summary>
		cv::Mat foveaAngles000;
		cv::Mat foveaAngles225;
		cv::Mat foveaAngles450;
		cv::Mat foveaAngles675;
		cv::Mat foveaAngles900;
		cv::Mat foveaAngles1125;
		cv::Mat foveaAngles1350;
		cv::Mat foveaAngles1575;

		/// <summary>
		/// Last frame to current frame difference in the fovea.
		/// Size is 3 (being RGB), CameraFoveaMap_Height, CameraFoveaMap_Width
		/// </summary>
		cv::Mat foveaAbsDifference;
		/// <summary>
		/// How well centered circular features are on the fovea.
		/// Size is 3 (being RGB), CameraFoveaMap_Height, CameraFoveaMap_Width
		/// </summary>
		cv::Mat foveaCentricity;
		/// <summary>
		/// How noisy the fovea is. Sum foveaEdges per pixel.
		/// Size is 3 (being RGB), CameraFoveaMap_Height, CameraFoveaMap_Width
		/// </summary>
		cv::Mat foveaRoughness;
		/// <summary>
		/// A histogram of fovea RGB colors.
		/// Size is 3 (being RGB), CameraFoveaMap_Height, CameraFoveaMap_Width
		/// </summary>
		cv::Mat foveaColorHistogram;

		/// 3 x 48(rows) x 64(cols) range 0.0 to 1.0 for RGB colors.
		cv::Mat currentFrameLowRes;
		cv::Mat previousFrameLowRes;
		cv::Mat currentAbsDifferenceLowRes;

		static const int AbsDiffWidth = 64;
		static const int AbsDiffHeight = 48;

		/// <summary>
		/// 7 x 7 32F1 kernels of a rotated line. 0 degrees, 22.5 degrees, 45 degrees, 67.5 degrees, 90 degrees.
		/// Used for fovea center angle detection to into foveaAngles. Values are zeros with the line as 1.0
		/// </summary>
		cv::Mat rotatedLines000_7x7_32FC1;
		cv::Mat rotatedLines225_7x7_32FC1;
		cv::Mat rotatedLines450_7x7_32FC1;
		cv::Mat rotatedLines675_7x7_32FC1;
		cv::Mat rotatedLines900_7x7_32FC1;
		cv::Mat rotatedLines1125_7x7_32FC1;
		cv::Mat rotatedLines1350_7x7_32FC1;
		cv::Mat rotatedLines1575_7x7_32FC1;

		void prepRotatedLines();

		CameraInIO();
		~CameraInIO();

		virtual bool Init();
		virtual void Shutdown();

		/// <summary>
		/// Called for each IOCommon at the start of tick in Brain.
		/// </summary>
		virtual void PreTickHardwareAndIO();
		/// <summary>
		/// Called for each IOCommon at the end of tick in Brain.
		/// </summary>
		virtual void PostTickHardwareAndUI();

		/// <summary>
		/// Get the camera size from Win32 calls. Not a cached answer. Returns 0 on fail.
		/// </summary>
		/// <returns></returns>
		int GetCameraWidthWin32();
		int GetCameraHeightWin32();

		/// <summary>
		/// Get camera size as cached.
		/// </summary>
		/// <returns></returns>
		int GetCameraWidth() { return w; }
		int GetCameraHeight() { return h; }
		Rect GetCameraRect() { return Rect(0, 0, w, h); }

		bool AcquireFrame();
		/// <summary>
		/// CV_8UC3 640(cols) x 480(rows)
		/// </summary>
		cv::Mat getCurrentImage() { return vidHelper.currentImage3UC8; }
		/// <summary>
		/// CV_8UC3 640(cols) x 480(rows)
		/// </summary>
		cv::Mat getPreviousImage() { return vidHelper.previousImage3UC8; }
		/// <summary>
		/// CV_8UC3 64(cols) x 48(rows)
		/// </summary>
		cv::Mat getCurrentImageLowRes() { return vidHelper.currentImageLowRes3UC8; }
		/// <summary>
		/// CV_8UC3 64(cols) x 48(rows)
		/// </summary>
		cv::Mat getPreviousImageLowRes() { return vidHelper.previousImageLowRes3UC8; }

		/// <summary>
		/// Copy a sub rectangle from screen to outM.
		/// </summary>
		/// <param name="outM"></param>
		/// <param name="centerPoint"></param>
		void GetSubRect(cv::Mat& outM, const SRS22::Rect& region);

		/// <summary>
		/// Does a cv::imshow on the current screen.
		/// </summary>
		void DebugCurrentScreen() {
			cv::imshow(std::string("Debug Current Scrren"), vidHelper.currentImage3UC8);
		}

		void imShowFoveaConvolutionKernels();

		void UnitTest();
	};
}
