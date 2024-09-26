#!/bin/bash

# List of Diablo 2 runes
runes=("El" "Eld" "Tir" "Nef" "Eth" "Ith" "Tal" "Ral" "Ort" "Thul" "Amn" "Sol" "Shael" "Dol" "Hel" "Io" "Lum" "Ko" "Fal" "Lem" "Pul" "Um" "Mal" "Ist" "Gul" "Vex" "Ohm" "Lo" "Sur" "Ber" "Jah" "Cham" "Zod")

rune_list="";
# Iterate over each rune and download the image
for rune in "${runes[@]}"; do
    lowercase_rune=$(echo "$rune" | tr '[:upper:]' '[:lower:]')
    rune_list+="<file>runes/${lowercase_rune}_rune.png.webp</file>"$'\n'

done

echo "$rune_list";