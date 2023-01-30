// (C) 2006-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLCASTER_HPP_
#define MW_MWTOOLCASTER_HPP_
#include "mwAutoPointer.hpp"
#include "mwBarrelTaperMill.hpp"
#include "mwBullMill.hpp"
#include "mwChamferMill.hpp"
#include "mwChiselingTool.hpp"
#include "mwException.hpp"
#include "mwGenericExtrudedTool.hpp"
#include "mwGenericRevolvedTool.hpp"
#include "mwGenericTool.hpp"
#include "mwOpticDiamondTool.hpp"
#include "mwOverrideFinal.hpp"
#include "mwRevolvedTool.hpp"
#include "mwSawingTool.hpp"
#include "mwSlotMill.hpp"
#include "mwTaperMill.hpp"
#include "mwThreadTapTool.hpp"
#include "mwTool.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwTypedRevolvedTool.hpp"
#include "mwTypedSawingTool.hpp"
#include "mwWireTool.hpp"
#include "mwThreadMillSingleFormTool.hpp"

namespace cadcam
{
class MW_5AXUTIL_API mwToolCaster
{
public:
	static const misc::mwAutoPointer<cadcam::mwRevolvedTool> SafeCast2Revolved(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2RevolvedChecker castingChecker;
		tool->AcceptVirtual(castingChecker);

		misc::mwAutoPointer<cadcam::mwRevolvedTool> result;
		result.UnsafeAssign(tool);
		return result;
	}

	static const misc::mwAutoPointer<cadcam::mwTaperMill> SafeCast2TaperMill(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCaster2Taper caster;
		tool->AcceptVirtual(caster);

		return caster.GetResult();
	}

	static const misc::mwAutoPointer<cadcam::mwChamferMill> SafeCast2ChamferMill(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCaster2Chamfer caster;
		tool->AcceptVirtual(caster);

		return caster.GetResult();
	}

	static const misc::mwAutoPointer<cadcam::mwBullMill> SafeCast2BullMill(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCaster2Bull caster;
		tool->AcceptVirtual(caster);

		return caster.GetResult();
	}

	static const misc::mwAutoPointer<cadcam::mwSlotMill> SafeCast2SlotMill(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCaster2Slot caster;
		tool->AcceptVirtual(caster);

		return caster.GetResult();
	}


	static const misc::mwAutoPointer<cadcam::mwBarrelTaperMill> SafeCast2BarrelTaperMill(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCaster2BarrelTaper caster;
		tool->AcceptVirtual(caster);

		return caster.GetResult();
	}

	static const cadcam::mwRevolvedTool& SafeCast2Revolved(const cadcam::mwTool& tool)
	{
		mwCasting2RevolvedChecker castingChecker;
		tool.AcceptVirtual(castingChecker);
		const cadcam::mwRevolvedTool* result = static_cast<const cadcam::mwRevolvedTool*>(&tool);

		return *result;
	}

	static bool CanCast2Revolved(const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2RevolvedChecker castingChecker(false);
		tool->AcceptVirtual(castingChecker);

		return !castingChecker.MetException();
	}

	static bool CanCast2Revolved(const cadcam::mwTool& tool)
	{
		mwCasting2RevolvedChecker castingChecker(false);
		tool.AcceptVirtual(castingChecker);

		return !castingChecker.MetException();
	}

	static const cadcam::mwChiselingTool& SafeCast2ChiselingTool(const cadcam::mwTool& tool)
	{
		mwCasting2ChiselingToolChecker castingChecker;
		tool.AcceptVirtual(castingChecker);
		const cadcam::mwChiselingTool* result = static_cast<const cadcam::mwChiselingTool*>(&tool);

		return *result;
	}

	static bool CanCast2ChiselingTool(const cadcam::mwTool& tool)
	{
		mwCasting2ChiselingToolChecker castingChecker(false);
		tool.AcceptVirtual(castingChecker);

		return !castingChecker.MetException();
	}

