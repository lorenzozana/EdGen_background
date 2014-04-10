#ifndef __EventData_h
#define __EventData_h

#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"

struct eventsdata {


  int n_evt; // number of events
  int track_id; // primary, secondary, etc.
  int part_id;
  double enedep_tg;
  double zdep_tg;
  double ener ;
  double mom_x;
  double mom_y;
  double mom_z;
  double vert_x;
  double vert_y;
  double vert_z;
  double mass;
  double en_sideleak_neut; //16
  double en_forwleak_neut; //17
  double en_backleak_neut; //18
  double en_leak_prot; //19
  double en_leak_chargpion; //20
  double en_deptg_beam; //23
  double en_EMdeptg_beam; //24
  double en_pideptg_beam; //25
  double en_protdeptg_beam; //26
  

};

class EventData {
    public:
	EventData();
	~EventData();

	void SetEventData( eventsdata d ){ fData = d; }
	eventsdata GetEventData(){ return fData; }

    private:
	eventsdata fData;
	
    public:

};
#endif//__EventData_h
