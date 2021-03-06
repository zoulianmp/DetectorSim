#!/bin/bash
export G4WORKDIR=/home/murffer/G4DetectorSim/LightYeildEDep

#
# Setting up the job
#
function JobSetup()
{
  echo "#!/bin/bash" > job
  echo "#PBS -q gen1" >> job
  echo "#PBS -V" >> job
  echo "#PBS -l nodes=1:ppn=2" >> job
  echo "export PBS_O_WORKDIR=$G4WORKDIR" >> job
  echo 'cd $PBS_O_WORKDIR' >> job
}

function runGamma()
{
  JobSetup
  echo "exec $G4WORKDIR/build/lightYield $G4WORKDIR/macros/gRun.mac > GammaOutput.txt" >> job
  mv job gSub.qsub
  qsub gSub.qsub
}
function runNeutron()
{
  JobSetup
  echo "exec $G4WORKDIR/build/lightYield $G4WORKDIR/macros/nRun.mac > NeutronOutput.txt" >> job
  mv job nSub.qsub
  qsub nSub.qsub
}

# Running the jobs
runGamma
runNeutron
# Cleaning up
rm nSub.qsub
rm gSub.qsub

