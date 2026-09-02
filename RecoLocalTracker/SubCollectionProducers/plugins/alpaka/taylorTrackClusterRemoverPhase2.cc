#include "FWCore/Framework/interface/global/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/Phase2TrackerCluster/interface/Phase2TrackerCluster1D.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/Provenance/interface/ProductID.h"
#include "DataFormats/Common/interface/ContainerMask.h"

#include "DataFormats/DetId/interface/DetId.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackerRecHit2D/interface/ClusterRemovalInfo.h"
#include "DataFormats/TrackerRecHit2D/interface/VectorHit.h"

#include "TrackingTools/PatternTools/interface/TrackCollectionTokens.h"

#include "RecoTracker/TransientTrackingRecHit/interface/Traj2TrackHits.h"

#include <limits>

#include "DataFormats/SiStripCluster/interface/SiStripHitsSoA.h"
#include "DataFormats/SiStripCluster/interface/SiStripHitsHostCollection.h"
#include "DataFormats/SiStripCluster/interface/SiStripHitsDeviceCollection.h"
#include "DataFormats/SiStripCluster/interface/alpaka/SiStripHitsSoACollection.h"

#include "HeterogeneousCore/AlpakaInterface/interface/config.h"
#include "HeterogeneousCore/AlpakaCore/interface/alpaka/global/EDProducer.h"
//#include ""

namespace ALPAKA_ACCELERATOR_NAMESPACE {

  class taylorTrackClusterRemoverPhase2 : public global::EDProducer<> {
  public:
	
	explicit taylorTrackClusterRemoverPhase2(const edm::ParameterSet& iConfig);
	~taylorTrackClusterRemoverPhase2() override = default;

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

	private:
		virtual void produce(edm::StreamID sid, device::Event& iEvent, device::EventSetup const& iSetUp) const;

		const device::EDPutToken<SiStripHitsMaskingDevice<Device>> deviceToken_;
		const device::EDGetToken<std::vector<SiStripHitsMaskingSoA>> siStripHitsToken_;
//		const device::EDPutToken<SiStripHitsMaskingDevice<Device>> deviceToken_;
//		const device::EDGetToken<SiStripHitsMaskingSoA> siStripToken_; 
		// idk if the second one is needed anymore since we're doing rec hits now instead of pixel and strip hits like before
	};

    taylorTrackClusterRemoverPhase2::taylorTrackClusterRemoverPhase2(const edm::ParameterSet& iConfig)
		: EDProducer(iConfig),
		  deviceToken_{produces()},
		  siStripHitsToken_(consumes(iConfig.getParameter<edm::InputTag>("siStripHitsSoA")))//,//,
//		  produces<edm::ContainerMask<edmNew::DetSetVector<SiPixelCluster>>>
		 // siStripToken_(consumes(iConfig.getParameter<edm::InputTag>("siStripSoA")))
	{}

    void taylorTrackClusterRemoverPhase2::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
		edm::ParameterSetDescription desc;
		desc.add<edm::InputTag>("siStripHitsMaskingSoA", edm::InputTag("siStripHitsMaskingSoA"));
//		desc.add<edm::InputTag>("phase2OTClusters", edm::InputTag("siPhase2Clusters"));
		descriptions.addWithDefaultLabel(desc);
	}
	
	void taylorTrackClusterRemoverPhase2::produce(edm::StreamID sid, device::Event& iEvent, device::EventSetup const& iSetUp) const {
		std::cout<<"TRACK CLUSTER REMOVER"<<std::endl;
		auto queue = iEvent.queue();
		const std::vector<SiStripHitsMaskingSoA>& stripHitsColl = iEvent.get(siStripHitsToken_);
		//const auto& stripColl = iEvent.get(siStripToken_);
	
		int32_t stripHitsSize = stripHitsColl.size();

		SiStripHitsMaskingHost hostProductSiStripHits{queue, stripHitsSize};
		auto& viewHostStripHits = hostProductSiStripHits.view();

		std::cout<<"Si pixel cluster IDs:"<<std::endl;
		int32_t i = 0;
		for (auto& stripHit : stripHitsColl){
			viewHostStripHits[i].recHitMask() = i % 2;
			std::cout << viewHostStripHits[i].recHitMask() << std::endl;
		}	

		SiStripHitsMaskingDevice deviceProductSiStripHits{queue, stripHitsSize};
		alpaka::memcpy(queue, deviceProductSiStripHits.buffer(), hostProductSiStripHits.buffer());
		iEvent.emplace(deviceToken_, std::move(deviceProductSiStripHits));
//old:		edm::Handle<edmNew::DetSetVector<SiPixelCluster>> pixelClusters;	
//		edm::Handle<edmNew::DetSetVector<Phase2TrackerCluster1D>> phase2OTClusters;

//		std::vector<bool> collectedPixels;
//		std::vector<bool> collectedPhase2OTs;

//		auto sipixelVec = iEvent.get(pixelClusters_);
//		int32_t siPixelSize = sipixelVec.size();

//		Phase2TrackerClusterHostCollection hostSiPixel{siPixelSize, iEvent.queue()};
//		auto& viewSiPixelCluster = hostSiPixel.view();

//		std::cout<<"Si pixel cluster IDs:"<<std::endl;
//		int32_t i = 0;
//		for (auto& sipixel : sipixelVec){
//			viewSiPixelCluster[i].siPixelClusterID() = i;
//			std::cout<<viewSiPixelCluster[i].siPixelClusterID()<<std::endl;		
		
	}

//  private:
//    using PixelMaskContainer = edm::ContainerMask<edmNew::DetSetVector<SiPixelCluster>>;
//    using Phase2OTMaskContainer = edm::ContainerMask<edmNew::DetSetVector<Phase2TrackerCluster1D>>;

//    const edm::EDGetTokenT<edmNew::DetSetVector<SiPixelCluster>> pixelClusters_;
//    const edm::EDGetTokenT<edmNew::DetSetVector<Phase2TrackerCluster1D>> phase2OTClusters_;

//    edm::EDGetTokenT<PixelMaskContainer> oldPxlMaskToken_;
//    edm::EDGetTokenT<Phase2OTMaskContainer> oldPh2OTMaskToken_;

}  // namespace ALPAKA_ACCELERATOR_NAMESPACE

#include "HeterogeneousCore/AlpakaCore/interface/alpaka/MakerMacros.h"
DEFINE_FWK_ALPAKA_MODULE(taylorTrackClusterRemoverPhase2);
