# Dices

> **Work in Progress**

Dices is a **turn-based dice combat prototype developed in Unreal Engine 5 using C++**.

The project focuses on gameplay programming, physics-based dice mechanics, enemy decision-making and modular gameplay systems.

![Dices roll](media/dices_roll.gif)

## Features

* Turn-based dice combat
* Physics-based dice rolling
* Dice selection and placement system
* Multiple dice types with different behaviours
* Enemy decision-making system
* Data-driven enemy strategies
* Turn and brawl management
* Drink and condition system
* Branching dialogue system
* Component-based player functionality

## Technologies

* C++
* Unreal Engine 5
* Unreal Engine C++ API
* Blueprints
* UMG
* Visual Studio
* Rider

## Gameplay

### Rules

The player faces a series of opponents in a turn-based dice game built around strategic placement.

Both players roll their dices on their side of the table, keeping the results hidden from their opponent.

### Dice Placement

Players take turns placing their dices in the center of the table by a **2 / 4 / 4 / 2 placement pattern**, making **6 opposing dice pairs**.

A coin toss determines who places first. After each Brawl, the placement order is reversed.

Because players cannot see their opponent's dices before they are placed, each decision involves predicting where the opponent may commit their stronger or weaker rolls.

![Dices placement](media/dices_placement.gif)

### Pair

Each pair compares one player die against one opponent die.

To win a pair, a player's result must be at least **2 points higher** than the opponent's result.

**Winning a Pair -> +1 Small Point**

### Brawl

Once all 6 pairs have been resolved, the player with more Small Points wins the Brawl.

**Winning a Brawl -> +1 Big Point**

After the Brawl, the placement order is reversed and another round begins.

### Fight

The first player to earn **2 Big Points** wins the Fight.

Winning the Fight ends the encounter — with the winner smashing their opponent over the head and knocking out one of their fangs.

### Rewards & Progression

Winning a Fight rewards the player with **gold coins**.

Gold can be spent on:

* **Drinks** purchased from the waiter
* **Items** offered by certain opponents

These rewards can influence future encounters and give the player additional options as they progress through the game.

### Core Gameplay Loop

**Roll Dice -> Place Dice -> Resolve Pairs -> Win Brawl -> Earn Big Point -> Win Fight -> Receive Gold -> Buy Drinks / Items -> Face Next Opponent**


## Enemy Decision System

Enemies use an `EnemyDecisionComponent` to determine which dice should be played.

The system evaluates available dice and the current state of the board before selecting an action. Different enemy behaviours can use different approaches to decision-making, including decisions made with limited information and decisions based on the known state of the board.

Scoring data used by enemy strategies can be modified using Unreal Engine Data Tables.

![Dices big](media/dices_big.gif)

## Dice System

Dices are physics-based gameplay actors.

The player can select, roll and place dice during combat. Beside standard dices there are also specialized ones with additional behaviours, for example:

* Fang earned by losing HP, that allow to tie selected pair
* Jumping Dice that change side after hitting the table
* Dice with alternative face values

Player dice functionality is managed by `PlayerDiceManagerComponent`, which handles selection, rolling, placement and resetting dice between gameplay states.

![Dices fake](media/dices_fake.gif)

## Drinks & Conditions

Drinks can temporarily modify gameplay by applying different `Condition` components to the player.

Conditions have lifetime measured in turns and are responsible for applying their gameplay effects.

These effects can include:

* Modifying dice results
* Allowing additional dice interactions
* Temporarily replacing dice with dice using different face values

![Dices reroll](media/dices_reroll.gif)

## Dialogue System

The project includes a branching dialogue system.

Dialogue content is stored using Unreal Engine Data Assets. Dialogue can contain multiple player choices which determine the next dialogue line.

The system involves:

* `DialogueData` — stores dialogue content and available choices
* `DialogueManager` — controls dialogue progression
* `DialogueWidget` — handles dialogue presentation

![Dices dialogue](media/dices_dialogue.gif)

## Technical Features

* Gameplay systems implemented primarily in C++
* Actor Component-based gameplay functionality
* Physics-based dice mechanics
* Turn and brawl state management
* Data-driven enemy decision making
* Delegates for communication between gameplay systems
* C++ and Blueprint integration
* UMG-based UI and dialogue presentation
* Reusable gameplay classes through inheritance

## Project Status

The project is currently **work in progress**.

The core gameplay systems and combat prototype are implemented, while content, presentation and balancing are still being developed.

### Planned Improvements

* Rework enemy dice rolls to use probability-based results, with dice physically rolled for presentation and rotated to the predetermined result when placed
* Gameplay and visual polish
* Additional enemy behaviours
* Additional dice, drink and item types
* UI improvements
* Gameplay balancing
* Expanded dialogue and game content
* Sound effects and music
