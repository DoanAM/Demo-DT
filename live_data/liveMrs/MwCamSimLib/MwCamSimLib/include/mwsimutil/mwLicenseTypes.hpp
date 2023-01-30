// (C) 2015-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWLICENSETYPES_HPP_
#define MW_MWLICENSETYPES_HPP_
namespace mwLicenseAPI
{
	//////////////////////////////////////////////////////////////////////////
	// !! Important note:
	//    Each time you are adding a new license type to enum LicenseType, 
	//    please increase NUMBER_OF_LICENSES !!
	//////////////////////////////////////////////////////////////////////////	
	#define NUMBER_OF_LICENSES	 129
	//////////////////////////////////////////////////////////////////////////
	// !! Important note:
	//    Each time you are changing the serialization /deserialization 
	//	  of the  encrypted string  
	//    please increase LICENSE_FILE_VERSION !!
	//////////////////////////////////////////////////////////////////////////
	#define LICENSE_FILE_VERSION 0xB
	//////////////////////////////////////////////////////////////////////////
	// !! Important note:
	//    Each time you are changing the licensing API 
	//	  of the  encrypted string  
	//    please increase LICENSE_FILE_VERSION !!
	//////////////////////////////////////////////////////////////////////////
	#define LICENSE_API_VERSION 0x1