	static const cadcam::mwOpticDiamondTool& SafeCast2OpticDiamondTool(const cadcam::mwTool& tool)
	{
		mwCasting2OpticDiamondToolChecker castingChecker;
		tool.AcceptVirtual(castingChecker);
		const cadcam::mwOpticDiamondTool* result =
			static_cast<const cadcam::mwOpticDiamondTool*>(&tool);

		return *result;
	}

	static bool CanCast2OpticDiamondTool(const cadcam::mwTool& tool)
	{
		mwCasting2OpticDiamondToolChecker castingChecker(false);
		tool.AcceptVirtual(castingChecker);

		return !castingChecker.MetException();
	}

	static const cadcam::mwGenericRevolvedTool& SafeCast2GenericRevolved(const cadcam::mwTool& tool)
	{
		mwCasting2GenericRevolvedChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		return static_cast<const cadcam::mwGenericRevolvedTool&>(tool);
	}

	static const misc::mwAutoPointer<cadcam::mwGenericRevolvedTool> SafeCast2GenericRevolved(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2GenericRevolvedChecker castingChecker;
		tool->AcceptVirtual(castingChecker);

		misc::mwAutoPointer<cadcam::mwGenericRevolvedTool> result;
		result.UnsafeAssign(tool);
		return result;
	}

	static bool CanCast2GenericRevolved(const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2GenericRevolvedChecker castingChecker(false);
		tool->AcceptVirtual(castingChecker);

		return !castingChecker.MetException();
	}

	static bool CanCast2GenericRevolved(const cadcam::mwTool& tool)
	{
		mwCasting2GenericRevolvedChecker castingChecker(false);
		tool.AcceptVirtual(castingChecker);

		return !castingChecker.MetException();
	}

	static const misc::mwAutoPointer<cadcam::mwGenericExtrudedTool> SafeCast2GenericExtruded(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2GenericExtrudedChecker castingChecker;
		tool->AcceptVirtual(castingChecker);

		misc::mwAutoPointer<cadcam::mwGenericExtrudedTool> result;
		result.UnsafeAssign(tool);
		return result;
	}

	static const cadcam::mwGenericExtrudedTool& SafeCast2GenericExtruded(const cadcam::mwTool& tool)
	{
		mwCasting2GenericExtrudedChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		return static_cast<const cadcam::mwGenericExtrudedTool&>(tool);
	}

	static const cadcam::mwGenericExtrudedTool& SafeCast2GenericExtruded(
		const cadcam::mwExtrudedTool& tool)
	{
		mwCastingToGenericExtrudedChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		return static_cast<const cadcam::mwGenericExtrudedTool&>(tool);
	}

	static const misc::mwAutoPointer<cadcam::mwWireTool> SafeCast2Wire(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2WireChecker castingChecker;
		tool->AcceptVirtual(castingChecker);

		misc::mwAutoPointer<cadcam::mwWireTool> result;
		result.UnsafeAssign(tool);
		return result;
	}

	static const cadcam::mwWireTool& SafeCast2Wire(const cadcam::mwTool& tool)
	{
		mwCasting2WireChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		return static_cast<const cadcam::mwWireTool&>(tool);
	}

	static const misc::mwAutoPointer<cadcam::mwTypedRevolvedTool> SafeCast2TypedRevolved(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2TypedRevolvedChecker castingChecker;
		tool->AcceptVirtual(castingChecker);

		misc::mwAutoPointer<cadcam::mwTypedRevolvedTool> result;
		result.UnsafeAssign(tool);
		return result;
	}

	static const cadcam::mwTypedRevolvedTool& SafeCast2TypedRevolved(const cadcam::mwTool& tool)
	{
		mwCasting2TypedRevolvedChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		const cadcam::mwTypedRevolvedTool* result =
			static_cast<const cadcam::mwTypedRevolvedTool*>(&tool);
		return *result;
	}

