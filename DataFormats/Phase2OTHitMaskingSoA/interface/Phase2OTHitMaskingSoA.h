#ifndef DataFormats_Phase2OTHitMaskingSoA_interface_Phase2OTHitMaskingSoA_h
#define DataFormats_Phase2OTHitMaskingSoA_interface_Phase2OTHitMaskingSoA_h

#include "DataFormats/SoATemplate/interface/SoACommon.h"
#include "DataFormats/SoATemplate/interface/SoALayout.h"

GENERATE_SOA_LAYOUT(Phase2OTHitMaskingLayout,
	SOA_COLUMN(uint32_t,recHitMask), // 0 = available, 1 = used	
	SOA_COLUMN(uint32_t, detId), // which module
	SOA_COLUMN(uint32_t, clusterIndex) // flat key into DetSetVector<Phase2OTHitMaskingSoA>	
)

using Phase2OTHitMaskingSoA = Phase2OTHitMaskingLayout<>;
using Phase2OTHitMaskingView = Phase2OTHitMaskingSoA::View;
using Phase2OTHitMaskingConstView = Phase2OTHitMaskingSoA::ConstView;

#endif
