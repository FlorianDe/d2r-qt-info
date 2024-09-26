#!/bin/bash

# Directory to save downloaded images
DOWNLOAD_DIR="rune_images"
mkdir -p "$DOWNLOAD_DIR"

# List of Diablo 2 runes
runes=("El" "Eld" "Tir" "Nef" "Eth" "Ith" "Tal" "Ral" "Ort" "Thul" "Amn" "Sol" "Shael" "Dol" "Hel" "Io" "Lum" "Ko" "Fal" "Lem" "Pul" "Um" "Mal" "Ist" "Gul" "Vex" "Ohm" "Lo" "Sur" "Ber" "Jah" "Cham" "Zod")

# Base URL with placeholder
BASE_URL="https://www.purediablo.com/wp-content/uploads/2021/04"

# Iterate over each rune and download the image
for rune in "${runes[@]}"; do
    lowercase_rune=$(echo "$rune" | tr '[:upper:]' '[:lower:]')
    # Replace placeholder with actual rune
    url="${BASE_URL}/${lowercase_rune}_rune.png.webp"
    
    # Download the image
    echo "Downloading $url"
    curl -L "$url" -o "$DOWNLOAD_DIR/${lowercase_rune}_rune.png.webp"
    
    # Check if the file was downloaded successfully
    if [ $? -eq 0 ]; then
        echo "Downloaded ${lowercase_rune}_rune.png.webp successfully."
    else
        echo "Failed to download ${lowercase_rune}_rune.png.webp."
    fi

    sleep 1
done

echo "Download complete."