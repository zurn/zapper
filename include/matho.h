
#ifndef __CORE_MATH
#define __CORE_MATH 1

#include <cmath>
//#include <iostream>
//using std::ostream;

//-------------------------------------------------------------------
// A floating point number
typedef float scalar;
//-------------------------------------------------------------------
//
// A 3D vector
//
class Vector
{
	public:
		scalar x,y,z; //x,y,z coordinates
	public:
		Vector()
			: x(0), y(0), z(0)
			{}
		Vector( const scalar& a, const scalar& b, const scalar& c )
			: x(a), y(b), z(c){}

//		friend ostream& operator << (ostream& o, const Vector &c) {
//			o <<"x: " << c.x << "\ny: " << c.y << "\nz: " << c.z << "\n";
//			return o;
//		}

		//index a component
		//NOTE: returning a reference allows
		//you to assign the indexed element
		scalar& operator [] ( const long i ) {
			return *((&x) + i);
		}
		//compare
		const bool operator == ( const Vector& v ) const {
			return (v.x==x && v.y==y && v.z==z);
		}
		const bool operator != ( const Vector& v ) const {
			return !(v == *this);
		}
		//negate
		const Vector operator - () const {
			return Vector( -x, -y, -z );
		}
		//assign
		const Vector& operator = ( const Vector& v ) {
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}
		//increment
		const Vector& operator += ( const Vector& v ) {
			x+=v.x;
			y+=v.y;
			z+=v.z;
			return *this;
		}
		//decrement
		const Vector& operator -= ( const Vector& v ) {
			x-=v.x;
			y-=v.y;
			z-=v.z;
			return *this;
		}
		//self-multiply
		const Vector& operator *= ( const scalar& s ) {
			x*=s;
			y*=s;
			z*=s;
			return *this;
		}
		//self-divide
		const Vector& operator /= ( const scalar& s ) {
			const scalar r = 1 / s;
			x *= r;
			y *= r;
			z *= r;
			return *this;
		}
		//add
		const Vector operator + ( const Vector& v ) const {
			return Vector(x + v.x, y + v.y, z + v.z);
		}
		//subtract
		const Vector operator - ( const Vector& v ) const {
			return Vector(x - v.x, y - v.y, z - v.z);
		}
		//post-multiply by a scalar
		const Vector operator * ( const scalar& s ) const {
			return Vector( x*s, y*s, z*s );
		}
		//pre-multiply by a scalar
		friend inline const Vector operator * ( const scalar& s, 
															const Vector& v ) {
			return v * s;
		}
		//divide
		const Vector operator / (scalar s) const {
			s = 1/s;
			return Vector( s*x, s*y, s*z );
		}
		//cross product
		const Vector cross( const Vector& v ) const {
		//Davis, Snider, "Introduction to Vector Analysis", p. 44
			return Vector( y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x );
		}
		//scalar dot product
		const scalar dot( const Vector& v ) const {
			return x*v.x + y*v.y + z*v.z;
		}
		//length
		const scalar length() const {
			return (scalar)sqrt( (double)this->dot(*this) );
		}
		//unit vector
		const Vector unit() const {
			return (*this) / length();
		}
		//make this a unit vector
		void normalize() {
			(*this) /= length();
		}
		//equal within an error ‘e’
		const bool nearlyEquals( const Vector& v, const scalar e ) const
		{
		return fabs(x-v.x)<e && fabs(y-v.y)<e && fabs(z-v.z)<e;
		}
};

const Vector ZERO(0,0,0);

#endif /* __CORE_MATH */

