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
#include "DataFormats/TrackerRecHit2D/interface/SiStripMatchedRecHit2D.h"

#include "TrackingTools/PatternTools/interface/TrackCollectionTokens.h"

#include "RecoTracker/TransientTrackingRecHit/interface/Traj2TrackHits.h"

#include <limits>

#include "DataFormats/Phase2OTHitMaskingSoA/interface/Phase2OTHitMaskingSoA.h"
#include "DataFormats/Phase2OTHitMaskingSoA/interface/Phase2OTHitMaskingHostCollection.h"
#include "DataFormats/Phase2OTHitMaskingSoA/interface/alpaka/Phase2OTHitMaskingDeviceCollection.h"

#include "HeterogeneousCore/AlpakaInterface/interface/config.h"
#include "HeterogeneousCore/AlpakaCore/interface/alpaka/global/EDProducer.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE {

  class taylorTrackClusterRemoverPhase2 : public global::EDProducer<> {
  public:
	
	explicit taylorTrackClusterRemoverPhase2(const edm::ParameterSet& iConfig);
	~taylorTrackClusterRemoverPhase2() override = default;

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

	private:
		virtual void produce(edm::StreamID sid, device::Event& iEvent, device::EventSetup const& iSetUp) const;

		const device::EDPutToken<Phase2OTHitMaskingDevice> deviceToken_;
		const device::EDGetToken<std::vector<Phase2OTHitMaskingSoA>> Phase2OTHitMaskingToken_;
		const edm::EDGetTokenT<SiStripMatchedRecHit2D> RecHitToken_;
	};

    taylorTrackClusterRemoverPhase2::taylorTrackClusterRemoverPhase2(const edm::ParameterSet& iConfig)
		: EDProducer(iConfig),
		  deviceToken_{produces()},
		  RecHitToken_(consumes(iConfig.getParameter<edm::InputTag>("SiStripMatchedRecHit2D")))
	{
//		produces<edm::ContainerMask<edmNew::DetSetVector<HitMask>>>();
	}

    void taylorTrackClusterRemoverPhase2::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
		edm::ParameterSetDescription desc;
		desc.add<edm::InputTag>("SiStripMatchedRecHit2D", edm::InputTag("SiStripMatchedRecHit2D"));
		descriptions.addWithDefaultLabel(desc);
	}
	
	void taylorTrackClusterRemoverPhase2::produce(edm::StreamID sid, device::Event& iEvent, device::EventSetup const& iSetUp) const {
		std::cout<<"TRACK CLUSTER REMOVER"<<std::endl;
		auto queue = iEvent.queue();
		const std::vector<Phase2OTHitMaskingSoA>& hitsColl = iEvent.get(Phase2OTHitMaskingToken_);
	
		int32_t hitsSize = hitsColl.size();

		Phase2OTHitMaskingHost hostProductPhase2OTHitMasking{queue, hitsSize};
		auto& viewHostHits = hostProductPhase2OTHitMasking.view();

		std::cout<<"Si pixel cluster IDs:"<<std::endl;
		int32_t i = 0;
		for (auto& hit : hitsColl){
			viewHostHits[i].recHitMask() = i % 2;
			std::cout << viewHostHits[i].recHitMask() << std::endl;
			i++;
		}	

//		Phase2OTHitMaskingDevice deviceProductPhase2OTHitMasking{queue, hitsSize};
//		alpaka::memcpy(queue, deviceProductPhase2OTHitMasking.buffer(), hostProductPhase2OTHitMasking.buffer());
		iEvent.emplace(deviceToken_, iEvent.queue(), 0);

		
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
