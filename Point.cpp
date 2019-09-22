#include "Point.h"

#ifndef __SSE3__
#include <algorithm>
#include <cmath>
using namespace std;
#endif


Point::Point( void ) noexcept
#ifdef __SSE3__
	: v( _mm_setzero_pd() )
#else
	: x( 0.0f )
	, y( 0.0f )
#endif
{

}

Point::Point( const double x, const double y ) noexcept
#ifdef __SSE3__
	: v( _mm_set_pd( y, x ) )
#else
	: x( x )
	, y( y )
#endif
{
}

Point::Point( const Point & point ) noexcept
#ifdef __SSE3__
	: v( point.v )
#else
	: x( point.x )
	, y( point.y )
#endif
{

}

Point &Point::operator=( const Point &point ) noexcept
{
#ifdef __SSE3__
	v = point.v;
#else
	x = point.x;
	y = point.y;
#endif
	return *this;
}

Point::operator bool( void ) const noexcept
{
	return !!*this;
}

bool Point::operator!( void ) const noexcept
{
	return ( !x & !y );
}

Point Point::operator+( const Point & point ) const noexcept
{
#ifdef __SSE3__
	return Point( v + point.v );
#else
	return Point( x + point.x, y + point.y );
#endif
}

Point& Point::operator+=( const Point & point ) noexcept
{
#ifdef __SSE3__
	v += point.v;
#else
	x += point.x;
	y += point.y;
#endif
	return *this;
}

Point Point::operator-( const Point & point ) const noexcept
{
#ifdef __SSE3__
	return Point( v - point.v );
#else
	return Point( x - point.x, y - point.y );
#endif
}

Point & Point::operator-=( const Point & point ) noexcept
{
#ifdef __SSE3__
	v -= point.v;
#else
	x -= point.x;
	y -= point.y;
#endif
	return *this;
}

Point Point::operator-( void ) const noexcept
{
	return Point() - *this;
}

Point Point::operator*( const double scalar ) const noexcept
{
#ifdef __SSE3__
	return Point( v * _mm_loaddup_pd( &scalar ) );
#else
	return Point( x * scalar, y * scalar );
#endif
}

Point Point::operator*( const Point & point ) const noexcept
{
#ifdef __SSE3__
	Point result;
	result.v = v * other.v;
	return result;
#else
	return Point( x * point.x, y * point.y );
#endif
}

Point & Point::operator*=( const double scalar ) noexcept
{
#ifdef __SSE3__
	v *= _mm_loaddup_pd(&scalar);
#else
	x *= scalar;
	y *= scalar;
#endif
	return *this;
}

Point Point::operator/(const double scalar) const noexcept
{
#ifdef __SSE3__
	return Point( v / _mm_loaddup_pd( &scalar ) );
#else
	return Point( x / scalar, y / scalar );
#endif
}

Point& Point::operator/=( const double scalar ) noexcept
{
#ifdef __SSE3__
	v /= _mm_loaddup_pd(&scalar);
#else
	x /= scalar;
	y /= scalar;
#endif
	return *this;
}

Point operator*( const double scalar, const Point & point ) noexcept
{
#ifdef __SSE3__
		return Point(point.v * _mm_loaddup_pd( &scalar ) );
#else
		return Point( point.x * scalar, point.y * scalar );
#endif
}

Point abs( const Point & point ) noexcept
{
#ifdef __SSE3__
	static const __m128d sign_mask = _mm_set1_pd( -0. );
	return Point( _mm_andnot_pd( sign_mask, p.v ) );
#else
	return Point( abs( point.x), abs( point.y ) );
#endif
}

Point min( const Point & lhs, const Point & rhs ) noexcept
{
#ifdef __SSE3__
	return Point( _mm_min_pd( lhs.v, rhs.v ) );
#else
	return Point( min( lhs.x, rhs.x ), min( lhs.y, rhs.y ) );
#endif
}

Point max( const Point & lhs, const Point & rhs ) noexcept
{
#ifdef __SSE3__
	return Point( _mm_max_pd( lhs.v, rhs.v ) );
#else
	return Point( max( lhs.x, rhs.x), max( lhs.y, rhs.y ) );
#endif
}


void Point::set( const double x, const double y ) noexcept
{
#ifdef __SSE3__
	v = _mm_set_pd( y, x );
#else
	this->x = x;
	this->y = y;
#endif
}

double Point::dot( const Point & point ) const noexcept
{
#ifdef __SSE3__
	__m128d b = v * point.v;
	b = _mm_hadd_pd( b, b );
	return reinterpret_cast<double &>( b );
#else
	return x * point.x + y * point.y;
#endif
}

double Point::cross( const Point & point ) const noexcept
{
#ifdef __SSE3__
	__m128d b = _mm_shuffle_pd( point.v, point.v, 0x01 );
	b *= v;
	b = _mm_hsub_pd( b, b );
	return reinterpret_cast<double &>( b );
#else
	return x * point.y - y * point.x;
#endif
}

double Point::length( void ) const noexcept
{
#ifdef __SSE3__
	__m128d b = v * v;
	b = _mm_hadd_pd( b, b );
	b = _mm_sqrt_pd( b );
	return reinterpret_cast<double &>( b );
#else
	return sqrt( x * x + y * y );
#endif
}

double Point::lengthSquared(void) const noexcept
{
	return dot( *this );
}

Point Point::unit(void) const noexcept
{
#ifdef __SSE3__
	__m128d b = v * v;
	b = _mm_hadd_pd( b, b );
	if ( !_mm_cvtsd_f64( b ) )
		return Point( 1., 0. );
	b = _mm_sqrt_pd( b );
	return Point( v / b );
#else
	double b = x * x + y * y;
	if (!b)
	{
		return Point( 1., 0. );
	}
		
	b = 1. / sqrt( b );
	return Point( x * b, y * b );
#endif
}

double Point::distance( const Point & point ) const noexcept
{
	return ( *this - point ).length();
}

double Point::distanceSquared( const Point & point ) const noexcept
{
	return ( *this - point ).lengthSquared();
}
