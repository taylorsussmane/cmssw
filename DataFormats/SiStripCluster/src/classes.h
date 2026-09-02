#ifndef DATAFORMATS_SISTRIPCLUSTER_CLASSES_H
#define DATAFORMATS_SISTRIPCLUSTER_CLASSES_H

#include "DataFormats/Common/interface/Wrapper.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/SiStripCluster/interface/SiStripClustersSOA.h"
#include "DataFormats/SiStripCluster/interface/SiStripApproximateCluster.h"
#include "DataFormats/SiStripCluster/interface/SiStripApproximateCluster_v1.h"
#include "DataFormats/SiStripCluster/interface/SiStripApproximateClusterCollection.h"
#include "DataFormats/SiStripCluster/interface/SiStripApproximateClusterCollection_v1.h"
#include "DataFormats/SiStripCluster/interface/SiStripHitsSoA.h"
#include "DataFormats/SiStripCluster/interface/SiStripHitsHostCollection.h"
//#include "DataFormats/SiStripCluster/interface/SiStripHitsDeviceCollection.h"
#include "DataFormats/Common/interface/ContainerMask.h"

//edm::Wrapper<SiStripHitsMaskingHost> wrapperHostColl;
//struct dictionary {
//	SiStripHitsMaskingSoA soa;
//	SiStripHitsMaskingSoA::View view;
//	SiStripHitsMaskingSoA::ConstView constView;
//
//	SiStripHitsMaskingHost hostColl;
//	edm::Wrapper<SiStripHitsMaskingHost> wrapperHostColl;
//};

#endif  // SISTRIPCLUSTER_CLASSES_H

