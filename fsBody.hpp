#pragma once

#include "fsMath.hpp"
#include "fsWorld.hpp"
#include "Box2D/Box2D.h"


namespace fs{
    class fsBody : private b2Body {
    public:
        

        /// Creates a fixture and attach it to this body. Use this function if you need
	/// to set some fixture parameters, like friction. Otherwise you can create the
	/// fixture directly from a shape.
	/// If the density is non-zero, this function automatically updates the mass of the body.
	/// Contacts are not created until the next time step.
	/// @param def the fixture definition.
	/// @warning This function is locked during callbacks.
//	b2Fixture* CreateFixture(const b2FixtureDef* def);

	/// Creates a fixture from a shape and attach it to this body.
	/// This is a convenience function. Use b2FixtureDef if you need to set parameters
	/// like friction, restitution, user data, or filtering.
	/// If the density is non-zero, this function automatically updates the mass of the body.
	/// @param shape the shape to be cloned.
	/// @param density the shape density (set to zero for static bodies).
	/// @warning This function is locked during callbacks.
//	b2Fixture* CreateFixture(const b2Shape* shape, float32 density);

	/// Destroy a fixture. This removes the fixture from the broad-phase and
	/// destroys all contacts associated with this fixture. This will
	/// automatically adjust the mass of the body if the body is dynamic and the
	/// fixture has positive density.
	/// All fixtures attached to a body are implicitly destroyed when the body is destroyed.
	/// @param fixture the fixture to be removed.
	/// @warning This function is locked during callbacks.
//	void DestroyFixture(b2Fixture* fixture);

	/// Set the position of the body's origin and rotation.
	/// Manipulating a body's transform may cause non-physical behavior.
	/// Note: contacts are updated on the next call to b2World::Step.
	/// @param position the world position of the body's local origin.
	/// @param angle the world rotation in radians.
	void setTransform(fsVec2& position, float32 angle){SetTransform(position.convertTob2(), angle);}

	/// Get the body transform for the body's origin.
	/// @return the world transform of the body's origin.
//	const b2Transform& GetTransform() const;

	/// Get the world body origin position.
	/// @return the world position of the body's origin.
	const fsVec2& getPosition() const{return (fsVec2)GetPosition();}

	/// Get the angle in radians.
	/// @return the current world rotation angle in radians.
	float32 getAngle() const{return GetAngle();}

	/// Get the world position of the center of mass.
	const fsVec2& getWorldCenter() const{return (fsVec2)GetWorldCenter();}

	/// Get the local position of the center of mass.
	const fsVec2& getLocalCenter() const{return (fsVec2)GetLocalCenter();}

	/// Set the linear velocity of the center of mass.
	/// @param v the new linear velocity of the center of mass.
	void setLinearVelocity(fsVec2& v){SetLinearVelocity(v.convertTob2());}

	/// Get the linear velocity of the center of mass.
	/// @return the linear velocity of the center of mass.
	const fsVec2& getLinearVelocity() const{return (fsVec2)GetLinearVelocity();}

	/// Set the angular velocity.
	/// @param omega the new angular velocity in radians/second.
	void setAngularVelocity(float32 omega){SetAngularVelocity(omega);}

	/// Get the angular velocity.
	/// @return the angular velocity in radians/second.
	float32 getAngularVelocity() const{return GetAngularVelocity();}

	/// Apply a force at a world point. If the force is not
	/// applied at the center of mass, it will generate a torque and
	/// affect the angular velocity. This wakes up the body.
	/// @param force the world force vector, usually in Newtons (N).
	/// @param point the world position of the point of application.
	/// @param wake also wake up the body
	void applyForce(fsVec2& force, fsVec2& point, bool wake){ApplyForce(force.convertTob2(), point.convertTob2(),wake);}

	/// Apply a force to the center of mass. This wakes up the body.
	/// @param force the world force vector, usually in Newtons (N).
	/// @param wake also wake up the body
	void applyForceToCenter(fsVec2& force, bool wake){ApplyForceToCenter(force.convertTob2(),wake);}

