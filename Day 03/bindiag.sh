 #!/bin/bash

while read -r line; do ((total++)) && for((i=0; i<${#line}; i++)) do ((counts[$i]+=${line:$i:1}));  done  done < input.txt
for((i=0; i<${#counts[@]}; i++)) do gamma+="$(( counts[$i] > $(( total / 2 )) ? 1 : 0))"; done
echo $((2#$gamma * 2#$(echo $gamma | tr 01 10)))
