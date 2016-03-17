#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <vector>
#include <QPointF>

struct Edge
{
	int u_, v_;
	double min_cost_;
	int type_;  // 得到最小cost时的情况，分三种，0：u，1：v，2：（u+v)/2
	Edge(){}
	Edge( int u, int v ): u_( u ), v_( v ){}
	Edge( int u, int v, double min_cost, int type )
		: u_( u ), v_( v ), min_cost_( min_cost ), type_( type )
	{}
	bool operator < ( const Edge &e ) const
	{
		return min_cost_ > e.min_cost_;
	}
};

struct Point3D
{
	double x_, y_, z_;
	Point3D(): x_( 0 ), y_( 0 ), z_( 0 ){}
	Point3D( double x, double y, double z ): x_( x ), y_( y ), z_( z ){}
	void ResetValue( const Point3D &p )
	{
		x_ = p.x_;
		y_ = p.y_;
		z_ = p.z_;
	}
	Point3D( double p[] )
	{
		x_ = p[ 0 ];
		y_ = p[ 1 ];
		z_ = p[ 2 ];
	}
	double &rx()
	{
		return x_;
	}
	double &ry()
	{
		return y_;
	}
	double &rz()
	{
		return z_;
	}
	Point3D GetMiddlePoint3D( const Point3D &p1, const Point3D &p2 )
	{
		Point3D middle_p = Point3D( ( p1.x_ + p2.x_ ) / 2, 
			                        ( p1.y_ + p2.y_ ) / 2,
			                        ( p1.z_ + p2.z_ ) / 2 );
		return middle_p;
	}
	double GetDistance( const Point3D &p )
	{
		return ( x_ - p.x_ ) * ( x_ - p.x_ ) + ( y_ - p.y_ ) * ( y_ - p.y_ ) + 
			   ( z_ - p.z_ ) * ( z_ - p.z_ );

	}
	bool operator < ( const Point3D &p ) const 
	{
		if( x_ != p.x_ )
		{
			return x_ < p.x_;
		}
		else
		{
			if( y_ != p.y_ )
			{
				return y_ < p.y_;
			}
			else
			{
				return z_ < p.z_;
			}
		}
	}
};

class Plane
{
public:
	static void GetFourParametersFromThreePoints( Point3D &p1, Point3D &p2, Point3D &p3, double paras[] );
	static void GetFourParametersFromVectorPoints( std::vector< Point3D > &three_points, double paras[] );
	static double ComputeCost( std::vector< double > &v, std::vector< double > &q );
	static double ComputeCost( Point3D &v, std::vector< double > &q );
};

#endif