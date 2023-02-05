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
#include "mwTypedRevolvedTool.hpp"

// including tool libs:
#include "mwEndMill.hpp"
#include "mwSphereMill.hpp"
#include "mwBarrelMill.hpp"
#include "mwFaceMill.hpp"
#include "mwChamferMill.hpp"
#include "mwDrill.hpp"

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
extern "C" MWCAMSIM_API void load_file(char *inputfile);
extern "C" MWCAMSIM_API void set_precision(float precision);
extern "C" MWCAMSIM_API void set_stock(float init_x, float init_y, float init_z, float end_x, float end_y, float end_z);
// tool setting:
extern "C" MWCAMSIM_API void set_tool_endmill(int tool_id, float diameter, float flute_length, float shoulder_length);
extern "C" MWCAMSIM_API void set_tool_facemill(int tool_id, float diameter, float flute_length, float shoulder_length, float corner_radius, float outside_diameter, float taper_angle);
extern "C" MWCAMSIM_API void set_tool_chamfer(int tool_id, float diameter, float flute_length, float shoulder_length, float corner_radius, float taper_angle, float outside_diameter);
extern "C" MWCAMSIM_API void set_tool_drillmill(int tool_id, float diameter, float flute_length, float shoulder_length, float tip_angle);
extern "C" MWCAMSIM_API void set_tool_barrelmill(int tool_id, float upper_diameter, float max_diameter, float flute_length, float shoulder_length, float corner_radius, float profile_radius);
extern "C" MWCAMSIM_API void set_tool_ballmill(int tool_id, float diameter, float flute_length, float shoulder_length);
extern "C" MWCAMSIM_API void set_current_tool(int tool_id);
extern "C" MWCAMSIM_API void set_visualization(bool visual_mode);
extern "C" MWCAMSIM_API void export_mesh(char *stlfile);
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
	char *stlPath);
extern "C" MWCAMSIM_API void engagement_analysis();
extern "C" MWCAMSIM_API void visualization(bool isshow_in_this_turn, int show_range);
extern "C" MWCAMSIM_API void config();
extern "C" MWCAMSIM_API void window_close();

void opengl_config();