	static const cadcam::mwSawingTool& SafeCast2SawingTool(const cadcam::mwTool& tool)
	{
		mwCasting2SawingToolChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		const cadcam::mwSawingTool* result = static_cast<const cadcam::mwSawingTool*>(&tool);
		return *result;
	}

	static const cadcam::mwExtrudedTool& SafeCast2ExtrudedTool(const cadcam::mwTool& tool)
	{
		mwCasting2ExtrudedToolChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		const cadcam::mwExtrudedTool* result = static_cast<const cadcam::mwExtrudedTool*>(&tool);
		return *result;
	}

	static const misc::mwAutoPointer<cadcam::mwSawingTool> SafeCast2SawingTool(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2SawingToolChecker castingChecker;
		tool->AcceptVirtual(castingChecker);

		misc::mwAutoPointer<cadcam::mwSawingTool> result;
		result.UnsafeAssign(tool);
		return result;
	}

	static bool CanCast2SawingTool(const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2SawingToolChecker castingChecker(false);
		tool->AcceptVirtual(castingChecker);

		return !castingChecker.MetException();
	}

	static bool CanCast2SawingTool(const cadcam::mwTool& tool)
	{
		mwCasting2SawingToolChecker castingChecker(false);
		tool.AcceptVirtual(castingChecker);

		return !castingChecker.MetException();
	}

	static const cadcam::mwTypedSawingTool& SafeCast2TypedSawingTool(const cadcam::mwTool& tool)
	{
		mwCasting2TypedSawToolChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		const cadcam::mwTypedSawingTool* result =
			static_cast<const cadcam::mwTypedSawingTool*>(&tool);
		return *result;
	}

	static const misc::mwAutoPointer<cadcam::mwTypedSawingTool> SafeCast2TypedSawingTool(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCasting2TypedSawToolChecker castingChecker;
		tool->AcceptVirtual(castingChecker);

		misc::mwAutoPointer<cadcam::mwTypedSawingTool> result;
		result.UnsafeAssign(tool);
		return result;
	}

	static bool CanCast2TypedExtrudedTool(const cadcam::mwTool& tool)
	{
		mwCasting2TypedExtrudedToolChecker castingChecker(false);
		tool.AcceptVirtual(castingChecker);

		return !castingChecker.MetException();
	}

	static const misc::mwAutoPointer<cadcam::mwTypedExtrudedTool> SafeCast2TypedExtrudedTool(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		if (tool.IsNull())
			return MW_NULL;

		mwCasting2TypedExtrudedToolChecker castingChecker;
		tool->AcceptVirtual(castingChecker);

		misc::mwAutoPointer<cadcam::mwTypedExtrudedTool> result;
		result.UnsafeAssign(tool);
		return result;
	}

	static const cadcam::mwTypedExtrudedTool& SafeCast2TypedExtrudedTool(const cadcam::mwTool& tool)
	{
		mwCasting2TypedExtrudedToolChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		return static_cast<const cadcam::mwTypedExtrudedTool&>(tool);
	}

	static bool CanCast2GenericTool(const cadcam::mwTool& tool)
	{
		mwCastingToGenericToolChecker castingChecker(false);
		tool.AcceptVirtual(castingChecker);

		return castingChecker.MetGenericTool();
	}

	static const cadcam::mwGenericTool& SafeCast2GenericTool(const cadcam::mwTool& tool)
	{
		mwCastingToGenericToolChecker castingChecker;
		tool.AcceptVirtual(castingChecker);

		return static_cast<const cadcam::mwGenericTool&>(tool);
	}

	static const misc::mwAutoPointer<cadcam::mwThreadTapTool> SafeCast2ThreadTap(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCaster2ThreadTap caster;
		tool->AcceptVirtual(caster);

		return caster.GetResult();
	}

