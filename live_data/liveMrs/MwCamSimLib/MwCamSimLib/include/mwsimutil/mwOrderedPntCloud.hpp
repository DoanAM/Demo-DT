// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWORDEREDPNTCLOUD_HPP_
#define MW_MWORDEREDPNTCLOUD_HPP_
#include "mw3dBoundingBox.hpp"
#include "mw3dGeometry.hpp"
#include "mwTPoint3d.hpp"


#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <sys/mman.h>
#endif

namespace cadcam
{
/// This class represents a ordered point cloud.
template <typename T>
class mwTOrderedPntCloud;
/// This class represents a ordered point cloud.
typedef mwTOrderedPntCloud<float> mwOrderedPntCloud;

class mwOrderedPntCloudVisitor
{
public:
	virtual ~mwOrderedPntCloudVisitor(){};
	virtual void Visit(mwOrderedPntCloud& tv) = 0;
	virtual void Visit(const mwOrderedPntCloud& tv) const = 0;
};

/// This class represents a ordered point cloud.
template <typename T>
class MW_5AXUTIL_API mwTOrderedPntCloud: public mw3dObject<T>
{
};
/// This class represents a ordered point cloud.
template <>
class MW_5AXUTIL_API mwTOrderedPntCloud<float>: public mw3dObject<float>
{
public:
	typedef misc::mwAutoPointer<mwTOrderedPntCloud<float>> Ptr;
	typedef mwTPoint3d<float> cldPnt;

	/// Constructor
	///
	/// Constructs a ordered point cloud using the
	///   parameters given:
	///   @param rows number of rows in the matrix
	///   @param columns number of columns in the matrix
	mwTOrderedPntCloud(const size_t rows, const size_t columns)
		: mPoint(new cldPnt*[rows]),
		  mNormal(MW_NULL),
		  mRowNormals(rows),
		  mColumnNormals(columns),
		  mRowCount(rows),
		  mColumnCount(columns),
		  mFlat(true)
	{
		AllocateRows(mPoint, mChunkRowCount);

		const cldPnt up(0, 0, 1);
		for (size_t r = 0; r < mRowCount; r++)
			mRowNormals[r] = up;
		for (size_t n = 0; n < mColumnCount; n++)
			mColumnNormals[n] = up;
	}

	~mwTOrderedPntCloud()
	{
		FreeRows(mPoint, mChunkRowCount);
		FreeRows(mNormal, mChunkRowCount);
	}

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mwOrderedPntCloudVisitor& visitor) { visitor.Visit(*this); }
	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor const ref to visitor
	virtual void AcceptVisitor(const mwOrderedPntCloudVisitor& visitor) const
	{
		visitor.Visit(*this);
	}

	/// Get number of rows
	///
	/// Get number of rows in the cloud matrix
	///	@returns number of rows in the cloud matrix
	const size_t GetNumberOfRows() const { return static_cast<size_t>(mRowCount); }

	/// Get number of columns
	///
	/// Get number of rows in the cloud columns
	///	@returns number of rows in the cloud columns
	const size_t GetNumberOfColumns() const { return static_cast<size_t>(mColumnCount); }

	/// Indexer operator for const values
	///
	/// Returns, for a given index,a row.
	///	@param index position of the row in the array
	///	@returns a row.
	cldPnt* operator[](const size_t index)
	{
		if (mRowCount <= index)
			throw misc::mwIdxRangeException<size_t>(mRowCount - 1, index);
		return mPoint[index];
	}

	/// Indexer operator for const values
	///
	/// Returns, for a given index,a row.
	///	@param index position of the row in the array
	///	@returns a const row.
	const cldPnt* operator[](const size_t index) const
	{
		if (mRowCount <= index)
			throw misc::mwIdxRangeException<size_t>(mRowCount - 1, index);
		return mPoint[index];
	}

