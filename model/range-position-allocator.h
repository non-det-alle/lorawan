/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Alessandro Aimi <alessandro.aimi@cnam.fr>
 *                         <alessandro.aimi@orange.com>
 */

#ifndef RANGE_POSITION_ALLOCATOR_H
#define RANGE_POSITION_ALLOCATOR_H

#include "ns3/position-allocator.h"
#include "ns3/node-container.h"
#include <cmath>

namespace ns3 {

class RangePositionAllocator : public PositionAllocator
{
public:
  static TypeId GetTypeId (void);
  RangePositionAllocator ();
  ~RangePositionAllocator ();

  /**
     * \param rho the value of the radius of the allocation disc
     */
  void SetRho (double rho);

  /**
     * \param range the max range from any gateway
     */
  void SetRange (double range);

  /**
     * \param x  the X coordinate of the center of the disc
     */
  void SetX (double x);

  /**
     * \param y   the Y coordinate of the center of the disc
     */
  void SetY (double y);

  /**
     * \param z   the Z coordinate of all the positions allocated
     */
  void SetZ (double z);

  /**
     * \param nodes the nodes to be in range of
     */
  void SetNodes (NodeContainer nodes);

  virtual Vector GetNext (void) const;
  virtual int64_t AssignStreams (int64_t stream);

private:
  bool OutOfRange (double x, double y) const;

  Ptr<UniformRandomVariable> m_rv; //!< pointer to uniform random variable
  double m_rho; //!< value of the radius of the disc
  double m_range; //!< the max range from any gateway
  double m_x; //!< x coordinate of center of disc
  double m_y; //!< y coordinate of center of disc
  double m_z; //!< z coordinate of the disc
  NodeContainer m_nodes; //!< the nodes to be in range of
};

} // namespace ns3

#endif /* RANGE_POSITION_ALLOCATOR_H */
