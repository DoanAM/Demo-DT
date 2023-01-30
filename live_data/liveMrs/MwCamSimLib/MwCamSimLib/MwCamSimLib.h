#pragma once
#ifdef MWCAMSIM_EXPORTS 
#define MWCAMSIM_API __declspec(dllexport)
#else
#define MWCAMSIM_API __declspec(dllimport)
#endif 
// dependencies for cutting simulation 
#include <iostream>
#include <fstream>
#include <algorithm>

#include "mwMachSimVerifier.hpp"
#include "mwvEngagementHelpers.hpp"
#include "mwEndMill.hpp"
#include "mwChamferMill.hpp"
#include "mwTypedRevolvedTool.hpp"
#include "mwSTLTranslator.hpp"

#include "mwTPoint2d.hpp"
#include "mwTPoint3d.hpp"

// dependencies for visualzation: 
#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "gl/glut.h"

// pop-up window size 
#define WIDTH 640



typedef mwMachSimVerifier::float3d float3d;
typedef mwMachSimVerifier::float2d float2d;

extern "C" MWCAMSIM_API void init();
extern "C" MWCAMSIM_API void load_file(char* inputfile);
extern "C" MWCAMSIM_API void set_precision(float precision);
extern "C" MWCAMSIM_API void set_stock(char* inputStock);
extern "C" MWCAMSIM_API void new_stock(float init_x, float init_y, float init_z, float end_x, float end_y, float end_z, char* location);
extern "C" MWCAMSIM_API void set_tool(float fDiameter, float fDiameterTop, float fShoulderHeight, float fHeight, int tool_id);
extern "C" MWCAMSIM_API void set_tool_chamfer(float cDiameter, float cDiameterOut, float cDiameterTop, float cShoulderHeight, float cHeight, float taperangle, int tool_id);
extern "C" MWCAMSIM_API void set_current_tool(int tool_id);
extern "C" MWCAMSIM_API void set_visualization(bool visual_mode);
extern "C" MWCAMSIM_API void export_mesh(char* stlfile);
extern "C" MWCAMSIM_API void DoCut(
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
	char* stlPath);

extern "C" MWCAMSIM_API void cut(float x_start,
	float y_start,
	float z_start,
	float x_end,
	float y_end,
	float z_end);
extern "C" MWCAMSIM_API void createTool();

extern "C" MWCAMSIM_API void engagement_analysis();
extern "C" MWCAMSIM_API void visualization(bool isshow_in_this_turn, int show_range); 
extern "C" MWCAMSIM_API void config();
extern "C" MWCAMSIM_API void window_close();

void opengl_config();

