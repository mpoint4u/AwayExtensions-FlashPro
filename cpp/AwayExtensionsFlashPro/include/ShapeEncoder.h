#ifndef SHAPEENCODER_H_
#define SHAPEENCODER_H_

#include "awd.h"
#include "Utils.h"
#include "FontPathShape.h"
#include "shape2D.h"

class ShapeEncoder 
{
    private:
		AWDShape2D* awd_shape;
		vector<AWDBlock*> alLFills;
		vector<FontPathShape*> all_fontShapes;
        string lastString;		
		vector<SimplePoint*> points;
		vector<SimplePoint*> boundaryPoints;
		vector<vector<SimplePoint*> > allPoints;
		vector<AWDPathSegment*> allPathSegments;
		vector<AWDPathSegment*> boundary_segments;
		vector<vector<AWDPathSegment*> > all_segments;
		vector<SimplePoint*> allLines;
		vector<awd_uint32> triangles_inner;
		vector<awd_uint32> triangles_straight_edge;
		vector<awd_uint32> triangles_straight_edge_out;
		vector<awd_uint32> triangles_concave_edge;
		vector<awd_uint32> triangles_covex_edge;
		vector<int> pointlength;
		double red;
		double green;
		double blue;
		double alpha;
		double maxSize;
		
		AWD* awd;
		bool double_subdivide;
		double outline_threshold;
        FCM::PIFCMCallback m_pCallback;
		
		vector<AWD_edge_type> get_edge_styles(int thisIdx1, int thisIdx2, int thisIdx3);
		void add_outter_face(int thisIdx1, int thisIdx2, int thisIdx3);

    public:
        ShapeEncoder(FCM::PIFCMCallback* pCallback, AWD* awd);
        ~ShapeEncoder();

		void encode_subShape(bool);// ShapeEncoderEncode.cpp
		bool bounds_interesect(vector<double> bounds1, vector<double> bounds2) ;
		vector<double> mergeBounds(vector<double> bounds1, vector<double> bounds2) ;
		void add_inner_tri(int idx1, int idx2, int idx3);
		int Intersecting(float p0x,float p0y, float p1x, float p1y, float t0x, float t0y, float t1x, float t1y, float t2x,float t2y);
		
        void reset(AWDShape2D*);
        AWDShape2D* get_shape();
		void set_color(double, double, double, double);
		FCM::PIFCMCallback* get_mCallback();
		
        bool add_point(int, SimplePoint *);
        void add_hole();
        int get_hole_idx();
		bool PointInPath(double, double);
		bool PointInHole(int holeIdx, double x, double y);
		bool PointInTri(double x, double y, double x1, double y1, double x2, double y2,double x3, double y3);
        void add_path_segment(AWDPathSegment*);
        void add_new_point(SimplePoint *);
		bool remove_overlapping();
		int get_point_idx(SimplePoint *);
        AWDPathSegment* get_path_segment(SimplePoint * a, SimplePoint* b);
		void get_edge_style(AWDPathSegment* , SimplePoint* c);
		vector<double> subDivideCurve(double startx, double starty, double cx, double cy, double endx, double endy);
        
		bool tris_intersecting(ShapePoint *, ShapePoint *, ShapePoint *, ShapePoint *, ShapePoint *, ShapePoint *);
        bool point_in_tr(ShapePoint *, ShapePoint *, ShapePoint *, ShapePoint *);
        bool line_intersect(ShapePoint *, ShapePoint *, ShapePoint *, ShapePoint *);
        ShapePoint * line_intersection_point(ShapePoint *, ShapePoint *, ShapePoint *, ShapePoint *);
		bool resolve_segment_intersection(AWDPathIntersection* thisIntersection);
		bool test_bounding_box_lines(ShapePoint * a1, ShapePoint* a2, ShapePoint * b1, ShapePoint * b2);
		bool test_bounding_box(ShapePoint * a1, ShapePoint* a2, ShapePoint * a3, ShapePoint * b1, ShapePoint * b2, ShapePoint * b3);
		double Sign(ShapePoint * p1, ShapePoint * p2, ShapePoint * p3);
		
		double maximum(double x, double y, double z);
		double minimum(double x, double y, double z);

        void add_straight_edge(SimplePoint *, SimplePoint*);
        void add_curve(SimplePoint *, SimplePoint*, SimplePoint*);
        string& get_edge_string(SimplePoint *, SimplePoint*);
		double side_of_line(ShapePoint *, ShapePoint *, ShapePoint *);
		double edge_length(SimplePoint *, SimplePoint*);
		SimplePoint * calc_fill_point(SimplePoint *, SimplePoint*, SimplePoint*, double);

		
};
#endif