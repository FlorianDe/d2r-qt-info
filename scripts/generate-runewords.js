const { log } = require("console");
const fs = require("fs");

const runes = [
  { name: "El", tier: 1 },
  { name: "Eld", tier: 1 },
  { name: "Tir", tier: 1 },
  { name: "Nef", tier: 1 },
  { name: "Eth", tier: 1 },
  { name: "Ith", tier: 1 },
  { name: "Tal", tier: 1 },
  { name: "Ral", tier: 1 },
  { name: "Ort", tier: 1 },
  { name: "Thul", tier: 1 },
  { name: "Amn", tier: 1 },
  { name: "Sol", tier: 2 },
  { name: "Shael", tier: 2 },
  { name: "Dol", tier: 2 },
  { name: "Hel", tier: 2 },
  { name: "Io", tier: 2 },
  { name: "Lum", tier: 2 },
  { name: "Ko", tier: 2 },
  { name: "Fal", tier: 2 },
  { name: "Lem", tier: 2 },
  { name: "Pul", tier: 2 },
  { name: "Um", tier: 2 },
  { name: "Mal", tier: 3 },
  { name: "Ist", tier: 3 },
  { name: "Gul", tier: 3 },
  { name: "Vex", tier: 3 },
  { name: "Ohm", tier: 3 },
  { name: "Lo", tier: 3 },
  { name: "Sur", tier: 3 },
  { name: "Ber", tier: 3 },
  { name: "Jah", tier: 3 },
  { name: "Cham", tier: 3 },
  { name: "Zod", tier: 3 },
];

