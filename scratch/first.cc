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
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScript");

int main ()
{
  int  node = 2;
  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

  /*
    Creating nodes for point to point
  */
  NodeContainer nodes;
  nodes.Create (node);

  /*
    Creating point to point helper
  */
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

  /*
    Installing net deivice to nodes
    Can use PointToPointHelper or CsmaHelper classes
  */
  NetDeviceContainer device;
  device = pointToPoint.Install(nodes);

  /*
    Installing protocol stack
  */
  InternetStackHelper internet;
  internet.Install(nodes);

  /*
    Creating an IP address
  */
  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.1.1.0", "255.255.255.0");

  /*
    Assigning an IP address
  */
  Ipv4InterfaceContainer interface = ipv4.Assign(device);

  // Creating topology is done

  UdpEchoServerHelper server(10);

  ApplicationContainer serverApps = server.Install(nodes.Get(1));
  serverApps.Start(Seconds(1.0));
  serverApps.Stop(Seconds(10.0));

  UdpEchoClientHelper client(interface.GetAddress(1),10);
  client.SetAttribute("MaxPackets", UintegerValue(2));
  client.SetAttribute("Interval", TimeValue(Seconds(2.0)));
  client.SetAttribute("PacketSize", UintegerValue(1024));

  ApplicationContainer clientApps = client.Install(nodes.Get(0));
  clientApps.Start(Seconds(2.0));
  clientApps.Stop(Seconds(9.0));

  AnimationInterface anim("first.xml");
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