	/// Get point
	///
	/// Get point in the cloud matrix with given parameters:
	///	@param rowindex const rowindex in the cloud matrix
	///	@param columnindex const columnindex in the cloud matrix
	///	@returns const cloud point (3d point)
	const cldPnt GetPoint(const size_t rowindex, const size_t columnindex) const
	{
		return mPoint[rowindex][columnindex];
	}

	/// Set point
	///
	/// Set point in the cloud matrix with given parameters:
	///	@param rowindex const rowindex in the cloud matrix
	///	@param columnindex const columnindex in the cloud matrix
	///	@param pt const reference to a cloud point
	void SetPoint(const size_t rowindex, const size_t columnindex, const cldPnt& pt)
	{
		mPoint[rowindex][columnindex] = pt;
	}

	/// Get bounding box
	///
	/// Get bounding box of the point cloud.
	///	@returns const reference to the bounding box
	const mw3dBoundingBox<float>& GetBoundingBox() const
	{
		if (mBBox.IsSinglePoint() || !mBBox.IsInitialized())
			CalculateBoundingBox();
		return mBBox;
	}

	/// Calculate bounding box
	void CalculateBoundingBox() const
	{
		if ((mColumnCount < 1) || (mRowCount < 1))
			return;

		float minx = mPoint[0][0].x(), maxx = mPoint[0][0].x();
		float miny = mPoint[0][0].y(), maxy = mPoint[0][0].y();
		float minz = mPoint[0][0].z(), maxz = mPoint[0][0].z();
		const size_t nRows = mRowCount;
		const size_t nColumns = mColumnCount;
		for (size_t y = 0; y < nRows; y++)
			for (size_t x = 0; x < nColumns; x++)
			{
				// I guess it's faster for large nr of rows and columns to leave
				// next 2 lines commented out
				// if (!y && !x)
				//	continue;//skip first point, it's already taken into account

				const cldPnt& point = mPoint[y][x];

				if (minx > point.x())
					minx = point.x();
				if (maxx < point.x())
					maxx = point.x();
				if (miny > point.y())
					miny = point.y();
				if (maxy < point.y())
					maxy = point.y();
				if (minz > point.z())
					minz = point.z();
				if (maxz < point.z())
					maxz = point.z();
			}
		mBBox.SetCorners(mwTPoint3d<float>(minx, miny, minz), mwTPoint3d<float>(maxx, maxy, maxz));
	}

	/// Set bounding box
	///
	/// Set bounding box for given parameters:
	///	@param newBox const reference to the new bounding box
	void SetBoundingBox(const mw3dBoundingBox<float>& newBox) { mBBox = newBox; }

	/// @brief	The AcceptVisitor function
	/// @param	visitor	a parameter of type mw3dfObjectVisitor&
	virtual void AcceptVisitor(mw3dfObjectVisitor& visitor) { visitor.Visit(*this); }

	/// @brief	The AcceptVisitor function
	/// @param	visitor	a parameter of type const mw3dfObjectVisitor&
	virtual void AcceptVisitor(const mw3dfObjectVisitor& visitor) const { visitor.Visit(*this); }