const rws = [
  /* 1.09 */
  {
    title: "Ancient's Pledge",
    runes: ["Ral", "Ort", "Tal"],
    level: 21,
    ttypes: ["Shields"],
  },
  {
    title: "Black",
    runes: ["Thul", "Io", "Nef"],
    level: 35,
    ttypes: ["Clubs", "Hammers", "Maces"],
  },
  {
    title: "Fury",
    runes: ["Jah", "Gul", "Eth"],
    level: 65,
    ttypes: ["Melee Weapons"],
  },
  {
    title: "Holy Thunder",
    runes: ["Eth", "Ral", "Ort", "Tal"],
    level: 21,
    ttypes: ["Scepters"],
  },
  {
    title: "Honor",
    runes: ["Amn", "El", "Ith", "Tir", "Sol"],
    level: 27,
    ttypes: ["Melee Weapons"],
  },
  {
    title: "King's Grace",
    runes: ["Amn", "Ral", "Thul"],
    level: 25,
    ttypes: ["Swords", "Scepters"],
  },
  {
    title: "Leaf",
    runes: ["Tir", "Ral"],
    level: 19,
    ttypes: ["Staves"],
    tinfos: "(Not Orbs/Wands)",
  },
  {
    title: "Lionheart",
    runes: ["Hel", "Lum", "Fal"],
    level: 41,
    ttypes: ["Body Armors"],
  },
  {
    title: "Lore",
    runes: ["Ort", "Sol"],
    level: 27,
    ttypes: ["Helms"],
  },
  {
    title: "Malice",
    runes: ["Ith", "El", "Eth"],
    level: 15,
    ttypes: ["Melee Weapons"],
  },
  {
    title: "Melody",
    runes: ["Shael", "Ko", "Nef"],
    level: 39,
    ttypes: ["Missile Weapons"],
  },
  {
    title: "Memory",
    runes: ["Lum", "Io", "Sol", "Eth"],
    level: 37,
    ttypes: ["Staves"],
    tinfos: "(Not Orbs/Wands)",
  },
  {
    title: "Nadir",
    runes: ["Nef", "Tir"],
    level: 13,
    ttypes: ["Helms"],
  },
  {
    title: "Radiance",
    runes: ["Nef", "Sol", "Ith"],
    level: 27,
    ttypes: ["Helms"],
  },
  {
    title: "Rhyme",
    runes: ["Shael", "Eth"],
    level: 29,
    ttypes: ["Shields"],
  },
  {
    title: "Silence",
    runes: ["Dol", "Eld", "Hel", "Ist", "Tir", "Vex"],
    level: 55,
    ttypes: ["Weapons"],
  },
  {
    title: "Smoke",
    runes: ["Nef", "Lum"],
    level: 37,
    ttypes: ["Body Armors"],
  },
  {
    title: "Stealth",
    runes: ["Tal", "Eth"],
    level: 17,
    ttypes: ["Body Armors"],
  },
  {
    title: "Steel",
    runes: ["Tir", "El"],
    level: 13,
    ttypes: ["Swords", "Axes", "Maces"],
  },
  {
    title: "Strength",
    runes: ["Amn", "Tir"],
    level: 25,
    ttypes: ["Melee Weapons"],
  },
  {
    title: "Venom",
    runes: ["Tal", "Dol", "Mal"],
    level: 49,
    ttypes: ["Weapons"],
  },
  {
    title: "Wealth",
    runes: ["Lem", "Ko", "Tir"],
    level: 43,
    ttypes: ["Body Armors"],
  },
  {
    title: "White",
    runes: ["Dol", "Io"],
    level: 35,
    ttypes: ["Wands"],
    tinfos: "(Necromancer)",
  },
  {
    title: "Zephyr",
    runes: ["Ort", "Eth"],
    level: 21,
    ttypes: ["Missile Weapons"],
  },
  /* 1.10 */
  {
    title: "Beast",
    runes: ["Ber", "Tir", "Um", "Mal", "Lum"],
    level: 63,
    ttypes: ["Axes", "Scepters", "Hammers"],
    version: '1.10',
  },
  {
    title: "Bramble",
    runes: ["Ral", "Ohm", "Sur", "Eth"],
    level: 61,
    ttypes: ["Body Armors"],
    version: '1.10',
  },
  {
    title: "Breath of the Dying",
    runes: ["Vex", "Hel", "El", "Eld", "Zod", "Eth"],
    level: 69,
    ttypes: ["Weapons"],
    version: '1.10',
  },
  {
    title: "Call to Arms",
    runes: ["Amn", "Ral", "Mal", "Ist", "Ohm"],
    level: 57,
    ttypes: ["Weapons"],
    version: '1.10',
  },
  {
    title: "Chaos",
    runes: ["Fal", "Ohm", "Um"],
    level: 57,
    ttypes: ["Claws"],
    tinfos: "(Assassin)",
    version: '1.10',
  },
  {
    title: "Chains of Honor",
    runes: ["Dol", "Um", "Ber", "Ist"],
    level: 63,
    ttypes: ["Body Armors"],
    version: '1.10',
  },
  {
    title: "Crescent Moon",
    runes: ["Shael", "Um", "Tir"],
    level: 47,
    ttypes: ["Axes", "Swords", "Polearms"],
    version: '1.10',
  },
  {
    title: "Delirium",
    runes: ["Lem", "Ist", "Io"],
    level: 51,
    ttypes: ["Helms"],
    version: '1.10',
  },
  {
    title: "Doom",
    runes: ["Hel", "Ohm", "Um", "Lo", "Cham"],
    level: 67,
    ttypes: ["Axes", "Polearms", "Hammers"],
    version: '1.10',
  },
  {
    title: "Duress",
    runes: ["Shael", "Um", "Thul"],
    level: 47,
    ttypes: ["Body Armors"],
    version: '1.10',
  },
  {
    title: "Enigma",
    runes: ["Jah", "Ith", "Ber"],
    level: 65,
    ttypes: ["Body Armors"],
    version: '1.10',
  },
  {
    title: "Eternity",
    runes: ["Amn", "Ber", "Ist", "Sol", "Sur"],
    level: 63,
    ttypes: ["Melee Weapons"],
    version: '1.10',
  },
  {
    title: "Exile",
    runes: ["Vex", "Ohm", "Ist", "Dol"],
    level: 57,
    ttypes: ["Paladin Shields"],
    tinfos: "(Paladin)",
    version: '1.10',
  },
  {
    title: "Famine",
    runes: ["Fal", "Ohm", "Ort", "Jah"],
    level: 65,
    ttypes: ["Axes", "Hammers"],
    version: '1.10',
  },
  {
    title: "Gloom",
    runes: ["Fal", "Um", "Pul"],
    level: 47,
    ttypes: ["Body Armors"],
    version: '1.10',
  },
  {
    title: "Hand of Justice",
    runes: ["Sur", "Cham", "Amn", "Lo"],
    level: 67,
    ttypes: ["Weapons"],
    version: '1.10',
  },
  {
    title: "Heart of the Oak",
    runes: ["Ko", "Vex", "Pul", "Thul"],
    level: 55,
    ttypes: ["Staves", "Maces"],
    version: '1.10',
  },
  {
    title: "Kingslayer",
    runes: ["Mal", "Um", "Gul", "Fal"],
    level: 53,
    ttypes: ["Swords", "Axes"],
    version: '1.10',
  },
  {
    title: "Passion",
    runes: ["Dol", "Ort", "Eld", "Lem"],
    level: 43,
    ttypes: ["Weapons"],
    version: '1.10',
  },
  {
    title: "Prudence",
    runes: ["Mal", "Tir"],
    level: 49,
    ttypes: ["Body Armors"],
    version: '1.10',
  },
  {
    title: "Sanctuary",
    runes: ["Ko", "Ko", "Mal"],
    level: 49,
    ttypes: ["Shields"],
    version: '1.10',
  },
  {
    title: "Splendor",
    runes: ["Eth", "Lum"],
    level: 37,
    ttypes: ["Shields"],
    version: '1.10',
  },
  {
    title: "Stone",
    runes: ["Shael", "Um", "Pul", "Lum"],
    level: 47,
    ttypes: ["Body Armors"],
    version: '1.10',
  },
  {
    title: "Wind",
    runes: ["Sur", "El"],
    level: 61,
    ttypes: ["Melee Weapons"],
    version: '1.10',
  },
  /* 1.10 LADDER */
  {
    title: "Brand",
    runes: ["Jah", "Lo", "Mal", "Gul"],
    level: 65,
    ttypes: ["Missile Weapons"],
    version: '1.10',
  },
  {
    title: "Death",
    runes: ["Hel", "El", "Vex", "Ort", "Gul"],
    level: 55,
    ttypes: ["Swords", "Axes"],
    version: '1.10',
  },
  {
    title: "Destruction",
    runes: ["Vex", "Lo", "Ber", "Jah", "Ko"],
    level: 65,
    ttypes: ["Polearms", "Swords"],
    version: '1.10',
  },
  {
    title: "Dragon",
    runes: ["Sur", "Lo", "Sol"],
    level: 61,
    ttypes: ["Body Armors", "Shields"],
    version: '1.10',
  },
  {
    title: "Dream",
    runes: ["Io", "Jah", "Pul"],
    level: 65,
    ttypes: ["Helms", "Shields"],
  },
  {
    title: "Edge",
    runes: ["Tir", "Tal", "Amn"],
    level: 25,
    ttypes: ["Missile Weapons"],
    version: '1.10',
  },
  {
    title: "Faith",
    runes: ["Ohm", "Jah", "Lem", "Eld"],
    level: 65,
    ttypes: ["Missile Weapons"],
    version: '1.10',
  },
  {
    title: "Fortitude",
    runes: ["El", "Sol", "Dol", "Lo"],
    level: 59,
    ttypes: ["Weapons", "Body Armors"],
    version: '1.10',
  },
  {
    title: "Grief",
    runes: ["Eth", "Tir", "Lo", "Mal", "Ral"],
    level: 59,
    ttypes: ["Swords", "Axes"],
    version: '1.10',
  },
  {
    title: "Harmony",
    runes: ["Tir", "Ith", "Sol", "Ko"],
    level: 39,
    ttypes: ["Missile Weapons"],
    version: '1.10',
  },
  {
    title: "Ice",
    runes: ["Amn", "Shael", "Jah", "Lo"],
    level: 65,
    ttypes: ["Missile Weapons"],
    version: '1.10',
  },
  {
    title: "Infinity",
    runes: ["Ber", "Mal", "Ber", "Ist"],
    level: 63,
    ttypes: ["Polearms", "Spears"],
    version: '1.10',
  },
  {
    title: "Insight",
    runes: ["Ral", "Tir", "Tal", "Sol"],
    level: 27,
    ttypes: ["Missile Weapons", "Polearms", "Staves"],
    version: '1.10',
  },
  {
    title: "Last Wish",
    runes: ["Jah", "Mal", "Jah", "Sur", "Jah", "Ber"],
    level: 65,
    ttypes: ["Swords", "Hammers", "Axes"],
    version: '1.10',
  },
  {
    title: "Lawbringer",
    runes: ["Amn", "Lem", "Ko"],
    level: 43,
    ttypes: ["Swords", "Hammers", "Scepters"],
    version: '1.10',
  },
  {
    title: "Oath",
    runes: ["Shael", "Pul", "Mal", "Lum"],
    level: 49,
    ttypes: ["Swords", "Axes", "Maces"],
    version: '1.10',
  },
  {
    title: "Obedience",
    runes: ["Hel", "Ko", "Thul", "Eth", "Fal"],
    level: 41,
    ttypes: ["Polearms", "Spears"],
    version: '1.10',
  },
  {
    title: "Phoenix",
    runes: ["Vex", "Vex", "Lo", "Jah"],
    level: 65,
    ttypes: ["Weapons", "Shields"],
    version: '1.10',
  },
  {
    title: "Pride",
    runes: ["Cham", "Sur", "Io", "Lo"],
    level: 67,
    ttypes: ["Polearms", "Spears"],
    version: '1.10',
  },
  {
    title: "Rift",
    runes: ["Hel", "Ko", "Lem", "Gul"],
    level: 53,
    ttypes: ["Polearms", "Scepters"],
    version: '1.10',
  },
  {
    title: "Spirit",
    runes: ["Tal", "Thul", "Ort", "Amn"],
    level: 25,
    ttypes: ["Swords", "Shields"],
    version: '1.10',
  },
  {
    title: "Voice of Reason",
    runes: ["Lem", "Ko", "El", "Eld"],
    level: 43,
    ttypes: ["Swords", "Maces"],
    version: '1.10',
  },
  {
    title: "Wrath",
    runes: ["Pul", "Lum", "Ber", "Mal"],
    level: 63,
    ttypes: ["Missile Weapons"],
    version: '1.10',
  },
  /* 1.11 */
  {
    title: "Bone",
    runes: ["Sol", "Um", "Um"],
    level: 47,
    ttypes: ["Body Armors"],
    tinfos: "(Necromancer)",
    version: '1.11',
  },
  {
    title: "Enlightenment",
    runes: ["Pul", "Ral", "Sol"],
    level: 45,
    ttypes: ["Body Armors"],
    tinfos: "(Sorceress)",
    version: '1.11',
  },
  {
    title: "Myth",
    runes: ["Hel", "Amn", "Nef"],
    level: 25,
    ttypes: ["Body Armors"],
    tinfos: "(Barbarian)",
    version: '1.11',
  },
  {
    title: "Peace",
    runes: ["Shael", "Thul", "Amn"],
    level: 29,
    ttypes: ["Body Armors"],
    tinfos: "(Amazon)",
    version: '1.11',
  },
  {
    title: "Principle",
    runes: ["Ral", "Gul", "Eld"],
    level: 53,
    ttypes: ["Body Armors"],
    tinfos: "(Paladin)",
    version: '1.11',
  },
  {
    title: "Rain",
    runes: ["Ort", "Mal", "Ith"],
    level: 49,
    ttypes: ["Body Armors"],
    tinfos: "(Druid)",
    version: '1.11',
  },
  {
    title: "Treachery",
    runes: ["Shael", "Thul", "Lem"],
    level: 43,
    ttypes: ["Body Armors"],
    tinfos: "(Assassin)",
    version: '1.11',
  },
  /* D2R 2.4 */
  {
    title: "Plague",
    runes: ["Cham", "Shael", "Um"],
    level: 67,
    ttypes: ["Swords", "Claws", "Daggers"],
    version: '2.4',
  },
  {
    title: "Pattern",
    runes: ["Tal", "Ort", "Thul"],
    level: 23,
    ttypes: ["Claws"],
    tinfos: "(Assassin)",
    version: '2.4',
  },
  {
    title: "Unbending Will",
    runes: ["Fal", "Io", "Ith", "Eld", "El", "Hel"],
    level: 41,
    ttypes: ["Swords"],
    version: '2.4',
  },
  {
    title: "Wisdom",
    runes: ["Pul", "Ith", "Eld"],
    level: 45,
    ttypes: ["Helms"],
    version: '2.4',
  },
  {
    title: "Obsession",
    runes: ["Zod", "Ist", "Lem", "Lum", "Io", "Nef"],
    level: 69,
    ttypes: ["Staves"],
    version: '2.4',
  },
  {
    title: "Flickering Flame",
    runes: ["Nef", "Pul", "Vex"],
    level: 55,
    ttypes: ["Helms"],
    version: '2.4',
  },
  {
    title: "Mist",
    runes: ["Cham", "Shael", "Gul", "Thul", "Ith"],
    level: 67,
    ttypes: ["Missile Weapons"],
    version: '2.4',
  },
  {
    title: "Bulwark",
    runes: ["Shael", "Io", "Sol"],
    level: 35,
    ttypes: ["Helms"],
    ladder: true,
    version: '2.6',
  },
  {
    title: "Cure",
    runes: ["Shael", "Io", "Tal"],
    level: 35,
    ttypes: ["Helms"],
    ladder: true,
    version: '2.6',
  },
  {
    title: "Ground",
    runes: ["Shael", "Io", "Ort"],
    level: 35,
    ttypes: ["Helms"],
    ladder: true,
    version: '2.6',
  },
  {
    title: "Hearth",
    runes: ["Shael", "Io", "Thul"],
    level: 35,
    ttypes: ["Helms"],
    ladder: true,
    version: '2.6',
  },
  {
    title: "Temper",
    runes: ["Shael", "Io", "Ral"],
    level: 35,
    ttypes: ["Helms"],
    ladder: true,
    version: '2.6',
  },
  {
    title: "Hustle",
    runes: ["Shael", "Ko", "Eld"],
    level: 39,
    ttypes: ["Weapons", "Body Armors"],
    ladder: true,
    version: '2.6',
  },
  {
    title: "Mosaic",
    runes: ["Mal", "Gul", "Amn"],
    level: 53,
    ttypes: ["Claws"],
    tinfos: "(Assassin)",
    ladder: true,
    version: '2.6',
  },
  {
    title: "Metamorphosis",
    runes: ["Io", "Cham", "Fal"],
    level: 67,
    ttypes: ["Helms"],
    ladder: true,
    tinfos: "(Druid)",
    version: '2.6',
  },
]

