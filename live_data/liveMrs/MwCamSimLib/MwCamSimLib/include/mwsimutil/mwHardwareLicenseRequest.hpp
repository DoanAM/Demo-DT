// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MC Integration

#ifndef MW_MWHARDWARELICENSEREQUEST_HPP_
#define MW_MWHARDWARELICENSEREQUEST_HPP_

#if defined (_WIN32)

#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include <vector>

namespace misc
{
	///Contains a customer request for a hardware license 
	class MW_5AXUTIL_API mwHardwareLicenseRequest
	{
	public:
	
		///Contains info about a requested product
		class MW_5AXUTIL_API mwRequestedProduct
		{
		public:
			mwRequestedProduct();

			const int GetType() const;
			void SetType(const int toSet);

			const misc::mwstring& GetName() const;
			void SetName(const misc::mwstring&  toSet);
		private:
			int m_type;
			misc::mwstring m_name;
		};
		
		///container for all requested products
		typedef std::vector <mwRequestedProduct> RequestedProducts;

		const RequestedProducts& GetRequestedProducts() const;
		void SetRequestedProducts(const RequestedProducts& toSet);

		const misc::mwstring& GetHardwareKey() const;
		void SetHardwareKey(const misc::mwstring& toSet);

		const misc::mwstring& GetPersonName() const;
		void SetPersonName(const misc::mwstring& toSet);

		const misc::mwstring& GetCompanyName() const;
		void SetCompanyName(const misc::mwstring& toSet);

		const misc::mwstring& GetComment() const;
		void SetComment(const misc::mwstring& toSet);
	
	private:

		RequestedProducts			 m_requestedProducts;
		misc::mwstring				 m_hardwareKey;
		misc::mwstring				 m_personName;
		misc::mwstring				 m_companyName;
		misc::mwstring				 m_comment;
	};
};//namespace
#endif

#endif //MW_MWHARDWARELICENSEREQUEST_HPP_

