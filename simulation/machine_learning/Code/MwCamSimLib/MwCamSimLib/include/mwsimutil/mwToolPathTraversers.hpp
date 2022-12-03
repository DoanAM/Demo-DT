// (C) 2013-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPATHTRAVERSERS_HPP_
#define MW_MWTOOLPATHTRAVERSERS_HPP_
#include "mwCNCMove.hpp"
#include "mwTPPass.hpp"
#include "mwTPSection.hpp"
#include "mwTPSectionFit.hpp"
#include "mwTPSlice.hpp"
#include "mwToolPath.hpp"

namespace cadcam
{
namespace mwToolPathTraverser
{
namespace Internal
{
template <typename FunctionOnContainedGeometry, typename ToolPathGeometry>
class ToolPathGeometryBrowser;

template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwToolPath>
{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(mwToolPath& src)
	{
		for (mwToolPath::OverTPPassesIterator passIt = src.GetPassesBegin();
			 passIt != src.GetPassesEnd();
			 ++passIt)
		{
			m_functionOnContainedGeometry(**passIt);
		}
	}

private:
	ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwToolPath>& operator=(
		const ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwToolPath>&);
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};

template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwTPPass>
{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(mwTPPass& src)
	{
		for (mwTPPass::OverTPSlicesIterator sliceIt = src.GetSlicesBegin();
			 sliceIt != src.GetSlicesEnd();
			 ++sliceIt)
		{
			m_functionOnContainedGeometry(**sliceIt);
		}
	}

private:
	ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwTPPass>& operator=(
		const ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwTPPass>&);
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};

template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwTPSlice>
{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(mwTPSlice& src)
	{
		for (mwTPSlice::OverTPSectionsIterator sectionIt = src.GetSectionsBegin();
			 sectionIt != src.GetSectionsEnd();
			 ++sectionIt)
		{
			m_functionOnContainedGeometry(**sectionIt);
		}
	}

private:
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};

template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwTPSection>
{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(mwTPSection& src)
	{
		for (mwTPSection::OverTPSectionsFitIterator sectionFitIt = src.GetSectionsFitBegin();
			 sectionFitIt != src.GetSectionsFitEnd();
			 ++sectionFitIt)
		{
			m_functionOnContainedGeometry(**sectionFitIt);
		}
	}

private:
	ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwTPSection>& operator=(
		const ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwTPSection>&);
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};

template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, mwTPSectionFit>
{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(mwTPSectionFit& src)
	{
		for (mwTPSectionFit::OverMovesIterator moveIt = src.GetMovesBegin();
			 moveIt != src.GetMovesEnd();
			 ++moveIt)
		{
			m_functionOnContainedGeometry(**moveIt);
		}
	}

private:
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};
template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwToolPath>

{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(const mwToolPath& src)
	{
		for (mwToolPath::ConstOverTPPassesIterator passIt = src.GetPassesBegin();
			 passIt != src.GetPassesEnd();
			 ++passIt)
		{
			m_functionOnContainedGeometry(**passIt);
		}
	}

private:
	ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwToolPath>& operator=(
		const ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwToolPath>&);
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};

template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPPass>
{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(const mwTPPass& src)
	{
		for (mwTPPass::ConstOverTPSlicesIterator sliceIt = src.GetSlicesBegin();
			 sliceIt != src.GetSlicesEnd();
			 ++sliceIt)
		{
			m_functionOnContainedGeometry(**sliceIt);
		}
	}

private:
	ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPPass>& operator=(
		const ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPPass>&);
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};

template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPSlice>
{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(const mwTPSlice& src)
	{
		for (mwTPSlice::ConstOverTPSectionsIterator sectionIt = src.GetSectionsBegin();
			 sectionIt != src.GetSectionsEnd();
			 ++sectionIt)
		{
			m_functionOnContainedGeometry(**sectionIt);
		}
	}

private:
	ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPSlice>& operator=(
		const ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPSlice>&);
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};

template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPSection>
{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(const mwTPSection& src)
	{
		for (mwTPSection::ConstOverTPSectionsFitIterator sectionFitIt = src.GetSectionsFitBegin();
			 sectionFitIt != src.GetSectionsFitEnd();
			 ++sectionFitIt)
		{
			m_functionOnContainedGeometry(**sectionFitIt);
		}
	}

private:
	ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPSection>& operator=(
		const ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPSection>&);
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};

template <typename FunctionOnContainedGeometry>
class MW_5AXUTIL_API ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPSectionFit>
{
public:
	explicit ToolPathGeometryBrowser(FunctionOnContainedGeometry& functionOnContainedGeometry)
		: m_functionOnContainedGeometry(functionOnContainedGeometry)
	{
	}
	void operator()(const mwTPSectionFit& src)
	{
		for (mwTPSectionFit::ConstOverMovesIterator moveIt = src.GetMovesBegin();
			 moveIt != src.GetMovesEnd();
			 ++moveIt)
		{
			m_functionOnContainedGeometry(**moveIt);
		}
	}

private:
	ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPSectionFit>& operator=(
		const ToolPathGeometryBrowser<FunctionOnContainedGeometry, const mwTPSectionFit>&);
	FunctionOnContainedGeometry& m_functionOnContainedGeometry;
};


}  //  namespace Internal

template <typename Toolpath, typename Functor>
void ForEachPass(Toolpath& src, Functor& functorOnPass)
{
	Internal::ToolPathGeometryBrowser<Functor, Toolpath> browser(functorOnPass);
	browser(src);
}

template <typename ToolPathGeometry, typename Functor>
void ForEachSlice(ToolPathGeometry& object, Functor& functorOnSlice)
{
	Internal::ToolPathGeometryBrowser<Functor, mwTPPass> browser(functorOnSlice);
	ForEachPass(object, browser);
}

template <typename ToolPathGeometry, typename Functor>
void ForEachSlice(const ToolPathGeometry& object, Functor& functorOnSlice)
{
	Internal::ToolPathGeometryBrowser<Functor, const mwTPPass> browser(functorOnSlice);
	ForEachPass(object, browser);
}


template <typename Functor>
void ForEachSlice(mwTPPass& pass, Functor& functorOnSlice)
{
	Internal::ToolPathGeometryBrowser<Functor, mwTPPass> browser(functorOnSlice);
	browser(pass);
}

template <typename ToolPathGeometry, typename Functor>
void ForEachSection(ToolPathGeometry& object, Functor& functorOnSection)
{
	Internal::ToolPathGeometryBrowser<Functor, mwTPSlice> browser(functorOnSection);
	ForEachSlice(object, browser);
}

template <typename ToolPathGeometry, typename Functor>
void ForEachSection(const ToolPathGeometry& object, Functor& functorOnSection)
{
	Internal::ToolPathGeometryBrowser<Functor, const mwTPSlice> browser(functorOnSection);
	ForEachSlice(object, browser);
}

template <typename Functor>
void ForEachSection(mwTPSlice& slice, Functor& functorOnSection)
{
	Internal::ToolPathGeometryBrowser<Functor, mwTPSlice> browser(functorOnSection);
	browser(slice);
}

template <typename ToolPathGeometry, typename Functor>
void ForEachSectionFit(ToolPathGeometry& object, Functor& functionOnSectionFit)
{
	Internal::ToolPathGeometryBrowser<Functor, mwTPSection> browser(functionOnSectionFit);
	ForEachSection(object, browser);
}

template <typename ToolPathGeometry, typename Functor>
void ForEachSectionFit(const ToolPathGeometry& object, Functor& functionOnSectionFit)
{
	Internal::ToolPathGeometryBrowser<Functor, const mwTPSection> browser(functionOnSectionFit);
	ForEachSection(object, browser);
}

template <typename Functor>
void ForEachSectionFit(mwTPSection& section, Functor& functionOnSectionFit)
{
	Internal::ToolPathGeometryBrowser<Functor, mwTPSection> browser(functionOnSectionFit);
	browser(section);
}

template <typename ToolPathGeometry, typename Functor>
void ForEachMove(const ToolPathGeometry& object, Functor& functionOnMove)
{
	Internal::ToolPathGeometryBrowser<Functor, const mwTPSectionFit> browser(functionOnMove);
	ForEachSectionFit(object, browser);
}


template <typename ToolPathGeometry, typename Functor>
void ForEachMove(ToolPathGeometry& object, Functor& functionOnMove)
{
	Internal::ToolPathGeometryBrowser<Functor, mwTPSectionFit> browser(functionOnMove);
	ForEachSectionFit(object, browser);
}

template <typename ToolPath, typename Functor>
void ForEachMovePtr(ToolPath& object, Functor& functionOnMove)
{
	for (typename ToolPath::OverMovesIterator it = object.GetMovesBegin();
		 it != object.GetMovesEnd();
		 ++it)
	{
		functionOnMove(*it);
	}
}

template <typename Functor>
void ForEachMove(mwTPSectionFit& sectionFit, Functor& functionOnMove)
{
	Internal::ToolPathGeometryBrowser<Functor, mwTPSectionFit> browser(functionOnMove);
	browser(sectionFit);
}

template <typename Functor>
void ForEachMove(const mwTPSectionFit& sectionFit, Functor& functionOnMove)
{
	Internal::ToolPathGeometryBrowser<Functor, const mwTPSectionFit> browser(functionOnMove);
	browser(sectionFit);
}

}  // namespace mwToolPathTraverser
}  //  namespace cadcam
#endif  //	MW_MWTOOLPATHTRAVERSERS_HPP_
