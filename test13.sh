rm listexec.txt prex_*_poly_proton_* prex_*_poly_neutron_* prex_*_poly_electron_*
for j in 5 10 40 100
do
    perl -pe "s/.*/\/testhadr\/TargetLength     ${j}.0 cm / if $. == 11 ; s/.*/\/outputrec\/FileName         Neutron_${j}_beam_poly / if $. == 25" < prex_20_poly_neutron.in > prex_${j}_poly_neutron.in
    perl -pe "s/.*/\/testhadr\/TargetLength     ${j}.0 cm / if $. == 11 ; s/.*/\/outputrec\/FileName         Electron_${j}_beam_poly / if $. == 25" < prex_20_poly_electron.in > prex_${j}_poly_electron.in
    perl -pe "s/.*/\/testhadr\/TargetLength     ${j}.0 cm / if $. == 11 ; s/.*/\/outputrec\/FileName         Proton_${j}_beam_poly / if $. == 25" < prex_20_poly_proton.in > prex_${j}_poly_proton.in
done
i=1
while [ $i -le 9 ]
do
    for j in 5 10 40 100
    do
	perl -pe "s/.*/\/outputrec\/FileName         Proton_beam_${j}_poly_${i}_ / if $. == 25 ; s/.*/\/gun\/energy         ${i} MeV / if $. == 28" < prex_${j}_poly_proton.in > prex_${j}_poly_proton_${i}.in
	echo "/bin/tcsh -c \"source tcshrc ; setenv PHYSLIST QGSP_BERT_HP ; nice ./targetsim  prex_${j}_poly_proton_"${i}".in \" " >> listexec.txt
    done
    i=$[$i+1]
	
done
i=1
while [ $i -le 9 ]
do
    for j in 5 10 40 100
    do
    perl -pe "s/.*/\/outputrec\/FileName         Proton_beam_${j}_poly_${i}0_ / if $. == 25 ; s/.*/\/gun\/energy         ${i}0 MeV / if $. == 28" < prex_${j}_poly_proton.in > prex_${j}_poly_proton_${i}0.in
    echo "/bin/tcsh -c \"source tcshrc ; setenv PHYSLIST QGSP_BERT_HP ; nice ./targetsim  prex_${j}_poly_proton_"${i}"0.in \" " >> listexec.txt
    done
    i=$[$i+1]
done
i=1
while [ $i -le 10 ]
do    
    for j in 5 10 40 100
    do
    perl -pe "s/.*/\/outputrec\/FileName         Proton_beam_${j}_poly_${i}00_ / if $. == 25 ; s/.*/\/gun\/energy         ${i}00 MeV / if $. == 28" < prex_${j}_poly_proton.in > prex_${j}_poly_proton_${i}00.in
    echo "/bin/tcsh -c \"source tcshrc ; setenv PHYSLIST QGSP_BERT_HP ; nice ./targetsim  prex_${j}_poly_proton_"${i}"00.in \" " >> listexec.txt
    done
    i=$[$i+1]
done


i=1
while [ $i -le 9 ]
do
    for j in 5 10 40 100
    do
    perl -pe "s/.*/\/outputrec\/FileName         Neutron_beam_${j}_poly_${i}_ / if $. == 25 ; s/.*/\/gun\/energy         ${i} MeV / if $. == 28" < prex_${j}_poly_neutron.in > prex_${j}_poly_neutron_${i}.in
    echo "/bin/tcsh -c \"source tcshrc ; setenv PHYSLIST QGSP_BERT_HP ; nice ./targetsim  prex_${j}_poly_neutron_"${i}".in \" " >> listexec.txt
    done
    i=$[$i+1]
done
i=1
while [ $i -le 9 ]
do
    for j in 5 10 40 100
    do
	perl -pe "s/.*/\/outputrec\/FileName         Neutron_beam_${j}_poly_${i}0_ / if $. == 25 ; s/.*/\/gun\/energy         ${i}0 MeV / if $. == 28" < prex_${j}_poly_neutron.in > prex_${j}_poly_neutron_${i}0.in
	echo "/bin/tcsh -c \"source tcshrc ; setenv PHYSLIST QGSP_BERT_HP ; nice ./targetsim  prex_${j}_poly_neutron_"${i}"0.in \" " >> listexec.txt
    done
    i=$[$i+1]
done
i=1
while [ $i -le 10 ]
do
    for j in 5 10 40 100
    do
    perl -pe "s/.*/\/outputrec\/FileName         Neutron_beam_${j}_poly_${i}00_ / if $. == 25 ; s/.*/\/gun\/energy         ${i}00 MeV / if $. == 28" < prex_${j}_poly_neutron.in > prex_${j}_poly_neutron_${i}00.in
    echo "/bin/tcsh -c \"source tcshrc ; setenv PHYSLIST QGSP_BERT_HP ; nice ./targetsim  prex_${j}_poly_neutron_"${i}"00.in \" " >> listexec.txt
    done
    i=$[$i+1]
done


i=1
while [ $i -le 9 ]
do
    for j in 5 10 40 100
    do
    perl -pe "s/.*/\/outputrec\/FileName         Electron_beam_${j}_poly_${i}_ / if $. == 25 ; s/.*/\/gun\/energy         ${i} MeV / if $. == 28" < prex_${j}_poly_electron.in > prex_${j}_poly_electron_${i}.in
    echo "/bin/tcsh -c \"source tcshrc ; setenv PHYSLIST QGSP_BERT_HP ; nice ./targetsim  prex_${j}_poly_electron_"${i}".in \" " >> listexec.txt
    done
    i=$[$i+1]
done
i=1
while [ $i -le 9 ]
do
    for j in 5 10 40 100
    do
    perl -pe "s/.*/\/outputrec\/FileName         Electron_beam_${j}_poly_${i}0_ / if $. == 25 ; s/.*/\/gun\/energy         ${i}0 MeV / if $. == 28" < prex_${j}_poly_electron.in > prex_${j}_poly_electron_${i}0.in
    echo "/bin/tcsh -c \"source tcshrc ; setenv PHYSLIST QGSP_BERT_HP ; nice ./targetsim  prex_${j}_poly_electron_"${i}"0.in \" " >> listexec.txt
    done
    i=$[$i+1]
done
i=1
while [ $i -le 10 ]
do
    for j in 5 10 40 100
    do
    perl -pe "s/.*/\/outputrec\/FileName         Electron_beam_${j}_poly_${i}00_ / if $. == 25 ; s/.*/\/gun\/energy         ${i}00 MeV / if $. == 28" < prex_${j}_poly_electron.in > prex_${j}_poly_electron_${i}00.in
    echo "/bin/tcsh -c \"source tcshrc ; setenv PHYSLIST QGSP_BERT_HP ; nice ./targetsim  prex_${j}_poly_electron_"${i}"00.in \" " >> listexec.txt
    done
    i=$[$i+1]
done


