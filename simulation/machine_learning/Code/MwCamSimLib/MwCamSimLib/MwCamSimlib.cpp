#include "pch.h"
#include "MwCamSimLib.h"

static std::unique_ptr<mwMachSimVerifier> verifier;
static std::ifstream tool_path_file;
static std::ofstream feature_file;
static bool isvisual = false;
static float precision_mw;
static GLFWwindow* sim_window;
static VerifierUtil::SetToolsParameters m_tools;
// record the number of tools 
static int num_tool = 0;

//@brief: init a object of moduleworks machine simulation 
//@param: void
//@ret: void 
void init()
{
	verifier = mwMachSimVerifier::Create();
	std::wcout << L"[\033[1;32mOK\033[0m]  MWCam startup" << std::endl;
}

//@brief: load the tool path file 
//@param: inputfile: file path of tool path 
//@ret: void 
void load_file(char* inputfile)
{
	
	feature_file.open(inputfile);
	// check if file exists under the input path 
	if (feature_file.good())
	{
		std::cout << "[\033[1;32mOK\033[0m]  Create a feature file" << std::endl;
		feature_file << "Timestamp;" << "XCurrPos;" << "YCurrPos;" << "ZCurrPos;" << "S1Actrev;" << "Actfeed;" << "ToolID;" << "Area;" << "Depth;" << "Width;"
			<< "Removal_Volume;" << "Angles" << std::endl;
	}
	else
	{
		std::cout << "[\033[1;31mERROR\033[0m]  Invalid feature file, please check the feature file path" << std::endl;
	}
}

//@brief: set simulation precision 
//@param: precision: desired precision (mm)
//@ret: void 
void set_precision(float precision)
{
	precision_mw = precision;
	verifier->ForceDataModel(mwMachSimVerifier::MWV_FM_DEXELBLOCK);
	verifier->SetPrecision(precision);
	std::cout << "[\033[1;32mOK\033[0m]  Set work piece precision: " << precision << std::endl;
}

//@brief: creat a raw workpiece model in simulation environment  
//@param: init_x: x coordinate of lower corner of workpiece
//@param: init_y: y coordinate of lower corner of workpiece
//@param: init_z: z coordinate of lower corner of workpiece
//@param: end_x: x coordinate of upper corner of workpiece
//@param: end_y: y coordinate of upper corner of workpiece
//@param: end_z: z coordinate of upper corner of workpiece
//@ret: void 
void set_stock(float init_x, float init_y, float init_z, float end_x, float end_y, float end_z)
{
	float3d lowercorner(init_x, init_y, init_z); 
	float3d uppercorner(end_x, end_y, end_z); 
	std::cout << "[  ]  Configuring the work stock cube(it may takes serveral minutes)...\r";
	verifier->SetStockCube(lowercorner, uppercorner);
	std::cout << "[\033[1;32mOK\033[0m]  Configuring the work stock cube(it may takes serveral minutes)    " << std::endl;
	
}

//@brief: set end milling tool 
//@param: fDiameter: cutter diameter (mm) 
//@param: fDiameterTop: shaft diameter (mm)
//@param: fShoulderHeight: shaft length (mm)
//@param: fHeight: cutter length (mm)
//@param: tool_id: tool id in simulation
//@ret: void 
void set_tool(float fDiameter, float fDiameterTop, float fShoulderHeight, float fHeight, int tool_id)
{

	// set tool holder 
	cadcam::mwHolderDefinition<double> holderDefinition =
		cadcam::ToolHelper::CreateHolderAsCylinder(
			fDiameterTop * 2.0, fDiameterTop * 4.0, measures::mwUnitsFactory::METRIC);

	// set tool arbor
	cadcam::mwArborDefinition<double> arborDefinition =
		cadcam::ToolHelper::CreateArborAsCylinder(
			fDiameterTop, fDiameterTop, measures::mwUnitsFactory::METRIC
		);

	// create end milling tool 
	cadcam::mwToolPtr pMill = new cadcam::mwEndMill(
		fDiameter,
		holderDefinition,
		fShoulderHeight,
		fHeight,
		arborDefinition,
		measures::mwUnitsFactory::METRIC
	);

	// if current tool is the first tool, create a toolset and insert this tool 
	if (tool_id == 0)
	{
		m_tools.push_back(VerifierUtil::SetToolParameters(pMill, tool_id));
		verifier->SetTools(m_tools);
		++num_tool;
		
	}
	else
	{
		verifier->AddTool(pMill, tool_id);
		++num_tool;
		
	}
	
	std::cout << "[\033[1;32mOK\033[0m]  Define a Flat Tool with ID: " << tool_id << " Diameter: \033[1;35m"<< fDiameter << "\033[0m Height: \033[1;35m" << fHeight << "\033[0m"  << std::endl;

}

