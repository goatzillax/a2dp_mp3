# a2dp_mp3
test case for mp3->a2dp streaming


samples converted with:

```
ffmpeg -i $f -af "aformat=sample_fmts=s16:sample_rates=44100" -ac 2 -b:a 96k `basename $f`
```
