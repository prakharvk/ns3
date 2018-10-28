#include <fstream>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("client_server");

int main (int argc, char *argv[]) {
  double lat = 2.0;
  uint64_t rate = 5000000;
  double interval = 0.05;

 LogComponentEnable ("UdpClient", LOG_LEVEL_INFO);
 LogComponentEnable ("UdpServer", LOG_LEVEL_INFO);

  NS_LOG_INFO ("Create nodes.");
  NodeContainer n;
  n.Create (5);

  NS_LOG_INFO ("Create channels.");
  InternetStackHelper internet;
  internet.Install (n);

  PointToPointHelper p2p;

  p2p.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (lat)));
  p2p.SetDeviceAttribute ("DataRate", DataRateValue (DataRate (rate)));
  p2p.SetDeviceAttribute ("Mtu", UintegerValue (1400));

  NetDeviceContainer dev1 = p2p.Install (n.Get(0), n.Get(1));
  NetDeviceContainer dev2 = p2p.Install (n.Get(1), n.Get(2));
  NetDeviceContainer dev3 = p2p.Install (n.Get(2), n.Get(3));
  NetDeviceContainer dev4 = p2p.Install (n.Get(3), n.Get(4));
  NetDeviceContainer dev5 = p2p.Install (n.Get(4), n.Get(0));

  Ipv4AddressHelper ipv4;

  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i1 = ipv4.Assign (dev1);

  ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i2 = ipv4.Assign (dev2);

  ipv4.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer i3 = ipv4.Assign (dev3);

  ipv4.SetBase ("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer i4 = ipv4.Assign (dev4);

  ipv4.SetBase ("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer i5 = ipv4.Assign (dev5);

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  NS_LOG_INFO ("Create Applications.");

  uint16_t port1 = 8000;
  uint16_t port2 = 8001;
  uint16_t port3 = 8002;
  UdpServerHelper server1 (port1);
  UdpServerHelper server2 (port2);
  UdpServerHelper server3 (port3);

  ApplicationContainer apps;
  apps = server1.Install (n.Get (1));
  apps = server2.Install (n.Get (1));
  apps = server3.Install (n.Get (1));

  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  uint32_t MaxPacketSize = 1024;
  Time interPacketInterval = Seconds (interval);
  uint32_t maxPacketCount = 320;
  UdpClientHelper client1 (i1.GetAddress (1), port1);
  UdpClientHelper client2 (i1.GetAddress (1), port2);
  UdpClientHelper client3 (i1.GetAddress (1), port3);

  client1.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client1.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client1.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));

  client2.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client2.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client2.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));

  client3.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client3.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client3.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));

  apps = client1.Install (n.Get (4));
  apps = client2.Install (n.Get (2));
  apps = client3.Install (n.Get (3));

  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (10.0));

  AnimationInterface anim ("ring.xml");

  anim.SetConstantPosition(n.Get(0),200,200);
  anim.SetConstantPosition(n.Get(1),150,200);
  anim.SetConstantPosition(n.Get(2),100,200);
  anim.SetConstantPosition(n.Get(3),150,100);
  anim.SetConstantPosition(n.Get(4),150,300);

  Simulator::Run ();
  return 0;
}
