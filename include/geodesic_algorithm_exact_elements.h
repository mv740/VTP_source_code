#ifndef GEODESIC_ALGORITHM_EXACT_ELEMENTS
#define GEODESIC_ALGORITHM_EXACT_ELEMENTS

#include "stdafx.h"
#include "geodesic_memory.h"
#include "geodesic_mesh_elements.h"

namespace geodesic {

	class Interval;
	class IntervalList;
	typedef Interval* interval_pointer;
	typedef IntervalList* list_pointer;

	struct Triangle // Components of a face to be propagated
	{
		face_pointer face; // Current Face

		edge_pointer bottom_edge, // Edges
			left_edge,
			right_edge;

		vertex_pointer top_vertex, // Vertices 
			left_vertex,
			right_vertex;

		double top_alpha,
			left_alpha,
			right_alpha; // Angles

		list_pointer left_list,
			right_list; // Lists
	};

	class Interval						//interval of the edge
	{
	public:

		Interval() {};
		~Interval() {};

		double& start() { return m_start; };
		double& stop() { return m_stop; };
		double& d() { return m_d; };
		double& pseudo_x() { return m_pseudo_x; };
		double& pseudo_y() { return m_pseudo_y; };

		double& sp() { return m_sp; };

		double& shortest_distance() { return m_shortest_distance; }

		interval_pointer& next() { return m_next; };
		interval_pointer& previous() { return m_previous; };

	private:
		double m_start;						//initial point of the interval on the edge
		double m_stop;
		double m_d;							//distance from the source to the pseudo-source
		double m_pseudo_x;					//coordinates of the pseudo-source in the local coordinate system
		double m_pseudo_y;					//y-coordinate should be always negative

		double m_sp;                        //separating point

		double m_shortest_distance;         //shortest distance from the interval to top_vertex, for numerical precision issue

		interval_pointer m_next;			//pointer to the next interval in the list	
		interval_pointer m_previous;        //pointer to the previous interval in the list
	};

	class IntervalList						//list of the of intervals of the given edge
	{
	public:
		IntervalList() {  m_start = nullptr; m_edge = nullptr; m_sp = -1; m_begin = m_end = nullptr; }
		~IntervalList() {};

		void clear() { m_begin = m_end = nullptr; }
		void initialize(edge_pointer e) { m_edge = e; }

		vertex_pointer& start_vertex() { return m_start; }
		edge_pointer& edge() { return m_edge; }

		double& sp() { return m_sp; };

		double& pseudo_x() { return m_pseudo_x; };
		double& pseudo_y() { return m_pseudo_y; };

		// List operation
		interval_pointer& begin() { return m_begin; }

		interval_pointer& end() { return m_end; }

		bool empty() { return m_begin == nullptr; }

		void push_back(interval_pointer & w)
		{
			if (!m_end)
			{
				w->previous() = nullptr;
				w->next() = nullptr;
				m_begin = m_end = w;
			}
			else
			{
				w->next() = nullptr;
				w->previous() = m_end;
				m_end->next() = w;
				m_end = w;
			}
		}

		void erase(interval_pointer & w)
		{
			if ((w == m_begin) && (w == m_end))
			{
				m_begin = m_end = nullptr;
			}
			else if (w == m_begin)
			{
				m_begin = m_begin->next();
				m_begin->previous() = nullptr;
			}
			else if (w == m_end)
			{
				m_end = m_end->previous();
				m_end->next() = nullptr;
			}
			else
			{
				w->previous()->next() = w->next();
				w->next()->previous() = w->previous();
			}
		}

	private:

		edge_pointer     m_edge;		    //edge that owns this list
		vertex_pointer   m_start;           //vertex from which the interval list starts

		interval_pointer m_begin;
		interval_pointer m_end;

		double m_pseudo_x;
		double m_pseudo_y;

		double m_sp;                        //separating point
	};

}		//geodesic

#endif
