#include "ShapeEncoder.h"

#ifdef _DEBUG
	#include <stdlib.h>
	#include <crtdbg.h>
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG
ShapeEncoder::ShapeEncoder(FCM::PIFCMCallback* pCallback, AWD* awd)
{

    m_pCallback=*pCallback;
	string name("nameless");
	this->awd=awd;
	this->red=0.5;
	this->green=0.5;
	this->blue=0.5;
	this->alpha=1.0;
	vector<AWDPathSegment *> boundary_segs;
	all_segments.push_back(boundary_segs);
}

ShapeEncoder::~ShapeEncoder()
{	
		std::vector<AWDBlock*>().swap(alLFills);
		std::vector<FontPathShape*>().swap(all_fontShapes);
		//std::vector<SimplePoint*>().swap(points);
	//	std::vector<SimplePoint*>().swap(boundaryPoints);
		//std::vector<vector<SimplePoint*> >().swap(allPoints);
		std::vector<vector<AWDPathSegment*> >().swap(all_segments);
		std::vector<AWDPathSegment*>().swap(allPathSegments);
		std::vector<AWDPathSegment*>().swap(boundary_segments);
		std::vector<SimplePoint*>().swap(allLines);
		std::vector<awd_uint32>().swap(triangles_inner);
		std::vector<awd_uint32>().swap(triangles_straight_edge);
		std::vector<awd_uint32>().swap(triangles_straight_edge_out);
		std::vector<awd_uint32>().swap(triangles_concave_edge);
		std::vector<awd_uint32>().swap(triangles_covex_edge);
}
void
ShapeEncoder::reset(AWDShape2D* newShape){
	this->awd_shape=newShape;
	all_segments.clear();
	vector<AWDPathSegment *> boundary_segs;
	all_segments.push_back(boundary_segs);
}
AWDShape2D* 
ShapeEncoder::get_shape(){
	return this->awd_shape;
}

void
ShapeEncoder::set_color(double red, double green, double blue, double alpha)
{
	this->red=red;
	this->green=green;
	this->blue=blue;
	this->alpha=alpha;
}

void
ShapeEncoder::add_path_segment(AWDPathSegment* newPath)

{
	if((newPath->get_startPoint()->x==newPath->get_endPoint()->x)&&(newPath->get_startPoint()->y==newPath->get_endPoint()->y)){
		if(newPath->get_edgeType()==CURVED_EDGE){
			//AwayJS::Utils::Trace(m_pCallback, "Cannot create curved -Segment, if both ancor-points share same point %f %f\n", newPath->get_endPoint()->x, newPath->get_endPoint()->y);
			//AwayJS::Utils::Trace(m_pCallback, "control point of ignored Path Segment is at %f %f\n", newPath->get_controlPoint()->x, newPath->get_controlPoint()->y);
		}
		else{
			//AwayJS::Utils::Trace(m_pCallback, "Cannot create line-Segment, if both points share same point %f %f\n", newPath->get_endPoint()->x, newPath->get_endPoint()->y);
		}
		return;
	}
	all_segments.back().push_back(newPath);
}

void
ShapeEncoder::add_hole()
{
	vector<AWDPathSegment *> newHole;
	all_segments.push_back(newHole);	
}
int
ShapeEncoder::get_hole_idx()
{
	return this->all_segments.size();
}
/*
bool
ShapeEncoder::add_point(int hole_idx, SimplePoint * point)
{
	
    //AwayJS::Utils::Trace(m_pCallback, "AddPoint: %f, %f\n", point->x, point->y);
	for (SimplePoint * p : points)
	{
		if((p->x==point->x)&&(p->y==point->y)){			
			delete point;
			//AwayJS::Utils::Trace(m_pCallback, "Point already exists in list!: %f, %f\n", p->x, p->y);
			return false;
		}
	}	
	points.push_back(point);
	allPoints[hole_idx].push_back(point);
	return true;
}
*/