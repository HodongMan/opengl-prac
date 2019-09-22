#pragma once

#ifdef __SSE3__
#include <pmmintrin.h>
#endif


class Point
{
public:
	Point( void ) noexcept;
	Point( const double x, const double y ) noexcept;
	Point( const Point& point ) noexcept;

	Point&			operator=( const Point& point ) noexcept;

	explicit		operator bool( void ) const noexcept;
	bool			operator!( void ) const noexcept;

	Point			operator+( const Point& point ) const noexcept;
	Point&			operator+=( const Point& point ) noexcept;
	Point			operator-( const Point& point ) const noexcept;
	Point&			operator-=( const Point& point) noexcept;
	Point			operator-( void ) const noexcept;

	Point			operator*( const double scalar ) const noexcept;
	Point			operator*( const Point& point ) const noexcept;
	friend Point	operator*( const double scalar, const Point& point ) noexcept;
	Point&			operator*=( const double scalar ) noexcept;
	Point			operator/( const double scalar ) const noexcept;
	Point&			operator/=( const double scalar ) noexcept;

	double&			X( void ) noexcept;
	const double&	X( void ) const noexcept;
	double&			Y( void ) noexcept;
	const double&	Y( void ) const noexcept;

	void			set( const double x, const double y ) noexcept;

	double			dot( const Point& point ) const noexcept;
	double			cross( const Point& point ) const noexcept;

	double			length( void ) const noexcept;
	double			lengthSquared( void ) const noexcept;
	Point			unit( void ) const noexcept;

	double			distance( const Point& point ) const noexcept;
	double			distanceSquared( const Point& point ) const noexcept;

	friend Point	abs( const Point& point ) noexcept;
	friend Point	min( const Point& lhs, const Point& rhs ) noexcept;
	friend Point	max( const Point& lhs, const Point& rhs ) noexcept;

private:
#ifdef __SSE3__

	explicit Point( const __m128d &v );


private:
	union {
		__m128d v;
		struct {
			double x;
			double y;
		};
	};
#else
	double x;
	double y;
#endif

};

inline double& Point::X( void ) noexcept
{
	return x;
}

inline const double& Point::X( void ) const noexcept
{
	return x;
}

inline double& Point::Y( void ) noexcept
{
	return y;
}

inline const double& Point::Y( void ) const noexcept
{
	return y;
}
