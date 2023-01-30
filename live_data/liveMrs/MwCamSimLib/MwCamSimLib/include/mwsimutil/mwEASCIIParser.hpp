// (C) 2004-2019 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWEASCIIPARSER_HPP_
#define MW_MWEASCIIPARSER_HPP_
#include <fstream>
#include <list>
#include "mwTPoint3d.hpp"
#include "mw3dPolyLine.hpp"
#include "mw3dGeometry.hpp"
#include "mwColor.hpp"
#include "mwStringTokenizer.hpp"
#include "mwStringOps.hpp"
#include "mwStream.hpp"



namespace machsim
{
	/*! mwEASCIIParser
		mwEASCIIParser class parses an ascii file (toolpath.asc usually located 
		in the machine definition folder), and produces an associated toolpath
		geometry.		
	*/
	class mwEASCIIParser
	{
	public:
		typedef cadcam::mwTPoint3d<float>			TPoint;
		typedef cadcam::mw3dPoint<float>			Point;
        typedef misc::mwAutoPointer< Point >		PointPtr;
		
		typedef misc::mwColor						ascColor;
		typedef cadcam::mwTPoint3d<float>			ascPnt;		

		struct ciPnt
		{
			ascPnt		pnt;
			ascColor	clr;
		};

		typedef cadcam::mw3dPolyLine<float>			ascPoly;		
		typedef std::list<ciPnt>					pntArray;
		typedef cadcam::mw3dPolyLine<float>			PolyLine;		
		
		struct coloredPolyLine
		{
			PolyLine		polyLine;
			misc::mwColor	colour;
		};
		typedef std::list<coloredPolyLine>			polyData;
		typedef misc::mwAutoPointer<polyData> 		polyDataRef;
		typedef polyData							polyArray;


		
		typedef misc::mwAutoPointer< pntArray >		pntArrayPtr;
		typedef misc::mwAutoPointer< polyArray >	polyArrayPtr;
		
		typedef pntArray::iterator					pntIterator;
		typedef pntArray::const_iterator			constPntIterator;
				
		typedef polyArray::iterator					polyIterator;
		typedef polyArray::const_iterator			constPolyIterator;

		//!Default constructor
		/*!
			\param input stream to parse
		*/
		explicit mwEASCIIParser( misc::mwIStream &input )
			:	mInput( input )
		{
		}

		//!Parse
		/*!Parses the input stream. Unknown tokens are silently ignored*/
		void Parse()
		{
			misc::mwStringTokenizer tokenizer( _T(" \t\n;") );
		
			const unsigned short lineLength = 1024;
			wchar_t line[lineLength];
			ascColor	currClr( 1., 1., 1. );

			while( mInput )
			{
				mInput.getline( line, lineLength );

				if( !mInput )
					break;

				tokenizer.Parse( line );
			
				if( tokenizer.GetTokens().size() != 4 )				
					continue;

				else
				{
					if( tokenizer[0] == _T("RGB") )
					{
						int color;
						misc::to_value (tokenizer[1],color);
						currClr.SetRed( static_cast<float> (color/255.) );
						misc::to_value (tokenizer[2],color);
						currClr.SetGreen(static_cast<float> (color/255.) );
						misc::to_value (tokenizer[3],color);
						currClr.SetBlue( static_cast<float> (color/255.) );
					}
					else if( tokenizer[0] == _T("PA") )
					{					
						mPolys.push_back( coloredPolyLine() );

						mPolys.back().colour = currClr;
						float value1;
						float value2;
						float value3;
						misc::to_value( tokenizer[1], value1 );
						misc::to_value( tokenizer[2], value2 );
						misc::to_value( tokenizer[3], value3 );						
						mPolys.back().polyLine.AddPoint(TPoint(value1, value2, value3));
											
					}
					else if( tokenizer[0] == _T("PE") )
					{
						float value1;
						float value2;
						float value3;
						misc::to_value( tokenizer[1], value1 );
						misc::to_value( tokenizer[2], value2 );
						misc::to_value( tokenizer[3], value3 );
						if( mPolys.size() > 0 )
						{
						  mPolys.back().polyLine.AddPoint(TPoint(value1, value2, value3));
						}
				
					}
					else if( tokenizer[0] == _T("PT") )
					{
						float value1;
						float value2;
						float value3;
						misc::to_value( tokenizer[1], value1 );
						misc::to_value( tokenizer[2], value2 );
						misc::to_value( tokenizer[3], value3 );
						mPoints.push_back( ciPnt() );
						mPoints.back().clr = currClr;
						mPoints.back().pnt.x( value1 );
						mPoints.back().pnt.y( value2 );
						mPoints.back().pnt.z( value3 );
					}
				}
			}
		}

		//!Get the list of polylines with corresponding colors
        polyArray GetPolyList()
		{
			return mPolys;
		}
		
		//!Get begin of the points array
		/*!Get iterator pointing to the begin of the points array*/
		pntIterator	GetPointsBegin()
		{
			return mPoints.begin();
		}

		constPntIterator GetPointsBegin() const	
		{
			return mPoints.begin();
		}

		//!Get end of the point array
		/*!Returns iterator pointing to the end of the points array*/
		pntIterator	GetPointsEnd()
		{
		    return mPoints.end();
		}

		constPntIterator GetPointsEnd() const
		{
		    return mPoints.end();
		}

		//!Get begin of the poly array
		/*!Get iterator pointing to the begin of the poly array*/
		polyIterator	GetPolyBegin()
		{
		    return mPolys.begin();
		}

		constPolyIterator GetPolyBegin() const
		{
		    return mPolys.begin();
		}


		//!Get end of the poly array
		/*!Returns iterator pointing to the end of the poly array*/
		polyIterator GetPolyEnd()
		{
		    return mPolys.end();
		}

		constPolyIterator GetPolyEnd() const
		{
		    return mPolys.end();
		}


	protected:
	private:
		// avoid warning c4512
		mwEASCIIParser& operator=(const mwEASCIIParser&);
		
		pntArray			mPoints;
		polyArray			mPolys;
		misc::mwIStream&	mInput;
	};
};
#endif	//	MW_MWEASCIIPARSER_HPP_