	static const misc::mwAutoPointer<cadcam::mwThreadMillSingleFormTool> SafeCast2ThreadMillSingleForm(
		const misc::mwAutoPointer<const cadcam::mwTool>& tool)
	{
		mwCaster2ThreadMillSingleForm caster;
		tool->AcceptVirtual(caster);

		return caster.GetResult();
	}

private:
	class mwCasting2RevolvedChecker: public mwToolBranchVisitor
	{
	public:
		explicit mwCasting2RevolvedChecker(bool bAlwaysThrow = true)
			: m_bAlwaysThrow(bAlwaysThrow), m_bExceptionMet(false)
		{
		}

		~mwCasting2RevolvedChecker() {}

		void Visit(const mwRevolvedTool&)
		{
			// do conversion;
		}

		const bool MetException() const { return m_bExceptionMet; }

	private:
		bool m_bAlwaysThrow;
		bool m_bExceptionMet;

		virtual void Default()
		{
			m_bExceptionMet = true;
			if (m_bAlwaysThrow)
				MW_EXCEPTION("mwCasting2RevolvedChecker: Illegal casting");
		}
	};

	class mwCasting2ChiselingToolChecker: public mwToolBranchVisitor
	{
	public:
		explicit mwCasting2ChiselingToolChecker(bool bAlwaysThrow = true)
			: m_bExceptionMet(false), m_bAlwaysThrow(bAlwaysThrow)
		{
		}

		~mwCasting2ChiselingToolChecker() {}

		void Visit(const mwChiselingTool&)
		{
			// do conversion;
		}

		const bool MetException() const { return m_bExceptionMet; }

	private:
		bool m_bExceptionMet;
		bool m_bAlwaysThrow;

		virtual void Default()
		{
			m_bExceptionMet = true;
			if (m_bAlwaysThrow)
				MW_EXCEPTION("mwCasting2ChiselingToolChecker: Illegal casting");
		}
	};

	class mwCasting2OpticDiamondToolChecker: public mwToolBranchVisitor
	{
	public:
		explicit mwCasting2OpticDiamondToolChecker(bool bAlwaysThrow = true)
			: m_bAlwaysThrow(bAlwaysThrow), m_bExceptionMet(false)
		{
		}

		~mwCasting2OpticDiamondToolChecker() {}

		void Visit(const mwOpticDiamondTool&)
		{
			// do conversion;
		}

		const bool MetException() const { return m_bExceptionMet; }

	private:
		bool m_bAlwaysThrow;
		bool m_bExceptionMet;

		virtual void Default()
		{
			m_bExceptionMet = true;
			if (m_bAlwaysThrow)
				MW_EXCEPTION("mwCasting2OpticDiamondToolChecker: Illegal casting");
		}
	};

	class mwCaster2Taper: public mwToolVisitor
	{
	public:
		explicit mwCaster2Taper(): m_isConverted(false) {}

		~mwCaster2Taper() {}

		void Visit(const mwTaperMill& toCopy)
		{
			res = misc::mwAutoPointer<mwTaperMill>(new mwTaperMill(toCopy));
			m_isConverted = true;
		}
		misc::mwAutoPointer<mwTaperMill> GetResult() const
		{
			if (!m_isConverted)
				MW_EXCEPTION("Tool hav'nt been converted");
			return res;
		}

	private:
		misc::mwAutoPointer<mwTaperMill> res;
		bool m_isConverted;
	};

	class mwCaster2Chamfer: public mwToolVisitor
	{
	public:
		explicit mwCaster2Chamfer(): m_isConverted(false) {}

		~mwCaster2Chamfer() {}

		void Visit(const mwChamferMill& toCopy)
		{
			res = misc::mwAutoPointer<mwChamferMill>(new mwChamferMill(toCopy));
			m_isConverted = true;
		}
		misc::mwAutoPointer<mwChamferMill> GetResult() const
		{
			if (!m_isConverted)
				MW_EXCEPTION("Tool hav'nt been converted");
			return res;
		}

	private:
		misc::mwAutoPointer<mwChamferMill> res;
		bool m_isConverted;
	};

