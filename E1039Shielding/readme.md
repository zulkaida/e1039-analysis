
### clone the analysis repository
```
git clone https://github.com/E1039-Collaboration/seaquest-analysis.git
```

### run the Fun4All  shielding macro into the local gpvm machine:
```
cd <path-to-/seaquest-analysis/E1039Shielding>
root -l Fun4HodoAccGap.C
```
Several root files are generated.
The 'trk_eval.root' contains the information from the evaluator [`TrkEval`]. You may open that file and check the contents.

```
$root -l trk_eval.root 
root [0] 
Attaching file trk_eval.root as _file0...
root [1] .ls
TFile**		trk_eval.root	
 TFile*		trk_eval.root	
  KEY: TTree	T;1	TrkEval
```

### analysis
This root file 'trk_eval.root' needs to be attached in the macro  for analysis. The analysis macro  `ana.C` is for acceptance vs hole size studies and the macro `loop_ana.C` is for acceptance vs dimuon mass study. You may test it using the example data from the trk_eval.root.
```
root -l
root [0] .L ana.C 
root [1] drawRelAcc()
root [2] drawAccPhi()
```

### run the Fun4All  shielding macro in Fermilab grid:

```
./gridsub.sh opening 1 100 1000 1
```
### Check the status and  output root file

```
jobsub_q --user=<your-user-id>
cd /pnfs/e906/persistent/users/<your-user-id>/E1039Shielding

```
### Collect all the root files in a single root file

```hadd strk_eval.root /pnfs/e906/persistent/users/<your-user-id>/E1039Shielding/shield_target98/*/out/trk_eval.root ```

### analysis
This root file 'trk_eval.root' needs to be attached in the macro  for analysis. The analysis macro  `ana.C` is for acceptance vs hole size studies and the macro `loop_ana.C` is for acceptance vs dimuon mass study. You may test it using the example data.
```
root -l
root [0] .L ana.C 
root [1] drawRelAcc()
root [2] drawAccPhi()
```

