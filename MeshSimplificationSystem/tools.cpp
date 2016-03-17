#include "tools.h"

void Plane::GetFourParametersFromThreePoints( Point3D &p1, Point3D &p2, Point3D &p3, double paras[] )
{
	double a_up = ( p3.z_ - p1.z_ ) * ( p1.y_ * p2.z_ - p2.y_ * p1.z_ ) -
		          ( p2.z_ - p1.z_ ) * ( p1.y_ * p3.z_ - p3.y_ * p1.z_ );
	double a_down = ( p1.x_ * p2.z_ - p2.x_ * p1.z_ ) * ( p1.y_ * p3.z_ - p3.y_ * p1.z_ ) - 
		            ( p1.x_ * p3.z_ - p3.x_ * p1.z_ ) * ( p1.y_ * p2.z_ - p2.y_ * p1.z_ );

	double b_up = ( p3.z_ - p1.z_ ) * ( p1.x_ * p2.z_ - p2.x_ * p1.z_ ) -
				  ( p2.z_ - p1.z_ ) * ( p1.x_ * p3.z_ - p3.x_ * p1.z_ );
	double b_down = ( p1.y_ * p2.z_ - p2.y_ * p1.z_ ) * ( p1.x_ * p3.z_ - p3.x_ * p1.z_ ) - 
		            ( p1.y_ * p3.z_ - p3.y_ * p1.z_ ) * ( p1.x_ * p2.z_ - p2.x_ * p1.z_ );

	double c_up = ( p3.x_ - p1.x_ ) * ( p1.y_ * p2.x_ - p2.y_ * p1.x_ ) -
		          ( p2.x_ - p1.x_ ) * ( p1.y_ * p3.x_ - p3.y_ * p1.x_ );
	double c_down = ( p1.z_ * p2.x_ - p2.z_ * p1.x_ ) * ( p1.y_ * p3.x_ - p3.y_ * p1.x_ ) - 
		            ( p1.z_ * p3.x_ - p3.z_ * p1.x_ ) * ( p1.y_ * p2.x_ - p2.y_ * p1.x_ );

	if( 0 == a_down || 0 == b_down || 0 == c_down )
	{
		return;
	}

	double a = a_up / a_down;
	double b = b_up / b_down;
	double c = c_up / c_down;
	double temp = std::sqrt( a * a + b * b + c * c );

	paras[ 0 ] = a / temp;
	paras[ 1 ] = b / temp;
	paras[ 2 ] = c / temp;
	paras[ 3 ] = 1 / temp;
}

void Plane::GetFourParametersFromVectorPoints( std::vector< Point3D > &three_points, double paras[] )
{
	GetFourParametersFromThreePoints( three_points[ 0 ], three_points[ 1 ], three_points[ 2 ], paras );
}

double Plane::ComputeCost( std::vector< double > &v, std::vector< double > &q )
{
	if( v.size() != 4 && q.size() != 16 ) return 1e60;
	return ( q[ 0 ] * v[ 0 ] + q[ 4 ] * v[ 1 ] + q[ 8 ] * v[ 2 ] + q[ 12 ] ) * v[ 0 ] + 
		   ( q[ 1 ] * v[ 0 ] + q[ 5 ] * v[ 1 ] + q[ 9 ] * v[ 2 ] + q[ 13 ] ) * v[ 1 ] + 
		   ( q[ 2 ] * v[ 0 ] + q[ 6 ] * v[ 1 ] + q[ 10 ] * v[ 2 ] + q[ 14 ] ) * v[ 2 ] + 
		   ( q[ 3 ] + q[ 7 ] + q[ 11 ] + q[ 15 ] );
}

double Plane::ComputeCost( Point3D &v, std::vector< double > &q )
{
	if( q.size() != 16 ) return 1e60;
	return ( q[ 0 ] * v.x_ + q[ 4 ] * v.y_ + q[ 8 ] * v.z_ + q[ 12 ] ) * v.x_ + 
		   ( q[ 1 ] * v.x_ + q[ 5 ] * v.y_ + q[ 9 ] * v.z_ + q[ 13 ] ) * v.y_ + 
		   ( q[ 2 ] * v.x_ + q[ 6 ] * v.y_ + q[ 10 ] * v.z_ + q[ 14 ] ) * v.z_ + 
		   ( q[ 3 ] + q[ 7 ] + q[ 11 ] + q[ 15 ] );
}