#/bin/bash
F=$1
tr ',' ' ' <$F>out1
tr '\\n' '\n' <out1> out2
sed '/^$/d' out2> out3
tr ' ' ',' <out3> out4
cp out4 $F
rm -rf ./out*