	/// GetPointNormal function
	///
	///	@param rowindex of type size_t
	///	@param columnindex of type size_t
	///	@param step of type int
	///	@returns GetPointNormal of type const cldPnt
	const cldPnt GetPointNormal(size_t rowindex, size_t columnindex, int step = 1) const
	{
		cldPnt normal;

		if (rowindex >= mRowCount)
		{
			throw misc::mwIdxRangeException<size_t>(rowindex, mRowCount - 1);
		}
		if (columnindex > mColumnCount)
		{
			throw misc::mwIdxRangeException<size_t>(columnindex, mColumnCount - 1);
		}

		cldPnt vec1;
		cldPnt vec2;
		cldPnt vec3;
		cldPnt vec4;

		if (rowindex == 0 && columnindex == 0)
		{
			vec1 = mPoint[rowindex + step][columnindex] - mPoint[rowindex][columnindex];
			vec2 = mPoint[rowindex][columnindex + step] - mPoint[rowindex][columnindex];

			normal = vec1 % vec2;
			normal.Normalize();
		}
		else if (rowindex >= mRowCount - step && columnindex == mColumnCount - step)
		{
			vec1 = mPoint[rowindex - step][columnindex] - mPoint[rowindex][columnindex];
			vec2 = mPoint[rowindex][columnindex - step] - mPoint[rowindex][columnindex];

			normal = vec1 % vec2;
			normal.Normalize();
		}
		else if (rowindex == 0)
		{
			vec1 = mPoint[rowindex + step][columnindex] - mPoint[rowindex][columnindex];
			vec2 = mPoint[rowindex][columnindex + step] - mPoint[rowindex][columnindex];
			vec3 = mPoint[rowindex][columnindex - step] - mPoint[rowindex][columnindex];

			normal = vec1 % vec2 + vec3 % vec1;
			normal.Normalize();
		}
		else if (columnindex == 0)
		{
			vec1 = mPoint[rowindex + step][columnindex] - mPoint[rowindex][columnindex];
			vec2 = mPoint[rowindex][columnindex + step] - mPoint[rowindex][columnindex];
			vec3 = mPoint[rowindex - step][columnindex] - mPoint[rowindex][columnindex];

			normal = vec1 % vec2 + vec2 % vec3;
			normal.Normalize();
		}
		else if (rowindex >= mRowCount - step)
		{
			vec1 = mPoint[rowindex - step][columnindex] - mPoint[rowindex][columnindex];
			vec2 = mPoint[rowindex][columnindex - step] - mPoint[rowindex][columnindex];
			vec3 = mPoint[rowindex][columnindex] - mPoint[rowindex][columnindex + step];

			normal = vec1 % vec2 + vec3 % vec1;
			normal.Normalize();
		}
		else if (columnindex == mColumnCount - step)
		{
			vec1 = mPoint[rowindex - step][columnindex] - mPoint[rowindex][columnindex];
			vec2 = mPoint[rowindex][columnindex - step] - mPoint[rowindex][columnindex];
			vec1 = mPoint[rowindex + step][columnindex] - mPoint[rowindex][columnindex];

			normal = vec1 % vec2 + vec2 % vec3;
			normal.Normalize();
		}
		else
		{
			vec1 = mPoint[rowindex + step][columnindex] - mPoint[rowindex][columnindex];
			vec2 = mPoint[rowindex][columnindex + step] - mPoint[rowindex][columnindex];
			vec3 = mPoint[rowindex - step][columnindex] - mPoint[rowindex][columnindex];
			vec4 = mPoint[rowindex][columnindex - step] - mPoint[rowindex][columnindex];

			normal = vec1 % vec2 + vec3 % vec4;
			normal.Normalize();
		}

		return normal;
	}

	/// SetRowNormal function
	///
	///	@param rowIndex of type size_t
	///	@param normal of type const cldPnt &
	///	@returns SetRowNormal of type void
	void SetRowNormal(size_t rowIndex, const cldPnt& normal) { mRowNormals[rowIndex] = normal; }

	/// GetRowNormal function
	///
	///	@param rowIndex of type size_t
	///	@returns &GetRowNormal of type const cldPnt
	const cldPnt& GetRowNormal(size_t rowIndex) const { return mRowNormals[rowIndex]; }

	/// SetColumnNormal function
	///
	///	@param columnIndex of type size_t
	///	@param normal of type const cldPnt &
	///	@returns SetColumnNormal of type void
	void SetColumnNormal(size_t columnIndex, const cldPnt& normal)
	{
		mColumnNormals[columnIndex] = normal;
	}

	/// GetColumnNormal function
	///
	///	@param columnIndex of type size_t
	///	@returns &GetColumnNormal of type const cldPnt
	const cldPnt& GetColumnNormal(size_t columnIndex) const { return mColumnNormals[columnIndex]; }

	const bool IsFlat() const { return mFlat; }

	void SetFlat(bool flat) { mFlat = flat; }

	void AllocateNormals()
	{
		if (mNormal == MW_NULL)
		{
			mNormal = new cldPnt*[mRowCount];
			AllocateRows(mNormal, mChunkRowCount);
		}
	}

