// Public interface for src/gui_interface.f90

#ifndef CRITIC2_H
#define CRITIC2_H

namespace c2 {

//xx// Variables made available through host association in 
//xx// gui_interface.f90. See gui_interface.f90 for documentation.
// sticks
extern "C" struct c_stick {
  float r1[3];
  float r2[3];
  float rmid[3];
  float length;
  float thick;
  float rgb[3];
  float rot[4][4];
};

// balls
extern "C" struct c_ball {
  float r[3];
  float rad;
  float rgb[3];
};

// glboal flags
extern "C" bool isinit;
extern "C" bool ispreview;
extern "C" bool ismolecule;

// atoms
extern "C" struct c_atom {
  char name[11];
  int z;
  struct c_ball b;
};
extern "C" int nat;
extern "C" struct c_atom *at;

// bonds
extern "C" struct c_bond {
  int i1;
  int i2;
  struct c_stick s;
};
extern "C" int nbond;
extern "C" struct c_bond *bond;

// critical points
extern "C" struct c_critp {
  int type;
  char name[11];
  struct c_ball b;
};
extern "C" int ncritp;
extern "C" struct c_critp *critp;

// unit cell
extern "C" float cell_x0[3];
extern "C" float cell_lat[3][3];
extern "C" int cell_nstick;
extern "C" struct c_stick cell_s[12];

// bounding box
extern "C" float box_xmin[3];
extern "C" float box_xmax[3];
extern "C" float box_xcm[3];
extern "C" float box_xmaxlen;
extern "C" float box_xmaxclen;

// library information
extern "C" int nlib_crys;
extern "C" int nlib_mol;
extern "C" char (*lib_crys)[255];
extern "C" char (*lib_mol)[255];

// crystal seed
extern "C" struct c_crystalseed {
  int type; // 0 = molecule, 1 = crystal
  int achoice; // 0 = aa, 1 = rr
  char straa[255];
  char strbb[255];
  char strrr[255*5];
  char strat[255*1024];
  char strspg[255];
  bool molcubic;
  float molborder;
  int borunits;
  int aaunits;
  int rrunits;
  int atunits;
  int errcode;
  char errmsg[255];
};

//xx// Procedures made available in gui_interface.f90

// initialize critic2
extern "C" void critic2_initialize(void);

// end the critic2 run
extern "C" void critic2_end(void);

// read a new molecule/crystal from an external file
extern "C" void open_structure(const char **filename, int isMolecule); 

// read a new molecule/crystal from the library
extern "C" void open_structure_from_library(int nstr, int isMolecule); 

// create a structure from scratch
extern "C" int new_structure(struct c_crystalseed *useed, bool preview);

// preview a new structure 
extern "C" int preview_structure(struct c_crystalseed *useed);

// accept the previewed structure
extern "C" void accept_previewed_structure(void);

// reject the previewed structure
extern "C" void reject_previewed_structure(void);

// calculate critical points for the current field
extern "C" void call_auto(void); 

// update the data in the scene (fortran module variables) to make
// it available to the GUI 
extern "C" void update_scene(void); 

// clear the scene
extern "C" void clear_scene(bool unload); 

// get information text about the current structure
extern "C" char *get_text_info(int imode); 

// get the seed from the loaded structure
extern "C" struct c_crystalseed  get_seed_from_current_structure(void); 

// set the library file
extern "C" void set_library_file(const char **filename,int type); 

// run a critic2 command
extern "C" void run_critic2_command(char *command); 

}

#endif