//@brief: set chamfer milling tool 
//@param: cDiameter: cutter diameter (mm) 
//@param: cDiameterOut: cutter outside diameter (mm) 
//@param: cDiameterTop: shaft diameter (mm)
//@param: cShoulderHeight: shaft length (mm)
//@param: cHeight: cutter length (mm)
//@param: taperangle: taper angle (degree)
//@param: tool_id: tool id in simulation 
//@ret: void 
void set_tool_chamfer(float cDiameter, float cDiameterOut, float cDiameterTop, float cShoulderHeight, float cHeight, float taperangle, int tool_id)
{
	// set tool holder 
	cadcam::mwHolderDefinition<double> holderDefinition =
		cadcam::ToolHelper::CreateHolderAsCylinder(
			cDiameterTop * 2.0, cDiameterTop * 4.0, measures::mwUnitsFactory::METRIC);

	// set tool arbor
	cadcam::mwArborDefinition<double> arborDefinition =
		cadcam::ToolHelper::CreateArborAsCylinder(
			cDiameterTop, cDiameterTop, measures::mwUnitsFactory::METRIC
		);
	cadcam::mwTypedRevolvedTool::cornerRadiusType cornerDefiniton = cadcam::mwTypedRevolvedTool::cornerRadiusType::none;
	// create end milling tool 
	cadcam::mwToolPtr pMill = new cadcam::mwChamferMill(
		cDiameter,
		holderDefinition,
		cShoulderHeight,
		cHeight,
		arborDefinition,
		0.1, 
		taperangle,
		cDiameterOut,
		cornerDefiniton,
		measures::mwUnitsFactory::METRIC
	);

	// if current tool is the first tool, create a toolset and insert this tool
	if (tool_id == 0)
	{
		m_tools.push_back(VerifierUtil::SetToolParameters(pMill, tool_id));
		verifier->SetTools(m_tools);
		++num_tool;

	}
	else
	{
		verifier->AddTool(pMill, tool_id);
		++num_tool;

	}

	std::cout << "[\033[1;32mOK\033[0m]  Define Chamfer Tool with ID: " << tool_id << "\033[0m Diameter: \033[1;35m" << cDiameter << "\033[0m Height: \033[1;35m" << cHeight << "\033[0m Taperangle: \033[1;35m" << taperangle<< "\033[0m" << std::endl;
}

//@brief: set using tool in the current simulation step 
//@param: tool_id_current: tool id indicates the tool that will be used in current step 
//@ret: void
void set_current_tool(int tool_id_current)
{
	size_t tool_idx = (size_t)tool_id_current;

	if (tool_idx > num_tool - 1)
	{
		std::cout << "\033[1;31mERROR: Tool index out of the range of current tool set\033[0m" << std::endl;
		return;
	}

	verifier->SetCurrentCutTool(tool_idx);

}

//@brief: set if show the animation 
//@param: visual_mode: flag, if show the animation  
//@ret: void
void set_visualization(bool visual_mode)
{
	isvisual = visual_mode;
}

