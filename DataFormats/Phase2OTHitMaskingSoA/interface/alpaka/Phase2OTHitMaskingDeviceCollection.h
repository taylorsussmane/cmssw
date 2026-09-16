#ifndef DataFormats_Phase2OTHitMaskingSoA_interface_alpaka_Phase2OTHitMaskingDeviceCollection_h
#define DataFormats_Phase2OTHitMaskingSoA_interface_alpaka_Phase2OTHitMaskingDeviceCollection_h

#include <alpaka/alpaka.hpp>
#include <cstdint>

#include "DataFormats/Common/interface/Uninitialized.h"
#include "DataFormats/Portable/interface/alpaka/PortableCollection.h"
#include "DataFormats/PortableTestObjects/interface/TestSoA.h"
#include "HeterogeneousCore/AlpakaInterface/interface/config.h"

#include "DataFormats/Phase2OTHitMaskingSoA/interface/Phase2OTHitMaskingSoA.h"
#include "DataFormats/Phase2OTHitMaskingSoA/interface/Phase2OTHitMaskingHostCollection.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE{
	using Phase2OTHitMaskingDevice = PortableCollection<Phase2OTHitMaskingSoA>;
}

ASSERT_DEVICE_MATCHES_HOST_COLLECTION(Phase2OTHitMaskingDevice, Phase2OTHitMaskingHost);

#endif