	enum LicenseType 
	{
		//////////////////////////////////////////////////////////////////////////
		TC_LT_SURFACE_TP_CALC_BASIC              =0   ,//SurfaceTpCalc - Basic license
		TC_LT_SURFACE_TP_CALC_ADVANCED	         =1   ,//SurfaceTpCalc - Advanced license
		TC_LT_TRIANGLE_MESH_TP_CALC_BASIC        =2   ,//TriangleMeshTpCalc - Basic license
		TC_LT_TRIANGLE_MESH_TP_CALC_ADVANCED	 =3   ,//TriangleMeshTpCalc - Advanced license
		TC_LT_DRILLING_TP_CALC_BASIC			 =4   ,//DrillingTpCalc - Basic license
		TC_LT_DRILLING_TP_CALC_ADVANCED			 =5   ,//DrillingTpCalc - Advanced license
		TC_LT_WIREFRAME_TP_CALC_BASIC			 =6   ,//WireframeTpCalc - Basic license
		TC_LT_WIREFRAME_TP_CALC_ADVANCED		 =7   ,//WireframeTpCalc - Advanced license
		TC_LT_EXISTING_TP_CALC_BASIC			 =8   ,//ExistingToolpath - Basic license
		TC_LT_EXISTING_TP_CALC_ADVANCED			 =9   ,//ExistingToolpath - Advanced license
		TC_LT_MULTIBLADE_TP_CALC_BASIC			 =10  ,//MultibladeTpCalc  - Basic license
		TC_LT_MULTIBLADE_TP_CALC_ADVANCED		 =11  ,//MultibladeTpCalc  - Advanced license
		TC_LT_SWARFING_TP_CALC_BASIC			 =12  ,//SwarfingTpCalc - Basic license
		TC_LT_SWARFING_TP_CALC_ADVANCED			 =13  ,//SwarfingTpCalc - Advanced license
		TC_LT_PORT_MACHINING_TP_CALC_BASIC		 =14  ,//PortMachiningTpCalc - Basic license
		TC_LT_PORT_MACHINING_TP_CALC_ADVANCED	 =15  ,//PortMachiningTpCalc - Advanced license
		TC_LT_MULTIAXIS_ROUGHING_TP_CALC_BASIC	 =16  ,//MultiaxisRoughingTpCalc - Basic license
		TC_LT_MULTIAXIS_ROUGHING_TP_CALC_ADVANCED=17  ,//MultiaxisRoughingTpCalc - Advanced license
		TC_LT_OPTIC_TP_CALC_BASIC				 =18  ,//Optic - Basic license
		TC_LT_OPTIC_TP_CALC_ADVANCED			 =19  ,//Optic - Advanced license
		TC_LT_2AXIS_TP_CALC_BASIC				 =20  ,//2Axis module - Basic license
		TC_LT_2AXIS_TP_CALC_ADVANCED			 =21  ,//2Axis module - Advanced license
		TC_LT_TURNING_TP_CALC_BASIC				 =22  ,//Turning - Basic license
		TC_LT_TURNING_TP_CALC_ADVANCED			 =23  ,//Turning - Advanced license
		TC_LT_LINK2TOOLPATHS_BASIC				 =24  ,//Link 2 toolpaths - Basic license
		TC_LT_LINK2TOOLPATHS_ADVANCED			 =25  ,//Link 2 toolpaths - Advanced license
		TC_LT_ROTARY_MACHINING_BASIC			 =26  ,//RotaryMachining - Basic license
		TC_LT_ROTARY_MACHINING_ADVANCED			 =27  ,//RotaryMachining - Advanced license
		TC_LT_SAW_MACHINING_BASIC				 =28  ,//Saw machining - Basic license
		TC_LT_SAW_MACHINING_ADVANCED			 =29  ,//Saw machining - Advanced license
		TC_LT_HIGH_SPEED_MACHINING_ADVANCED		 =30  ,//High Speed Machining license - doesn't need Basic/Advanced types
		TC_LT_WELDING_ADVANCED					 =31  ,//Welding advanced
		//////////////////////////////////////////////////////////////////////////
		MW_MACHSIM								 =32  ,//MachSim module
		MW_MULTIXPOST							 =33  ,//MultiXPost module			
		MW_CUTSIM								 =34  ,//MW_CUTSIM / ADDSIM
		MW_CNCSIM								 =35  ,//CNCSim
		MW_STOCKMANAGER							 =36  ,//StockManager module
		MW_CL									 =37  ,//MWCL module
		NO_LICENSE								 =38  ,//NO LICENSE	
		MW_NCEDITOR_BACKPLOT					 =39  ,//NcEditor - All licenses, for all sub-types
		//////////////////////////////////////////////////////////////////////////
		TC_LT_ORTHOTICS_ADVANCED				 =40  ,//Orthotics manufacturing - Advanced license
		TC_LT_TROCHOIDAL						 =41  ,//Trochoidal namufacturing
		//////////////////////////////////////////////////////////////////////////
		TC_LT_CIRCULAR_SAW_MACHINING             =42  ,//Circular Saw machining - Advanced license
		//////////////////////////////////////////////////////////////////////////
		//Specific NC_EDITOR licenses, for each subtype
		MW_NCEDITOR_PARSER						 =43  ,//NCEditor - Parser license
		MW_NCEDITOR_MILLING						 =44  ,//NCEditor - Milling license
		MW_NCEDITOR_TURNING					     =45  ,//NCEditor - Turning license
		MW_NCEDITOR_BASIC						 =46  ,//NCEditor - 5Axis license
		MW_NCEDITOR_VERIFICATION				 =47  ,//NCEditor - Verification license
		TC_LT_AUTOMATIC_ROUGHING                 =48  ,//Automatic 3+2 axis license
		TC_LT_TURN_MILLING 						 =49  ,//Turn Milling license
		TC_LT_DEBURRING_BASIC					 =50  ,//Deburring basic license
		TC_LT_DEBURRING_ADVANCED				 =51  ,//Deburring advanced license
		TC_LT_SPEED_SHAPE_BASIC				     =52  ,//Speed shape basic
		TC_LT_SPEED_SHAPE_ADVANCED               =53  ,//Speed shape advanced
		TC_LT_HAMMERING_BASIC					 =54  ,//Hammering basic
		TC_LT_HAMMERING_ADVANCED				 =55  ,//Hammering advanced
		TC_LT_GEODESIC_MACHINING_BASIC			 =56  ,//GeodesicMachining basic
		TC_LT_GEODESIC_MACHINING_ADVANCED		 =57  ,//GeodesicMachining advanced
		TC_LT_ABRASIVE_CUTTING_BASIC			 =58  ,//AbrasiveCutting basic
		TC_LT_ABRASIVE_CUTTING_ADVANCED			 =59  ,//AbrasiveCutting advanced
		TC_LT_CONTOURING_BASIC					 =60  ,//Contouring basic
		TC_LT_CONTOURING_ADVANCED				 =61  ,//Contouring advanced		
		TC_LT_GEODESIC_MACHINING_BASIC_PLUS_CAD  =62  ,//Geodesic MAchining plus CAD features
		TC_LT_WELDING_BASIC 					 =63  ,//Welding basic
		TC_LT_JOB_SETUP_UI						 =64  ,//Job Setup UI
		TC_LT_JOB_SETUP_CORE					 =65  ,//Job Setup Core
		TC_LT_5_AXIS_DRILLING_TP_CALC_BASIC		 =66  ,//5 Axis DrillingTpCalc - Basic license
		TC_LT_5_AXIS_DRILLING_TP_CALC_ADVANCED	 =67  ,//5 Axis DrillingTpCalc - Advanced license
		TC_LT_WIREFRAME_2_AXIS_ROUGHING			 =68  ,//2 Axis Adaptive Roughing
		TC_LT_2_AXIS_ADAPTIVE_ROUGHING_ADVANCED  =69  ,//DELETED - 2 Axis Adaptive Roughing - Advanced license
		TC_LT_3_AXIS_ADAPTIVE_ROUGHING_BASIC	 =70  ,//3 Axis Adaptive Roughing - Basic license
		TC_LT_3_AXIS_ADAPTIVE_ROUGHING_ADVANCED  =71  ,//3 Axis Adaptive Roughing - Advanced license
		TC_LT_TRIANGLE_MESH_GEODESIC_BASIC		 =72  ,//TriangleMesh Geodesic- Basic license
		TC_LT_TRIANGLE_MESH_GEODESIC_ADVANCED	 =73  ,//TriangleMesh Geodesic - Advanced license
		TC_LT_WIREFRAME_5_AXIS_PROFILING_BASIC	 =74  ,//Wireframe 5 Axis Profiling- Basic license
		TC_LT_WIREFRAME_5_AXIS_PROFILING_ADVANCED=75  ,//Wireframe 5 Axis Profiling - Advanced license
		TC_LT_WIREFRAME_EXTRUDE_BASIC			 =76  ,//Wireframe Extrude - Basic license
		TC_LT_WIREFRAME_EXTRUDE_ADVANCED		 =77  ,//Wireframe Extrude - Advanced license
		TC_LT_TRIANGLE_MESH_PROJECTION_BASIC	 =78  ,//TriangleMesh Projection- Basic license
		TC_LT_TRIANGLE_MESH_PROJECTION_ADVANCED	 =79  ,//TriangleMesh Projection - Advanced license
		TC_LT_TRIANGLE_MESH_ROTARY_BASIC		 =80  ,//TriangleMesh Rotary- Basic license
		TC_LT_TRIANGLE_MESH_ROTARY_ADVANCED		 =81  ,//TriangleMesh Rotary - Advanced license
		TC_LT_WIREFRAME_TP_CALC_INTERMEDIATE	 =82  ,//WireframeTpCalc - Intermediate license
		TC_LT_WIREFRAME_ENGRAVE					 =83  ,//Wireframe Engrave license
		TC_LT_ENGRAVE_ADVANCED					 =84  ,//DELETED - Engrave - Advanced license
		TC_LT_RASTER_TO_VECTOR_BASIC			 =85  ,//Raster to vector - Basic license
		TC_LT_RASTER_TO_VECTOR_ADVANCED			 =86  ,//Raster to vector - Advanced license
		TC_LT_MESH_TOOLKIT_BASIC				 =87  ,//Mesh toolkit - Basic license
		TC_LT_MESH_TOOLKIT_ADVANCED				 =88  ,//Mesh toolkit - Advanced license
		TC_LT_LASER_HARDENING_BASIC				 =89  ,//Laser hardening - Basic license
		TC_LT_LASER_HARDENING_ADVANCED			 =90  ,//Laser hardening - Advanced license
		TC_LT_MACHINE_AWARENESS_BASIC			 =91  ,//Machine awareness - Basic license
		TC_LT_MACHINE_AWARENESS_ADVANCED		 =92  ,//Machine awareness - Advanced license
		TC_LT_PPF_BASIC							 =93  ,//PPFramework - Basic license
		TC_LT_PPF_DEBUG_POST					 =94  ,//PPFramework - Debug Post license
		TC_LT_PPF_REMOTE_SERVER					 =95  ,//PPFramework - Remote Server license
		TC_LT_PPF_DEVELOPMENT_ADVANCED			 =96  ,//PPFramework - Development Advanced license
		TC_LT_EXISTING_TP_AUTOTILT_3_TO_5_AXIS 	 =97  ,//Existing Toolpath - Autotilt 3 to 5 axis
		MW_MACHSIM_ENGAGEMENT_DATA_ANALYSIS		 =98  ,//MachSim module - Engagement Tracking
		TC_LT_TURNING_TP_CALC_PRIME				 =99  ,//Turning - Prime license
		TC_LT_BARREL_AUTOTILT					 =100 ,//Autotilt license for barrel tool
		TC_LT_SELECTIVE_LASER_MELTING_BASIC		 = 101,//Additive machining Selective Laser Melting - Basic license
		TC_LT_SELECTIVE_LASER_MELTING_ADVANCED   = 102,//Additive machining Selective Laser Melting - Advanced license
		TC_LT_FUSED_DEPOSITION_MODELING_BASIC    = 103,//Additive machining Fused Deposition Modeling - Basic license
		TC_LT_FUSED_DEPOSITION_MODELING_ADVANCED = 104,//Additive machining Fused Deposition Modeling - Advanced license
		TC_LT_POCKET_MACHINING					 = 105,//Pocket machining license	- Advanced license
		TC_LT_RIB_MACHINING						 = 106,//RIB machining license
		TC_LT_KNIFE_GRINDING_MACHINING			 = 107,//Knife grinding machining license
		TC_LT_HOLE_MAKING_THREAD_TAPPING		 = 108,//HoleMaking ThreadTapping license
		MW_MULTIXPOST_ROBOTS					 = 109,// MultiXPost Robots license
		MW_NEXTGEN_SHOPFLOOR					 = 110,// NextGen Shopfloor license
		MW_VISUAL_TWIN							 = 111,// Visual Twin
		MW_CUTTING_SIMULATION_SMART_MEASURE		 = 112,//Cutting Simulation - Smart Measure
		MW_NEXTGEN_SHOPFLOOR_UI					 = 113,// NextGen Shopfloor UI license
		MW_COLLISION_CHECKER					 = 114,// Collision Checker license
		MW_MACHINE_BUILDER						 = 115,// Machine Builder license
		TC_LT_WIREFRAME_6_AXIS_PROFILING		 = 116,//Wireframe 6 Axis Profiling
		TC_LT_HOLE_MAKING_REAMING				 = 117,//HoleMaking Reaming license
		TC_LT_HOLE_MAKING_DRILLING				 = 118, //HoleMaking Drilling license
		TC_LT_WIREFRAME_TROCHOIDAL				 = 119,//Wireframe Trochoidal
		TC_LT_WIREFRAME_3_AXIS_PROFILING		 = 120,// Wireframe 3 Axis Profiling
		MW_PARAMETRIC_SURFACE_EDITOR			 = 121,//Parametric surface editor
		TC_LT_MULTIBLADE_BLISK					 = 122,//Multiblade Blisk license
		TC_LT_OPTICS_BASIC						 = 123,//New Optics Basic license
		TC_LT_6_AXIS_AUTOTILT					 = 124,//6 axis autotilt license
		TC_LT_TRIMLINE_FINDER					 = 125,//Trimline Finder license
		MW_CNC_SIMULATION_ADVANCED_KINEMATICS    = 126,//CNC Simulation - Advanced Kinematics license
		TC_LT_SAFE_RETRACT						 = 127,//Safe retract license
		TC_LT_HOLE_MAKING_THREAD_MILLING		 = 128,//HoleMaking ThreadMilling license

		//!! keep this last when updating this enum, it is an invalid type but we use it for validations !!
		LAST_TYPE_USED_FOR_VALIDATIONS
	};
};
#endif	//	MW_MWLICENSETYPES_HPP_
