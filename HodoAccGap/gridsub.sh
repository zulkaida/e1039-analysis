#!/bin/bash

jobname=$1

do_sub=$2
if [ $do_sub == 1 ]; then
  echo "grid!"
else
  echo "local!"
fi

njobs=$3
echo "njobs=$njobs"

macros=/e906/app/users/yuhw/seaquest-analysis/HodoAccGap

if [ $do_sub == 1 ]; then
work=/pnfs/e906/persistent/users/yuhw/HodoAccGap/$jobname
else
work=$macros/scratch
fi

mkdir -p $work
chmod -R 01755 $work

cd $macros
tar -czvf $work/input.tar.gz *.C *.cfg *.opts
cd -

for (( id=1; id<=$njobs; id++ ))
do  
  mkdir -p $work/$id/log
  mkdir -p $work/$id/out
  chmod -R 01755 $work/$id

  rsync -av $macros/gridrun.sh $work/$id

  cmd="jobsub_submit"
  cmd="$cmd -g --OS=SL6 --use_gftp --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC -e IFDHC_VERSION --expected-lifetime='short'"
  cmd="$cmd -L $work/$id/log/log.txt"
  cmd="$cmd -f $work/input.tar.gz"
  cmd="$cmd -d OUTPUT $work/$id/out"
  cmd="$cmd file://`which $work/$id/gridrun.sh`"
  echo $cmd

  if [ $do_sub == 1 ]; then
    $cmd
  else
    mkdir -p $work/$id/input
    rsync -av $work/input.tar.gz $work/$id/input
    cd $work/$id/
    $work/$id/gridrun.sh | tee $work/$id/log/log.txt
    rsync -av *.root $work/$id/out
    cd -
  fi
done
