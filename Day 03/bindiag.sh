 #!/bin/bash

# challenge 1
while read -r line; do ((total++)) && for((i=0; i<${#line}; i++)) do ((counts[$i]+=${line:$i:1}));  done  done < input.txt
for((i=0; i<${#counts[@]}; i++)) do gamma+="$(( counts[$i] > $(( total / 2 )) ? 1 : 0))"; done
echo "Submarine power consumption: $((2#$gamma * 2#$(echo $gamma | tr 01 10)))"

# challenge 2
while read -r line; do oxygen+=("$line") && co2+=("$line"); done < input.txt

for ((i = 0; i < ${#counts[@]}; i++))
do
    if [ ${#oxygen[@]} -gt 1 ]
    then
        bit=0
        for((o = 0; o < ${#oxygen[@]}; o++)) do (( bit += ${oxygen[$o]:$i:1} )); done
        bit=$(( bit == 1 || bit >= (${#oxygen[@]} + 2 -1) / 2 ? 1 : 0 ))
        oxygen=( $( for r in ${oxygen[@]} ; do echo $r ; done | egrep "^.{$i}$bit" ) )
    fi

    if [ ${#co2[@]} -gt 1 ]
    then
        bit=0
        for((o = 0; o < ${#co2[@]}; o++)) do (( bit += ${co2[$o]:$i:1} )); done
        bit=$(( (bit == 0 || bit >= (${#co2[@]} + 2 - 1) / 2)  ? 0 : 1 ))
        co2=( $( for r in ${co2[@]} ; do echo $r ; done | egrep "^.{$i}$bit" ) )
    fi
done

echo "Life support rating: $(( 2#${oxygen[0]} * 2#${co2[@]} ))"