const rwDescriptions = {
  "Ancient's Pledge": `
    +50% Enhanced Defense
    Cold Resist +43%
    Fire Resist +48%
    Lightning Resist +48%
    Poison Resist +48%
    10% Damage Goes To Mana
    `,

  Black: `
    +120% Enhanced Damage
    40% Chance Of Crushing Blow
    +200 To Attack Rating
    Adds 3-14 Cold Damage - Cold Duration 3 Seconds
    +10 To Vitality
    15% Increased Attack Speed
    Knockback
    Magic Damage Reduced By 2
    Level 4 Corpse Explosion (12 Charges)
    `,

  Fury: `
    +209% Enhanced Damage
    40% Increased Attack Speed
    Prevent Monster Heal
    66% Chance Of Open Wounds
    33% Deadly Strike
    Ignore Target's Defense
    -25% Target Defense
    20% Bonus To Attack Rating
    6% Life Stolen Per Hit
    +5 To Frenzy (Barbarian Only)
    `,

  "Holy Thunder": `
    +60% Enhanced Damage
    -25% Target Defense
    Adds 5-30 Fire Damage
    Adds 21-110 Lightning Damage
    +75 Poison Damage Over 5 Seconds
    +10 To Maximum Damage
    Lightning Resistance +60%
    +5 To Maximum Lightning Resistance
    +3 To Holy Shock (Paladin Only)
    Level 7 Chain Lightning (60 Charges)
    `,

  Honor: `
    +160% Enhanced Damage
    +9 To Minimum Damage
    +9 To Maximum Damage
    25% Deadly Strike
    +250 To Attack Rating
    +1 to All Skills
    7% Life Stolen Per Hit
    Replenish Life +10
    +10 To Strength
    +1 To Light Radius
    +2 To Mana After Each Kill
    `,

  "King's Grace": `
    +100% Enhanced Damage
    +100% Damage To Demons
    +50% Damage To Undead
    Adds 5-30 Fire Damage
    Adds 3-14 Cold Damage - 3 Second Duration
    +150 To Attack Rating
    +100 To Attack Rating Against Demons
    +100 To Attack Rating Against Undead
    7% Life Stolen Per Hit
    `,

  Leaf: `
    Adds 5-30 Fire Damage
    +3 To Fire Skills
    +3 To Fire Bolt (Sorceress Only)
    +3 To Inferno (Sorceress Only)
    +3 To Warmth (Sorceress Only)
    +2 To Mana After Each Kill
    + (2 Per Character Level) +2-198 To Defense (Based On Character Level)
    Cold Resist +33%
    `,

  Lionheart: `
    +20% Enhanced Damage
    Requirements -15%
    +25 To Strength
    +10 To Energy
    +20 To Vitality
    +15 To Dexterity
    +50 To Life
    All Resistances +30
    `,

  Lore: `
    +1 To All Skill Levels
    +10 To Energy
    +2 To Mana After Each Kill
    Lightning Resist +30%
    Damage Reduced By 7
    +2 To Light Radius
    `,

  Malice: `
    +33% Enhanced Damage
    +9 To Maximum Damage
    100% Chance Of Open Wounds
    -25% Target Defense
    -100 To Monster Defense Per Hit
    Prevent Monster Heal
    +50 To Attack Rating
    Drain Life -5
    `,

  Melody: `
    +50% Enhanced Damage
    +300% Damage To Undead
    +3 To Bow and Crossbow Skills (Amazon Only)
    +3 To Critical Strike (Amazon Only)
    +3 To Dodge (Amazon Only)
    +3 To Slow Missiles (Amazon Only)
    20% Increased Attack Speed
    +10 To Dexterity
    Knockback
    `,

  Memory: `
    +3 to Sorceress Skill Levels
    33% Faster Cast Rate
    Increase Maximum Mana 20%
    +3 Energy Shield (Sorceress Only)
    +2 Static Field (Sorceress Only)
    +10 To Energy
    +10 To Vitality
    +9 To Minimum Damage
    -25% Target Defense
    Magic Damage Reduced By 7
    +50% Enhanced Defense
    `,

  Nadir: `
    +50% Enhanced Defense
    +10 Defense
    +30 Defense vs. Missile
    Level 13 Cloak of Shadows (9 Charges)
    +2 To Mana After Each Kill
    +5 To Strength
    -33% Extra Gold From Monsters
    -3 To Light Radius
    `,

  Radiance: `
    +75% Enhanced Defense
    +30 Defense Vs. Missile
    +10 To Energy
    +10 To Vitality
    15% Damage Goes To Mana
    Magic Damage Reduced By 3
    +33 To Mana
    Damage Reduced By 7
    +5 To Light Radius
    `,

  Rhyme: `
    20% Increased Chance of Blocking
    40% Faster Block Rate
    All Resistances +25
    Regenerate Mana 15%
    Cannot Be Frozen
    50% Extra Gold From Monsters
    25% Better Chance Of Getting Magic Items
    `,

  Silence: `
    200% Enhanced Damage
    +75% Damage To Undead
    Requirements -20%
    20% Increased Attack Speed
    +50 To Attack Rating Against Undead
    +2 To All Skills
    All Resistances +75
    20% Faster Hit Recovery
    11% Mana Stolen Per Hit
    Hit Causes Monster To Flee 25%
    Hit Blinds Target +33
    +2 To Mana After Each Kill
    30% Better Chance Of Getting Magic Items
    `,

  Smoke: `
    +75% Enhanced Defense
    +280 Defense Vs. Missile
    All Resistances +50
    20% Faster Hit Recovery
    Level 6 Weaken (18 Charges)
    +10 To Energy
    -1 To Light Radius
    `,

  Stealth: `
    Magic Damage Reduced By 3
    +6 To Dexterity
    +15 To Maximum Stamina
    Poison Resist +30%
    Regenerate Mana 15%
    25% Faster Run/Walk
    25% Faster Cast Rate
    25% Faster Hit Recovery
    `,

  Steel: `
    20% Enhanced Damage
    +3 To Minimum Damage
    +3 To Maximum Damage
    +50 To Attack Rating
    50% Chance Of Open Wounds
    25% Increased Attack Speed
    +2 To Mana After Each Kill
    +1 To Light Radius
    `,

  Strength: `
    35% Enhanced Damage
    25% Chance Of Crushing Blow
    7% Life Stolen Per Hit
    +2 To Mana After Each Kill
    +20 To Strength
    +10 To Vitality
    `,

  Venom: `
    Hit Causes Monster To Flee 25%
    Prevent Monster Heal
    Ignore Target's Defense
    7% Mana Stolen Per Hit
    Level 15 Poison Explosion (27 Charges)
    Level 13 Poison Nova (11 Charges)
    +273 Poison Damage Over 6 seconds
    `,

  Wealth: `
    300% Extra Gold From Monsters
    100% Better Chance Of Getting Magic Items
    +2 To Mana After Each Kill
    +10 To Dexterity
    `,

  White: `
    Hit Causes Monster To Flee 25%
    +10 To Vitality
    +3 To Poison And Bone Skills (Necromancer Only)
    +3 To Bone Armor (Necromancer Only)
    +2 To Bone Spear (Necromancer Only)
    +4 To Skeleton Mastery (Necromancer Only)
    Magic Damage Reduced By 4
    20% Faster Cast Rate
    +13 To Mana
    `,

  Zephyr: `
    +33% Enhanced Damage
    +66 To Attack Rating
    Adds 1-50 Lightning Damage
    -25% Target Defense
    +25 Defense
    25% Faster Run/Walk
    25% Increased Attack Speed
    7% Chance To Cast Level 1 Twister When Struck
    `,

  Beast: `
    Level 9 Fanaticism Aura When Equipped
    +40% Increased Attack Speed
    +240-270% Enhanced Damage (varies)
    20% Chance of Crushing Blow
    25% Chance of Open Wounds
    +3 To Werebear
    +3 To Lycanthropy
    Prevent Monster Heal
    +25-40 To Strength (varies)
    +10 To Energy
    +2 To Mana After Each Kill
    Level 13 Summon Grizzly (5 Charges)
    `,

  Bramble: `
    Level 15-21 Thorns Aura When Equipped (varies)
    +50% Faster Hit Recovery
    +25-50% To Poison Skill Damage (varies)
    +300 Defense
    Increase Maximum Mana 5%
    Regenerate Mana 15%
    +5% To Maximum Cold Resist
    Fire Resist +30%
    Poison Resist +100%
    +13 Life After Each Kill
    Level 13 Spirit of Barbs (33 Charges)
    `,

  "Breath of the Dying": `
    50% Chance To Cast Level 20 Poison Nova When You Kill An Enemy
    Indestructible
    +60% Increased Attack Speed
    +350-400% Enhanced Damage (varies)
    +200% Damage To Undead
    -25% Target Defense
    +50 To Attack Rating
    +50 To Attack Rating Against Undead
    7% Mana Stolen Per Hit
    12-15% Life Stolen Per Hit (varies)
    Prevent Monster Heal
  <U>+30 To All Attributes</U>
    +1 To Light Radius
    Requirements -20%
    `,

  "Call to Arms": `
    +1 To All Skills
    +40% Increased Attack Speed
    +250-290% Enhanced Damage (varies)
    Adds 5-30 Fire Damage
    7% Life Stolen Per Hit
    +2-6 To Battle Command (varies)*
    +1-6 To Battle Orders (varies)*
    +1-4 To Battle Cry (varies)*
    Prevent Monster Heal
    Replenish Life +12
    30% Better Chance of Getting Magic Items
    `,

  Chaos: `
    9% Chance To Cast Level 11 Frozen Orb On Striking
    11% Chance To Cast Level 9 Charged Bolt On Striking
    +35% Increased Attack Speed
    +290-340% Enhanced Damage (varies)
    Adds 216-471 Magic Damage
    25% Chance of Open Wounds
    +1 To Whirlwind
    +10 To Strength
    +15 Life After Each Demon Kill
    `,

  "Chains of Honor": `
    +2 To All Skills
    +200% Damage To Demons
    +100% Damage To Undead
    8% Life Stolen Per Hit
    +70% Enhanced Defense
    +20 To Strength
    Replenish Life +7
    All Resistances +65
    Damage Reduced By 8%
    25% Better Chance of Getting Magic Items
    `,

  "Crescent Moon": `
    10% Chance To Cast Level 17 Chain Lightning On Striking
    7% Chance To Cast Level 13 Static Field On Striking
    +20% Increased Attack Speed
    +180-220% Enhanced Damage (varies)
    Ignore Target's Defense
    -35% To Enemy Lightning Resistance
    25% Chance of Open Wounds
    +9-11 Magic Absorb (varies)
    +2 To Mana After Each Kill
    Level 18 Summon Spirit Wolf (30 Charges)
    `,

  Delirium: `
    1% Chance To Cast Level 50 Delirium* (morph) When Struck
    6% Chance To Cast Level 14 Mind Blast When Struck
    14% Chance To Cast Level 13 Terror When Struck
    11% Chance To Cast Level 18 Confuse On Striking
    +2 To All Skills
    +261 Defense
    +10 To Vitality
    50% Extra Gold From Monsters
    25% Better Chance of Getting Magic Items
    Level 17 Attract (60 Charges)
    `,

  Doom: `
    5% Chance To Cast Level 18 Volcano On Striking
    Level 12 Holy Freeze Aura When Equipped
    +2 To All Skills
    +45% Increased Attack Speed
    +330-370% Enhanced Damage (varies)
    -(40-60)% To Enemy Cold Resistance (varies)
    20% Deadly Strike
    25% Chance of Open Wounds
    Prevent Monster Heal
    Freezes Target +3
    Requirements -20%
    `,

  Duress: `
    +40% Faster Hit Recovery
    +10-20% Enhanced Damage (varies)
    Adds 37-133 Cold Damage 2 sec. Duration (Normal)
    15% Chance of Crushing Blow
    33% Chance of Open Wounds
    +150-200% Enhanced Defense (varies)
    -20% Slower Stamina Drain
    Cold Resist +45%
    Lightning Resist +15%
    Fire Resist +15%
    Poison Resist +15%
    `,

  Enigma: `
    +2 To All Skills
    +45% Faster Run/Walk
    +1 To Teleport
    +750-775 Defense (varies)
    + (0.75 Per Character Level) +0-74 To Strength (Based On Character Level)
    Increase Maximum Life 5%
    Damage Reduced By 8%
    +14 Life After Each Kill
    15% Damage Taken Goes To Mana
    + (1 Per Character Level) +1-99% Better Chance of Getting Magic Items (Based On Character Level)
    `,

  Eternity: `
    Indestructible
    +260-310% Enhanced Damage (varies)
    +9 To Minimum Damage
    7% Life Stolen Per Hit
    20% Chance of Crushing Blow
    Hit Blinds Target
    Slows Target By 33%
    Regenerate Mana 16%
    Replenish Life +16
    Cannot Be Frozen
    30% Better Chance Of Getting Magic Items
    Level 8 Revive (88 Charges)
    `,

  Exile: `
    15% Chance To Cast Level 5 Life Tap On Striking
    Level 13-16 Defiance Aura When Equipped (varies)
    +2 To Offensive Auras (Paladin Only)
    +30% Faster Block Rate
    Freezes Target
    +220-260% Enhanced Defense (varies)
    Replenish Life +7
    +5% To Maximum Cold Resist
    +5% To Maximum Fire Resist
    25% Better Chance Of Getting Magic Items
    Repairs 1 Durability in 4 Seconds
    `,

  Famine: `
    +30% Increased Attack Speed
    +320-370% Enhanced Damage (varies)
    Ignore Target's Defense
    Adds 180-200 Magic Damage
    Adds 50-200 Fire Damage
    Adds 51-250 Lightning Damage
    Adds 50-200 Cold Damage
    12% Life Stolen Per Hit
    Prevent Monster Heal
    +10 To Strength
    `,

  Gloom: `
    15% Chance To Cast Level 3 Dim Vision When Struck
    +10% Faster Hit Recovery
    +200-260% Enhanced Defense (varies)
    +10 To Strength
    All Resistances +45
    Half Freeze Duration
    5% Damage Taken Goes To Mana
    -3 To Light Radius
    `,

  "Hand of Justice": `
    100% Chance To Cast Level 36 Blaze When You Level-Up
    100% Chance To Cast Level 48 Meteor When You Die
    Level 16 Holy Fire Aura When Equipped
    +33% Increased Attack Speed
    +280-330% Enhanced Damage (varies)
    Ignore Target's Defense
    7% Life Stolen Per Hit
    -20% To Enemy Fire Resistance
    20% Deadly Strike
    Hit Blinds Target
    Freezes Target +3
    `,

  "Heart of the Oak": `
    +3 To All Skills
    +40% Faster Cast Rate
    +75% Damage To Demons
    +100 To Attack Rating Against Demons
    Adds 3-14 Cold Damage, 3 sec. Duration (Normal)
    7% Mana Stolen Per Hit
    +10 To Dexterity
    Replenish Life +20
    Increase Maximum Mana 15%
    All Resistances +30-40 (varies)
    Level 4 Oak Sage (25 Charges)
    Level 14 Raven (60 Charges)
    `,

  Kingslayer: `
    +30% Increased Attack Speed
    +230-270% Enhanced Damage (varies)
    -25% Target Defense
    20% Bonus To Attack Rating
    33% Chance of Crushing Blow
    50% Chance of Open Wounds
    +1 To Vengeance
    Prevent Monster Heal
    +10 To Strength
    40% Extra Gold From Monsters
    `,

  Passion: `
    +25% Increased Attack Speed
    +160-210% Enhanced Damage (varies)
    50-80% Bonus To Attack Rating (varies)
    +75% Damage To Undead
    +50 To Attack Rating Against Undead
    Adds 1-50 Lightning Damage
    +1 To Berserk
    +1 To Zeal
    Hit Blinds Target +10
    Hit Causes Monster To Flee 25%
    75% Extra Gold From Monsters
    Level 3 Heart of Wolverine (12 Charges)
    `,

  Prudence: `
    +25% Faster Hit Recovery
    +140-170% Enhanced Defense (varies)
    All Resistances +25-35 (varies)
    Damage Reduced by 3
    Magic Damage Reduced by 17
    +2 To Mana After Each Kill
    +1 To Light Radius
    Repairs Durability 1 In 4 Seconds
    `,

  Sanctuary: `
    +20% Faster Hit Recovery
    +20% Faster Block Rate
    20% Increased Chance of Blocking
    +130-160% Enhanced Defense (varies)
    +250 Defense vs. Missile
    +20 To Dexterity
    All Resistances +50-70 (varies)
    Magic Damage Reduced By 7
    Level 12 Slow Missiles (60 Charges)
    `,

  Splendor: `
    +1 To All Skills
    +10% Faster Cast Rate
    +20% Faster Block Rate
    +60-100% Enhanced Defense (varies)
    +10 To Energy
    Regenerate Mana 15%
    50% Extra Gold From Monsters
    20% Better Chance of Getting Magic Items
    +3 To Light Radius
    `,

  Stone: `
    +60% Faster Hit Recovery
    +250-290% Enhanced Defense (varies)
    +300 Defense Vs. Missile
    +16 To Strength
    +16 To Vitality
    +10 To Energy
    All Resistances +15
    Level 16 Molten Boulder (80 Charges)
    Level 16 Clay Golem (16 Charges)
    `,

  Wind: `
    10% Chance To Cast Level 9 Tornado On Striking
    +20% Faster Run/Walk
    +40% Increased Attack Speed
    +15% Faster Hit Recovery
    +120-160% Enhanced Damage (varies)
    -50% Target Defense
    +50 To Attack Rating
    Hit Blinds Target
    +1 To Light Radius
    Level 13 Twister (127 Charges)
    `,

  Brand: `
    35% Chance To Cast Level 14 Amplify Damage When Struck
    100% Chance To Cast Level 18 Bone Spear On Striking
    +260-340% Enhanced Damage (varies)
    Ignore Target's Defense
    20% Bonus to Attack Rating
    +280-330% Damage To Demons (varies)
  
    20% Deadly Strike
    Prevent Monster Heal
    Knockback
    Fires Explosive Arrows or Bolts (15)
    `,

  Death: `
    100% Chance To Cast Level 44 Chain Lightning When You Die
    25% Chance To Cast Level 18 Glacial Spike On Attack
    Indestructible
    +300-385% Enhanced Damage (varies)*
    20% Bonus To Attack Rating
    +50 To Attack Rating
    Adds 1-50 Lightning Damage
    7% Mana Stolen Per Hit
    50% Chance of Crushing Blow
    +(0.5 per Character Level) 0.5-49.5% Deadly Strike (Based on Character Level)
    +1 To Light Radius
    Level 22 Blood Golem  (15 Charges)
    Requirements -20%
    `,

  Destruction: `
    23% Chance To Cast Level 12 Volcano On Striking
    5% Chance To Cast Level 23 Molten Boulder On Striking
    100% Chance To Cast level 45 Meteor When You Die
    15% Chance To Cast Level 22 Nova On Attack
    +350% Enhanced Damage
    Ignore Target's Defense
    Adds 100-180 Magic Damage
    7% Mana Stolen Per Hit
    20% Chance Of Crushing Blow
    20% Deadly Strike
    Prevent Monster Heal
    +10 To Dexterity
    `,

  Dragon: `
    20% Chance to Cast Level 18 Venom When Struck
    12% Chance To Cast Level 15 Hydra On Striking
    Level 14 Holy Fire Aura When Equipped
    +360 Defense
    +230 Defense Vs. Missile
    +3-5 To All Attributes (varies)
    +0.375-37.125 To Strength (Based on Character Level)
    Increase Maximum Mana 5% (Armor Only)
    +50 To Mana (Shields Only)
    +5% To Maximum Lightning Resist
    Damage Reduced by 7
    `,

  Dream: `
    10% Chance To Cast Level 15 Confuse When Struck
    Level 15 Holy Shock Aura When Equipped
    +20-30% Faster Hit Recovery (varies)
    +30% Enhanced Defense
    +150-220 Defense (varies)
    +10 To Vitality
    Increase Maximum Life 5% (Helms Only)
    +50 To Life (Shields Only)
    +0.625-61.875 To Mana (Based On Character Level)
    All Resistances +5-20 (varies)
    12-25% Better Chance of Getting Magic Items (varies)
    `,

  Edge: `
    Level 15 Thorns Aura When Equipped
    +35% Increased Attack Speed
    +320-380% Damage To Demons (varies)
    +280% Damage To Undead
    +75 Poison Damage Over 5 Seconds
    7% Life Stolen Per Hit
    Prevent Monster Heal
    +5-10 To All Attributes (varies)
    +2 To Mana After Each Kill
    Reduces All Vendor Prices 15%!!!
    `,

  Faith: `
    Level 12-15 Fanaticism Aura When Equipped (varies)
    +1-2 To All Skills (varies)
    +330% Enhanced Damage
    Ignore Target's Defense
    300% Bonus To Attack Rating
    +75% Damage To Undead
    +50 To Attack Rating Against Undead
    +120 Fire Damage
    All Resistances +15
    10% Reanimate As: Returned
    75% Extra Gold From Monsters
    `,

  Fortitude: `
    #### Weapons
    20% Chance To Cast Level 15 Chilling Armor when Struck
    +25% Faster Cast Rate
    +300% Enhanced Damage
    +9 To Minimum Damage
    +50 To Attack Rating
    20% Deadly Strike
    Hit Causes Monster To Flee 25%
    +200% Enhanced Defense
    +X To Life (Based on Character Level)*
    All Resistances +25-30 (varies)
    12% Damage Taken Goes To Mana
    +1 To Light Radius
  
    #### Body Armor
    20% Chance To Cast Level 15 Chilling Armor when Struck
    +25% Faster Cast Rate
    +300% Enhanced Damage
    +200% Enhanced Defense
    +15 Defense
    +X To Life (Based on Character Level)*
    Replenish Life +7
    +5% To Maximum Lightning Resist
    All Resistances +25-30 (varies)
    Damage Reduced By 7
    12% Damage Taken Goes To Mana
    +1 To Light Radius
    `,

  Grief: `
    35% Chance To Cast Level 15 Venom On Striking
    +30-40% Increased Attack Speed (varies)
    Damage +340-400 (varies)
    Ignore Target's Defense
    -25% Target Defense
    +(1.875 per character level) 1.875-185.625% Damage To Demons (Based on Character Level) 
    Adds 5-30 Fire Damage
    -20-25% To Enemy Poison Resistance (varies)
    20% Deadly Strike
    Prevent Monster Heal
    +2 To Mana After Each Kill
    +10-15 Life After Each Kill (varies)
    `,

  Harmony: `
    Level 10 Vigor Aura When Equipped
    +200-275% Enhanced Damage (varies)
    +9 To Minimum Damage
    +9 To Maximum Damage
    Adds 55-160 Lightning Damage
    Adds 55-160 Fire Damage
    Adds 55-160 Cold Damage
    +2-6 To Valkyrie (varies)
    +10 To Dexterity
    Regenerate Mana 20%
    +2 To Mana After Each Kill
    +2 To Light Radius
    Level 20 Revive (25 Charges)
    `,

  Ice: `
    100% Chance To Cast Level 40 Blizzard When You Level-up
    25% Chance To Cast Level 22 Frost Nova On Striking
    Level 18 Holy Freeze Aura When Equipped
    +20% Increased Attack Speed
    +140-210% Enhanced Damage (varies)
    Ignore Target's Defense
    +25-30% To Cold Skill Damage (varies)
    -20% To Enemy Cold Resistance
    7% Life Stolen Per Hit
    20% Deadly Strike
    3.125-309.375 Extra Gold From Monsters (Based on Character Level)
    `,

  Infinity: `
    50% Chance To Cast Level 20 Chain Lightning When You Kill An Enemy
    Level 12 Conviction Aura When Equipped
    +35% Faster Run/Walk
    +255-325% Enhanced Damage (varies)
    -(45-55)% To Enemy Lightning Resistance (varies)
    40% Chance of Crushing Blow
    Prevent Monster Heal
    0.5-49.5 To Vitality (Based on Character Level)
    30% Better Chance of Getting Magic Items
    Level 21 Cyclone Armor (30 Charges)
    `,

  Insight: `
    Level 12-17 Meditation Aura When Equipped (varies)
    +35% Faster Cast Rate
    +200-260% Enhanced Damage (varies)
    +9 To Minimum Damage
    180-250% Bonus to Attack Rating (varies)
    Adds 5-30 Fire Damage
    +75 Poison Damage Over 5 Seconds
    +1-6 To Critical Strike (varies)
    +5 To All Attributes
    +2 To Mana After Each Kill
    23% Better Chance of Getting Magic Items
    `,

  "Last Wish": `
    6% Chance To Cast Level 11 Fade When Struck
    10% Chance To Cast Level 18 Life Tap On Striking
    20% Chance To Cast Level 20 Charged Bolt On Attack
    Level 17 Might Aura When Equipped
    +330-375% Enhanced Damage (varies)
    Ignore Target's Defense
    60-70% Chance of Crushing Blow (varies)
    Prevent Monster Heal
    Hit Blinds Target
    +(0.5 per character level) 0.5-49.5% Chance of Getting Magic Items (Based on Character Level) 
    `,

  Lawbringer: `
    20% Chance To Cast Level 15 Decrepify On Striking
    Level 16-18 Sanctuary Aura When Equipped (varies)
    -50% Target Defense
    Adds 150-210 Fire Damage
    Adds 130-180 Cold Damage
    7% Life Stolen Per Hit
    Slain Monsters Rest In Peace
    +200-250 Defense Vs. Missile (varies)
    +10 To Dexterity
    75% Extra Gold From Monsters
    `,

  Oath: `
    30% Chance To Cast Level 20 Bone Spirit On Striking
    Indestructible
    +50% Increased Attack Speed
    +210-340% Enhanced Damage (varies)
    +75% Damage To Demons
    +100 To Attack Rating Against Demons
    Prevent Monster Heal
    +10 To Energy
    +10-15 Magic Absorb (varies)
    Level 16 Heart Of Wolverine (20 Charges)
    Level 17 Iron Golem (14 Charges)
    `,

  Obedience: `
    30% Chance To Cast Level 21 Enchant When You Kill An Enemy
    40% Faster Hit Recovery
    +370% Enhanced Damage
    -25% Target Defense
    Adds 3-14 Cold Damage 3 Second Duration (Normal)
    -25% To Enemy Fire Resistance
    40% Chance of Crushing Blow
    +200-300 Defense (varies)
    +10 To Strength
    +10 To Dexterity
    All Resistances +20-30 (varies)
    Requirements -20%
    `,

  Phoenix: `
    #### Weapons
    100% Chance To Cast level 40 Blaze When You Level-up
    40% Chance To Cast Level 22 Firestorm On Striking
    Level 10-15 Redemption Aura When Equipped (varies)
    +350-400% Enhanced Damage (varies)
    Ignores Target's Defense
    14% Mana Stolen Per Hit
    -28% To Enemy Fire Resistance
    20% Deadly Strike
    +350-400 Defense Vs. Missile (varies)
    +15-21 Fire Absorb (varies)
  
    #### Shields
    100% Chance To Cast level 40 Blaze When You Level-up
    40% Chance To Cast Level 22 Firestorm On Striking
    Level 10-15 Redemption Aura When Equipped (varies)
    +350-400 Defense Vs. Missile (varies)
    +350-400% Enhanced Damage (varies)
    -28% To Enemy Fire Resistance
    +50 To Life
    +5% To Maximum Lightning Resist
    +10% To Maximum Fire Resist
    +15-21 Fire Absorb (varies)
    `,

  Pride: `
    25% Chance To Cast Level 17 Fire Wall When Struck
    Level 16-20 Concentration Aura When Equipped (varies)
    260-300% Bonus To Attack Rating (varies)
    +1-99% Damage To Demons (Based on Character Level)
    Adds 50-280 Lightning Damage
    20% Deadly Strike
    Hit Blinds Target
    Freezes Target +3
    +10 To Vitality
    Replenish Life +8
    1.875-185.625% Extra Gold From Monsters (Based on Character Level)
    `,

  Rift: `
    20% Chance To Cast Level 16 Tornado On Striking
    16% Chance To Cast Level 21 Frozen Orb On Attack
    20% Bonus To Attack Rating
    Adds 160-250 Magic Damage
    Adds 60-180 Fire Damage
    +5-10 To All Stats (varies)
    +10 To Dexterity
    38% Damage Taken Goes To Mana
    75% Extra Gold From Monsters
    Level 15 Iron Maiden (40 Charges)
    Requirements -20%
    `,

  Spirit: `
    #### Swords
    +2 To All Skills
    +25-35% Faster Cast Rate (varies)
    +55% Faster Hit Recovery
    Adds 1-50 Lightning Damage
    Adds 3-14 Cold Damage 3 Second Duration (Normal)
    +75 Poison Damage Over 5 Seconds
    7% Life Stolen Per Hit
    +250 Defense Vs. Missile
    +22 To Vitality
    +89-112 To Mana (varies)
    +3-8 Magic Absorb (varies)
  
    #### Shields
    +2 To All Skills
    +25-35% Faster Cast Rate (varies)
    +55% Faster Hit Recovery
    +250 Defense Vs. Missile
    +22 To Vitality
    +89-112 To Mana (varies)
    Cold Resist +35%
    Lightning Resist +35%
    Poison Resist +35%
    +3-8 Magic Absorb (varies)
    Attacker Takes Damage of 14
    `,

  "Voice of Reason": `
    15% Chance To Cast Level 13 Frozen Orb On Striking
    18% Chance To Cast Level 20 Ice Blast On Striking
    +50 To Attack Rating
    +220-350% Damage To Demons
    +355-375% Damage To Undead (varies)
    +50 To Attack Rating Against Undead
    Adds 100-220 Cold Damage
    -24% To Enemy Cold Resistance
    +10 To Dexterity
    Cannot Be Frozen
    75% Extra Gold From Monsters
    +1 To Light Radius
    `,

  Wrath: `
    30% Chance To Cast Level 1 Decrepify On Striking
    5% Chance To Cast Level 10 Life Tap On Striking
    +375% Damage To Demons
    +100 To Attack Rating Against Demons
    +250-300% Damage To Undead (varies)
    Adds 85-120 Magic Damage
    Adds 41-240 Lightning Damage
    20% Chance of Crushing Blow
    Prevent Monster Heal
    +10 To Energy
    Cannot Be Frozen
    `,

  Bone: `
    15% Chance To Cast level 10 Bone Armor When Struck
    15% Chance To Cast level 10 Bone Spear On Striking
    +2 To Necromancer Skill Levels
    +100-150 To Mana (varies)
    All Resistances +30
    Damage Reduced By 7
    `,

  Enlightenment: `
    5% Chance To Cast Level 15 Blaze When Struck
    5% Chance To Cast level 15 Fire Ball On Striking
    +2 To Sorceress Skill Levels
    +1 To Warmth
    +30% Enhanced Defense
    Fire Resist +30%
    Damage Reduced By 7
    `,

  Myth: `
    3% Chance To Cast Level 1 Howl When Struck
    10% Chance To Cast Level 1 Taunt On Striking
    +2 To Barbarian Skill Levels
    +30 Defense Vs. Missile
    Replenish Life +10
    Attacker Takes Damage of 14
    Requirements -15%
    `,

  Peace: `
    4% Chance To Cast Level 5 Slow Missiles When Struck
    2% Chance To Cast level 15 Valkyrie On Striking
    +2 To Amazon Skill Levels
    +20% Faster Hit Recovery
    +2 To Critical Strike
    Cold Resist +30%
    Attacker Takes Damage of 14
    `,

  Principle: `
    100% Chance To Cast Level 5 Holy Bolt On Striking
    +2 To Paladin Skill Levels
    15% Slower Stamina Drain
    +5% To Maximum Poison Resist
    Fire Resist +30%
    `,

  Rain: `
    5% Chance To Cast Level 15 Cyclone Armor When Struck
    5% Chance To Cast Level 15 Twister On Striking
    +2 To Druid Skills
    +100-150 To Mana (varies)
    Lightning Resist +30%
    Magic Damage Reduced By 7
    15% Damage Taken Goes to Mana
    `,

  Treachery: `
    5% Chance To Cast Level 15 Fade When Struck
    25% Chance To Cast level 15 Venom On Striking
    +2 To Assassin Skills
    +45% Increased Attack Speed
    +20% Faster Hit Recovery
    Cold Resist +30%
    50% Extra Gold From Monsters
    `,

  /* Patch 2.4 - alpha sort maybe later, keep here for now easier to find */
  Plague: `
    20% Chance to Cast level 12 Lower Resist when struck
    25% Chance to Cast level 15 Poison Nova on striking
    Level 13-17 Cleansing Aura When Equipped (varies)
    +1-2 All Skills
    +20% Increased Attack Speed
    +220-320% Enhanced Damage (varies)
    -23% To Enemy Poison Resistance
    0.3% (0-29.7) Deadly Strike (Based on Character Level)
    +25% Chance of Open Wounds
    Freezes Target +3
    `,

  Pattern: `
    +30% Faster Block Rate
    +40-80% Enhanced Damage (varies)
    10% Bonus to Attack Rating
    Adds 17-62 Fire Damage
    Adds 1-50 Lightning Damage
    Adds 3-14 Cold Damage
    +75 Poison Damage Over 5 Seconds
    +6 to Strength
    +6 to Dexterity
    All Resistances +15
    `,

  "Unbending Will": `
    18% Chance to cast Level 18 Taunt on striking
    +3 To Combat Skills (Barbarian Only)
    +20-30% Increased Attack Speed (varies)
    +300-350% Enhanced Damage (varies)
    +9 To Maximum Damage
    +50 To Attack Rating
    +75% Damage to Undead
    +50 Attack Rating Against Undead
    8-10% Life Stolen Per Hit (varies)
    Prevent Monster Heal
    +10 To Strength
    +10 To Vitality
    Damage Reduced By 8
    +1 Light Radius
    Requirements -20%
    `,

  Wisdom: `
    +33% Piercing Attack
    +15-25% Bonus to Attack Rating (varies)
    4-8% Mana Stolen Per Hit (varies)
    +30% Enhanced Defense
    +10 Energy
    15% Slower Stamina Drain
    Cannot Be Frozen
    +5 Mana After Each Kill
    15% Damage Taken Goes to Mana
    `,

  Obsession: `
    Indestructible
    24% Chance to cast level 10 Weaken when struck
    +4 To All Skills
    +65% Faster Cast Rate
    +60% Faster Hit Recovery
    Knockback
    +10 To Vitality
    +10 To Energy
    Increase Maximum Life 15-25% (varies)
    Regenerate Mana 15-30% (varies)
    All Resistances +60-70 (varies)
    75% Extra Gold from Monsters
    30% Better Chance of Getting Magic Items
    `,

  "Flickering Flame": `
    Level 4-8 Resist Fire Aura When Equipped (varies)
    +3 To Fire Skills
    -10-15% to Enemy Fire Resistance (varies)
    +30% Enhanced Defense
    +30 Defense Vs. Missile
    +50-75 To Mana (varies)
    Half Freeze Duration
    +5% To Maximum Fire Resist
    Poison Length Reduced by 50%
    `,

  Mist: `
    Level 8-12 Concentration Aura When Equipped (varies)
    +3 To All Skills
    20% Increased Attack Speed
    +100% Piercing Attack
    +325-375% Enhanced Damage (varies)
    +9 To Maximum Damage
    20% Bonus to Attack Rating
    Adds 3-14 Cold Damage
    Freeze Target +3
    +24 Vitality
    All Resistances +40
    `,

  /* Patch 2.6 */
  Bulwark: `
    +20% Faster Hit Recovery
    +4-6% Life stolen per hit
    +75-100% Enhanced Defense
    +10 to Vitality
    Increase Maximum Life 5%
    Replenish Life +30
    Damage Reduced by 7
    Physical Damage Received Reduced by 10-15%
    `,

  Cure: `
    Level 1 Cleansing Aura when Equipped
    +20% Faster Hit Recovery
    +75-100% Enhanced Defense
    +10 to Vitality
    Increase Maximum Life 5%
    Poison Resist +40-60%
    Poison Length Reduced by 50%
    `,

  Ground: `
    +20% Faster Hit Recovery
    +75-100% Enhanced Defense
    +10 to Vitality
    Increase Maximum Life 5%
    Lightning Resist +40-60%
    Lightning Absorb +10-15%
    `,

  Hearth: `
    +20% Faster Hit Recovery
    +75-100% Enhanced Defense
    +10 to Vitality
    Increase Maximum Life 5%
    Cold Resist +40-60%
    Cold Absorb +10-15%
    Cannot be Frozen
    `,

  Temper: `
    +20% Faster Hit Recovery
    +75-100% Enhanced Defense
    +10 to Vitality
    Increase Maximum Life 5%
    Fire Resist +40-60%
    Fire Absorb +10-15%
    `,

  Hustle: `
    #### Weapons
    5% Chance to cast level 1 Burst of Speed on striking
    Level 1 Fanaticism Aura
    +30% Increased Attack Speed
    +180-200% Enhanced Damage
    +75% Damage to Undead
    +50 to Attack Rating against Undead
    +10 to Dexterity
  
    #### Body Armors
    +65% Faster Run/Walk
    +40% Increased Attack Speed
    +20% Faster Hit Recovery
    +6 to Evade
    +10 to Dexterity
    50% Slower Stamina Drain
    +All Resistances +10
    `,

  Mosaic: `
    +50% chance for finishing moves to not consume charges
    +2 to Martial Arts (Assassin only)
    +20% Increased Attack Speed
    +200-250% Enhanced Damage
    +20% Bonus to Attack Rating
    7% Life Steal
    +8-15% to Cold Skill Damage
    +8-15% to Lightning Skill Damage
    +8-15% to Fire Skill Damage
    Prevent Monster Heal
    `,

  Metamorphosis: `
    100% Chance to cast level 1 Mark of the Wolf on striking
    100% Chance to cast level 1 Mark of the Bear on striking
    +5 to Shape Shifting Skills (Druid only)
    +25% Chance of Crushing Blow
    +50-80% Enhanced Defense
    +10 to Strength
    +10 to Vitality
    All Resistances +10
    Cannot be Frozen
    `,
};

for (const rw of rws) {
  if(!rw["title"]){
    console.error(`Title is empty of ${rw}`)
  }
  rw["title"] = rw["title"] ?? null;
  if(!rw["runes"]){
    console.error(`Title is empty of ${rw}`)
  }
  rw["runes"] = rw["runes"] ?? [];
  rw["level"] = rw["level"] ?? 99;
  rw["ttypes"] = rw["ttypes"] ?? [];
  rw["ladder"] = rw["ladder"] ?? true; //not sure if correct
  rw["tinfos"] = rw["tinfos"] ?? "";
  rw["version"] = rw["version"] ?? "";
  if (!rwDescriptions[rw.title]) {
    console.log(`Description for ${rw.title} not found: ${rwDescriptions[rw.title]}`)
  }
  rw["description"] = rwDescriptions[rw.title].trim().split("\n").map(r => r.trim())
}

fs.writeFileSync("../res/runewords.json", JSON.stringify(rws, null, 2));