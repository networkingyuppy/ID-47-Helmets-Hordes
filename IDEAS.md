## Helmets & Hordes

Helmets & Hordes is an endless runner where you need to avoid enemies, dodge traps and collect coins and other treasures. You can also defeat enemies to obtain extra treasure. You can find and wear 7 helmets which give you unique powerups that let you play the game in different ways. The goal is to gather as much treasure as possible before the enemies defeat you.

We need to find the right balance of game speed, enemy variety, wave intensity and powerup functions to make this a fun game.

* Helena: The main character, a warrior who is trying to take as much loot as she can from a trapped dungeon filled with savage Orks (and maybe other creatures, too).
* HEALTH: Helga has 3 hit points, which are indicated through the character sprite.
  * Naked (no helmet, no armour) - Helga will die if she is hit.
  * Armoured (no helmet) - Helga will lose her armour if she is hit and will become Naked.
  * Armoured with Helmet (any helmet) - Helga will lose her helmet if she is hit and will become Armoured.
* Enemies:
  * Unarmed Ork: Charges at the player and carries no weapon. Can be defeated if you simply walk into it with your sword or dagger.
  * Ork Spearman (forward): Charges at the player and carries a spear pointed forwards. You need to jump over him or defeat him in some other manner.
  * Ork Spearman (upward): Charges at the player and carries a spear pointed upwards. If you try to jump over him, you'll be hurt by his spear. You can simply run into him with your sword or dagger to defeat him.
  * It would be cool to have other enemies too, like Skeletons or Slimes.
* Traps:
  * Spikes: These are laid in groups of 3 on the ground and will hurt the player if they are touched.
  * Arrows: Arrows are fired from trap pillars and must be avoided or hit with a special Helmet Ability.
  * Boulders: The Orks will sometimes drop boulders from overhead - you need to dodge them!
* Collecting treasure (coins) will give you points. You also get coins for killing enemies.
* There will be 8 Helmet Abilities (to fit 1 byte).

## ENEMY LIST (this is just a PLACEHOLDER right now)
| **SPRITE** | **SIZE** | **FRAMES** | **NAME** | **HP** | **SWIMMING** |
| ---        | ---      | ---        | ---      | ---    | ---          |
| **Trolly Fish** | 16x16 | 4 | trollyFish_16x16 | 1 or 2| 
| **Bad Fishy** | 12x12 | 4 | badFishy_16x16 | 1 |
| **Fast Bad Fishy** | 12x12 | 4 | badFishy_16x16 | 1 |
| **Jellyfish** | 16x24 | 4 | jellyFish_16x24 | 3 |
| **Eel** | 80x16 | 4 | eel_16x80 | 5 |
