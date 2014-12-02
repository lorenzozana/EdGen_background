EdGen_background
================

Background GEANT4 simulation for EdGeN (work in progress, integration with EdGen to be done)

Prerequisites
-------------
* CERN ROOT  (tested at now with version ROOT 5.34/09)
* GEANT4 (master branch works with GEant4.9.6p02; Geant4.10 branch (git checkout Geant4.10) works with Geant4.10.00.p01 ) 
* git 

Running
-------------
* compile with cmake:

1. cd EdGen_background
2. mkdir build
3. cd build
4. cmake ../
5. make
* go back to the EdGen_background directory
* ./targetsim test.in(modify the file at pleasure)
* See test13.sh as an example of create a listfile to be able to run using the multiple CPU of your machine (in case) with xjobs ( http://www.maier-komor.de/xjobs.html )

Input File
----------------
See test.in as possible input

 Target (is a cylinder)
-----------------------
* /testhadr/TargetMat        G4_W     (Target Material (GEANT4 material, or add your own in src/DetectorConstruction.cc (see inside the file for some example) )
* /testhadr/TargetRadius     10.0 cm  (Target Radius) 
* /testhadr/TargetLength     40.0 cm  (Target Length)

 Target container 
-----------------
* /testhadr/WindowMat        G4_Galactic  (Material of the container)
* /testhadr/WindowThick_r    0.01 cm    (Thickness of the container in r)      
* /testhadr/WindowThick_z    0.012 cm   (Thickness of the container in z) 

 Run with Input file 
---------------------
(root format): If not chosen, will run in the other mode, with particle gun, energy, etc. with the 
PHYSICS LIST chosen (in your environment or through this macro) 
* /testhadr/InChain          Photon  (Name of the TTree inside the file)
* /testhadr/Infile           test_collimator_photon.root  (Name of the input file)
* /run/beamOn 10000000         (How many events: If number of events are bigger than the one in the input file, the simulation will run with the current settings of PHYSICSLIST , beam particle and energy)  

 Run with GEANT4 PHYSICS LIST
------------------------------
* /gun/particle gamma 
* /gun/energy 40. GeV
* /run/beamOn 10000000

 PHYSICS LIST 
-------------
see option inside src/PhysicsList.cc (or put your favourite one in your environment variable and comment this one (ex. setenv PHYSLIST QGSP_BERT_HP )
* /testhadr/Physics          PHYSLIST

 Output
-----------
* /outputrec/FileName         Tungsten_photon_2112 (Output (root format) base name for the output file (a random number will be added (and .root) )	
* /outputrec/Particle         2 2112 211    (what you want to record in the output (ex. 2 (number of particles) 2112 211 (Particle ID (PDG) of the particle(s) recorded) ) REALLY IMPORTANT IF YOU NEED TO BUILD IN LOW CROSS SECTION PARTICLES (EXAMPLE: LOW SIZE OUTPUT FILE))

 	