//@brief: configurate the simualtion
//@param: void  
//@ret: void
void config()
{
	// enable engagement analysis 
	verifier->EnableEngagementTracking(true);
	// enable material removal simulation 
	verifier->EnableVolumeTracking(true);
	// use precise algorithm 
	VerifierUtil::EngagementOptions engagementOptions;
	engagementOptions.SetAlgorithm(VerifierUtil::EngagementOptions::ContourBased);
	verifier->SetEngagementOptions(engagementOptions);
	
	
	// if animation is turned on, configurate the opengl before showing animation 
	if (isvisual)
	{
		opengl_config();
	}

	std::wcout << L"[\033[1;32mOK\033[0m]  Configuring MW CAM simulation   " << std::endl;
}

//@brief: execute a single-step cutting simulation 
//@param: x_start: TCP start x position  
//@param: y_start: TCP start y position  
//@param: z_start: TCP start z position  
//@param: x_end: TCP target x position
//@param: y_end: TCP target y position
//@param: z_end: TCP target z position 
//@param: s1actrev: target spindle motor velocity
//@param: actfeed: target spindle feed rate
//@param: timestamp: timestamp for current movement 
//@param: toolid: id of current used tool
//@param: cut_id: simulation step index 
//@param: isCut: if execute a real cutting process in current step 
//@ret: void
void DoCut(
	float x_start, 
	float y_start, 
	float z_start, 
	float x_end, 
	float y_end, 
	float z_end,
	float s1actrev,
	float actfeed,
	long long timestamp,
	int toolid,
	int cut_id, 
	bool isCut,
	bool isTrace,
	char* stlPath
)
{
	verifier->SetMoveID(cut_id);
	float3d p_start(x_start, y_start, z_start);
	float3d orientation3x_start(0, 0, 1);
	float3d p_target(x_end, y_end, z_end);
	float3d orientation3x_target(0, 0, 1);
	verifier->SetRapidMode(!isCut);
	orientation3x_start.Normalize();
	orientation3x_target.Normalize();
	
	if (isTrace)
	{
		feature_file << timestamp << ";" << p_target.x() << ";" << p_target.y() << ";" << p_target.z() << ";" << s1actrev<< ";" << actfeed << ";" << toolid << ";";
	}
	

	mwMachSimVerifier::Frame from(
		p_start,
		MATH::OrientationToQuaternion<float>(orientation3x_start, 0)
	);
	mwMachSimVerifier::Frame to(
		p_target,
		MATH::OrientationToQuaternion<float>(orientation3x_target, 0)
	);
	verifier->Cut(from, to);

	if (cut_id % 100 == 0) {
		misc::mwstring currentId = std::to_string(cut_id);
		misc::mwstring path = stlPath;
		misc::mwstring resultName = path + "\\" + currentId + ".stl";
		verifier->GetMesh(&resultName);
		std::cout << "*  The generated mesh file is saved in: " << path << std::endl;
	}
}

//@brief: calculate engagement analysis and removal volume. record the result 
//@param: void  
//@ret: void
void engagement_analysis()
{
	std::vector<mwMachSimVerifier::EngagementProfilePtr> toolProfiles;
	std::vector<mwMachSimVerifier::EngagementAngleListList> angles;
	std::vector<float> areas, depths, widths, removedVolumesPerCut;

	verifier->GetRemovedVolumes(removedVolumesPerCut);
	verifier->GetEngagementAngles(toolProfiles, angles);
	verifier->GetEngagementAreas(areas);
	verifier->GetEngagementDepths(depths);
	verifier->GetEngagementWidths(widths);
	// we call the analysis after every single step. Therefore only record the first value in the return result
	feature_file << areas[0] << ";" << depths[0] << ";" << widths[0] << ";" << removedVolumesPerCut[0] << ";";

	typedef std::vector<mwMachSimVerifier::EngagementAngleListList>::iterator Iter;
	typedef mwMachSimVerifier::EngagementAngleListList::iterator Iter1;
	typedef mwMachSimVerifier::EngagementAngleList::iterator Iter2;

	if (angles.size() > 1)
		std::cout << "\033[1;33mWARNING: More than one cut are saved in engagement angles\033[0m" << std::endl;
	// engagement vector is a 3d array. iterate all elements and record every angle in the storage file
	for (Iter i = angles.begin(); i != angles.end(); i++)
	{
		feature_file << "[";
		for (Iter1 j = i->begin(); j != i->end(); j++)
		{
			if (!j->empty())
				feature_file << "[";
			for (Iter2 k = j->begin(); k != j->end(); k++)
			{
				const float angle_left = k->first * (float)mathdef::MW_R2D;
				const float angle_right = k->second * (float)mathdef::MW_R2D;

				feature_file << angle_right - angle_left;
				if (k + 1 != j->end())
					feature_file << ",";
			}
			if (!j->empty())
				feature_file << "]";
		}
		feature_file << "]";
	}
	feature_file << std::endl;
}

