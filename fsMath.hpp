#pragma once

#include "Box2D/Box2D/Common/b2Math.h"
#include "Box2D/Box2D/Dynamics/b2World.h"
#include <math.h>

namespace fs{
    /// This function is used to ensure that a floating point number is not a NaN or infinity.
    inline bool fsIsValid(float x){return b2IsValid((float32)x);}

    /// This is a approximate yet fast inverse square-root.
    inline float fsInvSqrt(float x){return b2InvSqrt((float32)x);}
    
    
    
    /// Un vector de 2 dimensiones
    struct fsVec2 : private b2Vec2{
        fsVec2():b2Vec2(){}
        fsVec2(b2Vec2 vector){
            x = vector.x;
            y = vector.y;
        }
        fsVec2(float x, float y):b2Vec2((float32)x, (float32)y){}
        virtual ~fsVec2(){}
        
        ///Usado para poner a 0 el vector
        void setZero(){SetZero();}
        ///Set de las coordenadas pasadas 
        void set(float x, float y){Set((float32)x, (float32)y);}
        ///Invierte el vector
        fsVec2 operator -() const { fsVec2 v; v.set(-x, -y); return v; }
        ///Sumar un vector a otro
        void operator += (const fsVec2& v){x += v.x; y += v.y;}
        ///Restar un vector a otro
        void operator -= (const fsVec2& v){x -= v.x; y -= v.y;}
        ///Multipliar el vector por un escalar
        void operator *= (float a){x *= a; y *= a;}
        ///Devuelve la longitud (la normal?)
        float length() const{return Length();}
        /// Get the length squared. For performance, use this instead of
	/// b2Vec2::Length (if possible).
        float lengthSquared() const{return LengthSquared();}
        /// Convert this vector into a unit vector. Returns the length.
        float normalizar(){return (float)Normalize();}
        /// Does this vector contain finite coordinates?
        bool isValid() const{return IsValid();}
        /// Get the skew vector such that dot(skew_vec, other) == cross(vec, other)
        fsVec2 skew() const{return skew();}
        
        ///Convierte el vector a Vector de Box2D
        b2Vec2 convertTob2(){return b2Vec2(x, y);}
        
        ///Imprime por consola los valores del vector separados por un espacio
        void print(){
            std::cout<<x<<" "<<y<<std::endl;
        }
    };
    
    struct fsRot : b2Rot{
        fsRot() : b2Rot(){}
        
        /// Initialize from an angle in radians
	explicit fsRot(float angle):b2Rot((float32) angle){}

	/// Set using an angle in radians.
	void set(float angle){set((float32) angle);}

	/// Set to the identity rotation
	void setIdentity()
	{
		s = 0.0f;
		c = 1.0f;
	}

	/// Get the angle in radians
	float getAngle() const{return GetAngle();}

	/// Get the x-axis
	fsVec2 GetXAxis() const {return fsVec2(c, s);}

	/// Get the u-axis
	fsVec2 GetYAxis() const{return fsVec2(-s, c);}
    };
}
