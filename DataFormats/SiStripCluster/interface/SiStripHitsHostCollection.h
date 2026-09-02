#ifndef DataFormats_SiStripCluster_interface_SiStripHitsHostCollection_h
#define DataFormats_SiStripCluster_interface_SiStripHitsHostCollection_h

#include "DataFormats/Portable/interface/PortableHostCollection.h"
#include "DataFormats/SiStripCluster/interface/SiStripHitsSoA.h"

using SiStripHitsMaskingHost = PortableHostCollection<SiStripHitsMaskingSoA>;

#endif