//@brief: show and update the animation  
//@param: isshow_in_this_turn: if update the frame in current step 
//@param: show_range: camera view range (mm) 
//@ret: void
void visualization(bool isshow_in_this_turn, int show_range)
{
	if (!glfwWindowShouldClose(sim_window) && isshow_in_this_turn)
	{
		// get framebuffer size
		int win_width, win_height;
		float ratio;
		glfwGetFramebufferSize(sim_window, &win_width, &win_height);
		ratio = win_width / (float)win_height;

		// set view point in window
		glViewport(0, 0, win_width, win_height);

		//clear and set color buffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// set matrix mode 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ToDo: find better view perspective 
		glOrtho(-show_range * ratio, show_range * ratio, -show_range, show_range, -show_range, show_range);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(-1, -1, 1, 0, 0, 0, 0, 0, 1);
		verifier->Draw();
		glfwSwapBuffers(sim_window);
		

	}
	else if (glfwWindowShouldClose(sim_window)) {
		glfwDestroyWindow(sim_window);
		glfwTerminate();
	}
	glfwPollEvents();
}

//@brief: save the generated mesh model 
//@param: void  
//@ret: void
void export_mesh(char* stlfile)
{
	std::wcout << L"[  ]  Cam simulation finish, save result mesh as stl file...\r";
	misc::mwstring fileName(stlfile);
	verifier->GetMesh(&fileName);
	std::wcout << L"[\033[1;32mOK\033[0m]  Cam simulation finish, save result mesh as stl file   " << std::endl;
	std::cout << "*  The generated mesh file is saved in: " << stlfile << std::endl;
}


//@brief: configurate the animation scene  
//@param: void  
//@ret: void
void opengl_config()
{
	float3d tool_color_cut(255, 106, 106);
	float3d tool_color_uncut(255, 193, 37);
	float3d tool_color_abor(128, 128, 128);
	float3d tool_color_holder(0, 0, 255);
	// set visualization mode:
	verifier->SetDrawMode(mwMachSimVerifier::WDM_TOOL_PATH_SEGMENT_LENGTH);
	verifier->SetMeshColor(0.5f, 0.5f, 0.5f);
	verifier->SetToolVisibility(true);
	verifier->SetToolColor(0, 0, 0, 0.5); 
	verifier->SetToolColor(tool_color_cut, tool_color_uncut, tool_color_abor, tool_color_holder, 0.2);

	//  check if the intialization is successful 
	if (!glfwInit())
	{
		std::cout << "[\033[1;31mERROR\033[0m]  Intialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// creata a window in OpenGL context 
	sim_window = glfwCreateWindow(WIDTH, WIDTH, "Cutting Simulation", NULL, NULL);

	// check if window is created successfully 
	if (!sim_window)
	{
		std::cout << "[\033[1;31mERROR\033[0m]  Window Initialization failed, please check if OpenGL or GLFW works correctly" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// create an OpenGL context
	glfwMakeContextCurrent(sim_window);

	// to avoid screen tearing, set swap interval to 1
	glfwSwapInterval(1);

	// set lighting ambient 
	static const GLfloat shad_ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, shad_ambient);


	// set which material tracking the current color
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
}

//@brief: close the animation window
//@param: void  
//@ret: void
void window_close()
{
	glfwDestroyWindow(sim_window);
	glfwTerminate();
}
