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
#include "range-position-allocator.h"
#include "ns3/double.h"
#include "ns3/mobility-module.h"
#include "ns3/node-container.h"

#include <cmath>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("RangePositionAllocator");

NS_OBJECT_ENSURE_REGISTERED (RangePositionAllocator);

TypeId
RangePositionAllocator::GetTypeId (void)
{
  static TypeId tid =
      TypeId ("ns3::RangePositionAllocator")
          .SetParent<PositionAllocator> ()
          .SetGroupName ("Mobility")
          .AddConstructor<RangePositionAllocator> ()
          .AddAttribute ("rho", "The radius of the allocation disc", DoubleValue (0.0),
                         MakeDoubleAccessor (&RangePositionAllocator::m_rho),
                         MakeDoubleChecker<double> ())
          .AddAttribute ("range", "The maximum range from the nodes", DoubleValue (0.0),
                         MakeDoubleAccessor (&RangePositionAllocator::m_range),
                         MakeDoubleChecker<double> ())
          .AddAttribute ("X", "The x coordinate of the center of the  disc.", DoubleValue (0.0),
                         MakeDoubleAccessor (&RangePositionAllocator::m_x),
                         MakeDoubleChecker<double> ())
          .AddAttribute ("Y", "The y coordinate of the center of the  disc.", DoubleValue (0.0),
                         MakeDoubleAccessor (&RangePositionAllocator::m_y),
                         MakeDoubleChecker<double> ())
          .AddAttribute ("Z", "The z coordinate of all the positions in the disc.",
                         DoubleValue (0.0), MakeDoubleAccessor (&RangePositionAllocator::m_z),
                         MakeDoubleChecker<double> ());
  return tid;
}

RangePositionAllocator::RangePositionAllocator ()
{
  m_rv = CreateObject<UniformRandomVariable> ();
}

RangePositionAllocator::~RangePositionAllocator ()
{
}

void
RangePositionAllocator::SetRho (double rho)
{
  m_rho = rho;
}

void
RangePositionAllocator::SetRange (double range)
{
  m_range = range;
}

void
RangePositionAllocator::SetX (double x)
{
  m_x = x;
}

void
RangePositionAllocator::SetY (double y)
{
  m_y = y;
}

void
RangePositionAllocator::SetZ (double z)
{
  m_z = z;
}

void
RangePositionAllocator::SetNodes (NodeContainer nodes)
{
  m_nodes = nodes;
}

bool
RangePositionAllocator::OutOfRange (double x, double y) const
{
  bool oor = true;
  for (NodeContainer::Iterator i = m_nodes.Begin (); i != m_nodes.End (); ++i)
    {
      Ptr<MobilityModel> pos = CreateObject<ConstantPositionMobilityModel> ();
      pos->SetPosition (Vector (x, y, m_z));
      double dist = (*i)->GetObject<MobilityModel> ()->GetDistanceFrom (pos);

      if (dist <= 1.0)
        return true;

      if (dist < m_range)
        {
          oor = false;
        }
    }
  return oor;
}

Vector
RangePositionAllocator::GetNext (void) const
{
  double x, y;
  do
    {
      x = m_rv->GetValue (-m_rho, m_rho);
      y = m_rv->GetValue (-m_rho, m_rho);
  } while (std::sqrt (x * x + y * y) > m_rho || OutOfRange (x + m_x, y + m_y));

  x += m_x;
  y += m_y;
  NS_LOG_DEBUG ("Disc position x=" << x << ", y=" << y);
  return Vector (x, y, m_z);
}

int64_t
RangePositionAllocator::AssignStreams (int64_t stream)
{
  m_rv->SetStream (stream);
  return 1;
}

} // namespace ns3