	class mwCaster2Bull: public mwToolVisitor
	{
	public:
		void Visit(const mwBullMill& toCopy)
		{
			res = misc::mwAutoPointer<mwBullMill>(new mwBullMill(toCopy));
		}
		misc::mwAutoPointer<mwBullMill> GetResult() const
		{
			if (res.IsNull())
				MW_EXCEPTION("Tool is not converted.");
			return res;
		}

	private:
		misc::mwAutoPointer<mwBullMill> res;
	};

	class mwCaster2Slot: public mwToolVisitor
	{
	public:
		void Visit(const mwSlotMill& toCopy)
		{
			res = misc::mwAutoPointer<mwSlotMill>(new mwSlotMill(toCopy));
		}
		misc::mwAutoPointer<mwSlotMill> GetResult() const
		{
			if (res.IsNull())
				MW_EXCEPTION("Tool is not converted.");
			return res;
		}

	private:
		misc::mwAutoPointer<mwSlotMill> res;
	};

	class mwCaster2BarrelTaper: public mwToolVisitor
	{
	public:
		explicit mwCaster2BarrelTaper(): m_isConverted(false) {}

		~mwCaster2BarrelTaper() {}

		void Visit(const mwBarrelTaperMill& toCopy)
		{
			res = misc::mwAutoPointer<mwBarrelTaperMill>(new mwBarrelTaperMill(toCopy));
			m_isConverted = true;
		}
		misc::mwAutoPointer<mwBarrelTaperMill> GetResult() const
		{
			if (!m_isConverted)
				MW_EXCEPTION("Tool hav'nt been converted");
			return res;
		}

	private:
		misc::mwAutoPointer<mwBarrelTaperMill> res;
		bool m_isConverted;
	};

	class mwCaster2ThreadTap: public mwToolVisitor
	{
	public:
		void Visit(const mwThreadTapTool& toCopy)
		{
			res = misc::mwAutoPointer<mwThreadTapTool>(new mwThreadTapTool(toCopy));
		}
		misc::mwAutoPointer<mwThreadTapTool> GetResult() const
		{
			if (res.IsNull())
				MW_EXCEPTION("Tool is not converted.");
			return res;
		}

	private:
		misc::mwAutoPointer<mwThreadTapTool> res;
	};

	class mwCaster2ThreadMillSingleForm : public mwToolVisitor
	{
	public:
		void Visit(const mwThreadMillSingleFormTool& toCopy)
		{
			res = misc::mwAutoPointer<mwThreadMillSingleFormTool>(new mwThreadMillSingleFormTool(toCopy));
		}
		misc::mwAutoPointer<mwThreadMillSingleFormTool> GetResult() const
		{
			if (res.IsNull())
				MW_EXCEPTION("Tool is not converted.");
			return res;
		}

	private:
		misc::mwAutoPointer<mwThreadMillSingleFormTool> res;
	};

	class mwCasting2GenericExtrudedChecker: public mwToolVisitor
	{
	public:
		~mwCasting2GenericExtrudedChecker() {}

		void Visit(const mwGenericExtrudedTool&)
		{
			// do conversion;
		}

	private:
		virtual void Default()
		{
			MW_EXCEPTION("mwCasting2GenericExtrudedChecker: Illegal casting");
		}
	};

	class mwCastingToGenericExtrudedChecker: public mwToolVisitor
	{
	public:
		void Visit(const mwGenericExtrudedTool&)
		{
			// do conversion;
		}

	private:
		virtual void Default() { MW_EXCEPTION("mwCastingToExtrudedChecker: Illegal casting"); }
	};

	class mwCastingToGenericToolChecker: public mwToolVisitor
	{
	public:
		explicit mwCastingToGenericToolChecker(bool bAlwaysThrow = true)
			: m_bAlwaysThrow(bAlwaysThrow), m_metGenericTool(false)
		{
		}

		void Visit(const mwGenericTool&) MW_OVERRIDE
		{
			// allow conversion
			m_metGenericTool = true;
		}