	/// Apply a torque. This affects the angular velocity
	/// without affecting the linear velocity of the center of mass.
	/// @param torque about the z-axis (out of the screen), usually in N-m.
	/// @param wake also wake up the body
	void applyTorque(float32 torque, bool wake){ApplyTorque(torque, wake);}

	/// Apply an impulse at a point. This immediately modifies the velocity.
	/// It also modifies the angular velocity if the point of application
	/// is not at the center of mass. This wakes up the body.
	/// @param impulse the world impulse vector, usually in N-seconds or kg-m/s.
	/// @param point the world position of the point of application.
	/// @param wake also wake up the body
	void applyLinearImpulse(fsVec2& impulse, fsVec2& point, bool wake){ApplyLinearImpulse(impulse.convertTob2(), point.convertTob2(), wake);}

	/// Apply an impulse to the center of mass. This immediately modifies the velocity.
	/// @param impulse the world impulse vector, usually in N-seconds or kg-m/s.
	/// @param wake also wake up the body
	void applyLinearImpulseToCenter(fsVec2& impulse, bool wake){ApplyLinearImpulseToCenter(impulse.convertTob2(),wake);}

	/// Apply an angular impulse.
	/// @param impulse the angular impulse in units of kg*m*m/s
	/// @param wake also wake up the body
	void applyAngularImpulse(float32 impulse, bool wake){ApplyAngularImpulse(impulse,wake);}

	/// Get the total mass of the body.
	/// @return the mass, usually in kilograms (kg).
	float32 getMass() const{return GetMass();}

	/// Get the rotational inertia of the body about the local origin.
	/// @return the rotational inertia, usually in kg-m^2.
	float32 getInertia() const{return GetInertia();}

	/// Get the mass data of the body.
	/// @return a struct containing the mass, inertia and center of the body.
//	void GetMassData(b2MassData* data) const;

	/// Set the mass properties to override the mass properties of the fixtures.
	/// Note that this changes the center of mass position.
	/// Note that creating or destroying fixtures can also alter the mass.
	/// This function has no effect if the body isn't dynamic.
	/// @param massData the mass properties.
//	void SetMassData(const b2MassData* data);

	/// This resets the mass properties to the sum of the mass properties of the fixtures.
	/// This normally does not need to be called unless you called SetMassData to override
	/// the mass and you later want to reset the mass.
	void resetMassData(){ResetMassData();}

	/// Get the world coordinates of a point given the local coordinates.
	/// @param localPoint a point on the body measured relative the the body's origin.
	/// @return the same point expressed in world coordinates.
	fsVec2 getWorldPoint(fsVec2& localPoint) const{return (fsVec2)GetWorldPoint(localPoint.convertTob2());}

	/// Get the world coordinates of a vector given the local coordinates.
	/// @param localVector a vector fixed in the body.
	/// @return the same vector expressed in world coordinates.
	fsVec2 getWorldVector(fsVec2& localVector) const{return (fsVec2)GetWorldVector(localVector.convertTob2());}

	/// Gets a local point relative to the body's origin given a world point.
	/// @param a point in world coordinates.
	/// @return the corresponding local point relative to the body's origin.
	fsVec2 getLocalPoint(fsVec2& worldPoint) const{return (fsVec2)GetLocalPoint(worldPoint.convertTob2());}

	/// Gets a local vector given a world vector.
	/// @param a vector in world coordinates.
	/// @return the corresponding local vector.
	fsVec2 getLocalVector(fsVec2& worldVector) const{return (fsVec2)GetLocalVector(worldVector.convertTob2());}

	/// Get the world linear velocity of a world point attached to this body.
	/// @param a point in world coordinates.
	/// @return the world velocity of a point.
	fsVec2 getLinearVelocityFromWorldPoint(fsVec2& worldPoint) const{return (fsVec2)GetLinearVelocityFromWorldPoint(worldPoint.convertTob2());}

	/// Get the world velocity of a local point.
	/// @param a point in local coordinates.
	/// @return the world velocity of a point.
	fsVec2 getLinearVelocityFromLocalPoint(fsVec2& localPoint) const{return (fsVec2)GetLinearVelocityFromLocalPoint(localPoint.convertTob2());}

