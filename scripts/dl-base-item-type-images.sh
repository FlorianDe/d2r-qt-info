#!/bin/bash

# Directory to save downloaded images
DOWNLOAD_DIR="../res/images/item_base_types"
mkdir -p "$DOWNLOAD_DIR"

#weapons=("Weapons" "Axes" "Staves" "Maces" "Clubs" "Hammers" "Scepters" "Swords" "Daggers" "Spears" "Polearms" "Two-Handed Staves" "Bows" "Crossbows" "Claws" "Orbs" "Amazon Bows" "Amazon Spears" "Armor" "Helms" "Normal Helms" "Druid Helms" "Barbarian Helms" "Circlets" "Shields" "Normal Shields" "Paladin Shields" "Shrunken Heads")
weapons=("polearms" "spears" "claws" "base" "swords" "hammerstwo" "clubs" "sceptres" "maces" "wands" "staves" "armors" "helms" "targes" "shields" "daggers" "spears" "crossbows" )

BASE_URL="https://diablo2.io/styles/zulu/theme/images/icons"

for weapon in "${weapons[@]}"; do
    lowercase_weapon=$(echo "$weapon" | tr '[:upper:]' '[:lower:]')

    url="${BASE_URL}/${lowercase_weapon}2x.png"
    
    # Download the image
    echo "Downloading $url"
    curl --fail --silent --location "$url" -o "$DOWNLOAD_DIR/${lowercase_weapon}.png"
    
    # Check if the file was downloaded successfully
    if [ $? -eq 0 ]; then
        echo "Downloaded ${lowercase_weapon}.png successfully."
    else
        echo "Failed to download ${lowercase_weapon}.png."
    fi

    sleep 1
done

echo "Download complete."