		bool MetGenericTool() const { return m_metGenericTool; }

	protected:
		virtual void Default() MW_OVERRIDE
		{
			m_metGenericTool = false;
			if (m_bAlwaysThrow)
				MW_EXCEPTION("mwCastingToGenericToolChecker: Illegal casting");
		}

	private:
		bool m_bAlwaysThrow;
		bool m_metGenericTool;
	};

	class mwCasting2GenericRevolvedChecker: public mwToolVisitor
	{
	public:
		explicit mwCasting2GenericRevolvedChecker(bool bAlwaysThrow = true)
			: m_bAlwaysThrow(bAlwaysThrow), m_bExceptionMet(false)
		{
		}

		void Visit(const mwGenericRevolvedTool&)
		{
			// do conversion;
		}

		const bool MetException() const { return m_bExceptionMet; }

	private:
		bool m_bAlwaysThrow;
		bool m_bExceptionMet;

		virtual void Default()
		{
			m_bExceptionMet = true;
			if (m_bAlwaysThrow)
				MW_EXCEPTION("mwCasting2GenericRevolvedTool: Illegal casting");
		}
	};

	class mwCasting2WireChecker: public mwToolBranchVisitor
	{
	public:
		~mwCasting2WireChecker() {}

		void Visit(const mwWireTool&)
		{
			// do conversion;
		}

	private:
		virtual void Default() { MW_EXCEPTION("mwCasting2WireChecker: Illegal casting"); }
	};

	class mwCasting2TypedRevolvedChecker: public mwToolVisitor
	{
	public:
		~mwCasting2TypedRevolvedChecker() {}

