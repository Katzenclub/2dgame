#include <algorithm>
#include <utility>
#include <iostream>
#include <limits>

#include <cassert>
#include <cstring>
#include <cmath>

#include "GuillotineBinPack.h"

namespace gp
{
	using namespace std;

	GuillotineBinPack::GuillotineBinPack(int width, int height)
	{
		Init(width, height);
	}

	void GuillotineBinPack::Init(int width, int height)
	{
		binWidth = width;
		binHeight = height;

		// We start with a single big free rectangle that spans the whole bin.
		RectInfo n;
		n.x = 0;
		n.y = 0;
		n.width = width;
		n.height = height;

		freeRectangles.clear();
		freeRectangles.push_back(n);
	}

	std::vector<RectInfo> GuillotineBinPack::Insert(std::vector<RectInfo> &rects, bool merge)
	{
		std::vector<RectInfo> resultRects;

		int bestFreeRect = 0;
		int bestRect = 0;

		// Pack rectangles one at a time until we have cleared the rects array of all rectangles.
		// rects will get destroyed in the process.
		while (rects.size() > 0)
		{
			// Stores the penalty score of the best rectangle placement - bigger=worse, smaller=better.
			int bestScore = std::numeric_limits<int>::max();

			for (size_t i = 0; i < freeRectangles.size(); ++i)
			{
				for (size_t j = 0; j < rects.size(); ++j)
				{
					// If this rectangle is a perfect match, we pick it instantly.
					if (rects[j].width == freeRectangles[i].width && rects[j].height == freeRectangles[i].height)
					{
						bestFreeRect = i;
						bestRect = j;
						bestScore = std::numeric_limits<int>::min();
						i = freeRectangles.size(); // Force a jump out of the outer loop as well - we got an instant fit.
						break;
					}
					// Try if we can fit the rectangle upright.
					else if (rects[j].width <= freeRectangles[i].width && rects[j].height <= freeRectangles[i].height)
					{
						int score = ScoreBestAreaFit(rects[j].width, rects[j].height, freeRectangles[i]);
						if (score < bestScore)
						{
							bestFreeRect = i;
							bestRect = j;
							bestScore = score;
						}
					}
				}
			}

			// If we didn't manage to find any rectangle to pack, abort.
			if (bestScore == std::numeric_limits<int>::max()) {
				return std::vector<RectInfo>();
			}

			RectInfo resultRect;
			resultRect.x = freeRectangles[bestFreeRect].x;
			resultRect.y = freeRectangles[bestFreeRect].y;
			resultRect.width = rects[bestRect].width;
			resultRect.height = rects[bestRect].height;
			resultRect.textureSizePointer = rects[bestRect].textureSizePointer;
			resultRect.texturePositionPointer = rects[bestRect].texturePositionPointer;
			resultRect.texture = rects[bestRect].texture;

			// Remove the free space we lost in the bin.
			SplitFreeRectByHeuristic(freeRectangles[bestFreeRect], resultRect);
			freeRectangles.erase(freeRectangles.begin() + bestFreeRect);

			rects.erase(rects.begin() + bestRect);

			if (merge) {
				MergeFreeList();
			}

			resultRects.push_back(resultRect);
		}
		std::copy(resultRects.begin(), resultRects.end(), back_inserter(rects));
		return resultRects;
	}

	int GuillotineBinPack::ScoreBestAreaFit(int width, int height, const RectInfo &freeRect)
	{
		return freeRect.width * freeRect.height - width * height;
	}

	void GuillotineBinPack::SplitFreeRectByHeuristic(const RectInfo &freeRect, const RectInfo &placedRect)
	{
		const int w = freeRect.width - placedRect.width;
		const int h = freeRect.height - placedRect.height;

		bool splitHorizontal = (placedRect.width * h <= w * placedRect.height);

		SplitFreeRectAlongAxis(freeRect, placedRect, (placedRect.width * h <= w * placedRect.height));
	}

	/// This function will add the two generated rectangles into the freeRectangles array. The caller is expected to
	/// remove the original rectangle from the freeRectangles array after that.
	void GuillotineBinPack::SplitFreeRectAlongAxis(const RectInfo &freeRect, const RectInfo &placedRect, bool splitHorizontal)
	{
		RectInfo bottom;
		bottom.x = freeRect.x;
		bottom.y = freeRect.y + placedRect.height;
		bottom.height = freeRect.height - placedRect.height;

		RectInfo right;
		right.x = freeRect.x + placedRect.width;
		right.y = freeRect.y;
		right.width = freeRect.width - placedRect.width;

		if (splitHorizontal)
		{
			bottom.width = freeRect.width;
			right.height = placedRect.height;
		}
		else
		{
			bottom.width = placedRect.width;
			right.height = freeRect.height;
		}

		if (bottom.width > 0 && bottom.height > 0)
		{
			freeRectangles.push_back(bottom);
		}
		if (right.width > 0 && right.height > 0)
		{
			freeRectangles.push_back(right);
		}
	}

	void GuillotineBinPack::MergeFreeList()
	{
		// Do a Theta(n^2) loop to see if any pair of free rectangles could me merged into one.
		// Note that we miss any opportunities to merge three rectangles into one. (should call this function again to detect that)
		for (size_t i = 0; i < freeRectangles.size(); ++i)
		{
			for (size_t j = i + 1; j < freeRectangles.size(); ++j)
			{
				if (freeRectangles[i].width == freeRectangles[j].width && freeRectangles[i].x == freeRectangles[j].x)
				{
					if (freeRectangles[i].y == freeRectangles[j].y + freeRectangles[j].height)
					{
						freeRectangles[i].y -= freeRectangles[j].height;
						freeRectangles[i].height += freeRectangles[j].height;
						freeRectangles.erase(freeRectangles.begin() + j);
						--j;
					}
					else if (freeRectangles[i].y + freeRectangles[i].height == freeRectangles[j].y)
					{
						freeRectangles[i].height += freeRectangles[j].height;
						freeRectangles.erase(freeRectangles.begin() + j);
						--j;
					}
				}
				else if (freeRectangles[i].height == freeRectangles[j].height && freeRectangles[i].y == freeRectangles[j].y)
				{
					if (freeRectangles[i].x == freeRectangles[j].x + freeRectangles[j].width)
					{
						freeRectangles[i].x -= freeRectangles[j].width;
						freeRectangles[i].width += freeRectangles[j].width;
						freeRectangles.erase(freeRectangles.begin() + j);
						--j;
					}
					else if (freeRectangles[i].x + freeRectangles[i].width == freeRectangles[j].x)
					{
						freeRectangles[i].width += freeRectangles[j].width;
						freeRectangles.erase(freeRectangles.begin() + j);
						--j;
					}
				}
			}
		}
	}
}
