// powerflow/pole.h
// Copyright (C) 2018, Stanford University

#ifndef _POLE_H
#define _POLE_H

#include "node.h"
#include "pole_configuration.h"

class pole : public node
{
public:
	typedef struct s_wiredata {
		double height;
		double diameter;
		double heading;
		double tension;
		double span;
		struct s_wiredata *next;
	} WIREDATA;
	inline void add_wire(double height, double diameter, double heading, double tension, double span) {
		WIREDATA *item = new WIREDATA;
		item->height = height;
		item->diameter = diameter;
		item->heading = heading;
		item->tension = tension;
		item->span = span;
		if ( wire_data != NULL )
			wire_data->next = item;
		wire_data = item;
	};
	inline WIREDATA *get_next_wire(WIREDATA *wire) { return wire->next;};
	inline WIREDATA *get_first_wire(void) { return wire_data;};
public:
	static CLASS *oclass;
	static CLASS *pclass;
public:
	enum {PT_WOOD=0, PT_STEEL=1, PT_CONCRETE=2};
	enumeration pole_type;
	enum {PS_OK=0, PS_FAILED=1,};
	enumeration pole_status;
	double tilt_angle;
	double tilt_direction;
	object weather;
	object configuration;
	double equipment_area;		// (see Section E)
	double equipment_height;	// (see Section E)
	double fragility_metric;
	double wind_pressure;		// (see Section D)
	double *wind_speed;
private:
	double ice_thickness;
	double wind_loading;
	double resisting_moment; 	// (see Section B)
	double pole_moment;		// (see Section D)
	double equipment_moment;	// (see Section E)
	double wire_load;		// (see Section F)
	double wire_moment;		// (see Section F)
	double wire_tension;	// (see Section G)
	object cable_configuration;
	bool is_deadend;
private:
	pole_configuration *config;
	double last_wind_speed;
//	double *wind_speed;
	double *wind_direction;
	double *wind_gust;
	WIREDATA *wire_data;
	TIMESTAMP down_time;
public:
	pole(MODULE *);
	int isa(char *);
	int create(void);
	int init(OBJECT *);
	TIMESTAMP presync(TIMESTAMP);
	TIMESTAMP sync(TIMESTAMP);
	TIMESTAMP postsync(TIMESTAMP);
};

#endif // _POLE_H

