/*
 * Copyright (c) 2016 Daniel Kuhner <kuhnerd@informatik.uni-freiburg.de>.
 * All rights reserved.
 * 
 *  Created on: Jan 28, 2016
 *      Author: Daniel Kuhner <kuhnerd@informatik.uni-freiburg.de>
 * 	  Filename: trajectory.h
 */

#ifndef TRAJECTORY_H_
#define TRAJECTORY_H_

#include <ais_definitions/math.h>
#include <boost/shared_ptr.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames.hpp>
#include <kdl/jntarray.hpp>
#include <nav_msgs/Path.h>
#include <ros/ros.h>
#include <spline_library/spline.h>
#include <spline_library/vector.h>
#include <Eigen/Geometry>

namespace prm_planner
{

class Path;

class Trajectory
{
public:
	struct SplineInfo
	{
		boost::shared_ptr<Spline<Vector3>> spline;
		double length;
	};

	struct Pose
	{
		Pose()
		{
		}
		Pose(const Eigen::Affine3d& pose);
		Pose(const KDL::Frame& pose);
		Pose(const boost::shared_ptr<KDL::ChainFkSolverPos_recursive>& fk,
				const KDL::JntArray& joints);
		void reset(const boost::shared_ptr<KDL::ChainFkSolverPos_recursive>& fk,
				const KDL::JntArray& joints);
		void reset(const Eigen::Affine3d& pose);
		void updateRotation();
		void get(KDL::Frame& frame);
		void get(Eigen::Affine3d& pose);
		void transform(Eigen::Affine3d& t);
		Vector6d x;
		Eigen::Quaterniond quaternion;
	};

	Trajectory(const boost::shared_ptr<Path>& path,
			const Vector6d& startVelocity,
			const double maxVelocityLinear,
			const double maxVelocityAngular,
			const ros::Time& now,
			const std::string frame);
	virtual ~Trajectory();

	bool getPose(const ros::Time& now,
			Pose& pose,
			int& currentWaypoint);
	nav_msgs::PathConstPtr getRosTrajectory();

	double getPredictedExecutionTime() const;
	void setPredictedExecutionTime(const double predictionTime);

	void setNow(const ros::Time& now);

	bool isValid();

	void writeGnuplotFile(const std::string& file);

private:
	bool getPoseFromT(const double& t,
			Pose& pose);
	void initializeSpline();
	void computeSmoothFirstDerivative(const double t,
			Vector3& d);

private:
	struct WaypointInfos
	{
		double startTime;
		double distToStart;
		double progress; //between 0...1
	};
	boost::shared_ptr<Path> m_path;
	Vector6d m_startVelocity;
	SplineInfo m_spline;
	nav_msgs::PathPtr m_rosTrajectory;
	double m_predictedExecutionTime;
	std::vector<WaypointInfos> m_waypointInfos;
	ros::Time m_start;

public:
	const double c_maxVelocityLinear;
	const double c_maxVelocityAngular;
	const std::string c_frame;
};

} /* namespace prm_planner */

#endif /* TRAJECTORY_H_ */
