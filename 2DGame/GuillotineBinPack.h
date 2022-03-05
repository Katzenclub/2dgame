#pragma once

#include <vector>

#include "ObjectAsset.h"
#include "Block.h"

namespace gp
{
	struct RectInfo
	{
		int width;
		int height;
		int x;
		int y;
		gp::object::ObjectAsset* objectAsset;
	};

	class GuillotineBinPack
	{
	public:
		GuillotineBinPack(int width, int height);

		/// (Re)initializes the packer to an empty bin of width x height units. Call whenever
		/// you need to restart with a new bin.
		void Init(int width, int height);

		/// Inserts a list of rectangles into the bin.
		/// @param rects The list of rectangles to add. This list will be destroyed in the packing process.
		/// @param merge If true, performs Rectangle Merge operations during the packing process.
		/// @param rectChoice The free rectangle choice heuristic rule to use.
		/// @param splitMethod The free rectangle split heuristic rule to use.
		std::vector<RectInfo> Insert(std::vector<RectInfo> &rects, bool merge);

		/// Returns the internal list of disjoint rectangles that track the free area of the bin. You may alter this vector
		/// any way desired, as long as the end result still is a list of disjoint rectangles.
		std::vector<RectInfo> &GetFreeRectangles() { return freeRectangles; }

		/// Performs a Rectangle Merge operation. This procedure looks for adjacent free rectangles and merges them if they
		/// can be represented with a single rectangle. Takes up Theta(|freeRectangles|^2) time.
		void MergeFreeList();

	private:
		int binWidth;
		int binHeight;

		std::vector<RectInfo> freeRectangles;

		// The following functions compute (penalty) score values if a rect of the given size was placed into the
		// given free rectangle. In these score values, smaller is better.
		static int ScoreBestAreaFit(int width, int height, const RectInfo &freeRect);

		/// Splits the given L-shaped free rectangle into two new free rectangles after placedRect has been placed into it.
		/// Determines the split axis by using the given heuristic.
		void SplitFreeRectByHeuristic(const RectInfo &freeRect, const RectInfo &placedRect);

		/// Splits the given L-shaped free rectangle into two new free rectangles along the given fixed split axis.
		void SplitFreeRectAlongAxis(const RectInfo &freeRect, const RectInfo &placedRect, bool splitHorizontal);
	};
}