		/// Visit const mwTool
		virtual void Visit(const mwTool&)
		{
			MW_EXCEPTION("Illegal casting of mwTool& to mwTypedRevolvedTool& type object");
		}
		/// Visit const mwBoreBar
		virtual void Visit(const mwBoreBar&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwBullMill
		virtual void Visit(const mwBullMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwChamferMill
		virtual void Visit(const mwChamferMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwCntrBore
		virtual void Visit(const mwCntrBore&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwCSink
		virtual void Visit(const mwCSink&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwCtrDrill
		virtual void Visit(const mwCtrDrill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwDoveMill
		virtual void Visit(const mwDoveMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwDrill
		virtual void Visit(const mwDrill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwEndMill
		virtual void Visit(const mwEndMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwFaceMill
		virtual void Visit(const mwFaceMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwLolMill
		virtual void Visit(const mwLolMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwRadMill
		virtual void Visit(const mwRadMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwReamer
		virtual void Visit(const mwReamer&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwSlotMill
		virtual void Visit(const mwSlotMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwSphereMill
		virtual void Visit(const mwSphereMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwSpotDrill
		virtual void Visit(const mwSpotDrill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwTaperMill
		virtual void Visit(const mwTaperMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwTapLH
		virtual void Visit(const mwTapLH&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwTapRH
		virtual void Visit(const mwTapRH&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwBarrelMill
		virtual void Visit(const mwBarrelMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwBarrelAdvancedMill
		virtual void Visit(const mwBarrelAdvancedMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwBarrelBarrSecMill
		virtual void Visit(const mwBarrelBarrSecMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwBarrelDProfMill
		virtual void Visit(const mwBarrelDProfMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwBarrelTangentMill
		virtual void Visit(const mwBarrelTangentMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwBarrelTangentMillConicalShaft
		virtual void Visit(const mwBarrelTangentMillConicalShaft&) {
		}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwBarrelLensMill
		virtual void Visit(const mwBarrelLensMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwBarrelTaperMill
		virtual void Visit(const mwBarrelTaperMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwConvexTipMill
		virtual void Visit(const mwConvexTipMill&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwPotGrinderTool
		virtual void Visit(const mwPotGrinderTool&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwThreadTapTool
		virtual void Visit(const mwThreadTapTool&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwThreadMillSingleFormTool
		virtual void Visit(const mwThreadMillSingleFormTool&) {}  // ok, this is a mwTypedRevoledTool
		/// Visit const mwGenericRevolvedTool
		virtual void Visit(const mwGenericRevolvedTool&) {}  // ok, this is a mwTypedRevoledTool
	private:
		virtual void Default() { MW_EXCEPTION("mwCasting2TypedRevolvedChecker: illegal casting"); }
	};

	class mwCasting2SawingToolChecker: public mwToolBranchVisitor
	{
	public:
		explicit mwCasting2SawingToolChecker(bool bAlwaysThrow = true)
			: m_bAlwaysThrow(bAlwaysThrow), m_bExceptionMet(false)
		{
		}

		~mwCasting2SawingToolChecker() {}

		void Visit(const mwSawingTool&)
		{
			// do conversion;
		}
		const bool MetException() const { return m_bExceptionMet; }

	private:
		bool m_bAlwaysThrow;
		bool m_bExceptionMet;

		virtual void Default()
		{
			m_bExceptionMet = true;
			if (m_bAlwaysThrow)
				MW_EXCEPTION("mwCasting2SawingToolChecker: Illegal casting");
		}
	};

	class mwCasting2TypedSawToolChecker: public mwToolBranchVisitor
	{
	public:
		~mwCasting2TypedSawToolChecker() {}
		virtual void Visit(const mwChainSawTool&)
		{
			// ok, this is a mwTypedSawingTool ???
		}

		void Visit(const mwSawingTool&)
		{
			// do conversion;
		}

	private:
		virtual void Default() { MW_EXCEPTION("mwCasting2TypedSawToolChecker: Illegal casting"); }
	};

	class mwCasting2ExtrudedToolChecker: public mwToolBranchVisitor
	{
	public:
		explicit mwCasting2ExtrudedToolChecker(bool bAlwaysThrow = true)
			: m_bAlwaysThrow(bAlwaysThrow), m_bExceptionMet(false)
		{
		}

		void Visit(const mwExtrudedTool&) {}
		const bool MetException() const { return m_bExceptionMet; }

	private:
		bool m_bAlwaysThrow;
		bool m_bExceptionMet;

		virtual void Default()
		{
			m_bExceptionMet = true;
			if (m_bAlwaysThrow)
				MW_EXCEPTION("Illegal casting");
		}
	};

	class mwCasting2TypedExtrudedToolChecker: public mwToolVisitor
	{
	public:
		explicit mwCasting2TypedExtrudedToolChecker(bool bAlwaysThrow = true)
			: m_bAlwaysThrow(bAlwaysThrow), m_bExceptionMet(false)
		{
		}

		~mwCasting2TypedExtrudedToolChecker() {}

		void Visit(const mwTriangleTurningTool&) {}
		void Visit(const mwParallelogramTurningTool&) {}
		void Visit(const mwSquareTurningTool&) {}
		void Visit(const mwPentagonalTurningTool&) {}
		void Visit(const mwRoundTurningTool&) {}
		void Visit(const mwOctagonalTurningTool&) {}
		void Visit(const mwHexagonalTurningTool&) {}
		void Visit(const mwGrooveTurningTool&) {}
		void Visit(const mwDiamondTurningTool&) {}
		void Visit(const mwContourTurningTool&) {}
		void Visit(const mwThreadTriangleTurningTool&) {}
		void Visit(const mwPrimeTurningTool&) {}

		const bool MetException() const { return m_bExceptionMet; }

	private:
		bool m_bAlwaysThrow;
		bool m_bExceptionMet;

		virtual void Default()
		{
			m_bExceptionMet = true;

			if (m_bAlwaysThrow)
				MW_EXCEPTION("mwCasting2TypedExtrudedToolChecker: Illegal casting");
		}
	};
};
}  // namespace cadcam
#endif  //	MW_MWTOOLCASTER_HPP_
