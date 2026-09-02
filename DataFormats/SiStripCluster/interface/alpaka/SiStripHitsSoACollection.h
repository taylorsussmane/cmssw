#ifndef DataFormats_SiStripCluster_interface_alpaka_SiStripHitsSoACollection_h
#define DataFormats_SiStripCluster_interface_alpaka_SiStripHitsSoACollection_h

#include <type_traits>

#include <alpaka/alpaka.hpp>

#include "DataFormats/Portable/interface/alpaka/PortableCollection.h"
#include "DataFormats/SiStripCluster/interface/SiStripHitsDeviceCollection.h"
#include "DataFormats/SiStripCluster/interface/SiStripHitsHostCollection.h"
#include "Geometry/CommonTopologies/interface/SimplePixelTopology.h"
#include "HeterogeneousCore/AlpakaInterface/interface/AssertDeviceMatchesHostCollection.h"
#include "HeterogeneousCore/AlpakaInterface/interface/CopyToHost.h"
#include "HeterogeneousCore/AlpakaInterface/interface/config.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE{
	using ::SiStripHitsMaskingDevice;
	using ::SiStripHitsMaskingHost;
	using SiStripHitsMaskingSoA = std::conditional_t<std::is_same_v<Device, alpaka::DevCpu>, SiStripHitsMaskingHost, SiStripHitsMaskingDevice<Device>>;

}// namespace ALPAKA_ACCELERATOR_NAMESPACE

ASSERT_DEVICE_MATCHES_HOST_COLLECTION(SiStripHitsMaskingSoA, SiStripHitsMaskingHost);

#endif
