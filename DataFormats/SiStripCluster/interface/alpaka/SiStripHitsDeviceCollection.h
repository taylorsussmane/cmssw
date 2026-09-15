#ifndef DataFormats_SiStripCluster_interface_alpaka_SiStripHitsDeviceCollection_h
#define DataFormats_SiStripCluster_interface_alpaka_SiStripHitsDeviceCollection_h

#include <alpaka/alpaka.hpp>
#include <cstdint>

#include "DataFormats/Common/interface/Uninitialized.h"
#include "DataFormats/Portable/interface/alpaka/PortableCollection.h"
#include "DataFormats/PortableTestObjects/interface/TestSoA.h"
#include "HeterogeneousCore/AlpakaInterface/interface/config.h"

#include "DataFormats/SiStripCluster/interface/SiStripHitsSoA.h"
#include "DataFormats/SiStripCluster/interface/SiStripHitsHostCollection.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE{
	using SiStripHitsMaskingDevice = PortableCollection<SiStripHitsMaskingSoA>;
}

ASSERT_DEVICE_MATCHES_HOST_COLLECTION(SiStripHitsMaskingDevice, SiStripHitsMaskingHost);

#endif