	cldPnt** const GetPointRows() const { return mPoint; }

	cldPnt** const GetNormalRows() const { return mNormal; }

	void SetNormal(const size_t rowIndex, const size_t columnIndex, const cldPnt& normal)
	{
		mNormal[rowIndex][columnIndex] = normal;
	}

	const cldPnt& GetNormal(const size_t rowIndex, const size_t columnIndex) const
	{
		return mNormal[rowIndex][columnIndex];
	}

private:
	mwTOrderedPntCloud(const mwTOrderedPntCloud&);
	const mwTOrderedPntCloud& operator=(const mwTOrderedPntCloud&);

	void AllocateRows(cldPnt**& rows, size_t& chunkRowCount) const
	{
		// We allocate data in chunks of a certain size.
		// The last chunk is fully allocated even if we only store a single row inside it to avoid
		// heap fragmentation. A chunk cannot start in the middle of a row. In rows we store
		// pointers to the beginning of all rows. Not all these pointers were really allocated,
		// since many rows can fit inside a chunk.

		const size_t CHUNK_SIZE = 1 * 1024 * 1024;  // 1 MB
		const size_t rowSize = mColumnCount * sizeof(cldPnt);
		chunkRowCount = CHUNK_SIZE / rowSize;
		for (size_t i = 0; i < mRowCount; i += chunkRowCount)
		{
#if defined(_WIN32)
			rows[i] = reinterpret_cast<cldPnt*>(
				VirtualAlloc(MW_NULL, CHUNK_SIZE, MEM_COMMIT, PAGE_READWRITE));
			if (rows[i] == MW_NULL)
				throw misc::mwException(0, _T("Failed to allocate memory"));
#elif defined(__linux__) || defined(__APPLE__)
			int fd;
			rows[i] = reinterpret_cast<cldPnt*>(mmap(
				MW_NULL,
				CHUNK_SIZE,
				PROT_READ | PROT_WRITE,
				MAP_FIXED | MAP_SHARED | MAP_ANON,
				-1,
				0));
			if (rows[i] == reinterpret_cast<cldPnt*>(MAP_FAILED))
				throw misc::mwException(0, _T("Failed to allocate memory"));
			msync(reinterpret_cast<void*>(rows[i]), CHUNK_SIZE, MS_SYNC | MS_INVALIDATE);
#endif
			size_t lastRow = i + chunkRowCount;
			if (lastRow >= mRowCount)
				lastRow = mRowCount;
			for (size_t j = i + 1; j < lastRow; j++)
				rows[j] = rows[j - 1] + mColumnCount;
		}
	}

	void FreeRows(cldPnt**& rows, size_t chunkRowCount) const
	{
		if (rows != MW_NULL)
		{
			for (size_t i = 0; i < mRowCount; i += chunkRowCount)
			{
#if defined(_WIN32)
				VirtualFree(rows[i], 0, MEM_RELEASE);
#elif defined(__linux__) || defined(__APPLE__)
				msync(reinterpret_cast<void*>(rows[i]), chunkRowCount, MS_SYNC);
				munmap(reinterpret_cast<void*>(rows[i]), chunkRowCount);
#endif
			}
			delete[] rows;
			rows = MW_NULL;
		}
	}

	typedef std::vector<cldPnt> normalArray;

	mutable mw3dBoundingBox<float> mBBox;

	cldPnt** mPoint;
	cldPnt** mNormal;
	size_t mRowCount;
	size_t mColumnCount;
	size_t mChunkRowCount;

	normalArray mRowNormals;
	normalArray mColumnNormals;

	bool mFlat;  // false if the point cloud is wrapped
};

typedef mwTOrderedPntCloud<float> mwOrderedPntCloud;
typedef misc::mwAutoPointer<mwOrderedPntCloud> mwOrderedPntCloudPtr;
}  // namespace cadcam
#endif  //	MW_MWORDEREDPNTCLOUD_HPP_
