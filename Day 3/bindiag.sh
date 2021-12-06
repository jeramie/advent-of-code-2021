 #!/bin/bash

# challenge 1
while read -r line; do ((total++)) && for((i=0; i<${#line}; i++)) do ((counts[$i]+=${line:$i:1}));  done done < input.txt
for((i=0; i<${#counts[@]}; i++)) do gamma+="$(( counts[$i] > $(( total / 2 )) ? 1 : 0))"; done
echo "Submarine power consumption: $((2#$gamma * 2#$(echo $gamma | tr 01 10)))"

# challenge 2
while read -r line; do inputs+=("$line"); done < input.txt

find_rating() {
    common=$1
    shift
    arr=("$@")
    for ((i = 0; i < ${#counts[@]}; i++))
    do
        if [ ${#arr[@]} -gt 1 ]
        then
            total=0
            for l in ${arr[@]}; do (( total += ${l:$i:1} )); done
            arr=( $( for r in ${arr[@]} ; do echo $r ; done | egrep "^.{$i}$((total >= (${#arr[@]} + 2 -1) / 2 ? $common : (1 - $common)))" ) )
        fi
    done
    echo "${arr[0]}"
}

oxygen=$(find_rating 1 "${inputs[@]}")
co2=$(find_rating 0 "${inputs[@]}")

echo "Life support rating: $(( 2#${oxygen} * 2#${co2} ))"