	/// Get the linear damping of the body.
	float32 getLinearDamping() const{return GetLinearDamping();}

	/// Set the linear damping of the body.
	void setLinearDamping(float32 linearDamping){SetLinearDamping(linearDamping);}

	/// Get the angular damping of the body.
	float32 getAngularDamping() const{return GetAngularDamping();}

	/// Set the angular damping of the body.
	void setAngularDamping(float32 angularDamping){SetAngularDamping(angularDamping);}

	/// Get the gravity scale of the body.
	float32 getGravityScale() const{return GetGravityScale();}

	/// Set the gravity scale of the body.
	void setGravityScale(float32 scale){SetGravityScale(scale);}

	/// Set the type of this body. This may alter the mass and velocity.
//	void SetType(b2BodyType type);

	/// Get the type of this body.
//	b2BodyType GetType() const;

	/// Should this body be treated like a bullet for continuous collision detection?
	void setBullet(bool flag){return SetBullet(flag);}

	/// Is this body treated like a bullet for continuous collision detection?
	bool isBullet() const{return IsBullet();}

	/// You can disable sleeping on this body. If you disable sleeping, the
	/// body will be woken.
	void setSleepingAllowed(bool flag){SetSleepingAllowed(flag);}

	/// Is this body allowed to sleep
	bool isSleepingAllowed() const{return IsSleepingAllowed();}

	/// Set the sleep state of the body. A sleeping body has very
	/// low CPU cost.
	/// @param flag set to true to wake the body, false to put it to sleep.
	void setAwake(bool flag){SetAwake(flag);}

	/// Get the sleeping state of this body.
	/// @return true if the body is awake.
	bool isAwake() const{return IsAwake();}

	/// Set the active state of the body. An inactive body is not
	/// simulated and cannot be collided with or woken up.
	/// If you pass a flag of true, all fixtures will be added to the
	/// broad-phase.
	/// If you pass a flag of false, all fixtures will be removed from
	/// the broad-phase and all contacts will be destroyed.
	/// Fixtures and joints are otherwise unaffected. You may continue
	/// to create/destroy fixtures and joints on inactive bodies.
	/// Fixtures on an inactive body are implicitly inactive and will
	/// not participate in collisions, ray-casts, or queries.
	/// Joints connected to an inactive body are implicitly inactive.
	/// An inactive body is still owned by a b2World object and remains
	/// in the body list.
	void setActive(bool flag){SetActive(flag);}

	/// Get the active state of the body.
	bool isActive() const{return IsActive();}

	/// Set this body to have fixed rotation. This causes the mass
	/// to be reset.
	void setFixedRotation(bool flag){SetFixedRotation(flag);}

	/// Does this body have fixed rotation?
	bool isFixedRotation() const{return IsFixedRotation();}

	/// Get the list of all fixtures attached to this body.
//	b2Fixture* GetFixtureList();
//	const b2Fixture* GetFixtureList() const;

	/// Get the list of all joints attached to this body.
//	b2JointEdge* GetJointList();
//	const b2JointEdge* GetJointList() const;

	/// Get the list of all contacts attached to this body.
	/// @warning this list changes during the time step and you may
	/// miss some collisions if you don't use b2ContactListener.
//	b2ContactEdge* GetContactList();
//	const b2ContactEdge* GetContactList() const;

	/// Get the next body in the world's body list.
	fsBody* getNext(){return (fsBody*)GetNext();}
	const fsBody* getNext() const{return (fsBody*)GetNext();}

	/// Get the user data pointer that was provided in the body definition.
	void* getUserData() const{GetUserData();}

	/// Set the user data. Use this to store your application specific data.
	void setUserData(void* data){SetUserData(data);}

	/// Get the parent world of this body.
	fsWorld* getWorld(){return (fsWorld*)GetWorld();}
	const fsWorld* getWorld() const{return (fsWorld*)GetWorld();}

	/// Dump this body to a log file
	void dump(){Dump();}
        
    private: 
        fsBody(){}
        ~fsBody(){}
        

    };
    
}