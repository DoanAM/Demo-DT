// (C) 2015-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSCOPEDPOINTER_HPP_
#define MW_MWSCOPEDPOINTER_HPP_
namespace misc
{
	template<typename T> inline void DeletePointerData(T* data, bool isArray) { (isArray) ? delete[] data : delete data; }

	template<typename T, bool Array = false>
	class mwScopedPointer
	{
	public:
		mwScopedPointer():
			m_data(0)
		{}
		mwScopedPointer(T* data):
			m_data(data)
		{}
		void reset(T* data)
		{
			Clear();
			m_data=data;
		}
		~mwScopedPointer()
		{
			Clear();
		}
		T* get()
		{
			return m_data;		
		}
		const T* get() const
		{
			return m_data;	
		}
		T* operator ->()
		{
			return get();
		}
		const T* operator ->() const
		{
			return get();
		}
		T& operator *()
		{
			return *get();
		}
		const T& operator *() const
		{
			return *get();
		}
	private:
		mwScopedPointer(const mwScopedPointer& ptr);
		const mwScopedPointer& operator =(const mwScopedPointer& ptr);
		void Clear()
		{
			if(m_data)
			{
				DeletePointerData<T>(m_data, Array);
			}
		}
		T* m_data;
	};
}
#endif	//	MW_MWSCOPEDPOINTER_HPP_
