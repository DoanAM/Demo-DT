// (C) 2008-2012 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWSCREENPOSITION_HPP_
#define MW_MWSCREENPOSITION_HPP_
namespace mmedia
{
	class mwScreenPosition
	{
	public:
		enum position
		{
			BOTTOM_LEFT = 0,
			BOTTOM_RIGHT,
			BOTTOM_CENTER,
			TOP_LEFT,
			TOP_RIGHT,
			TOP_CENTER,
			ORIGINAL_CENTER,
			FIT_CENTER,
			FILL_CENTER,
			STRECH_CENTER,
			ORIGINAL_TILED,
		};
	private:
		mwScreenPosition();
	};
}
#endif	//	MW_MWSCREENPOSITION_HPP_
