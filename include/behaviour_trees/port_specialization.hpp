/*!*******************************************************************************************
 *  \file       port_specialization.hpp
 *  \brief      List of custom ports
 *  \authors    Pedro Arias Pérez
 *              Miguel Fernández Cortizas
 *              David Pérez Saura
 *              Rafael Pérez Seguí
 *
 *  \copyright  Copyright (c) 2022 Universidad Politécnica de Madrid
 *              All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ********************************************************************************/

#ifndef PORT_SPECIALIZATION_HPP_
#define PORT_SPECIALIZATION_HPP_

#include "behaviortree_cpp_v3/bt_factory.h"
#include "geometry_msgs/msg/point_stamped.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

#include "as2_msgs/msg/trajectory_waypoints.hpp"

// Template specialization to converts a string to Position2D.
namespace BT {
template <>
inline geometry_msgs::msg::Pose convertFromString(BT::StringView str) {
  // We expect real numbers separated by semicolons
  auto parts = splitString(str, ';');
  if (parts.size() != 3) {
    throw RuntimeError("invalid input)");
  } else {
    geometry_msgs::msg::Pose output;
    output.position.x = convertFromString<double>(parts[0]);
    output.position.y = convertFromString<double>(parts[1]);
    output.position.z = convertFromString<double>(parts[2]);
    return output;
  }
}

template <>
inline geometry_msgs::msg::PointStamped convertFromString(BT::StringView str) {
  // We expect real numbers separated by semicolons
  auto parts = splitString(str, ';');
  if (parts.size() != 3) {
    throw RuntimeError("invalid input)");
  } else {
    geometry_msgs::msg::PointStamped output;
    output.point.x = convertFromString<double>(parts[0]);
    output.point.y = convertFromString<double>(parts[1]);
    output.point.z = convertFromString<double>(parts[2]);
    return output;
  }
}

// TODO: generalize
template <>
inline as2_msgs::msg::TrajectoryWaypoints
convertFromString(BT::StringView str) {
  // We expect real numbers separated by semicolons
  auto points = splitString(str, '|');
  auto parts = splitString(points[0], ';');
  if (parts.size() != 3) {
    throw RuntimeError("invalid input)");
  } else {
    as2_msgs::msg::TrajectoryWaypoints output;
    geometry_msgs::msg::PoseStamped mypose;
    mypose.pose.position.x = convertFromString<double>(parts[0]);
    mypose.pose.position.y = convertFromString<double>(parts[1]);
    mypose.pose.position.z = convertFromString<double>(parts[2]);

    auto parts_2 = splitString(points[1], ';');
    geometry_msgs::msg::PoseStamped mypose_2;
    mypose_2.pose.position.x = convertFromString<double>(parts_2[0]);
    mypose_2.pose.position.y = convertFromString<double>(parts_2[1]);
    mypose_2.pose.position.z = convertFromString<double>(parts_2[2]);

    output.poses.emplace_back(mypose);
    output.poses.emplace_back(mypose_2);
    return output;
  }
}

} // end namespace BT

#endif // PORT_SPECIALIZATION_HPP_