#ifndef DataFormats_SiStripCluster_interface_SiStripHitsSoA_h
#define DataFormats_SiStripCluster_interface_SiStripHitsSoA_h

#include "DataFormats/SoATemplate/interface/SoACommon.h"
#include "DataFormats/SoATemplate/interface/SoALayout.h"

GENERATE_SOA_LAYOUT(SiStripHitsMaskingLayout,
	SOA_COLUMN(uint32_t,recHitMask), // 0 = available, 1 = used	
	SOA_COLUMN(uint32_t, detId), // which module
	SOA_COLUMN(uint32_t, clusterIndex) // flat key into DetSetVector<SiStripCluster>	
)

using SiStripHitsMaskingSoA = SiStripHitsMaskingLayout<>;
using SiStripHitsMaskingView = SiStripHitsMaskingSoA::View;
using SiStripHitsMaskingConstView = SiStripHitsMaskingSoA::ConstView;

#endif
